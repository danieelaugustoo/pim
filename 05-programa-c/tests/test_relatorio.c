#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tipos.h"
#include "util.h"
#include "estante.h"
#include "relatorio.h"

#define HOJE "2026-10-29 10:00"

/* Preenche uma encomenda de teste. */
static void montar(Encomenda *e, int id, StatusEncomenda status, const char *recebida_em)
{
    memset(e, 0, sizeof *e);
    e->id = id;
    e->bloco = 'A';
    e->apartamento = 12;
    e->status = status;
    util_copiar_texto(e->recebida_em, TAM_DATA, recebida_em);
}

/* US12: percentual de ocupacao = ocupadas / total * 100. */
static void testar_ocupacao(void)
{
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];
    int i;

    estante_iniciar(e);
    assert(relatorio_percentual_ocupacao(e) == 0.0);
    for (i = 0; i < NUM_PRATELEIRAS; i++) {
        e[0][i] = i + 1;
    }
    /* uma estante cheia de NUM_ESTANTES = 25% */
    assert(relatorio_percentual_ocupacao(e) == 100.0 / NUM_ESTANTES);
    for (i = 0; i < NUM_ESTANTES * NUM_PRATELEIRAS; i++) {
        e[i / NUM_PRATELEIRAS][i % NUM_PRATELEIRAS] = i + 1;
    }
    assert(relatorio_percentual_ocupacao(e) == 100.0);
}

/* US13: so pendente com mais de DIAS_ALERTA dias alerta. */
static void testar_pendencias_antigas(void)
{
    Encomenda v[6];
    int dias = 0;

    montar(&v[0], 1, STATUS_PENDENTE, "2026-10-21 09:00"); /* 8 dias: alerta */
    montar(&v[1], 2, STATUS_PENDENTE, "2026-10-22 09:00"); /* 7 dias: ainda nao */
    montar(&v[2], 3, STATUS_PENDENTE, "2026-10-29 08:00"); /* hoje */
    montar(&v[3], 4, STATUS_RETIRADA, "2026-09-01 09:00"); /* antiga, mas retirada */
    montar(&v[4], 5, STATUS_DEVOLVIDA, "2026-09-01 09:00");
    montar(&v[5], 6, STATUS_PENDENTE, "2026-09-29 09:00"); /* 30 dias: alerta */

    assert(relatorio_pendencia_antiga(&v[0], HOJE, &dias) == 1 && dias == 8);
    assert(relatorio_pendencia_antiga(&v[1], HOJE, &dias) == 0);
    assert(relatorio_pendencia_antiga(&v[2], HOJE, &dias) == 0);
    assert(relatorio_pendencia_antiga(&v[3], HOJE, &dias) == 0);
    assert(relatorio_pendencia_antiga(&v[4], HOJE, &dias) == 0);
    assert(relatorio_pendencia_antiga(&v[5], HOJE, &dias) == 1 && dias == 30);
    assert(relatorio_contar_antigas(v, 6, HOJE) == 2);

    /* nenhuma antiga: o relatorio informa que nao ha alertas */
    assert(relatorio_pendencias_antigas(&v[1], 2, HOJE) == 0);
    assert(relatorio_pendencias_antigas(v, 6, HOJE) == 2);

    /* data invalida nunca alerta */
    montar(&v[0], 7, STATUS_PENDENTE, "sem data");
    assert(relatorio_pendencia_antiga(&v[0], HOJE, &dias) == 0);
}

/* US14: contagem por dia do mes e dia de pico. */
static void testar_pico_mensal(void)
{
    Encomenda v[7];
    int contagem[DIAS_NO_MES + 1];

    montar(&v[0], 1, STATUS_PENDENTE, "2026-10-05 09:00");
    montar(&v[1], 2, STATUS_RETIRADA, "2026-10-05 15:00");
    montar(&v[2], 3, STATUS_PENDENTE, "2026-10-20 09:00");
    montar(&v[3], 4, STATUS_PENDENTE, "2026-10-20 10:00");
    montar(&v[4], 5, STATUS_DEVOLVIDA, "2026-10-20 11:00");
    montar(&v[5], 6, STATUS_PENDENTE, "2026-11-20 09:00"); /* outro mes */
    montar(&v[6], 7, STATUS_PENDENTE, "2025-10-20 09:00"); /* outro ano */

    assert(relatorio_contar_por_dia(v, 7, 2026, 10, contagem) == 5);
    assert(contagem[5] == 2 && contagem[20] == 3 && contagem[1] == 0);
    assert(relatorio_dia_pico(contagem) == 20);

    /* empate: vence o dia mais cedo */
    montar(&v[2], 3, STATUS_PENDENTE, "2026-10-05 12:00");
    assert(relatorio_contar_por_dia(v, 7, 2026, 10, contagem) == 5);
    assert(relatorio_dia_pico(contagem) == 5);

    /* mes sem registros */
    assert(relatorio_contar_por_dia(v, 7, 2026, 12, contagem) == 0);
    assert(relatorio_dia_pico(contagem) == 0);
    relatorio_pico_mensal(v, 7, 2026, 12);
    relatorio_pico_mensal(v, 7, 2026, 10);
}

/* Central: antigas e pico por portaria. */
static void testar_consolidado(void)
{
    EncomendaConsolidada c[5];
    char data[TAM_DATA];
    int registros = 0;
    int i;

    memset(c, 0, sizeof c);
    for (i = 0; i < 5; i++) {
        c[i].id_portaria = i < 3 ? 1 : 2;
        c[i].id_encomenda = i + 1;
        c[i].bloco = 'A';
        c[i].apartamento = 1;
        c[i].status = STATUS_PENDENTE;
    }
    util_copiar_texto(c[0].recebida_em, TAM_DATA, "2026-10-01 09:00"); /* antiga */
    util_copiar_texto(c[1].recebida_em, TAM_DATA, "2026-10-28 09:00");
    util_copiar_texto(c[2].recebida_em, TAM_DATA, "2026-10-28 16:00");
    util_copiar_texto(c[3].recebida_em, TAM_DATA, "2026-10-02 09:00"); /* antiga */
    util_copiar_texto(c[4].recebida_em, TAM_DATA, "2026-10-03 09:00");
    c[4].status = STATUS_RETIRADA; /* antiga, mas retirada */

    assert(relatorio_contar_antigas_consolidadas(c, 5, 1, HOJE) == 1);
    assert(relatorio_contar_antigas_consolidadas(c, 5, 2, HOJE) == 1);
    assert(relatorio_contar_antigas_consolidadas(c, 5, 3, HOJE) == 0);

    assert(relatorio_pico_consolidado(c, 5, 1, data, TAM_DATA, &registros) == 1);
    assert(strcmp(data, "2026-10-28") == 0 && registros == 2);
    /* portaria 2: tres dias com 1 registro cada; vence o mais cedo */
    assert(relatorio_pico_consolidado(c, 5, 2, data, TAM_DATA, &registros) == 1);
    assert(strcmp(data, "2026-10-02") == 0 && registros == 1);
    assert(relatorio_pico_consolidado(c, 5, 3, data, TAM_DATA, &registros) == 0);
}

int main(void)
{
    int e[NUM_ESTANTES][NUM_PRATELEIRAS];

    testar_ocupacao();
    testar_pendencias_antigas();
    testar_pico_mensal();
    testar_consolidado();
    estante_iniciar(e);
    relatorio_mapa_estante(e);
    printf("test_relatorio: OK\n");
    return 0;
}
