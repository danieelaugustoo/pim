#include <stdio.h>
#include <assert.h>

#include "tipos.h"
#include "estante.h"

#define TOTAL_PM (NUM_ESTANTES * PRATELEIRA_INICIAL_G)
#define TOTAL_G (NUM_ESTANTES * (NUM_PRATELEIRAS - PRATELEIRA_INICIAL_G))

/* Volume P ou M vai para a estante do bloco, na primeira prateleira livre. */
static void testar_estante_do_bloco(void)
{
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    int linha = -1;
    int coluna = -1;

    estante_iniciar(e);
    assert(estante_alocar_posicao(e, 'B', 'M', 1, &linha, &coluna) == 1);
    assert(linha == 1 && coluna == 0);
    assert(e[1][0] == 1);
    assert(estante_alocar_posicao(e, 'B', 'P', 2, &linha, &coluna) == 1);
    assert(linha == 1 && coluna == 1);
    assert(estante_alocar_posicao(e, 'd', 'P', 3, &linha, &coluna) == 1);
    assert(linha == 3 && coluna == 0);
    /* bloco alem de D: volta ao inicio (E = 4, modulo 4 = estante 0) */
    assert(estante_alocar_posicao(e, 'E', 'P', 4, &linha, &coluna) == 1);
    assert(linha == 0 && coluna == 0);
    assert(estante_ocupacao(e) == 4);
}

/* Volume G vai para a faixa reservada (a partir da prateleira 10). */
static void testar_volume_grande(void)
{
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    int linha = -1;
    int coluna = -1;

    estante_iniciar(e);
    assert(estante_alocar_posicao(e, 'A', 'G', 1, &linha, &coluna) == 1);
    assert(linha == 0 && coluna == PRATELEIRA_INICIAL_G);
    assert(estante_alocar_posicao(e, 'A', 'G', 2, &linha, &coluna) == 1);
    assert(linha == 0 && coluna == PRATELEIRA_INICIAL_G + 1);
    /* volume P nao usa a faixa reservada */
    assert(estante_alocar_posicao(e, 'A', 'P', 3, &linha, &coluna) == 1);
    assert(coluna < PRATELEIRA_INICIAL_G);
}

/* Estante preferida cheia leva o volume para outra estante. */
static void testar_estante_cheia(void)
{
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    int linha = -1;
    int coluna = -1;
    int i;

    estante_iniciar(e);
    for (i = 0; i < PRATELEIRA_INICIAL_G; i++) {
        assert(estante_alocar_posicao(e, 'A', 'M', i + 1, &linha, &coluna) == 1);
        assert(linha == 0 && coluna == i);
    }
    assert(estante_alocar_posicao(e, 'A', 'M', 100, &linha, &coluna) == 1);
    assert(linha == 1 && coluna == 0);

    /* o mesmo para a faixa dos volumes G */
    for (i = 0; i < NUM_PRATELEIRAS - PRATELEIRA_INICIAL_G; i++) {
        assert(estante_alocar_posicao(e, 'A', 'G', 200 + i, &linha, &coluna) == 1);
        assert(linha == 0);
    }
    assert(estante_alocar_posicao(e, 'A', 'G', 300, &linha, &coluna) == 1);
    assert(linha == 1 && coluna == PRATELEIRA_INICIAL_G);
}

/* Com tudo cheio, retorna erro e nao altera a matriz. */
static void testar_tudo_cheio(void)
{
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    int linha = -1;
    int coluna = -1;
    int i;
    int antes;

    estante_iniciar(e);
    for (i = 0; i < TOTAL_PM; i++) {
        assert(estante_alocar_posicao(e, 'A', 'P', i + 1, &linha, &coluna) == 1);
    }
    antes = estante_ocupacao(e);
    assert(antes == TOTAL_PM);
    assert(estante_alocar_posicao(e, 'C', 'M', 999, &linha, &coluna) == 0);
    assert(estante_ocupacao(e) == antes);
    /* volumes G ainda tem vaga, pois a faixa e separada */
    for (i = 0; i < TOTAL_G; i++) {
        assert(estante_alocar_posicao(e, 'A', 'G', 1000 + i, &linha, &coluna) == 1);
    }
    assert(estante_alocar_posicao(e, 'A', 'G', 2000, &linha, &coluna) == 0);
    assert(estante_ocupacao(e) == NUM_ESTANTES * NUM_PRATELEIRAS);
}

/* Liberar uma posicao a deixa disponivel de novo. */
static void testar_liberar(void)
{
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    int linha = -1;
    int coluna = -1;

    estante_iniciar(e);
    assert(estante_alocar_posicao(e, 'C', 'P', 1, &linha, &coluna) == 1);
    assert(estante_alocar_posicao(e, 'C', 'P', 2, &linha, &coluna) == 1);
    assert(coluna == 1);
    estante_liberar_posicao(e, 2, 0);
    assert(e[2][0] == 0);
    assert(estante_ocupacao(e) == 1);
    assert(estante_alocar_posicao(e, 'C', 'P', 3, &linha, &coluna) == 1);
    assert(linha == 2 && coluna == 0);
    /* posicao fora da matriz e ignorada */
    estante_liberar_posicao(e, -1, 0);
    estante_liberar_posicao(e, 0, NUM_PRATELEIRAS);
    assert(estante_ocupacao(e) == 2);
}

/* A matriz e reconstruida so com as pendentes. */
static void testar_reconstruir(void)
{
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    Encomenda v[3] = {{0}};

    v[0].id = 1; v[0].estante = 0; v[0].prateleira = 3; v[0].status = STATUS_PENDENTE;
    v[1].id = 2; v[1].estante = 1; v[1].prateleira = 0; v[1].status = STATUS_RETIRADA;
    v[2].id = 3; v[2].estante = 2; v[2].prateleira = 10; v[2].status = STATUS_PENDENTE;

    assert(estante_reconstruir(e, v, 3) == 2);
    assert(e[0][3] == 1);
    assert(e[1][0] == 0);
    assert(e[2][10] == 3);
    assert(estante_ocupacao(e) == 2);
}

int main(void)
{
    testar_estante_do_bloco();
    testar_volume_grande();
    testar_estante_cheia();
    testar_tudo_cheio();
    testar_liberar();
    testar_reconstruir();
    printf("test_estante: OK\n");
    return 0;
}
