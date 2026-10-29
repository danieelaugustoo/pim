#ifndef CODIGO_H
#define CODIGO_H

#include "tipos.h"

/*
 * codigo.h
 * Codigo de retirada de 6 digitos, de uso unico entre as encomendas pendentes.
 */

/* Inicia o gerador de numeros aleatorios (chamar uma vez ao abrir o programa). */
void codigo_iniciar_aleatorio(void);

/* Retorna 1 se o numero tem exatamente 6 digitos. */
int codigo_valido(int codigo);

/* Retorna 1 se alguma encomenda pendente ja usa o codigo. */
int codigo_existe_pendente(const Encomenda encomendas[], int quantidade, int codigo);

/* A2: sorteia um codigo que nao exista entre as pendentes. Retorna 0 se nao conseguir. */
int codigo_gerar_unico(const Encomenda encomendas[], int quantidade);

/* Retorna 1 se o codigo digitado confere com o da encomenda. */
int codigo_conferir(int digitado, int esperado);

#endif /* CODIGO_H */
