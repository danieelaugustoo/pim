#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tipos.h"
#include "util.h"
#include "consolidacao.h"

#define LOG "bin/teste-P01.tmp.log"
#define LOG_P02 "bin/teste-P02.tmp.log"
#define LOG_OUTRO "bin/teste-outro.tmp.log"
#define APLICADAS "bin/teste-aplicadas.tmp.csv"
#define CONSOLIDADAS "bin/teste-consolidadas.tmp.csv"
#define RELATORIO "bin/teste-relatorio.tmp.txt"

#define CABECALHO_LOG "id_operacao;id_portaria;data_hora;tipo;id_encomenda;bloco;apartamento"

/* O estado tem centenas de KB: fica em memoria estatica, nao na pilha. */
static EstadoCentral estado1;
static EstadoCentral estado2;

/* Grava um log com as linhas dadas (a ultima deve ser NULL). */
static void gravar_log(const char *caminho, const char *linhas[])
{
    FILE *arq = fopen(caminho, "w");
    int i;

    assert(arq != NULL);
    fprintf(arq, "%s\n", CABECALHO_LOG);
    for (i = 0; linhas[i] != NULL; i++) {
        fprintf(arq, "%s\n", linhas[i]);
    }
    assert(fclose(arq) == 0);
}

/* Acrescenta uma linha ao final de um log. */
static void acrescentar_linha(const char *caminho, const char *linha)
{
    FILE *arq = fopen(caminho, "a");

    assert(arq != NULL);
    fprintf(arq, "%s\n", linha);
    assert(fclose(arq) == 0);
}

/* Procura a encomenda no consolidado. */
static const EncomendaConsolidada *achar(const EstadoCentral *e, int portaria, int encomenda)
{
    int i;

    for (i = 0; i < e->qtd_consolidadas; i++) {
        if (e->consolidadas[i].id_portaria == portaria && e->consolidadas[i].id_encomenda == encomenda) {
            return &e->consolidadas[i];
        }
    }
    return NULL;
}

/* Apaga os arquivos temporarios do teste. */
static void limpar(void)
{
    remove(LOG);
    remove(LOG_P02);
    remove(LOG_OUTRO);
    remove(APLICADAS);
    remove(CONSOLIDADAS);
    remove(RELATORIO);
}

/* Teste central: processar o mesmo log duas vezes nao duplica nada (US11). */
static void testar_mesmo_log_duas_vezes(void)
{
    const char *linhas[] = {
        "P01-000001;1;2026-10-20 09:15;REGISTRO;1;A;12",
        "P01-000002;1;2026-10-27 14:40;REGISTRO;2;A;12",
        "P01-000003;1;2026-10-21 18:30;RETIRADA;1;A;12",
        NULL};
    ResumoConsolidacao r;
    const EncomendaConsolidada *c;

    limpar();
    gravar_log(LOG, linhas);
    consolidacao_iniciar(&estado1);

    /* 1a vez: aplica as 3 operacoes */
    assert(consolidacao_processar_portaria(&estado1, 1, LOG, &r) == 1);
    assert(r.lidas == 3 && r.aplicadas == 3 && r.ja_aplicadas == 0 && r.rejeitadas == 0 && r.invalidas == 0);
    assert(estado1.qtd_aplicadas == 3);
    assert(estado1.qtd_consolidadas == 2);
    c = achar(&estado1, 1, 1);
    assert(c != NULL && c->status == STATUS_RETIRADA && strcmp(c->retirada_em, "2026-10-21 18:30") == 0);
    assert(c->bloco == 'A' && c->apartamento == 12 && strcmp(c->recebida_em, "2026-10-20 09:15") == 0);
    c = achar(&estado1, 1, 2);
    assert(c != NULL && c->status == STATUS_PENDENTE && c->retirada_em[0] == '\0');

    /* 2a vez, mesmo log: nada e duplicado nem alterado */
    assert(consolidacao_processar_portaria(&estado1, 1, LOG, &r) == 1);
    assert(r.lidas == 3 && r.aplicadas == 0 && r.ja_aplicadas == 3 && r.rejeitadas == 0);
    assert(estado1.qtd_aplicadas == 3);
    assert(estado1.qtd_consolidadas == 2);
    assert(achar(&estado1, 1, 1)->status == STATUS_RETIRADA);
    assert(achar(&estado1, 1, 2)->status == STATUS_PENDENTE);

    /* 3a vez, depois de repetir uma linha dentro do proprio log */
    acrescentar_linha(LOG, linhas[1]);
    assert(consolidacao_processar_portaria(&estado1, 1, LOG, &r) == 1);
    assert(r.lidas == 4 && r.aplicadas == 0 && r.ja_aplicadas == 4);
    assert(estado1.qtd_aplicadas == 3 && estado1.qtd_consolidadas == 2);
}

/* A idempotencia vale entre execucoes: o estado vai para arquivo e volta (reabrir a central). */
static void testar_entre_execucoes(void)
{
    ResumoConsolidacao r;

    assert(consolidacao_salvar_estado(&estado1, APLICADAS, CONSOLIDADAS) == 1);
    assert(consolidacao_carregar_estado(&estado2, APLICADAS, CONSOLIDADAS) == 1);
    assert(estado2.qtd_aplicadas == 3 && estado2.qtd_consolidadas == 2);
    assert(achar(&estado2, 1, 1)->status == STATUS_RETIRADA);
    assert(strcmp(achar(&estado2, 1, 1)->retirada_em, "2026-10-21 18:30") == 0);

    assert(consolidacao_processar_portaria(&estado2, 1, LOG, &r) == 1);
    assert(r.aplicadas == 0 && r.ja_aplicadas == 4);
    assert(estado2.qtd_aplicadas == 3 && estado2.qtd_consolidadas == 2);

    /* salvar de novo e recarregar continua igual */
    assert(consolidacao_salvar_estado(&estado2, APLICADAS, CONSOLIDADAS) == 1);
    assert(consolidacao_carregar_estado(&estado1, APLICADAS, CONSOLIDADAS) == 1);
    assert(estado1.qtd_aplicadas == 3 && estado1.qtd_consolidadas == 2);
}

/* Portarias diferentes podem ter o mesmo id de encomenda; log inexistente e ignorado. */
static void testar_duas_portarias(void)
{
    const char *linhas_p02[] = {
        "P02-000001;2;2026-10-22 10:00;REGISTRO;1;C;5",
        "P02-000002;2;2026-10-23 11:00;DEVOLUCAO;1;C;5",
        NULL};
    ResumoConsolidacao r;

    gravar_log(LOG_P02, linhas_p02);
    assert(consolidacao_processar_portaria(&estado1, 2, LOG_P02, &r) == 1);
    assert(r.aplicadas == 2);
    assert(estado1.qtd_consolidadas == 3);
    assert(achar(&estado1, 1, 1)->bloco == 'A');
    assert(achar(&estado1, 2, 1)->bloco == 'C');
    assert(achar(&estado1, 2, 1)->status == STATUS_DEVOLVIDA);
    assert(achar(&estado1, 1, 1)->status == STATUS_RETIRADA);

    assert(consolidacao_processar_portaria(&estado1, 3, "bin/nao-existe.tmp.log", &r) == 0);
    assert(r.lidas == 0 && r.aplicadas == 0);
}

/* Linhas invalidas e operacoes rejeitadas nao sao registradas como aplicadas. */
static void testar_invalidas_e_rejeitadas(void)
{
    const char *linhas_ruins[] = {
        "isto nao e uma operacao",
        "P02-000001;2;2026-10-22 10:00;REGISTRO;9;A;1",   /* log da portaria 1 com operacao da 2 */
        "P01-000004;1;2026-10-28 09:00;RETIRADA;99;A;1",  /* retirada de encomenda desconhecida */
        NULL};
    const char *linhas_ok[] = {
        "P01-000005;1;2026-10-28 08:00;REGISTRO;99;A;1",
        "P01-000004;1;2026-10-28 09:00;RETIRADA;99;A;1",  /* agora a encomenda existe */
        NULL};
    ResumoConsolidacao r;
    int antes = estado1.qtd_aplicadas;

    gravar_log(LOG_OUTRO, linhas_ruins);
    assert(consolidacao_processar_portaria(&estado1, 1, LOG_OUTRO, &r) == 1);
    assert(r.invalidas == 2 && r.lidas == 1 && r.rejeitadas == 1 && r.aplicadas == 0);
    assert(estado1.qtd_aplicadas == antes);
    assert(!consolidacao_operacao_ja_aplicada(&estado1, "P01-000004"));

    /* a operacao rejeitada pode ser aplicada depois que a que faltava chega */
    gravar_log(LOG_OUTRO, linhas_ok);
    assert(consolidacao_processar_portaria(&estado1, 1, LOG_OUTRO, &r) == 1);
    assert(r.aplicadas == 2 && r.rejeitadas == 0);
    assert(consolidacao_operacao_ja_aplicada(&estado1, "P01-000004"));
    assert(achar(&estado1, 1, 99)->status == STATUS_RETIRADA);
}

/* O efeito tambem e idempotente: uma queda entre os dois arquivos nao gera lixo. */
static void testar_efeito_idempotente(void)
{
    Operacao op;

    consolidacao_iniciar(&estado2);
    memset(&op, 0, sizeof op);
    util_copiar_texto(op.id_operacao, TAM_ID_OPERACAO, "P01-000001");
    op.id_portaria = 1;
    util_copiar_texto(op.data_hora, TAM_DATA, "2026-10-20 09:15");
    op.tipo = OP_REGISTRO;
    op.id_encomenda = 1;
    op.bloco = 'A';
    op.apartamento = 12;
    assert(consolidacao_aplicar_operacao(&estado2, &op) == CONS_APLICADA);
    assert(estado2.qtd_consolidadas == 1);

    /* simula a queda: o id aplicado se perdeu, mas a encomenda ja esta no consolidado */
    estado2.qtd_aplicadas = 0;
    assert(consolidacao_aplicar_operacao(&estado2, &op) == CONS_APLICADA);
    assert(estado2.qtd_consolidadas == 1);
    assert(estado2.qtd_aplicadas == 1);

    /* mesma encomenda com outra data: conflito, e rejeitada */
    estado2.qtd_aplicadas = 0;
    util_copiar_texto(op.data_hora, TAM_DATA, "2026-10-21 10:00");
    assert(consolidacao_aplicar_operacao(&estado2, &op) == CONS_REJEITADA);
    assert(estado2.qtd_consolidadas == 1 && estado2.qtd_aplicadas == 0);
}

/* Relatorio e arquivos criados na primeira execucao. */
static void testar_relatorio_e_primeira_execucao(void)
{
    FILE *arq;
    char texto[2048];
    size_t n;

    limpar();
    assert(consolidacao_carregar_estado(&estado2, APLICADAS, CONSOLIDADAS) == 1);
    assert(estado2.qtd_aplicadas == 0 && estado2.qtd_consolidadas == 0);
    arq = fopen(APLICADAS, "r");
    assert(arq != NULL);
    fclose(arq);

    assert(consolidacao_gerar_relatorio(&estado1, RELATORIO) == 1);
    arq = fopen(RELATORIO, "r");
    assert(arq != NULL);
    n = fread(texto, 1, sizeof texto - 1, arq);
    texto[n] = '\0';
    fclose(arq);
    assert(strstr(texto, "RELATORIO CONSOLIDADO") != NULL);
    assert(strstr(texto, "P01") != NULL);
    assert(strstr(texto, "P02") != NULL);
    assert(strstr(texto, "TOTAL") != NULL);
}

int main(void)
{
    testar_mesmo_log_duas_vezes();
    testar_entre_execucoes();
    testar_duas_portarias();
    testar_invalidas_e_rejeitadas();
    testar_efeito_idempotente();
    testar_relatorio_e_primeira_execucao();
    limpar();
    printf("test_consolidacao: OK\n");
    return 0;
}
