#ifndef RETIRADA_H
#define RETIRADA_H

#include "tipos.h"

/*
 * retirada.h
 * Retirada de encomenda: o codigo localiza a encomenda e o porteiro confirma antes de entregar.
 */

/* Marca a encomenda como RETIRADA, com data, hora e nome, e libera a posicao. Retorna 1 ou 0 se nao estava pendente. */
int retirada_efetuar(Encomenda *encomenda, int estante[][NUM_PRATELEIRAS], const char *retirado_por);

/* A3: pede o codigo, acha a encomenda pendente, pede a confirmacao do porteiro e registra a
   retirada. Retorna 1 se retirou e, nesse caso, grava em *indice a posicao da encomenda no vetor. */
int retirada_registrar(Encomenda encomendas[], int quantidade, int estante[][NUM_PRATELEIRAS],
                       int *indice);

#endif /* RETIRADA_H */
