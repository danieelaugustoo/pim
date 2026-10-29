#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tipos.h"
#include "util.h"
#include "sincronizacao.h"

#define NUM_CAMPOS_OPERACAO 7
#define MAX_NUMERO_OPERACAO 999999

static const char CABECALHO_OPERACOES[] =
    "id_operacao;id_portaria;data_hora;tipo;id_encomenda;bloco;apartamento";

/*
 * sincronizacao_tipo_texto
 * Objetivo: obter o nome do tipo de operacao para gravar em arquivo.
 * Parametros: tipo = valor do enum.
 * Retorno: "REGISTRO", "RETIRADA" ou "DEVOLUCAO".
 */
const char *sincronizacao_tipo_texto(TipoOperacao tipo)
{
    switch (tipo) {
    case OP_REGISTRO:
        return "REGISTRO";
    case OP_RETIRADA:
        return "RETIRADA";
    case OP_DEVOLUCAO:
        return "DEVOLUCAO";
    }
    return "REGISTRO";
}

/*
 * sincronizacao_tipo_de_texto
 * Objetivo: converter o texto lido do arquivo em tipo de operacao.
 * Parametros: texto = nome do tipo; tipo = recebe o valor.
 * Retorno: 1 se o texto e conhecido; 0 caso contrario.
 */
int sincronizacao_tipo_de_texto(const char *texto, TipoOperacao *tipo)
{
    if (strcmp(texto, "REGISTRO") == 0) {
        *tipo = OP_REGISTRO;
    } else if (strcmp(texto, "RETIRADA") == 0) {
        *tipo = OP_RETIRADA;
    } else if (strcmp(texto, "DEVOLUCAO") == 0) {
        *tipo = OP_DEVOLUCAO;
    } else {
        return 0;
    }
    return 1;
}

/*
 * sincronizacao_montar_id
 * Objetivo: montar o id unico de uma operacao.
 * Parametros: dest = recebe o id; tam = tamanho de dest (use TAM_ID_OPERACAO);
 *   id_portaria = 1 a MAX_PORTARIAS; numero = sequencia da portaria.
 * Retorno: nenhum.
 * Logica: formata "P01-000123". O id e unico no sistema todo porque junta a
 *   portaria com a sequencia dela.
 */
void sincronizacao_montar_id(char *dest, int tam, int id_portaria, int numero)
{
    snprintf(dest, (size_t)tam, "P%02d-%06d", id_portaria, numero);
}

/*
 * sincronizacao_operacao_para_linha
 * Objetivo: escrever uma operacao no formato do arquivo da fila e da rede.
 * Parametros: operacao = dados; dest = recebe a linha; tam = tamanho de dest.
 * Retorno: nenhum.
 */
void sincronizacao_operacao_para_linha(const Operacao *operacao, char *dest, int tam)
{
    snprintf(dest, (size_t)tam, "%s;%d;%s;%s;%d;%c;%d", operacao->id_operacao,
             operacao->id_portaria, operacao->data_hora, sincronizacao_tipo_texto(operacao->tipo),
             operacao->id_encomenda, operacao->bloco, operacao->apartamento);
}

/*
 * sincronizacao_id_valido (auxiliar interna)
 * Objetivo: conferir se o id tem o formato "Pnn-NNNNNN" e se o "nn" e o
 *   numero da portaria informado.
 * Parametros: id = texto do id; id_portaria = portaria da operacao.
 * Retorno: 1 se valido; 0 caso contrario.
 */
static int sincronizacao_id_valido(const char *id, int id_portaria)
{
    int i;
    int numero_portaria;

    if (strlen(id) != 10 || id[0] != 'P' || id[3] != '-') {
        return 0;
    }
    for (i = 1; i < 10; i++) {
        if (i != 3 && !isdigit((unsigned char)id[i])) {
            return 0;
        }
    }
    numero_portaria = (id[1] - '0') * 10 + (id[2] - '0');
    return numero_portaria == id_portaria;
}

/*
 * sincronizacao_operacao_de_linha
 * Objetivo: ler uma linha da fila ou do log da rede, validando cada campo.
 * Parametros: linha = texto (e alterado); operacao = recebe os dados.
 * Retorno: 1 se a linha e valida; 0 se esta mal formada.
 * Logica: divide em 7 campos; confere portaria, formato do id (que precisa
 *   combinar com a portaria), data, tipo, id da encomenda, bloco e apartamento.
 */
int sincronizacao_operacao_de_linha(char *linha, Operacao *operacao)
{
    char *campos[NUM_CAMPOS_OPERACAO];
    int bloco_ok;
    int dias;

    if (util_dividir_campos(linha, ';', campos, NUM_CAMPOS_OPERACAO) != NUM_CAMPOS_OPERACAO) {
        return 0;
    }
    bloco_ok = strlen(campos[5]) == 1 && campos[5][0] >= 'A' && campos[5][0] <= 'Z';
    if (!util_converter_inteiro(campos[1], 1, MAX_PORTARIAS, &operacao->id_portaria) ||
        !sincronizacao_id_valido(campos[0], operacao->id_portaria) ||
        !util_dias_entre(campos[2], campos[2], &dias) ||
        !sincronizacao_tipo_de_texto(campos[3], &operacao->tipo) ||
        !util_converter_inteiro(campos[4], 1, 999999, &operacao->id_encomenda) ||
        !bloco_ok ||
        !util_converter_inteiro(campos[6], 1, APARTAMENTO_MAX, &operacao->apartamento)) {
        return 0;
    }
    util_copiar_texto(operacao->id_operacao, TAM_ID_OPERACAO, campos[0]);
    util_copiar_texto(operacao->data_hora, TAM_DATA, campos[2]);
    operacao->bloco = campos[5][0];
    return 1;
}

/*
 * sincronizacao_proximo_numero
 * Objetivo: gerar o proximo numero de operacao da portaria, que nunca se
 *   repete nem depois de fechar e abrir o programa (US10).
 * Parametros: caminho_sequencia = arquivo com o ultimo numero usado.
 * Retorno: o novo numero (1 a 999999), ou 0 em caso de erro.
 * Logica: le o ultimo numero (arquivo ausente conta como 0), soma 1 e grava.
 *   Se o arquivo existir mas estiver corrompido, devolve erro em vez de
 *   recomecar de 1, o que geraria ids repetidos.
 */
int sincronizacao_proximo_numero(const char *caminho_sequencia)
{
    FILE *arq;
    char linha[64];
    int atual = 0;

    arq = fopen(caminho_sequencia, "r");
    if (arq != NULL) {
        if (fgets(linha, sizeof linha, arq) != NULL) {
            util_aparar(linha);
            if (linha[0] != '\0' && !util_converter_inteiro(linha, 0, MAX_NUMERO_OPERACAO, &atual)) {
                fclose(arq);
                return 0;
            }
        }
        fclose(arq);
    }
    if (atual >= MAX_NUMERO_OPERACAO) {
        return 0;
    }
    atual++;
    arq = fopen(caminho_sequencia, "w");
    if (arq == NULL) {
        return 0;
    }
    fprintf(arq, "%d\n", atual);
    return fclose(arq) == 0 ? atual : 0;
}

/*
 * sincronizacao_criar_se_ausente (auxiliar interna)
 * Objetivo: garantir que um arquivo de operacoes exista, com o cabecalho.
 * Parametros: caminho = arquivo.
 * Retorno: 1 se o arquivo existe ou foi criado; 0 se falhou.
 */
static int sincronizacao_criar_se_ausente(const char *caminho)
{
    FILE *arq = fopen(caminho, "r");

    if (arq != NULL) {
        fclose(arq);
        return 1;
    }
    arq = fopen(caminho, "w");
    if (arq == NULL) {
        return 0;
    }
    fprintf(arq, "%s\n", CABECALHO_OPERACOES);
    return fclose(arq) == 0;
}

/*
 * sincronizacao_registrar_operacao
 * Objetivo: guardar na fila uma operacao para enviar a central depois (RF09).
 * Parametros: caminho_fila = arquivo da fila; caminho_sequencia = arquivo do
 *   numero da operacao; id_portaria = portaria de origem; tipo = REGISTRO,
 *   RETIRADA ou DEVOLUCAO; encomenda = volume da operacao.
 * Retorno: 1 se a operacao entrou na fila; 0 se falhou.
 * Logica: pega o proximo numero, monta o id e os dados (data e hora do
 *   momento, id e unidade da encomenda) e acrescenta uma linha no final da
 *   fila. A fila fica em arquivo, entao sobrevive ao fechamento do programa.
 */
int sincronizacao_registrar_operacao(const char *caminho_fila, const char *caminho_sequencia,
                                     int id_portaria, TipoOperacao tipo, const Encomenda *encomenda)
{
    Operacao operacao;
    char linha[TAM_LINHA];
    int numero;
    FILE *arq;

    numero = sincronizacao_proximo_numero(caminho_sequencia);
    if (numero == 0 || !sincronizacao_criar_se_ausente(caminho_fila)) {
        return 0;
    }
    memset(&operacao, 0, sizeof operacao);
    sincronizacao_montar_id(operacao.id_operacao, TAM_ID_OPERACAO, id_portaria, numero);
    operacao.id_portaria = id_portaria;
    util_data_hora_atual(operacao.data_hora, TAM_DATA);
    operacao.tipo = tipo;
    operacao.id_encomenda = encomenda->id;
    operacao.bloco = encomenda->bloco;
    operacao.apartamento = encomenda->apartamento;
    sincronizacao_operacao_para_linha(&operacao, linha, TAM_LINHA);

    arq = fopen(caminho_fila, "a");
    if (arq == NULL) {
        return 0;
    }
    fprintf(arq, "%s\n", linha);
    return fclose(arq) == 0;
}

/*
 * sincronizacao_contar_pendentes
 * Objetivo: contar quantas operacoes aguardam envio (US10).
 * Parametros: caminho_fila = arquivo da fila.
 * Retorno: numero de operacoes (0 se o arquivo nao existe).
 * Logica: le a fila linha a linha, pula o cabecalho e conta as linhas nao
 *   vazias.
 */
int sincronizacao_contar_pendentes(const char *caminho_fila)
{
    FILE *arq = fopen(caminho_fila, "r");
    char linha[TAM_LINHA];
    int total = 0;

    if (arq == NULL) {
        return 0;
    }
    if (fgets(linha, TAM_LINHA, arq) != NULL) {
        while (fgets(linha, TAM_LINHA, arq) != NULL) {
            util_aparar(linha);
            if (linha[0] != '\0') {
                total++;
            }
        }
    }
    fclose(arq);
    return total;
}

/*
 * sincronizacao_enviar_pendentes (algoritmo A4)
 * Objetivo: enviar as operacoes da fila para a "rede" simulada (US10).
 * Parametros: caminho_fila = arquivo da fila; caminho_rede = log da portaria
 *   em dados/rede; online = 1 se a portaria esta online; enviadas = recebe
 *   quantas operacoes foram enviadas.
 * Retorno: SINC_OFFLINE, SINC_VAZIA, SINC_OK ou SINC_ERRO.
 * Logica: offline, nao mexe em nada. Sem pendencias, avisa. Online, copia
 *   cada linha da fila para o final do log e so depois esvazia a fila
 *   (deixa so o cabecalho). Se o programa cair entre as duas etapas, o
 *   proximo envio repete as operacoes no log; isso e seguro porque a central
 *   ignora operacoes ja aplicadas (idempotencia, ADR-003).
 */
int sincronizacao_enviar_pendentes(const char *caminho_fila, const char *caminho_rede, int online,
                                   int *enviadas)
{
    FILE *fila;
    FILE *rede;
    char linha[TAM_LINHA];
    int copiadas = 0;

    *enviadas = 0;
    if (!online) {
        return SINC_OFFLINE;
    }
    if (sincronizacao_contar_pendentes(caminho_fila) == 0) {
        return SINC_VAZIA;
    }
    if (!sincronizacao_criar_se_ausente(caminho_rede)) {
        return SINC_ERRO;
    }
    fila = fopen(caminho_fila, "r");
    rede = fopen(caminho_rede, "a");
    if (fila == NULL || rede == NULL) {
        if (fila != NULL) {
            fclose(fila);
        }
        if (rede != NULL) {
            fclose(rede);
        }
        return SINC_ERRO;
    }
    if (fgets(linha, TAM_LINHA, fila) != NULL) {
        while (fgets(linha, TAM_LINHA, fila) != NULL) {
            util_aparar(linha);
            if (linha[0] != '\0') {
                fprintf(rede, "%s\n", linha);
                copiadas++;
            }
        }
    }
    fclose(fila);
    if (fclose(rede) != 0) {
        return SINC_ERRO;
    }
    fila = fopen(caminho_fila, "w");
    if (fila == NULL) {
        return SINC_ERRO;
    }
    fprintf(fila, "%s\n", CABECALHO_OPERACOES);
    if (fclose(fila) != 0) {
        return SINC_ERRO;
    }
    *enviadas = copiadas;
    return SINC_OK;
}
