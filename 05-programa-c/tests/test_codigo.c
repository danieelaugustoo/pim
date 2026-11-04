#include <stdio.h>
#include <assert.h>

#include "tipos.h"
#include "codigo.h"

/* O codigo gerado tem sempre 6 digitos. */
static void testar_seis_digitos(void)
{
    Encomenda v[1] = {{0}};
    int i;
    int c;

    codigo_iniciar_aleatorio();
    for (i = 0; i < 2000; i++) {
        c = codigo_gerar_unico(v, 0);
        assert(c >= 100000 && c <= 999999);
        assert(codigo_valido(c));
    }
    assert(!codigo_valido(99999));
    assert(!codigo_valido(1000000));
    assert(!codigo_valido(0));
}

/* Nenhum codigo novo repete o de uma encomenda pendente. */
static void testar_sem_repeticao(void)
{
    static Encomenda v[MAX_ENCOMENDAS];
    int n;
    int i;
    int j;

    for (n = 0; n < MAX_ENCOMENDAS; n++) {
        v[n].id = n + 1;
        v[n].status = STATUS_PENDENTE;
        v[n].codigo = codigo_gerar_unico(v, n);
        assert(v[n].codigo != 0);
    }
    for (i = 0; i < MAX_ENCOMENDAS; i++) {
        for (j = i + 1; j < MAX_ENCOMENDAS; j++) {
            assert(v[i].codigo != v[j].codigo);
        }
    }
}

/* Codigo de encomenda ja retirada nao conta como em uso. */
static void testar_existe_pendente(void)
{
    Encomenda v[2] = {{0}};

    v[0].status = STATUS_PENDENTE;
    v[0].codigo = 123456;
    v[1].status = STATUS_RETIRADA;
    v[1].codigo = 654321;

    assert(codigo_existe_pendente(v, 2, 123456) == 1);
    assert(codigo_existe_pendente(v, 2, 654321) == 0);
    assert(codigo_existe_pendente(v, 2, 111111) == 0);
    assert(codigo_existe_pendente(v, 0, 123456) == 0);
}

/* Conferencia certa e errada. */
static void testar_conferir(void)
{
    assert(codigo_conferir(123456, 123456) == 1);
    assert(codigo_conferir(123456, 654321) == 0);
    assert(codigo_conferir(0, 123456) == 0);
    assert(codigo_conferir(0, 0) == 0);
}

/* A3: a busca pelo codigo acha so encomenda pendente e avisa se nao ha ou se repete. */
static void testar_localizar_pendente(void)
{
    Encomenda v[4] = {{0}};

    v[0].status = STATUS_PENDENTE;
    v[0].codigo = 123456;
    v[1].status = STATUS_RETIRADA;
    v[1].codigo = 222222;
    v[2].status = STATUS_PENDENTE;
    v[2].codigo = 333333;
    v[3].status = STATUS_DEVOLVIDA;
    v[3].codigo = 444444;

    /* acha a pendente certa pelo indice */
    assert(codigo_localizar_pendente(v, 3, 123456) == 0);
    assert(codigo_localizar_pendente(v, 3, 333333) == 2);
    /* codigo que nao existe ou de encomenda ja retirada ou devolvida */
    assert(codigo_localizar_pendente(v, 4, 999999) == CODIGO_NAO_ENCONTRADO);
    assert(codigo_localizar_pendente(v, 4, 222222) == CODIGO_NAO_ENCONTRADO);
    assert(codigo_localizar_pendente(v, 4, 444444) == CODIGO_NAO_ENCONTRADO);
    /* numero fora da faixa de 6 digitos e vetor vazio */
    assert(codigo_localizar_pendente(v, 4, 0) == CODIGO_NAO_ENCONTRADO);
    assert(codigo_localizar_pendente(v, 4, 1000000) == CODIGO_NAO_ENCONTRADO);
    assert(codigo_localizar_pendente(v, 0, 123456) == CODIGO_NAO_ENCONTRADO);

    /* o codigo de uma retirada pode ser reutilizado por uma pendente: acha a pendente */
    v[1].codigo = 333333;
    assert(codigo_localizar_pendente(v, 4, 333333) == 2);
    /* duas pendentes com o mesmo codigo: erro nos dados */
    v[1].status = STATUS_PENDENTE;
    assert(codigo_localizar_pendente(v, 4, 333333) == CODIGO_DUPLICADO);
}

int main(void)
{
    testar_seis_digitos();
    testar_sem_repeticao();
    testar_existe_pendente();
    testar_conferir();
    testar_localizar_pendente();
    printf("test_codigo: OK\n");
    return 0;
}
