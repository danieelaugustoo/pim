#include <stdio.h>
#include <string.h>

#include "tipos.h"
#include "util.h"
#include "encomenda.h"
#include "sincronizacao.h"
#include "consolidacao.h"

#define NUM_CAMPOS_CONSOLIDADA 7

static const char CABECALHO_APLICADAS[] = "id_operacao";
static const char CABECALHO_CONSOLIDADAS[] =
    "id_portaria;id_encomenda;bloco;apartamento;status;recebida_em;retirada_em";

/*
 * consolidacao_iniciar
 * Objetivo: deixar o estado da central vazio.
 * Parametros: estado = estado a zerar.
 * Retorno: nenhum.
 * Logica: zera os dois contadores; o conteudo dos vetores so vale ate esses
 *   contadores.
 */
void consolidacao_iniciar(EstadoCentral *estado)
{
    estado->qtd_aplicadas = 0;
    estado->qtd_consolidadas = 0;
}

/*
 * consolidacao_operacao_ja_aplicada
 * Objetivo: saber se uma operacao ja foi aplicada (base da idempotencia).
 * Parametros: estado = estado da central; id_operacao = id procurado.
 * Retorno: 1 se o id esta na lista de aplicadas; 0 se nao esta.
 * Logica: busca sequencial na lista de ids aplicados.
 */
int consolidacao_operacao_ja_aplicada(const EstadoCentral *estado, const char *id_operacao)
{
    int i;

    for (i = 0; i < estado->qtd_aplicadas; i++) {
        if (strcmp(estado->aplicadas[i], id_operacao) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
 * consolidacao_localizar (auxiliar interna)
 * Objetivo: achar uma encomenda no consolidado.
 * Parametros: estado = estado da central; id_portaria e id_encomenda =
 *   chave da encomenda (o id so e unico dentro da portaria).
 * Retorno: indice no vetor, ou -1 se nao existir.
 */
static int consolidacao_localizar(const EstadoCentral *estado, int id_portaria, int id_encomenda)
{
    int i;

    for (i = 0; i < estado->qtd_consolidadas; i++) {
        if (estado->consolidadas[i].id_portaria == id_portaria &&
            estado->consolidadas[i].id_encomenda == id_encomenda) {
            return i;
        }
    }
    return -1;
}

/*
 * consolidacao_efeito (auxiliar interna)
 * Objetivo: aplicar o efeito de uma operacao no consolidado, sem mexer na
 *   lista de ids aplicados.
 * Parametros: estado = estado da central; operacao = operacao valida.
 * Retorno: 1 se o efeito foi aplicado (ou ja estava aplicado); 0 se a
 *   operacao nao faz sentido para o estado atual.
 * Logica: REGISTRO cria a encomenda PENDENTE; RETIRADA marca RETIRADA com a
 *   data da operacao; DEVOLUCAO marca DEVOLVIDA. Repetir a mesma operacao
 *   (mesma data) devolve 1 sem alterar nada, para que uma queda entre a
 *   gravacao dos dois arquivos nao gere lixo ao reexecutar.
 */
static int consolidacao_efeito(EstadoCentral *estado, const Operacao *operacao)
{
    int indice = consolidacao_localizar(estado, operacao->id_portaria, operacao->id_encomenda);
    EncomendaConsolidada *c;

    if (operacao->tipo == OP_REGISTRO) {
        if (indice >= 0) {
            return strcmp(estado->consolidadas[indice].recebida_em, operacao->data_hora) == 0;
        }
        if (estado->qtd_consolidadas >= MAX_CONSOLIDADAS) {
            return 0;
        }
        c = &estado->consolidadas[estado->qtd_consolidadas];
        c->id_portaria = operacao->id_portaria;
        c->id_encomenda = operacao->id_encomenda;
        c->bloco = operacao->bloco;
        c->apartamento = operacao->apartamento;
        c->status = STATUS_PENDENTE;
        util_copiar_texto(c->recebida_em, TAM_DATA, operacao->data_hora);
        c->retirada_em[0] = '\0';
        estado->qtd_consolidadas++;
        return 1;
    }
    if (indice < 0) {
        return 0;
    }
    c = &estado->consolidadas[indice];
    if (operacao->tipo == OP_RETIRADA) {
        if (c->status == STATUS_PENDENTE) {
            c->status = STATUS_RETIRADA;
            util_copiar_texto(c->retirada_em, TAM_DATA, operacao->data_hora);
            return 1;
        }
        return c->status == STATUS_RETIRADA && strcmp(c->retirada_em, operacao->data_hora) == 0;
    }
    if (c->status == STATUS_PENDENTE) {
        c->status = STATUS_DEVOLVIDA;
        return 1;
    }
    return c->status == STATUS_DEVOLVIDA;
}

/*
 * consolidacao_aplicar_operacao
 * Objetivo: aplicar uma operacao na central uma unica vez (RF10, US11).
 * Parametros: estado = estado da central; operacao = operacao valida.
 * Retorno: CONS_APLICADA, CONS_JA_APLICADA ou CONS_REJEITADA.
 * Logica: se o id ja foi aplicado, ignora. Senao, confere a capacidade da
 *   lista de ids, aplica o efeito e, so se o efeito foi aceito, registra o
 *   id como aplicado. Uma operacao rejeitada nao e registrada, e pode ser
 *   aplicada depois, se a operacao que faltava chegar.
 */
int consolidacao_aplicar_operacao(EstadoCentral *estado, const Operacao *operacao)
{
    if (consolidacao_operacao_ja_aplicada(estado, operacao->id_operacao)) {
        return CONS_JA_APLICADA;
    }
    if (estado->qtd_aplicadas >= MAX_OPERACOES || !consolidacao_efeito(estado, operacao)) {
        return CONS_REJEITADA;
    }
    util_copiar_texto(estado->aplicadas[estado->qtd_aplicadas], TAM_ID_OPERACAO,
                      operacao->id_operacao);
    estado->qtd_aplicadas++;
    return CONS_APLICADA;
}

/*
 * consolidacao_processar_portaria (algoritmo A5)
 * Objetivo: consolidar o log de uma portaria sem duplicar registros (US11).
 * Parametros: estado = estado da central; id_portaria = portaria do log (1 a
 *   MAX_PORTARIAS); caminho_log = arquivo dados/rede/Pnn.log; resumo =
 *   recebe os contadores.
 * Retorno: 1 se o log existe e foi processado; 0 se o log nao existe.
 * Logica: le o log na ordem em que foi gravado (a ordem dentro de cada
 *   portaria e a da sequencia). Para cada linha: ignora cabecalho e linhas
 *   vazias; conta como invalida a linha mal formada ou de outra portaria;
 *   senao chama consolidacao_aplicar_operacao e conta o resultado.
 */
int consolidacao_processar_portaria(EstadoCentral *estado, int id_portaria, const char *caminho_log,
                                    ResumoConsolidacao *resumo)
{
    FILE *arq = fopen(caminho_log, "r");
    char linha[TAM_LINHA];
    Operacao operacao;

    memset(resumo, 0, sizeof *resumo);
    if (arq == NULL) {
        return 0;
    }
    while (fgets(linha, TAM_LINHA, arq) != NULL) {
        util_aparar(linha);
        if (linha[0] == '\0' || strncmp(linha, "id_operacao", 11) == 0) {
            continue;
        }
        if (!sincronizacao_operacao_de_linha(linha, &operacao) ||
            operacao.id_portaria != id_portaria) {
            resumo->invalidas++;
            continue;
        }
        resumo->lidas++;
        switch (consolidacao_aplicar_operacao(estado, &operacao)) {
        case CONS_APLICADA:
            resumo->aplicadas++;
            break;
        case CONS_JA_APLICADA:
            resumo->ja_aplicadas++;
            break;
        default:
            resumo->rejeitadas++;
            break;
        }
    }
    fclose(arq);
    return 1;
}

/*
 * consolidacao_ler_linha (auxiliar interna)
 * Objetivo: converter uma linha de encomendas-consolidadas.csv em registro.
 * Parametros: linha = texto (e alterado); c = recebe os dados.
 * Retorno: 1 se a linha e valida; 0 se esta mal formada.
 */
static int consolidacao_ler_linha(char *linha, EncomendaConsolidada *c)
{
    char *campos[NUM_CAMPOS_CONSOLIDADA];
    int dias;

    if (util_dividir_campos(linha, ';', campos, NUM_CAMPOS_CONSOLIDADA) != NUM_CAMPOS_CONSOLIDADA) {
        return 0;
    }
    if (!util_converter_inteiro(campos[0], 1, MAX_PORTARIAS, &c->id_portaria) ||
        !util_converter_inteiro(campos[1], 1, 999999, &c->id_encomenda) ||
        strlen(campos[2]) != 1 || campos[2][0] < 'A' || campos[2][0] > 'Z' ||
        !util_converter_inteiro(campos[3], 1, APARTAMENTO_MAX, &c->apartamento) ||
        !encomenda_status_de_texto(campos[4], &c->status) ||
        !util_dias_entre(campos[5], campos[5], &dias) ||
        strlen(campos[6]) >= TAM_DATA) {
        return 0;
    }
    c->bloco = campos[2][0];
    util_copiar_texto(c->recebida_em, TAM_DATA, campos[5]);
    util_copiar_texto(c->retirada_em, TAM_DATA, campos[6]);
    return 1;
}

/*
 * consolidacao_criar_arquivo (auxiliar interna)
 * Objetivo: criar um arquivo da central so com o cabecalho.
 * Parametros: caminho = arquivo; cabecalho = primeira linha.
 * Retorno: 1 se criou; 0 se falhou.
 */
static int consolidacao_criar_arquivo(const char *caminho, const char *cabecalho)
{
    FILE *arq = fopen(caminho, "w");

    if (arq == NULL) {
        return 0;
    }
    fprintf(arq, "%s\n", cabecalho);
    return fclose(arq) == 0;
}

/*
 * consolidacao_carregar_estado
 * Objetivo: recuperar o que a central ja aplicou em execucoes anteriores.
 * Parametros: estado = estado a preencher; caminho_aplicadas e
 *   caminho_consolidadas = arquivos da central.
 * Retorno: 1 se carregou; 0 se nao foi possivel abrir ou criar um arquivo.
 * Logica: zera o estado; cada arquivo ausente e criado so com o cabecalho.
 *   Linhas invalidas sao ignoradas com um aviso.
 */
int consolidacao_carregar_estado(EstadoCentral *estado, const char *caminho_aplicadas,
                                 const char *caminho_consolidadas)
{
    FILE *arq;
    char linha[TAM_LINHA];

    consolidacao_iniciar(estado);

    arq = fopen(caminho_aplicadas, "r");
    if (arq == NULL) {
        if (!consolidacao_criar_arquivo(caminho_aplicadas, CABECALHO_APLICADAS)) {
            return 0;
        }
    } else {
        if (fgets(linha, TAM_LINHA, arq) != NULL) {
            while (fgets(linha, TAM_LINHA, arq) != NULL && estado->qtd_aplicadas < MAX_OPERACOES) {
                util_aparar(linha);
                if (linha[0] != '\0' && strlen(linha) < TAM_ID_OPERACAO) {
                    util_copiar_texto(estado->aplicadas[estado->qtd_aplicadas], TAM_ID_OPERACAO, linha);
                    estado->qtd_aplicadas++;
                }
            }
        }
        fclose(arq);
    }

    arq = fopen(caminho_consolidadas, "r");
    if (arq == NULL) {
        return consolidacao_criar_arquivo(caminho_consolidadas, CABECALHO_CONSOLIDADAS);
    }
    if (fgets(linha, TAM_LINHA, arq) != NULL) {
        while (fgets(linha, TAM_LINHA, arq) != NULL && estado->qtd_consolidadas < MAX_CONSOLIDADAS) {
            util_aparar(linha);
            if (linha[0] == '\0') {
                continue;
            }
            if (consolidacao_ler_linha(linha, &estado->consolidadas[estado->qtd_consolidadas])) {
                estado->qtd_consolidadas++;
            } else {
                printf("Aviso: linha invalida ignorada em %s.\n", caminho_consolidadas);
            }
        }
    }
    fclose(arq);
    return 1;
}

/*
 * consolidacao_salvar_estado
 * Objetivo: gravar o estado da central nos arquivos.
 * Parametros: estado = estado da central; caminho_aplicadas e
 *   caminho_consolidadas = arquivos da central.
 * Retorno: 1 se gravou os dois arquivos; 0 se falhou.
 * Logica: grava primeiro as encomendas consolidadas e depois os ids
 *   aplicados. Se algo cair entre os dois, os ids que faltam fazem a
 *   proxima execucao reaplicar operacoes, o que e inofensivo porque o efeito
 *   de cada operacao tambem e idempotente.
 */
int consolidacao_salvar_estado(const EstadoCentral *estado, const char *caminho_aplicadas,
                               const char *caminho_consolidadas)
{
    FILE *arq;
    int i;
    const EncomendaConsolidada *c;

    arq = fopen(caminho_consolidadas, "w");
    if (arq == NULL) {
        return 0;
    }
    fprintf(arq, "%s\n", CABECALHO_CONSOLIDADAS);
    for (i = 0; i < estado->qtd_consolidadas; i++) {
        c = &estado->consolidadas[i];
        fprintf(arq, "%d;%d;%c;%d;%s;%s;%s\n", c->id_portaria, c->id_encomenda, c->bloco,
                c->apartamento, encomenda_status_texto(c->status), c->recebida_em, c->retirada_em);
    }
    if (fclose(arq) != 0) {
        return 0;
    }

    arq = fopen(caminho_aplicadas, "w");
    if (arq == NULL) {
        return 0;
    }
    fprintf(arq, "%s\n", CABECALHO_APLICADAS);
    for (i = 0; i < estado->qtd_aplicadas; i++) {
        fprintf(arq, "%s\n", estado->aplicadas[i]);
    }
    return fclose(arq) == 0;
}

/*
 * consolidacao_gerar_relatorio
 * Objetivo: gravar o relatorio consolidado por portaria.
 * Parametros: estado = estado da central; caminho = arquivo do relatorio.
 * Retorno: 1 se gravou; 0 se falhou.
 * Logica: para cada portaria de 1 a MAX_PORTARIAS conta as encomendas por
 *   status e escreve uma linha se a portaria tem alguma encomenda; no fim
 *   escreve os totais.
 */
int consolidacao_gerar_relatorio(const EstadoCentral *estado, const char *caminho)
{
    FILE *arq = fopen(caminho, "w");
    char agora[TAM_DATA];
    int p;
    int i;
    int pendentes;
    int retiradas;
    int devolvidas;
    int total_pendentes = 0;
    int total_retiradas = 0;
    int total_devolvidas = 0;

    if (arq == NULL) {
        return 0;
    }
    util_data_hora_atual(agora, TAM_DATA);
    fprintf(arq, "RELATORIO CONSOLIDADO - Administradora Morada Central\n");
    fprintf(arq, "Gerado em: %s\n\n", agora);
    fprintf(arq, "%-8s %-12s %-10s %-10s %-10s\n", "PORTARIA", "REGISTRADAS", "PENDENTES",
            "RETIRADAS", "DEVOLVIDAS");
    for (p = 1; p <= MAX_PORTARIAS; p++) {
        pendentes = 0;
        retiradas = 0;
        devolvidas = 0;
        for (i = 0; i < estado->qtd_consolidadas; i++) {
            if (estado->consolidadas[i].id_portaria == p) {
                if (estado->consolidadas[i].status == STATUS_PENDENTE) {
                    pendentes++;
                } else if (estado->consolidadas[i].status == STATUS_RETIRADA) {
                    retiradas++;
                } else {
                    devolvidas++;
                }
            }
        }
        if (pendentes + retiradas + devolvidas > 0) {
            fprintf(arq, "P%02d      %-12d %-10d %-10d %-10d\n", p, pendentes + retiradas + devolvidas,
                    pendentes, retiradas, devolvidas);
        }
        total_pendentes += pendentes;
        total_retiradas += retiradas;
        total_devolvidas += devolvidas;
    }
    fprintf(arq, "%-8s %-12d %-10d %-10d %-10d\n", "TOTAL",
            total_pendentes + total_retiradas + total_devolvidas, total_pendentes, total_retiradas,
            total_devolvidas);
    return fclose(arq) == 0;
}
