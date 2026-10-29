#include <stdlib.h>
#include <time.h>

#include "tipos.h"
#include "codigo.h"

#define CODIGO_MAX_SORTEIOS 1000 /* limite de sorteios para nunca travar o programa */

/*
 * codigo_iniciar_aleatorio
 * Objetivo: variar a sequencia de codigos a cada execucao.
 * Parametros: nenhum.
 * Retorno: nenhum.
 * Logica: usa a hora atual como semente de srand.
 */
void codigo_iniciar_aleatorio(void)
{
    srand((unsigned int)time(NULL));
}

/*
 * codigo_valido
 * Objetivo: conferir se um numero e um codigo de 6 digitos.
 * Parametros: codigo = numero a conferir.
 * Retorno: 1 se esta entre CODIGO_MIN e CODIGO_MAX; 0 caso contrario.
 */
int codigo_valido(int codigo)
{
    return codigo >= CODIGO_MIN && codigo <= CODIGO_MAX;
}

/*
 * codigo_existe_pendente
 * Objetivo: saber se um codigo ja esta em uso por uma encomenda pendente.
 * Parametros: encomendas = vetor; quantidade = tamanho usado; codigo = numero
 *   procurado.
 * Retorno: 1 se existe; 0 se nao existe.
 * Logica: percorre o vetor e compara o codigo so das encomendas PENDENTES
 *   (codigo de encomenda ja retirada pode ser reutilizado).
 */
int codigo_existe_pendente(const Encomenda encomendas[], int quantidade, int codigo)
{
    int i;

    for (i = 0; i < quantidade; i++) {
        if (encomendas[i].status == STATUS_PENDENTE && encomendas[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

/*
 * codigo_sortear (auxiliar interna)
 * Objetivo: sortear um numero de CODIGO_MIN a CODIGO_MAX.
 * Parametros: nenhum.
 * Retorno: numero sorteado.
 * Logica: rand() garante so 15 bits (ate 32767) em alguns compiladores, o que
 *   daria poucos codigos diferentes; por isso combina duas chamadas para obter
 *   30 bits antes de reduzir a faixa.
 */
static int codigo_sortear(void)
{
    long bruto = (long)(rand() % 32768) * 32768L + (long)(rand() % 32768);

    return CODIGO_MIN + (int)(bruto % (CODIGO_MAX - CODIGO_MIN + 1));
}

/*
 * codigo_gerar_unico (algoritmo A2)
 * Objetivo: criar o codigo de retirada de uma nova encomenda.
 * Parametros: encomendas = vetor atual; quantidade = tamanho usado.
 * Retorno: codigo de 6 digitos ainda nao usado por pendente; 0 se esgotar as
 *   tentativas.
 * Logica: sorteia um numero e repete enquanto ele ja existir em alguma
 *   encomenda pendente, com um limite de tentativas.
 */
int codigo_gerar_unico(const Encomenda encomendas[], int quantidade)
{
    int tentativa;
    int codigo;

    for (tentativa = 0; tentativa < CODIGO_MAX_SORTEIOS; tentativa++) {
        codigo = codigo_sortear();
        if (!codigo_existe_pendente(encomendas, quantidade, codigo)) {
            return codigo;
        }
    }
    return 0;
}

/*
 * codigo_conferir
 * Objetivo: validar o codigo informado na retirada.
 * Parametros: digitado = numero informado; esperado = codigo da encomenda.
 * Retorno: 1 se forem iguais e validos; 0 caso contrario.
 */
int codigo_conferir(int digitado, int esperado)
{
    return codigo_valido(esperado) && digitado == esperado;
}
