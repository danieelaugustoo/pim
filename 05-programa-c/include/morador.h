#ifndef MORADOR_H
#define MORADOR_H

#include "tipos.h"

/*
 * morador.h
 * Cadastro e busca de moradores e do canal de aviso de cada um.
 */

/* Resultados de morador_criar */
#define MOR_OK 0
#define MOR_VETOR_CHEIO 1
#define MOR_CONTATO_INVALIDO 2
#define MOR_DUPLICADO 3

/* Texto do canal ("APP", "SMS" ou "INTERFONE"). */
const char *morador_canal_texto(CanalAviso canal);

/* Converte o texto do canal. Retorna 1 se valido. */
int morador_canal_de_texto(const char *texto, CanalAviso *canal);

/* Confere se o contato serve para o canal (APP: nao vazio; SMS: 10 ou 11 digitos). */
int morador_contato_valido(CanalAviso canal, const char *contato);

/* Proximo id livre (maior id existente + 1). */
int morador_proximo_id(const Morador moradores[], int quantidade);

/* Cria o morador a partir de dados ja preenchidos. Retorna MOR_OK ou um codigo de erro. */
int morador_criar(Morador moradores[], int *quantidade, const Morador *dados);

/* Pergunta os dados e cadastra um morador. Retorna 1 se cadastrou. */
int morador_cadastrar(Morador moradores[], int *quantidade);

/* Mostra todos os moradores. Retorna quantos mostrou. */
int morador_listar(const Morador moradores[], int quantidade);

/* Escolhe quem avisar: o morador ativo da unidade com o nome do destinatario; senao o primeiro ativo da unidade. Retorna o indice ou -1. */
int morador_localizar_para_aviso(const Morador moradores[], int quantidade, char bloco,
                                 int apartamento, const char *destinatario);

#endif /* MORADOR_H */
