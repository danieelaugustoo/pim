#include <stdio.h>

#include "tipos.h"
#include "util.h"
#include "estante.h"
#include "codigo.h"
#include "encomenda.h"
#include "retirada.h"

/*
 * retirada_efetuar
 * Objetivo: aplicar a retirada a uma encomenda (US04).
 * Parametros: encomenda = encomenda pendente; estante = matriz de posicoes;
 *   retirado_por = nome de quem retira.
 * Retorno: 1 se a retirada foi aplicada; 0 se a encomenda nao estava pendente.
 * Logica: muda o status para RETIRADA, grava data, hora e nome, e libera a
 *   posicao que o volume ocupava.
 */
int retirada_efetuar(Encomenda *encomenda, int estante[][NUM_PRATELEIRAS], const char *retirado_por)
{
    if (encomenda->status != STATUS_PENDENTE) {
        return 0;
    }
    encomenda->status = STATUS_RETIRADA;
    util_data_hora_atual(encomenda->retirada_em, TAM_DATA);
    util_copiar_texto(encomenda->retirado_por, TAM_NOME, retirado_por);
    estante_liberar_posicao(estante, encomenda->estante, encomenda->prateleira);
    return 1;
}

/*
 * retirada_escolher (auxiliar interna)
 * Objetivo: pedir o id da encomenda e conferir se e uma pendente da unidade.
 * Parametros: encomendas = vetor; quantidade = tamanho usado; bloco e
 *   apartamento = unidade informada.
 * Retorno: indice da encomenda no vetor; -1 se o id nao serve; -2 se a
 *   entrada acabou.
 * Logica: le o id, localiza no vetor e confere status e unidade.
 */
static int retirada_escolher(const Encomenda encomendas[], int quantidade, char bloco, int apartamento)
{
    int id;
    int indice;

    if (!util_ler_inteiro("Id da encomenda a retirar: ", 1, 999999, &id)) {
        return -2;
    }
    indice = encomenda_localizar(encomendas, quantidade, id);
    if (indice < 0 || encomendas[indice].status != STATUS_PENDENTE ||
        encomendas[indice].bloco != bloco || encomendas[indice].apartamento != apartamento) {
        printf("Esse id nao esta entre as pendentes da unidade %c-%d.\n", bloco, apartamento);
        return -1;
    }
    return indice;
}

/*
 * retirada_pedir_codigo (auxiliar interna)
 * Objetivo: conferir o codigo, com ate MAX_TENTATIVAS tentativas.
 * Parametros: esperado = codigo da encomenda.
 * Retorno: 1 se o codigo conferiu; 0 se errou todas as tentativas ou a
 *   entrada acabou.
 * Logica: laco de 1 a MAX_TENTATIVAS; a cada erro avisa quantas restam.
 */
static int retirada_pedir_codigo(int esperado)
{
    int tentativa;
    int digitado;

    for (tentativa = 1; tentativa <= MAX_TENTATIVAS; tentativa++) {
        if (!util_ler_inteiro("Codigo de retirada (6 digitos): ", 0, CODIGO_MAX, &digitado)) {
            return 0;
        }
        if (codigo_conferir(digitado, esperado)) {
            return 1;
        }
        printf("Codigo incorreto (tentativa %d de %d).\n", tentativa, MAX_TENTATIVAS);
    }
    return 0;
}

/*
 * retirada_registrar (algoritmo A3, interativo)
 * Objetivo: registrar a retirada de uma encomenda pelo morador.
 * Parametros: encomendas = vetor; quantidade = tamanho usado; estante =
 *   matriz de posicoes.
 * Retorno: 1 se a retirada foi registrada (o chamador deve salvar); 0 caso
 *   contrario.
 * Logica: pede a unidade e lista as pendentes dela; pede o id da encomenda;
 *   confere o codigo (ate MAX_TENTATIVAS); se conferir, pede o nome de quem
 *   retira e aplica a retirada. Depois de todas as tentativas erradas, nega a
 *   retirada e a encomenda continua PENDENTE.
 */
int retirada_registrar(Encomenda encomendas[], int quantidade, int estante[][NUM_PRATELEIRAS])
{
    char bloco;
    int apartamento;
    int indice;
    char nome[TAM_NOME];

    printf("\n--- Registrar retirada ---\n");
    if (!encomenda_ler_unidade(&bloco, &apartamento)) {
        return 0;
    }
    if (encomenda_buscar_por_unidade(encomendas, quantidade, bloco, apartamento) == 0) {
        return 0;
    }
    indice = retirada_escolher(encomendas, quantidade, bloco, apartamento);
    if (indice < 0) {
        return 0;
    }
    if (!retirada_pedir_codigo(encomendas[indice].codigo)) {
        printf("Retirada negada. A encomenda continua pendente.\n");
        return 0;
    }
    if (!util_ler_texto("Nome de quem retira: ", nome, TAM_NOME)) {
        return 0;
    }
    retirada_efetuar(&encomendas[indice], estante, nome);
    printf("Retirada registrada: encomenda %d, em %s, por %s.\n", encomendas[indice].id,
           encomendas[indice].retirada_em, encomendas[indice].retirado_por);
    return 1;
}
