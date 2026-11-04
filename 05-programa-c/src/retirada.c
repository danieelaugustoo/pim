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
 * retirada_buscar_codigo (auxiliar interna)
 * Objetivo: pedir o codigo de retirada e achar a encomenda pendente que o usa,
 *   com ate MAX_TENTATIVAS tentativas.
 * Parametros: encomendas = vetor; quantidade = tamanho usado.
 * Retorno: indice da encomenda no vetor; -1 se nenhuma tentativa serviu, se o
 *   codigo esta repetido entre pendentes ou se a entrada acabou.
 * Logica: laco de 1 a MAX_TENTATIVAS; le o codigo e procura entre as
 *   pendentes; a cada codigo sem encomenda avisa quantas tentativas restam. Se
 *   mais de uma pendente tem o codigo, nega a retirada (erro nos dados).
 */
static int retirada_buscar_codigo(const Encomenda encomendas[], int quantidade)
{
    int tentativa;
    int digitado;
    int indice;

    for (tentativa = 1; tentativa <= MAX_TENTATIVAS; tentativa++) {
        if (!util_ler_inteiro("Codigo de retirada (6 digitos): ", 0, CODIGO_MAX, &digitado)) {
            return -1;
        }
        indice = codigo_localizar_pendente(encomendas, quantidade, digitado);
        if (indice >= 0) {
            return indice;
        }
        if (indice == CODIGO_DUPLICADO) {
            printf("Codigo repetido em mais de uma pendente (erro nos dados). Retirada negada.\n");
            return -1;
        }
        printf("Nenhuma encomenda pendente com esse codigo (tentativa %d de %d).\n", tentativa,
               MAX_TENTATIVAS);
    }
    printf("Retirada negada: %d codigos sem encomenda pendente. Nenhuma encomenda foi alterada.\n",
           MAX_TENTATIVAS);
    return -1;
}

/*
 * retirada_confirmar (auxiliar interna)
 * Objetivo: fazer o porteiro conferir com o morador qual encomenda sera
 *   entregue, antes de registrar a retirada.
 * Parametros: encomenda = encomenda encontrada pelo codigo.
 * Retorno: 1 se o porteiro confirmou (S); 0 se recusou (N) ou a entrada acabou.
 * Logica: mostra a unidade, o destinatario e a posicao (sem o codigo) e le S ou
 *   N. A confirmacao evita entregar o volume de outra pessoa quando um codigo
 *   errado coincide com o de outra encomenda.
 */
static int retirada_confirmar(const Encomenda *encomenda)
{
    char resposta;

    encomenda_mostrar_uma(encomenda);
    if (!util_ler_letra("Confirme com o morador a unidade e o destinatario. Entregar esta encomenda? (S/N): ",
                        "SN", &resposta)) {
        return 0;
    }
    return resposta == 'S';
}

/*
 * retirada_registrar (algoritmo A3, interativo)
 * Objetivo: registrar a retirada de uma encomenda pelo morador.
 * Parametros: encomendas = vetor; quantidade = tamanho usado; estante =
 *   matriz de posicoes; indice = recebe a posicao da encomenda retirada no
 *   vetor (para o chamador enfileirar a operacao).
 * Retorno: 1 se a retirada foi registrada (o chamador deve salvar); 0 caso
 *   contrario.
 * Logica: se nao ha pendentes, avisa e volta; pede o codigo e acha a encomenda
 *   pendente que o usa (ate MAX_TENTATIVAS); mostra a encomenda e pede a
 *   confirmacao do porteiro; se confirmada, pede o nome de quem retira e
 *   aplica a retirada. Se o porteiro recusar, ou se todas as tentativas
 *   falharem, nada e alterado e a encomenda continua PENDENTE.
 */
int retirada_registrar(Encomenda encomendas[], int quantidade, int estante[][NUM_PRATELEIRAS],
                       int *indice)
{
    int escolhida;
    char nome[TAM_NOME];

    printf("\n--- Registrar retirada ---\n");
    if (encomenda_contar_pendentes(encomendas, quantidade) == 0) {
        printf("Nao ha encomendas pendentes nesta portaria.\n");
        return 0;
    }
    escolhida = retirada_buscar_codigo(encomendas, quantidade);
    if (escolhida < 0) {
        return 0;
    }
    if (!retirada_confirmar(&encomendas[escolhida])) {
        printf("Retirada cancelada. A encomenda continua pendente.\n");
        return 0;
    }
    if (!util_ler_texto("Nome de quem retira: ", nome, TAM_NOME)) {
        return 0;
    }
    retirada_efetuar(&encomendas[escolhida], estante, nome);
    printf("Retirada registrada: encomenda %d, em %s, por %s.\n", encomendas[escolhida].id,
           encomendas[escolhida].retirada_em, encomendas[escolhida].retirado_por);
    *indice = escolhida;
    return 1;
}
