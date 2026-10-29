#ifndef ENCOMENDA_H
#define ENCOMENDA_H

#include "tipos.h"

/*
 * encomenda.h
 * Registro, listagem e busca de encomendas.
 */

/* Resultados de encomenda_criar */
#define ENC_OK 0
#define ENC_SEM_POSICAO 1   /* estante cheia */
#define ENC_VETOR_CHEIO 2   /* MAX_ENCOMENDAS atingido */
#define ENC_SEM_CODIGO 3    /* nao foi possivel gerar codigo unico */

/* Texto do status ("PENDENTE", "RETIRADA" ou "DEVOLVIDA"). */
const char *encomenda_status_texto(StatusEncomenda status);

/* Converte o texto do status. Retorna 1 se valido. */
int encomenda_status_de_texto(const char *texto, StatusEncomenda *status);

/* Proximo id livre (maior id existente + 1). */
int encomenda_proximo_id(const Encomenda encomendas[], int quantidade);

/* Indice da encomenda com o id, ou -1. */
int encomenda_localizar(const Encomenda encomendas[], int quantidade, int id);

/* Conta as pendentes de uma unidade. */
int encomenda_contar_pendentes_unidade(const Encomenda encomendas[], int quantidade,
                                       char bloco, int apartamento);

/* Cria a encomenda: id, posicao, codigo, data e status. Retorna ENC_OK ou um codigo de erro. */
int encomenda_criar(Encomenda encomendas[], int *quantidade, int estante[][NUM_PRATELEIRAS],
                    const Encomenda *dados);

/* Pergunta bloco e apartamento. Retorna 1 ou 0 no fim da entrada. */
int encomenda_ler_unidade(char *bloco, int *apartamento);

/* Pergunta os dados e registra uma encomenda. Retorna 1 se registrou. */
int encomenda_registrar(Encomenda encomendas[], int *quantidade, int estante[][NUM_PRATELEIRAS]);

/* Mostra todas as pendentes. Retorna quantas mostrou. */
int encomenda_listar_pendentes(const Encomenda encomendas[], int quantidade);

/* Mostra as pendentes de uma unidade. Retorna quantas mostrou. */
int encomenda_buscar_por_unidade(const Encomenda encomendas[], int quantidade,
                                 char bloco, int apartamento);

#endif /* ENCOMENDA_H */
