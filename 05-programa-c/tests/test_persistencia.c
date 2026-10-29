#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tipos.h"
#include "persistencia.h"

#define ARQUIVO_TESTE "bin/teste-encomendas.tmp.csv"

/* Preenche uma encomenda de teste. */
static void preencher(Encomenda *e, int id, char bloco, int apto, StatusEncomenda status)
{
    memset(e, 0, sizeof *e);
    e->id = id;
    e->bloco = bloco;
    e->apartamento = apto;
    strcpy(e->destinatario, "Pessoa Teste");
    strcpy(e->transportadora, "Transp Teste");
    e->tamanho = 'M';
    strcpy(e->recebida_em, "2026-10-20 09:15");
    e->estante = 1;
    e->prateleira = id;
    e->codigo = 100000 + id;
    e->status = status;
}

/* Arquivo inexistente: e criado so com o cabecalho e nenhuma encomenda e lida. */
static void testar_primeira_execucao(void)
{
    static Encomenda v[MAX_ENCOMENDAS];
    int n = -1;
    FILE *arq;

    remove(ARQUIVO_TESTE);
    assert(persistencia_carregar_encomendas(ARQUIVO_TESTE, v, MAX_ENCOMENDAS, &n) == PERSIST_OK);
    assert(n == 0);
    arq = fopen(ARQUIVO_TESTE, "r");
    assert(arq != NULL);
    fclose(arq);
}

/* Gravar e ler de volta devolve as mesmas encomendas, inclusive campos vazios. */
static void testar_ida_e_volta(void)
{
    static Encomenda gravadas[3];
    static Encomenda lidas[MAX_ENCOMENDAS];
    int n = -1;
    int i;

    preencher(&gravadas[0], 1, 'A', 12, STATUS_PENDENTE);
    preencher(&gravadas[1], 2, 'B', 203, STATUS_RETIRADA);
    strcpy(gravadas[1].retirada_em, "2026-10-21 18:30");
    strcpy(gravadas[1].retirado_por, "Joao Teste");
    preencher(&gravadas[2], 3, 'D', 7, STATUS_DEVOLVIDA);
    gravadas[2].tamanho = 'G';

    assert(persistencia_salvar_encomendas(ARQUIVO_TESTE, gravadas, 3) == PERSIST_OK);
    assert(persistencia_carregar_encomendas(ARQUIVO_TESTE, lidas, MAX_ENCOMENDAS, &n) == PERSIST_OK);
    assert(n == 3);
    for (i = 0; i < 3; i++) {
        assert(lidas[i].id == gravadas[i].id);
        assert(lidas[i].bloco == gravadas[i].bloco);
        assert(lidas[i].apartamento == gravadas[i].apartamento);
        assert(strcmp(lidas[i].destinatario, gravadas[i].destinatario) == 0);
        assert(strcmp(lidas[i].transportadora, gravadas[i].transportadora) == 0);
        assert(lidas[i].tamanho == gravadas[i].tamanho);
        assert(strcmp(lidas[i].recebida_em, gravadas[i].recebida_em) == 0);
        assert(lidas[i].estante == gravadas[i].estante);
        assert(lidas[i].prateleira == gravadas[i].prateleira);
        assert(lidas[i].codigo == gravadas[i].codigo);
        assert(lidas[i].status == gravadas[i].status);
        assert(strcmp(lidas[i].retirada_em, gravadas[i].retirada_em) == 0);
        assert(strcmp(lidas[i].retirado_por, gravadas[i].retirado_por) == 0);
    }
}

/* Linhas mal formadas sao ignoradas e as validas continuam sendo lidas. */
static void testar_linha_invalida(void)
{
    static Encomenda lidas[MAX_ENCOMENDAS];
    int n = -1;
    FILE *arq = fopen(ARQUIVO_TESTE, "a");

    assert(arq != NULL);
    fprintf(arq, "isto nao e uma linha valida\n");
    fprintf(arq, "9;Z;5;Nome;Transp;X;2026-10-20 09:15;0;0;123456;PENDENTE;;\n");
    fprintf(arq, "\n");
    fclose(arq);

    assert(persistencia_carregar_encomendas(ARQUIVO_TESTE, lidas, MAX_ENCOMENDAS, &n) == PERSIST_OK);
    assert(n == 3);
}

/* Caminho do arquivo da portaria. */
static void testar_caminho(void)
{
    char c[TAM_CAMINHO];

    persistencia_montar_caminho(c, TAM_CAMINHO, 1, "encomendas.csv");
    assert(strcmp(c, "dados/portarias/P01-encomendas.csv") == 0);
    persistencia_montar_caminho(c, TAM_CAMINHO, 10, "encomendas.csv");
    assert(strcmp(c, "dados/portarias/P10-encomendas.csv") == 0);
}

int main(void)
{
    testar_primeira_execucao();
    testar_ida_e_volta();
    testar_linha_invalida();
    testar_caminho();
    remove(ARQUIVO_TESTE);
    printf("test_persistencia: OK\n");
    return 0;
}
