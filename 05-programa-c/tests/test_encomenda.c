#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tipos.h"
#include "util.h"
#include "estante.h"
#include "codigo.h"
#include "encomenda.h"
#include "retirada.h"

/* Preenche os dados que o porteiro digita. */
static Encomenda dados_de(char bloco, int apto, char tamanho)
{
    Encomenda d;

    memset(&d, 0, sizeof d);
    d.bloco = bloco;
    d.apartamento = apto;
    util_copiar_texto(d.destinatario, TAM_NOME, "Maria Teste");
    util_copiar_texto(d.transportadora, TAM_TRANSPORTADORA, "Transp Teste");
    d.tamanho = tamanho;
    return d;
}

/* US01, US02 e US03: registro com posicao, codigo, data e status. */
static void testar_criar(void)
{
    static Encomenda v[MAX_ENCOMENDAS];
    int n = 0;
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    Encomenda d = dados_de('B', 101, 'M');
    int dias = -1;

    estante_iniciar(e);
    assert(encomenda_criar(v, &n, e, &d) == ENC_OK);
    assert(n == 1);
    assert(v[0].id == 1);
    assert(v[0].status == STATUS_PENDENTE);
    assert(v[0].estante == 1 && v[0].prateleira == 0);
    assert(v[0].codigo >= CODIGO_MIN && v[0].codigo <= CODIGO_MAX);
    assert(util_dias_entre(v[0].recebida_em, v[0].recebida_em, &dias) == 1 && dias == 0);
    assert(v[0].retirada_em[0] == '\0' && v[0].retirado_por[0] == '\0');
    assert(e[1][0] == 1);

    assert(encomenda_criar(v, &n, e, &d) == ENC_OK);
    assert(v[1].id == 2);
    assert(v[1].codigo != v[0].codigo);
    assert(encomenda_contar_pendentes_unidade(v, n, 'B', 101) == 2);
    assert(encomenda_contar_pendentes_unidade(v, n, 'B', 102) == 0);
    assert(encomenda_localizar(v, n, 2) == 1);
    assert(encomenda_localizar(v, n, 99) == -1);
}

/* Sem vaga na estante, a encomenda nao e gravada. */
static void testar_sem_vaga(void)
{
    static Encomenda v[MAX_ENCOMENDAS];
    int n = 0;
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    Encomenda d = dados_de('A', 1, 'G');
    int i;
    int vagas_g = NUM_ESTANTES * (NUM_PRATELEIRAS - PRATELEIRA_INICIAL_G);

    estante_iniciar(e);
    for (i = 0; i < vagas_g; i++) {
        assert(encomenda_criar(v, &n, e, &d) == ENC_OK);
    }
    assert(encomenda_criar(v, &n, e, &d) == ENC_SEM_POSICAO);
    assert(n == vagas_g);
}

/* US04: retirada muda o status, guarda data e nome e libera a posicao. */
static void testar_retirada(void)
{
    static Encomenda v[MAX_ENCOMENDAS];
    int n = 0;
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    Encomenda d = dados_de('C', 34, 'P');

    estante_iniciar(e);
    assert(encomenda_criar(v, &n, e, &d) == ENC_OK);
    assert(estante_ocupacao(e) == 1);

    assert(retirada_efetuar(&v[0], e, "Joao Teste") == 1);
    assert(v[0].status == STATUS_RETIRADA);
    assert(strcmp(v[0].retirado_por, "Joao Teste") == 0);
    assert(strlen(v[0].retirada_em) == 16);
    assert(estante_ocupacao(e) == 0);
    assert(encomenda_contar_pendentes_unidade(v, n, 'C', 34) == 0);

    /* nao retira duas vezes */
    assert(retirada_efetuar(&v[0], e, "Outra Pessoa") == 0);
    assert(strcmp(v[0].retirado_por, "Joao Teste") == 0);
}

/* US04 (A3): a retirada pelo codigo acha a encomenda certa, libera a posicao e a confirmacao
   negada nao altera nada. */
static void testar_retirada_por_codigo(void)
{
    static Encomenda v[MAX_ENCOMENDAS];
    int n = 0;
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    Encomenda d1 = dados_de('A', 12, 'P');
    Encomenda d2 = dados_de('B', 21, 'M');
    int codigo2;
    int indice;
    int estante_antes;

    estante_iniciar(e);
    assert(encomenda_criar(v, &n, e, &d1) == ENC_OK);
    assert(encomenda_criar(v, &n, e, &d2) == ENC_OK);
    assert(encomenda_contar_pendentes(v, n) == 2);
    assert(estante_ocupacao(e) == 2);
    codigo2 = v[1].codigo;

    /* o codigo da segunda encomenda leva a ela, e nao a primeira */
    indice = codigo_localizar_pendente(v, n, codigo2);
    assert(indice == 1);

    /* confirmacao negada: o porteiro nao chama retirada_efetuar, entao nada muda */
    estante_antes = estante_ocupacao(e);
    assert(v[indice].status == STATUS_PENDENTE);
    assert(estante_ocupacao(e) == estante_antes);
    assert(encomenda_contar_pendentes(v, n) == 2);

    /* confirmacao aceita: retira, libera a posicao e o codigo deixa de achar a encomenda */
    assert(retirada_efetuar(&v[indice], e, "Maria Teste") == 1);
    assert(v[1].status == STATUS_RETIRADA);
    assert(estante_ocupacao(e) == 1);
    assert(encomenda_contar_pendentes(v, n) == 1);
    assert(codigo_localizar_pendente(v, n, codigo2) == CODIGO_NAO_ENCONTRADO);
    /* a primeira continua pendente e ainda e achada pelo seu codigo */
    assert(codigo_localizar_pendente(v, n, v[0].codigo) == 0);
}

/* Conversao do status em texto e de volta. */
static void testar_status(void)
{
    StatusEncomenda s = STATUS_PENDENTE;

    assert(strcmp(encomenda_status_texto(STATUS_PENDENTE), "PENDENTE") == 0);
    assert(strcmp(encomenda_status_texto(STATUS_RETIRADA), "RETIRADA") == 0);
    assert(strcmp(encomenda_status_texto(STATUS_DEVOLVIDA), "DEVOLVIDA") == 0);
    assert(encomenda_status_de_texto("RETIRADA", &s) == 1 && s == STATUS_RETIRADA);
    assert(encomenda_status_de_texto("DEVOLVIDA", &s) == 1 && s == STATUS_DEVOLVIDA);
    assert(encomenda_status_de_texto("INVALIDO", &s) == 0);
}

int main(void)
{
    testar_criar();
    testar_sem_vaga();
    testar_retirada();
    testar_retirada_por_codigo();
    testar_status();
    printf("test_encomenda: OK\n");
    return 0;
}
