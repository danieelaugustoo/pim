#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "tipos.h"

/*
 * persistencia.h
 * Leitura e gravacao dos arquivos CSV da portaria (separador ';', primeira
 * linha = cabecalho, datas "AAAA-MM-DD HH:MM").
 */

#define PERSIST_OK 0
#define PERSIST_ERRO 1

/* Monta o caminho "dados/portarias/Pnn-sufixo". */
void persistencia_montar_caminho(char *dest, int tam, int id_portaria, const char *sufixo);

/* Monta o caminho do log da rede simulada: "dados/rede/Pnn.log". */
void persistencia_montar_caminho_rede(char *dest, int tam, int id_portaria);

/* Carrega as encomendas. Se o arquivo nao existir, cria um com o cabecalho. */
int persistencia_carregar_encomendas(const char *caminho, Encomenda encomendas[], int maximo,
                                     int *quantidade);

/* Grava todas as encomendas (reescreve o arquivo). */
int persistencia_salvar_encomendas(const char *caminho, const Encomenda encomendas[], int quantidade);

/* Carrega os moradores. Se o arquivo nao existir, cria um com o cabecalho. */
int persistencia_carregar_moradores(const char *caminho, Morador moradores[], int maximo,
                                    int *quantidade);

/* Grava todos os moradores (reescreve o arquivo). */
int persistencia_salvar_moradores(const char *caminho, const Morador moradores[], int quantidade);

#endif /* PERSISTENCIA_H */
