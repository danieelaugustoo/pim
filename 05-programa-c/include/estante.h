#ifndef ESTANTE_H
#define ESTANTE_H

#include "tipos.h"

/*
 * estante.h
 * Matriz estante[NUM_ESTANTES][NUM_PRATELEIRAS]: cada celula guarda o id da
 * encomenda que ocupa a posicao, ou 0 se estiver livre.
 */

/* Deixa todas as posicoes livres. */
void estante_iniciar(int estante[][NUM_PRATELEIRAS]);

/* A1: escolhe uma posicao livre para o volume e a marca como ocupada. Retorna 1 ou 0 se nao ha vaga. */
int estante_alocar_posicao(int estante[][NUM_PRATELEIRAS], char bloco, char tamanho,
                           int id_encomenda, int *linha, int *coluna);

/* Libera uma posicao. */
void estante_liberar_posicao(int estante[][NUM_PRATELEIRAS], int linha, int coluna);

/* Reconstroi a matriz a partir das encomendas pendentes. Retorna quantas posicoes foram ocupadas. */
int estante_reconstruir(int estante[][NUM_PRATELEIRAS], const Encomenda encomendas[], int quantidade);

/* Conta as posicoes ocupadas. */
int estante_ocupacao(int estante[][NUM_PRATELEIRAS]);

#endif /* ESTANTE_H */
