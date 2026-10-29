#ifndef UTIL_H
#define UTIL_H

/*
 * util.h
 * Leitura segura do teclado, conversao validada de numeros, datas e
 * separacao de campos de arquivos CSV.
 */

/* Le uma linha do teclado (fgets) sem a quebra de linha. Retorna 1 ou 0 no fim da entrada. */
int util_ler_linha(const char *rotulo, char *dest, int tam);

/* Le um texto obrigatorio, sem ';' e em ASCII, com no maximo tam - 1 caracteres. */
int util_ler_texto(const char *rotulo, char *dest, int tam);

/* Le um inteiro entre minimo e maximo, repetindo ate ser valido. */
int util_ler_inteiro(const char *rotulo, int minimo, int maximo, int *valor);

/* Le uma letra que esteja em validos (maiuscula ou minuscula) e devolve em maiuscula. */
int util_ler_letra(const char *rotulo, const char *validos, char *letra);

/* Converte texto em inteiro validando formato e faixa. */
int util_converter_inteiro(const char *txt, int minimo, int maximo, int *saida);

/* Remove espacos (e CR/LF) do inicio e do fim do texto, no proprio texto. */
void util_aparar(char *texto);

/* Copia texto para dest sem estourar o tamanho tam. */
void util_copiar_texto(char *dest, int tam, const char *origem);

/* Divide a linha em campos separados por sep. Retorna o total de campos encontrados. */
int util_dividir_campos(char *linha, char sep, char *campos[], int max_campos);

/* Grava a data e hora atuais no formato "AAAA-MM-DD HH:MM". */
void util_data_hora_atual(char *dest, int tam);

/* Calcula os dias corridos entre duas datas "AAAA-MM-DD HH:MM". Retorna 1 ou 0 se invalida. */
int util_dias_entre(const char *inicio, const char *fim, int *dias);

#endif /* UTIL_H */
