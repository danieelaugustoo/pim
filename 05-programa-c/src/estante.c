#include <ctype.h>

#include "tipos.h"
#include "estante.h"

/*
 * estante_iniciar
 * Objetivo: deixar a estante vazia.
 * Parametros: estante = matriz de posicoes.
 * Retorno: nenhum.
 * Logica: percorre linhas e colunas colocando 0 (livre) em cada celula.
 */
void estante_iniciar(int estante[][NUM_PRATELEIRAS])
{
    int i;
    int j;

    for (i = 0; i < NUM_ESTANTES; i++) {
        for (j = 0; j < NUM_PRATELEIRAS; j++) {
            estante[i][j] = 0;
        }
    }
}

/*
 * estante_faixa (auxiliar interna)
 * Objetivo: dizer quais prateleiras cada tamanho de volume pode usar.
 * Parametros: tamanho = 'P', 'M' ou 'G'; inicio e fim = recebem a faixa
 *   [inicio, fim).
 * Retorno: nenhum.
 * Logica: volumes G usam da prateleira PRATELEIRA_INICIAL_G em diante; P e M
 *   usam as anteriores.
 */
static void estante_faixa(char tamanho, int *inicio, int *fim)
{
    if (tamanho == 'G') {
        *inicio = PRATELEIRA_INICIAL_G;
        *fim = NUM_PRATELEIRAS;
    } else {
        *inicio = 0;
        *fim = PRATELEIRA_INICIAL_G;
    }
}

/*
 * estante_procurar_livre (auxiliar interna)
 * Objetivo: achar a primeira prateleira livre de uma estante dentro de uma faixa.
 * Parametros: estante = matriz; linha = estante a varrer; inicio e fim = faixa
 *   de prateleiras [inicio, fim).
 * Retorno: indice da prateleira livre, ou -1 se nao houver.
 * Logica: varre a linha da esquerda para a direita e para na primeira celula 0.
 */
static int estante_procurar_livre(int estante[][NUM_PRATELEIRAS], int linha, int inicio, int fim)
{
    int j;

    for (j = inicio; j < fim; j++) {
        if (estante[linha][j] == 0) {
            return j;
        }
    }
    return -1;
}

/*
 * estante_alocar_posicao (algoritmo A1)
 * Objetivo: indicar onde guardar um volume.
 * Parametros: estante = matriz; bloco = letra do bloco da unidade; tamanho =
 *   'P', 'M' ou 'G'; id_encomenda = id gravado na posicao escolhida; linha e
 *   coluna = recebem a posicao.
 * Retorno: 1 se achou posicao (ja marcada como ocupada); 0 se nao ha vaga.
 * Logica: a estante preferida e a posicao do bloco no alfabeto (A = 0, B = 1,
 *   ...) modulo NUM_ESTANTES. Procura a primeira prateleira livre da faixa do
 *   tamanho nessa estante; se estiver cheia, tenta as proximas estantes em
 *   ordem circular; se todas estiverem cheias, retorna 0.
 */
int estante_alocar_posicao(int estante[][NUM_PRATELEIRAS], char bloco, char tamanho,
                           int id_encomenda, int *linha, int *coluna)
{
    int preferida = 0;
    int inicio;
    int fim;
    int k;
    int candidata;
    int prateleira;

    if (isalpha((unsigned char)bloco)) {
        preferida = (toupper((unsigned char)bloco) - 'A') % NUM_ESTANTES;
    }
    estante_faixa(tamanho, &inicio, &fim);
    for (k = 0; k < NUM_ESTANTES; k++) {
        candidata = (preferida + k) % NUM_ESTANTES;
        prateleira = estante_procurar_livre(estante, candidata, inicio, fim);
        if (prateleira >= 0) {
            estante[candidata][prateleira] = id_encomenda;
            *linha = candidata;
            *coluna = prateleira;
            return 1;
        }
    }
    return 0;
}

/*
 * estante_liberar_posicao
 * Objetivo: marcar uma posicao como livre depois da retirada.
 * Parametros: estante = matriz; linha e coluna = posicao a liberar.
 * Retorno: nenhum.
 * Logica: confere se a posicao existe e coloca 0 nela.
 */
void estante_liberar_posicao(int estante[][NUM_PRATELEIRAS], int linha, int coluna)
{
    if (linha >= 0 && linha < NUM_ESTANTES && coluna >= 0 && coluna < NUM_PRATELEIRAS) {
        estante[linha][coluna] = 0;
    }
}

/*
 * estante_reconstruir
 * Objetivo: remontar a matriz ao abrir o programa, usando so as encomendas
 *   pendentes (a matriz nao tem arquivo proprio: ha uma unica fonte de verdade).
 * Parametros: estante = matriz; encomendas = vetor carregado do arquivo;
 *   quantidade = quantas encomendas ha no vetor.
 * Retorno: quantas posicoes foram ocupadas.
 * Logica: limpa a matriz e, para cada encomenda pendente com posicao valida e
 *   livre, grava o id da encomenda na posicao.
 */
int estante_reconstruir(int estante[][NUM_PRATELEIRAS], const Encomenda encomendas[], int quantidade)
{
    int i;
    int ocupadas = 0;
    int l;
    int c;

    estante_iniciar(estante);
    for (i = 0; i < quantidade; i++) {
        l = encomendas[i].estante;
        c = encomendas[i].prateleira;
        if (encomendas[i].status == STATUS_PENDENTE &&
            l >= 0 && l < NUM_ESTANTES && c >= 0 && c < NUM_PRATELEIRAS &&
            estante[l][c] == 0) {
            estante[l][c] = encomendas[i].id;
            ocupadas++;
        }
    }
    return ocupadas;
}

/*
 * estante_ocupacao
 * Objetivo: contar quantas posicoes estao ocupadas.
 * Parametros: estante = matriz.
 * Retorno: numero de posicoes ocupadas.
 * Logica: percorre a matriz e conta as celulas diferentes de 0.
 */
int estante_ocupacao(int estante[][NUM_PRATELEIRAS])
{
    int i;
    int j;
    int total = 0;

    for (i = 0; i < NUM_ESTANTES; i++) {
        for (j = 0; j < NUM_PRATELEIRAS; j++) {
            if (estante[i][j] != 0) {
                total++;
            }
        }
    }
    return total;
}
