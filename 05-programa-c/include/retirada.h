#ifndef RETIRADA_H
#define RETIRADA_H

#include "tipos.h"

/*
 * retirada.h
 * Retirada de encomenda com conferencia do codigo.
 */

/* Marca a encomenda como RETIRADA, com data, hora e nome, e libera a posicao. Retorna 1 ou 0 se nao estava pendente. */
int retirada_efetuar(Encomenda *encomenda, int estante[][NUM_PRATELEIRAS], const char *retirado_por);

/* A3: pede a unidade, a encomenda e o codigo e registra a retirada. Retorna 1 se retirou. */
int retirada_registrar(Encomenda encomendas[], int quantidade, int estante[][NUM_PRATELEIRAS]);

#endif /* RETIRADA_H */
