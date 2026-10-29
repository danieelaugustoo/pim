#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "tipos.h"
#include "util.h"

/*
 * util_ler_linha
 * Objetivo: ler uma linha do teclado com fgets, sem a quebra de linha.
 * Parametros: rotulo = texto mostrado antes da leitura; dest = area que
 *   recebe a linha; tam = tamanho de dest.
 * Retorno: 1 se leu uma linha; 0 se a entrada acabou (fim de arquivo).
 * Logica: mostra o rotulo, chama fgets, remove o '\n'; se a linha for maior
 *   que o espaco disponivel, descarta o restante dela para nao contaminar a
 *   proxima leitura.
 */
int util_ler_linha(const char *rotulo, char *dest, int tam)
{
    size_t n;
    int c;

    printf("%s", rotulo);
    fflush(stdout);
    if (fgets(dest, tam, stdin) == NULL) {
        return 0;
    }
    n = strlen(dest);
    if (n > 0 && dest[n - 1] == '\n') {
        dest[n - 1] = '\0';
    } else {
        while ((c = getchar()) != '\n' && c != EOF) {
            /* descarta o que sobrou da linha */
        }
    }
    return 1;
}

/*
 * util_aparar
 * Objetivo: tirar espacos, tabs e quebras de linha das pontas do texto.
 * Parametros: texto = texto alterado no proprio lugar.
 * Retorno: nenhum.
 * Logica: acha o primeiro caractere util, acha o ultimo, e desloca o trecho
 *   para o inicio do vetor.
 */
void util_aparar(char *texto)
{
    char *inicio = texto;
    size_t n;

    while (*inicio != '\0' && isspace((unsigned char)*inicio)) {
        inicio++;
    }
    n = strlen(inicio);
    while (n > 0 && isspace((unsigned char)inicio[n - 1])) {
        n--;
    }
    memmove(texto, inicio, n);
    texto[n] = '\0';
}

/*
 * util_copiar_texto
 * Objetivo: copiar texto com seguranca, sem passar do tamanho de dest.
 * Parametros: dest = destino; tam = tamanho de dest; origem = texto de origem.
 * Retorno: nenhum.
 * Logica: usa snprintf, que sempre termina o texto com '\0'.
 */
void util_copiar_texto(char *dest, int tam, const char *origem)
{
    snprintf(dest, (size_t)tam, "%s", origem);
}

/*
 * util_converter_inteiro
 * Objetivo: converter texto em inteiro validando o formato e a faixa.
 * Parametros: txt = texto digitado; minimo e maximo = faixa aceita;
 *   saida = recebe o valor convertido.
 * Retorno: 1 se o texto e um inteiro valido dentro da faixa; 0 caso contrario.
 * Logica: pula espacos, aceita um sinal, le os digitos acumulando o valor
 *   (no maximo 9 digitos, para nao estourar o int), aceita so espacos no fim
 *   e confere a faixa.
 */
int util_converter_inteiro(const char *txt, int minimo, int maximo, int *saida)
{
    const char *p = txt;
    long valor = 0;
    int sinal = 1;
    int digitos = 0;

    while (isspace((unsigned char)*p)) {
        p++;
    }
    if (*p == '-') {
        sinal = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }
    while (isdigit((unsigned char)*p)) {
        valor = valor * 10 + (*p - '0');
        digitos++;
        if (digitos > 9) {
            return 0;
        }
        p++;
    }
    if (digitos == 0) {
        return 0;
    }
    while (isspace((unsigned char)*p)) {
        p++;
    }
    if (*p != '\0') {
        return 0;
    }
    valor = valor * sinal;
    if (valor < minimo || valor > maximo) {
        return 0;
    }
    *saida = (int)valor;
    return 1;
}

/*
 * util_ler_texto
 * Objetivo: ler um texto obrigatorio que possa ser gravado no CSV.
 * Parametros: rotulo = pergunta; dest = area que recebe o texto; tam = tamanho
 *   de dest (inclui o '\0').
 * Retorno: 1 se leu um texto valido; 0 se a entrada acabou.
 * Logica: repete ate o texto (sem espacos nas pontas) ser nao vazio, caber em
 *   dest, nao conter ';' e usar so caracteres ASCII imprimiveis.
 */
int util_ler_texto(const char *rotulo, char *dest, int tam)
{
    char linha[TAM_LINHA];
    size_t i;
    int valido;

    for (;;) {
        if (!util_ler_linha(rotulo, linha, TAM_LINHA)) {
            return 0;
        }
        util_aparar(linha);
        valido = 1;
        if (linha[0] == '\0') {
            printf("Campo obrigatorio.\n");
            valido = 0;
        } else if ((int)strlen(linha) >= tam) {
            printf("Texto muito longo (maximo %d caracteres).\n", tam - 1);
            valido = 0;
        } else {
            for (i = 0; linha[i] != '\0'; i++) {
                unsigned char c = (unsigned char)linha[i];
                if (c == ';' || c < 32 || c > 126) {
                    printf("Use apenas letras sem acento, numeros e pontuacao simples (sem ';').\n");
                    valido = 0;
                    break;
                }
            }
        }
        if (valido) {
            util_copiar_texto(dest, tam, linha);
            return 1;
        }
    }
}

/*
 * util_ler_inteiro
 * Objetivo: ler um numero inteiro dentro de uma faixa.
 * Parametros: rotulo = pergunta; minimo e maximo = faixa aceita; valor =
 *   recebe o numero.
 * Retorno: 1 se leu um numero valido; 0 se a entrada acabou.
 * Logica: le uma linha e tenta converter; se falhar, avisa e repete.
 */
int util_ler_inteiro(const char *rotulo, int minimo, int maximo, int *valor)
{
    char linha[TAM_LINHA];

    for (;;) {
        if (!util_ler_linha(rotulo, linha, TAM_LINHA)) {
            return 0;
        }
        if (util_converter_inteiro(linha, minimo, maximo, valor)) {
            return 1;
        }
        printf("Valor invalido. Digite um numero entre %d e %d.\n", minimo, maximo);
    }
}

/*
 * util_ler_letra
 * Objetivo: ler uma unica letra entre as permitidas.
 * Parametros: rotulo = pergunta; validos = letras maiusculas aceitas (ex.:
 *   "PMG"); letra = recebe a letra em maiuscula.
 * Retorno: 1 se leu uma letra valida; 0 se a entrada acabou.
 * Logica: le a linha, exige exatamente um caractere, converte para maiuscula
 *   e confere se esta em validos; repete se nao estiver.
 */
int util_ler_letra(const char *rotulo, const char *validos, char *letra)
{
    char linha[TAM_LINHA];
    char c;

    for (;;) {
        if (!util_ler_linha(rotulo, linha, TAM_LINHA)) {
            return 0;
        }
        util_aparar(linha);
        if (strlen(linha) == 1) {
            c = (char)toupper((unsigned char)linha[0]);
            if (strchr(validos, c) != NULL) {
                *letra = c;
                return 1;
            }
        }
        printf("Opcao invalida. Valores aceitos: %s\n", validos);
    }
}

/*
 * util_dividir_campos
 * Objetivo: separar uma linha de CSV em campos, inclusive campos vazios.
 * Parametros: linha = texto alterado no proprio lugar (cada separador vira
 *   '\0'); sep = caractere separador; campos = vetor que recebe o inicio de
 *   cada campo; max_campos = tamanho de campos.
 * Retorno: total de campos encontrados (pode ser maior que max_campos; so os
 *   primeiros max_campos sao guardados).
 * Logica: percorre o texto; a cada separador troca por '\0' e comeca um novo
 *   campo. strtok nao serve porque ignora campos vazios.
 */
int util_dividir_campos(char *linha, char sep, char *campos[], int max_campos)
{
    int total = 0;
    char *p = linha;

    if (max_campos > 0) {
        campos[0] = p;
    }
    total = 1;
    while (*p != '\0') {
        if (*p == sep) {
            *p = '\0';
            if (total < max_campos) {
                campos[total] = p + 1;
            }
            total++;
        }
        p++;
    }
    return total;
}

/*
 * util_data_hora_atual
 * Objetivo: obter a data e a hora do relogio no formato do sistema.
 * Parametros: dest = area que recebe "AAAA-MM-DD HH:MM"; tam = tamanho de dest
 *   (use TAM_DATA).
 * Retorno: nenhum.
 * Logica: time + localtime + strftime; se algo falhar, grava uma data zerada.
 */
void util_data_hora_atual(char *dest, int tam)
{
    time_t agora = time(NULL);
    struct tm *info = localtime(&agora);

    if (info == NULL || strftime(dest, (size_t)tam, "%Y-%m-%d %H:%M", info) == 0) {
        util_copiar_texto(dest, tam, "0000-00-00 00:00");
    }
}

/*
 * util_dias_no_mes (auxiliar interna)
 * Objetivo: informar quantos dias tem um mes, considerando ano bissexto.
 * Parametros: ano e mes (1 a 12).
 * Retorno: numero de dias do mes.
 */
static int util_dias_no_mes(int ano, int mes)
{
    static const int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);

    if (mes == 2 && bissexto) {
        return 29;
    }
    return dias[mes - 1];
}

/*
 * util_interpretar_data (auxiliar interna)
 * Objetivo: validar o texto "AAAA-MM-DD HH:MM" e extrair ano, mes e dia.
 * Parametros: txt = texto; ano, mes, dia = recebem os valores.
 * Retorno: 1 se o texto e uma data valida; 0 caso contrario.
 * Logica: confere tamanho 16, separadores nas posicoes certas e digitos nas
 *   demais; converte com sscanf e confere mes, dia, hora e minuto.
 */
static int util_interpretar_data(const char *txt, int *ano, int *mes, int *dia)
{
    int i;
    int hora;
    int minuto;

    if (strlen(txt) != 16) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        if (i == 4 || i == 7) {
            if (txt[i] != '-') {
                return 0;
            }
        } else if (i == 10) {
            if (txt[i] != ' ') {
                return 0;
            }
        } else if (i == 13) {
            if (txt[i] != ':') {
                return 0;
            }
        } else if (!isdigit((unsigned char)txt[i])) {
            return 0;
        }
    }
    if (sscanf(txt, "%d-%d-%d %d:%d", ano, mes, dia, &hora, &minuto) != 5) {
        return 0;
    }
    if (*mes < 1 || *mes > 12 || *dia < 1 || *dia > util_dias_no_mes(*ano, *mes)) {
        return 0;
    }
    return hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59;
}

/*
 * util_dias_desde_epoca (auxiliar interna)
 * Objetivo: converter uma data em um numero de dias corridos, para poder
 *   subtrair duas datas.
 * Parametros: ano, mes e dia validos.
 * Retorno: dias corridos desde 1970-01-01 (calendario gregoriano).
 * Logica: algoritmo de contagem de dias por eras de 400 anos, com o ano
 *   comecando em marco para o dia 29 de fevereiro ficar no fim do ano.
 */
static long util_dias_desde_epoca(int ano, int mes, int dia)
{
    long a = ano - (mes <= 2 ? 1 : 0);
    long era = (a >= 0 ? a : a - 399) / 400;
    long ano_da_era = a - era * 400;
    long dia_do_ano = (153L * (mes + (mes > 2 ? -3 : 9)) + 2) / 5 + dia - 1;
    long dia_da_era = ano_da_era * 365 + ano_da_era / 4 - ano_da_era / 100 + dia_do_ano;

    return era * 146097 + dia_da_era - 719468;
}

/*
 * util_dias_entre
 * Objetivo: calcular quantos dias corridos separam duas datas.
 * Parametros: inicio e fim = datas "AAAA-MM-DD HH:MM"; dias = recebe
 *   (fim - inicio), que e negativo se fim for anterior a inicio.
 * Retorno: 1 se as duas datas sao validas; 0 caso contrario.
 * Logica: valida e converte cada data em dias corridos e subtrai. A hora nao
 *   entra na conta: conta-se por dia do calendario.
 */
int util_dias_entre(const char *inicio, const char *fim, int *dias)
{
    int a1, m1, d1, a2, m2, d2;

    if (!util_interpretar_data(inicio, &a1, &m1, &d1) ||
        !util_interpretar_data(fim, &a2, &m2, &d2)) {
        return 0;
    }
    *dias = (int)(util_dias_desde_epoca(a2, m2, d2) - util_dias_desde_epoca(a1, m1, d1));
    return 1;
}
