#include <stdio.h>
#include <string.h>

#include "tipos.h"
#include "util.h"
#include "encomenda.h"
#include "persistencia.h"

#define NUM_CAMPOS_ENCOMENDA 13

static const char CABECALHO_ENCOMENDAS[] =
    "id;bloco;apartamento;destinatario;transportadora;tamanho;recebida_em;"
    "estante;prateleira;codigo;status;retirada_em;retirado_por";

/*
 * persistencia_montar_caminho
 * Objetivo: montar o nome de um arquivo de dados da portaria.
 * Parametros: dest = recebe o caminho; tam = tamanho de dest; id_portaria =
 *   numero da portaria (1 a MAX_PORTARIAS); sufixo = parte final do nome.
 * Retorno: nenhum.
 * Logica: formata "dados/portarias/P01-encomendas.csv", por exemplo.
 */
void persistencia_montar_caminho(char *dest, int tam, int id_portaria, const char *sufixo)
{
    snprintf(dest, (size_t)tam, "dados/portarias/P%02d-%s", id_portaria, sufixo);
}

/*
 * persistencia_ler_linha_encomenda (auxiliar interna)
 * Objetivo: converter uma linha do CSV em uma Encomenda, validando cada campo.
 * Parametros: linha = texto da linha (e alterado); e = recebe os dados.
 * Retorno: 1 se a linha e valida; 0 se esta mal formada.
 * Logica: divide em 13 campos; converte e confere faixa de numeros, letras do
 *   bloco e do tamanho, status e codigo. Qualquer problema invalida a linha.
 */
static int persistencia_ler_linha_encomenda(char *linha, Encomenda *e)
{
    char *campos[NUM_CAMPOS_ENCOMENDA];
    int status_ok;
    int dias;

    if (util_dividir_campos(linha, ';', campos, NUM_CAMPOS_ENCOMENDA) != NUM_CAMPOS_ENCOMENDA) {
        return 0;
    }
    status_ok = encomenda_status_de_texto(campos[10], &e->status);
    if (!util_converter_inteiro(campos[0], 1, 999999, &e->id) ||
        strlen(campos[1]) != 1 || campos[1][0] < 'A' || campos[1][0] > 'Z' ||
        !util_converter_inteiro(campos[2], 1, APARTAMENTO_MAX, &e->apartamento) ||
        campos[3][0] == '\0' || campos[4][0] == '\0' ||
        strlen(campos[3]) >= TAM_NOME || strlen(campos[4]) >= TAM_TRANSPORTADORA ||
        strlen(campos[5]) != 1 || strchr("PMG", campos[5][0]) == NULL ||
        !util_dias_entre(campos[6], campos[6], &dias) ||
        !util_converter_inteiro(campos[7], 0, NUM_ESTANTES - 1, &e->estante) ||
        !util_converter_inteiro(campos[8], 0, NUM_PRATELEIRAS - 1, &e->prateleira) ||
        !util_converter_inteiro(campos[9], CODIGO_MIN, CODIGO_MAX, &e->codigo) ||
        !status_ok || strlen(campos[11]) >= TAM_DATA || strlen(campos[12]) >= TAM_NOME) {
        return 0;
    }
    e->bloco = campos[1][0];
    e->tamanho = campos[5][0];
    util_copiar_texto(e->destinatario, TAM_NOME, campos[3]);
    util_copiar_texto(e->transportadora, TAM_TRANSPORTADORA, campos[4]);
    util_copiar_texto(e->recebida_em, TAM_DATA, campos[6]);
    util_copiar_texto(e->retirada_em, TAM_DATA, campos[11]);
    util_copiar_texto(e->retirado_por, TAM_NOME, campos[12]);
    return 1;
}

/*
 * persistencia_criar_arquivo (auxiliar interna)
 * Objetivo: criar um arquivo de encomendas vazio, so com o cabecalho.
 * Parametros: caminho = arquivo a criar.
 * Retorno: PERSIST_OK ou PERSIST_ERRO.
 */
static int persistencia_criar_arquivo(const char *caminho)
{
    FILE *arq = fopen(caminho, "w");

    if (arq == NULL) {
        return PERSIST_ERRO;
    }
    fprintf(arq, "%s\n", CABECALHO_ENCOMENDAS);
    return fclose(arq) == 0 ? PERSIST_OK : PERSIST_ERRO;
}

/*
 * persistencia_carregar_encomendas
 * Objetivo: ler as encomendas gravadas, para nao perder registros ao fechar
 *   o programa (US06).
 * Parametros: caminho = arquivo CSV; encomendas = vetor que recebe os dados;
 *   maximo = capacidade do vetor; quantidade = recebe quantas foram lidas.
 * Retorno: PERSIST_OK ou PERSIST_ERRO (nao foi possivel abrir nem criar).
 * Logica: se o arquivo nao existe, cria com o cabecalho (primeira execucao).
 *   Senao, pula o cabecalho e le linha a linha; linhas vazias sao ignoradas e
 *   linhas invalidas sao ignoradas com um aviso.
 */
int persistencia_carregar_encomendas(const char *caminho, Encomenda encomendas[], int maximo,
                                     int *quantidade)
{
    FILE *arq;
    char linha[TAM_LINHA];
    int numero_linha = 1;

    *quantidade = 0;
    arq = fopen(caminho, "r");
    if (arq == NULL) {
        return persistencia_criar_arquivo(caminho);
    }
    if (fgets(linha, TAM_LINHA, arq) == NULL) {
        fclose(arq);
        return PERSIST_OK;
    }
    while (fgets(linha, TAM_LINHA, arq) != NULL) {
        numero_linha++;
        util_aparar(linha);
        if (linha[0] == '\0') {
            continue;
        }
        if (*quantidade >= maximo) {
            printf("Aviso: limite de %d encomendas; restante de %s ignorado.\n", maximo, caminho);
            break;
        }
        if (persistencia_ler_linha_encomenda(linha, &encomendas[*quantidade])) {
            (*quantidade)++;
        } else {
            printf("Aviso: linha %d de %s ignorada (formato invalido).\n", numero_linha, caminho);
        }
    }
    fclose(arq);
    return PERSIST_OK;
}

/*
 * persistencia_salvar_encomendas
 * Objetivo: gravar todas as encomendas no arquivo CSV.
 * Parametros: caminho = arquivo; encomendas = vetor; quantidade = tamanho usado.
 * Retorno: PERSIST_OK ou PERSIST_ERRO.
 * Logica: abre o arquivo para escrita (apaga o anterior), grava o cabecalho e
 *   uma linha por encomenda, com o codigo sempre em 6 digitos.
 */
int persistencia_salvar_encomendas(const char *caminho, const Encomenda encomendas[], int quantidade)
{
    FILE *arq = fopen(caminho, "w");
    int i;
    const Encomenda *e;

    if (arq == NULL) {
        return PERSIST_ERRO;
    }
    fprintf(arq, "%s\n", CABECALHO_ENCOMENDAS);
    for (i = 0; i < quantidade; i++) {
        e = &encomendas[i];
        fprintf(arq, "%d;%c;%d;%s;%s;%c;%s;%d;%d;%0*d;%s;%s;%s\n", e->id, e->bloco,
                e->apartamento, e->destinatario, e->transportadora, e->tamanho, e->recebida_em,
                e->estante, e->prateleira, TAM_CODIGO, e->codigo,
                encomenda_status_texto(e->status), e->retirada_em, e->retirado_por);
    }
    return fclose(arq) == 0 ? PERSIST_OK : PERSIST_ERRO;
}
