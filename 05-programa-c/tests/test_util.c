#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tipos.h"
#include "util.h"

/* Testa a diferenca em dias entre datas. */
static void testar_dias_entre(void)
{
    int dias = -99;

    assert(util_dias_entre("2026-10-29 10:00", "2026-10-29 23:59", &dias) == 1);
    assert(dias == 0);
    assert(util_dias_entre("2026-10-22 09:00", "2026-10-29 08:00", &dias) == 1);
    assert(dias == 7);
    assert(util_dias_entre("2026-10-30 09:00", "2026-11-02 09:00", &dias) == 1);
    assert(dias == 3);
    assert(util_dias_entre("2026-12-30 09:00", "2027-01-02 09:00", &dias) == 1);
    assert(dias == 3);
    /* ano bissexto: 2028 tem 29 de fevereiro */
    assert(util_dias_entre("2028-02-28 12:00", "2028-03-01 12:00", &dias) == 1);
    assert(dias == 2);
    assert(util_dias_entre("2026-02-28 12:00", "2026-03-01 12:00", &dias) == 1);
    assert(dias == 1);
    /* data final anterior: resultado negativo */
    assert(util_dias_entre("2026-10-29 09:00", "2026-10-27 09:00", &dias) == 1);
    assert(dias == -2);
    /* datas invalidas */
    assert(util_dias_entre("2026-13-01 09:00", "2026-10-27 09:00", &dias) == 0);
    assert(util_dias_entre("2026-02-30 09:00", "2026-03-01 09:00", &dias) == 0);
    assert(util_dias_entre("2026-10-27", "2026-10-28 09:00", &dias) == 0);
    assert(util_dias_entre("abcd-ef-gh ij:kl", "2026-10-28 09:00", &dias) == 0);
    assert(util_dias_entre("2026-10-27 25:00", "2026-10-28 09:00", &dias) == 0);
}

/* Testa a conversao validada de inteiros. */
static void testar_converter_inteiro(void)
{
    int v = 0;

    assert(util_converter_inteiro("42", 0, 100, &v) == 1 && v == 42);
    assert(util_converter_inteiro("  7  ", 0, 100, &v) == 1 && v == 7);
    assert(util_converter_inteiro("-5", -10, 10, &v) == 1 && v == -5);
    assert(util_converter_inteiro("", 0, 100, &v) == 0);
    assert(util_converter_inteiro("abc", 0, 100, &v) == 0);
    assert(util_converter_inteiro("12x", 0, 100, &v) == 0);
    assert(util_converter_inteiro("1 2", 0, 100, &v) == 0);
    assert(util_converter_inteiro("101", 0, 100, &v) == 0);
    assert(util_converter_inteiro("-1", 0, 100, &v) == 0);
    assert(util_converter_inteiro("99999999999", 0, 2000000000, &v) == 0);
}

/* Testa a separacao de campos, inclusive campos vazios. */
static void testar_dividir_campos(void)
{
    char linha1[] = "a;b;;d";
    char linha2[] = "1;2;3";
    char linha3[] = ";;";
    char *campos[4];

    assert(util_dividir_campos(linha1, ';', campos, 4) == 4);
    assert(strcmp(campos[0], "a") == 0);
    assert(strcmp(campos[1], "b") == 0);
    assert(strcmp(campos[2], "") == 0);
    assert(strcmp(campos[3], "d") == 0);

    assert(util_dividir_campos(linha2, ';', campos, 4) == 3);
    assert(util_dividir_campos(linha3, ';', campos, 4) == 3);

    /* mais campos do que o vetor comporta: o total indica o excesso */
    {
        char linha4[] = "1;2;3;4;5";
        assert(util_dividir_campos(linha4, ';', campos, 4) == 5);
    }
}

/* Testa a limpeza de espacos nas pontas. */
static void testar_aparar(void)
{
    char t1[] = "  ola mundo \r\n";
    char t2[] = "   ";
    char t3[] = "sem espacos";

    util_aparar(t1);
    util_aparar(t2);
    util_aparar(t3);
    assert(strcmp(t1, "ola mundo") == 0);
    assert(strcmp(t2, "") == 0);
    assert(strcmp(t3, "sem espacos") == 0);
}

/* Testa o formato da data e hora atuais. */
static void testar_data_hora_atual(void)
{
    char data[TAM_DATA];
    int dias = -1;

    util_data_hora_atual(data, TAM_DATA);
    assert(strlen(data) == 16);
    assert(util_dias_entre(data, data, &dias) == 1 && dias == 0);
}

int main(void)
{
    testar_dias_entre();
    testar_converter_inteiro();
    testar_dividir_campos();
    testar_aparar();
    testar_data_hora_atual();
    printf("test_util: OK\n");
    return 0;
}
