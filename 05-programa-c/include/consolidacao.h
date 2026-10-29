#ifndef CONSOLIDACAO_H
#define CONSOLIDACAO_H

#include "tipos.h"

/*
 * consolidacao.h
 * Aplicacao idempotente das operacoes das portarias na central (ADR-003).
 * Arquivos da central:
 *   operacoes-aplicadas.csv      ids das operacoes ja aplicadas
 *   encomendas-consolidadas.csv  encomendas como a central as conhece
 *   relatorio-consolidado.txt    relatorio por portaria
 */

#define CAMINHO_APLICADAS "dados/central/operacoes-aplicadas.csv"
#define CAMINHO_CONSOLIDADAS "dados/central/encomendas-consolidadas.csv"
#define CAMINHO_RELATORIO "dados/central/relatorio-consolidado.txt"

/* Resultados de consolidacao_aplicar_operacao */
#define CONS_APLICADA 0     /* operacao nova, efeito aplicado e id registrado */
#define CONS_JA_APLICADA 1  /* id ja registrado: ignorada, nada muda */
#define CONS_REJEITADA 2    /* nao foi possivel aplicar (ex.: retirada de encomenda desconhecida) */

/* Estado da central em memoria (vetores estaticos de tamanho fixo). */
typedef struct {
    char aplicadas[MAX_OPERACOES][TAM_ID_OPERACAO];
    int qtd_aplicadas;
    EncomendaConsolidada consolidadas[MAX_CONSOLIDADAS];
    int qtd_consolidadas;
} EstadoCentral;

/* Contadores do processamento de um log. */
typedef struct {
    int lidas;          /* linhas de operacao encontradas no log */
    int aplicadas;      /* operacoes novas aplicadas */
    int ja_aplicadas;   /* operacoes ignoradas por ja terem sido aplicadas */
    int rejeitadas;     /* operacoes validas que nao puderam ser aplicadas */
    int invalidas;      /* linhas mal formadas ou de outra portaria */
} ResumoConsolidacao;

/* Zera o estado. */
void consolidacao_iniciar(EstadoCentral *estado);

/* Retorna 1 se o id ja esta registrado como aplicado. */
int consolidacao_operacao_ja_aplicada(const EstadoCentral *estado, const char *id_operacao);

/* Aplica uma operacao uma unica vez. Retorna CONS_APLICADA, CONS_JA_APLICADA ou CONS_REJEITADA. */
int consolidacao_aplicar_operacao(EstadoCentral *estado, const Operacao *operacao);

/* A5: processa o log de uma portaria. Retorna 1 se o log existe, 0 se nao existe. */
int consolidacao_processar_portaria(EstadoCentral *estado, int id_portaria, const char *caminho_log,
                                    ResumoConsolidacao *resumo);

/* Carrega o estado dos arquivos (cria os arquivos vazios se nao existirem). */
int consolidacao_carregar_estado(EstadoCentral *estado, const char *caminho_aplicadas,
                                 const char *caminho_consolidadas);

/* Grava o estado nos arquivos. */
int consolidacao_salvar_estado(const EstadoCentral *estado, const char *caminho_aplicadas,
                               const char *caminho_consolidadas);

/* Gera o relatorio por portaria. Retorna 1 ou 0. */
int consolidacao_gerar_relatorio(const EstadoCentral *estado, const char *caminho);

#endif /* CONSOLIDACAO_H */
