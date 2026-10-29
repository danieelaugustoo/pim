#ifndef RELATORIO_H
#define RELATORIO_H

#include "tipos.h"

/*
 * relatorio.h
 * Mapa da estante, pendencias antigas e pico de encomendas (algoritmo A6).
 * As funcoes de calculo nao imprimem nada e recebem a data atual como texto,
 * para poderem ser testadas com datas fixas.
 */

/* Percentual de ocupacao da estante: ocupadas / total * 100. */
double relatorio_percentual_ocupacao(int estante[][NUM_PRATELEIRAS]);

/* US12: mostra a matriz (livre ou ocupada) e o resumo com o percentual. */
void relatorio_mapa_estante(int estante[][NUM_PRATELEIRAS]);

/* Retorna 1 se a encomenda esta PENDENTE ha mais de DIAS_ALERTA dias em relacao a agora.
   Quando retorna 1, grava os dias em *dias. */
int relatorio_pendencia_antiga(const Encomenda *encomenda, const char *agora, int *dias);

/* Conta as pendencias antigas do vetor. */
int relatorio_contar_antigas(const Encomenda encomendas[], int quantidade, const char *agora);

/* US13: lista as pendencias antigas, ou informa que nao ha alertas. Retorna quantas listou. */
int relatorio_pendencias_antigas(const Encomenda encomendas[], int quantidade, const char *agora);

/* Conta os registros de um mes, por dia: contagem[1..DIAS_NO_MES]. Retorna o total do mes. */
int relatorio_contar_por_dia(const Encomenda encomendas[], int quantidade, int ano, int mes,
                             int contagem[DIAS_NO_MES + 1]);

/* Dia com mais registros (o mais cedo, em caso de empate), ou 0 se nao ha registros. */
int relatorio_dia_pico(const int contagem[DIAS_NO_MES + 1]);

/* US14: mostra a contagem por dia de um mes e o dia de pico. */
void relatorio_pico_mensal(const Encomenda encomendas[], int quantidade, int ano, int mes);

/* Opcao 7 do menu: submenu de relatorios da portaria. */
void relatorio_menu(const Encomenda encomendas[], int quantidade, int estante[][NUM_PRATELEIRAS]);

/* Central: conta as pendencias antigas de uma portaria no consolidado. */
int relatorio_contar_antigas_consolidadas(const EncomendaConsolidada consolidadas[], int quantidade,
                                          int id_portaria, const char *agora);

/* Central: acha o dia com mais registros de uma portaria. Grava a data "AAAA-MM-DD" em data e a
   quantidade em *registros. Retorna 1 se a portaria tem registros; 0 se nao tem. */
int relatorio_pico_consolidado(const EncomendaConsolidada consolidadas[], int quantidade,
                               int id_portaria, char *data, int tam_data, int *registros);

#endif /* RELATORIO_H */
