#ifndef SINCRONIZACAO_H
#define SINCRONIZACAO_H

#include "tipos.h"

/*
 * sincronizacao.h
 * Fila de operacoes da portaria e envio para a "rede" simulada (ADR-003).
 * Formato da linha (fila e log da rede):
 *   id_operacao;id_portaria;data_hora;tipo;id_encomenda;bloco;apartamento
 */

/* Resultados de sincronizacao_enviar_pendentes */
#define SINC_OK 0        /* operacoes copiadas para a rede e fila esvaziada */
#define SINC_OFFLINE 1   /* portaria offline: fila preservada */
#define SINC_VAZIA 2     /* nao havia operacoes pendentes */
#define SINC_ERRO 3      /* falha de arquivo: fila preservada */

/* Texto do tipo ("REGISTRO", "RETIRADA" ou "DEVOLUCAO"). */
const char *sincronizacao_tipo_texto(TipoOperacao tipo);

/* Converte o texto do tipo. Retorna 1 se valido. */
int sincronizacao_tipo_de_texto(const char *texto, TipoOperacao *tipo);

/* Monta o id "Pnn-NNNNNN". */
void sincronizacao_montar_id(char *dest, int tam, int id_portaria, int numero);

/* Converte a operacao em linha de arquivo (sem quebra de linha). */
void sincronizacao_operacao_para_linha(const Operacao *operacao, char *dest, int tam);

/* Converte e valida uma linha. Retorna 1 se valida. A linha e alterada. */
int sincronizacao_operacao_de_linha(char *linha, Operacao *operacao);

/* Le o ultimo numero usado, soma 1, grava e devolve o novo numero (0 em caso de erro). */
int sincronizacao_proximo_numero(const char *caminho_sequencia);

/* Cria a operacao e a acrescenta ao final da fila. Retorna 1 ou 0. */
int sincronizacao_registrar_operacao(const char *caminho_fila, const char *caminho_sequencia,
                                     int id_portaria, TipoOperacao tipo, const Encomenda *encomenda);

/* Conta as operacoes da fila. */
int sincronizacao_contar_pendentes(const char *caminho_fila);

/* A4: se online, copia a fila para o log da rede e esvazia a fila. */
int sincronizacao_enviar_pendentes(const char *caminho_fila, const char *caminho_rede, int online,
                                   int *enviadas);

#endif /* SINCRONIZACAO_H */
