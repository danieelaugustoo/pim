#include <stdio.h>
#include <string.h>

#include "tipos.h"
#include "util.h"
#include "estante.h"
#include "codigo.h"
#include "encomenda.h"

/*
 * encomenda_status_texto
 * Objetivo: obter o nome do status para mostrar e gravar em arquivo.
 * Parametros: status = valor do enum.
 * Retorno: "PENDENTE", "RETIRADA" ou "DEVOLVIDA".
 * Logica: switch sobre o enum.
 */
const char *encomenda_status_texto(StatusEncomenda status)
{
    switch (status) {
    case STATUS_PENDENTE:
        return "PENDENTE";
    case STATUS_RETIRADA:
        return "RETIRADA";
    case STATUS_DEVOLVIDA:
        return "DEVOLVIDA";
    }
    return "PENDENTE";
}

/*
 * encomenda_status_de_texto
 * Objetivo: converter o texto lido do arquivo em status.
 * Parametros: texto = "PENDENTE", "RETIRADA" ou "DEVOLVIDA"; status = recebe
 *   o valor.
 * Retorno: 1 se o texto e conhecido; 0 caso contrario.
 * Logica: compara com cada nome valido.
 */
int encomenda_status_de_texto(const char *texto, StatusEncomenda *status)
{
    if (strcmp(texto, "PENDENTE") == 0) {
        *status = STATUS_PENDENTE;
    } else if (strcmp(texto, "RETIRADA") == 0) {
        *status = STATUS_RETIRADA;
    } else if (strcmp(texto, "DEVOLVIDA") == 0) {
        *status = STATUS_DEVOLVIDA;
    } else {
        return 0;
    }
    return 1;
}

/*
 * encomenda_proximo_id
 * Objetivo: escolher o id da proxima encomenda sem precisar de outro arquivo.
 * Parametros: encomendas = vetor; quantidade = tamanho usado.
 * Retorno: maior id existente mais 1 (ou 1 se o vetor estiver vazio).
 * Logica: percorre o vetor guardando o maior id.
 */
int encomenda_proximo_id(const Encomenda encomendas[], int quantidade)
{
    int i;
    int maior = 0;

    for (i = 0; i < quantidade; i++) {
        if (encomendas[i].id > maior) {
            maior = encomendas[i].id;
        }
    }
    return maior + 1;
}

/*
 * encomenda_localizar
 * Objetivo: achar uma encomenda pelo id.
 * Parametros: encomendas = vetor; quantidade = tamanho usado; id = procurado.
 * Retorno: indice no vetor, ou -1 se nao existir.
 * Logica: busca sequencial.
 */
int encomenda_localizar(const Encomenda encomendas[], int quantidade, int id)
{
    int i;

    for (i = 0; i < quantidade; i++) {
        if (encomendas[i].id == id) {
            return i;
        }
    }
    return -1;
}

/*
 * encomenda_contar_pendentes_unidade
 * Objetivo: contar quantas encomendas pendentes uma unidade tem.
 * Parametros: encomendas = vetor; quantidade = tamanho usado; bloco e
 *   apartamento = unidade.
 * Retorno: numero de pendentes da unidade.
 * Logica: percorre o vetor contando status PENDENTE com a mesma unidade.
 */
int encomenda_contar_pendentes_unidade(const Encomenda encomendas[], int quantidade,
                                       char bloco, int apartamento)
{
    int i;
    int total = 0;

    for (i = 0; i < quantidade; i++) {
        if (encomendas[i].status == STATUS_PENDENTE && encomendas[i].bloco == bloco &&
            encomendas[i].apartamento == apartamento) {
            total++;
        }
    }
    return total;
}

/*
 * encomenda_criar
 * Objetivo: aplicar as regras de um novo registro (US01, US02 e US03).
 * Parametros: encomendas = vetor; quantidade = tamanho usado (aumenta em 1 se
 *   der certo); estante = matriz de posicoes; dados = encomenda com bloco,
 *   apartamento, destinatario, transportadora e tamanho ja preenchidos.
 * Retorno: ENC_OK, ENC_VETOR_CHEIO, ENC_SEM_POSICAO ou ENC_SEM_CODIGO.
 * Logica: confere se cabe no vetor; define o id; aloca a posicao na estante
 *   (A1); gera o codigo unico (A2); preenche data, hora e status PENDENTE;
 *   acrescenta ao vetor. Se o codigo falhar, devolve a posicao a estante.
 */
int encomenda_criar(Encomenda encomendas[], int *quantidade, int estante[][NUM_PRATELEIRAS],
                    const Encomenda *dados)
{
    Encomenda nova = *dados;

    if (*quantidade >= MAX_ENCOMENDAS) {
        return ENC_VETOR_CHEIO;
    }
    nova.id = encomenda_proximo_id(encomendas, *quantidade);
    if (!estante_alocar_posicao(estante, nova.bloco, nova.tamanho, nova.id,
                                &nova.estante, &nova.prateleira)) {
        return ENC_SEM_POSICAO;
    }
    nova.codigo = codigo_gerar_unico(encomendas, *quantidade);
    if (nova.codigo == 0) {
        estante_liberar_posicao(estante, nova.estante, nova.prateleira);
        return ENC_SEM_CODIGO;
    }
    util_data_hora_atual(nova.recebida_em, TAM_DATA);
    nova.status = STATUS_PENDENTE;
    nova.retirada_em[0] = '\0';
    nova.retirado_por[0] = '\0';
    encomendas[*quantidade] = nova;
    (*quantidade)++;
    return ENC_OK;
}

/*
 * encomenda_ler_unidade
 * Objetivo: perguntar ao porteiro a unidade (bloco e apartamento).
 * Parametros: bloco = recebe a letra; apartamento = recebe o numero.
 * Retorno: 1 se leu; 0 se a entrada acabou.
 * Logica: usa as leituras validadas de util (letra de A a Z e numero de 1 ao
 *   maior apartamento).
 */
int encomenda_ler_unidade(char *bloco, int *apartamento)
{
    return util_ler_letra("Bloco (A-Z): ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", bloco) &&
           util_ler_inteiro("Apartamento: ", 1, APARTAMENTO_MAX, apartamento);
}

/*
 * encomenda_registrar (interativa)
 * Objetivo: registrar uma encomenda a partir do que o porteiro digita.
 * Parametros: encomendas = vetor; quantidade = tamanho usado; estante =
 *   matriz de posicoes.
 * Retorno: 1 se registrou (o chamador deve salvar); 0 se nao registrou.
 * Logica: le unidade, destinatario, transportadora e tamanho; chama
 *   encomenda_criar; mostra a posicao e o codigo ou o motivo da falha.
 */
int encomenda_registrar(Encomenda encomendas[], int *quantidade, int estante[][NUM_PRATELEIRAS])
{
    Encomenda dados;
    int resultado;
    const Encomenda *nova;

    memset(&dados, 0, sizeof dados);
    printf("\n--- Registrar encomenda ---\n");
    if (!encomenda_ler_unidade(&dados.bloco, &dados.apartamento) ||
        !util_ler_texto("Destinatario: ", dados.destinatario, TAM_NOME) ||
        !util_ler_texto("Transportadora: ", dados.transportadora, TAM_TRANSPORTADORA) ||
        !util_ler_letra("Tamanho (P, M ou G): ", "PMG", &dados.tamanho)) {
        return 0;
    }
    resultado = encomenda_criar(encomendas, quantidade, estante, &dados);
    if (resultado == ENC_SEM_POSICAO) {
        printf("Estante cheia para esse tamanho de volume. Encomenda NAO registrada.\n");
    } else if (resultado == ENC_VETOR_CHEIO) {
        printf("Limite de %d encomendas atingido. Encomenda NAO registrada.\n", MAX_ENCOMENDAS);
    } else if (resultado == ENC_SEM_CODIGO) {
        printf("Nao foi possivel gerar o codigo. Encomenda NAO registrada.\n");
    }
    if (resultado != ENC_OK) {
        return 0;
    }
    nova = &encomendas[*quantidade - 1];
    printf("Encomenda %d registrada para %c-%d.\n", nova->id, nova->bloco, nova->apartamento);
    printf("Guardar na estante %c, prateleira %d.\n", 'A' + nova->estante, nova->prateleira);
    printf("Codigo de retirada: %0*d\n", TAM_CODIGO, nova->codigo);
    return 1;
}

/*
 * encomenda_imprimir_cabecalho (auxiliar interna)
 * Objetivo: escrever o cabecalho da tabela de pendentes.
 */
static void encomenda_imprimir_cabecalho(void)
{
    printf("%-4s %-7s %-24s %-14s %-3s %-9s %s\n", "ID", "UNIDADE", "DESTINATARIO",
           "TRANSPORTADORA", "TAM", "POSICAO", "RECEBIDA EM");
}

/*
 * encomenda_imprimir_linha (auxiliar interna)
 * Objetivo: escrever uma encomenda na tabela. O codigo de retirada NAO e
 *   exibido (RNF04).
 * Parametros: e = encomenda a mostrar.
 * Logica: monta o texto da unidade e da posicao e imprime em colunas.
 */
static void encomenda_imprimir_linha(const Encomenda *e)
{
    char unidade[16];
    char posicao[16];

    snprintf(unidade, sizeof unidade, "%c-%d", e->bloco, e->apartamento);
    snprintf(posicao, sizeof posicao, "%c/%d", 'A' + e->estante, e->prateleira);
    printf("%-4d %-7s %-24.24s %-14.14s %-3c %-9s %s\n", e->id, unidade, e->destinatario,
           e->transportadora, e->tamanho, posicao, e->recebida_em);
}

/*
 * encomenda_listar_pendentes
 * Objetivo: mostrar todas as encomendas pendentes (US05).
 * Parametros: encomendas = vetor; quantidade = tamanho usado.
 * Retorno: quantas pendentes foram mostradas.
 * Logica: percorre o vetor imprimindo as de status PENDENTE; se nao houver
 *   nenhuma, avisa.
 */
int encomenda_listar_pendentes(const Encomenda encomendas[], int quantidade)
{
    int i;
    int mostradas = 0;

    for (i = 0; i < quantidade; i++) {
        if (encomendas[i].status == STATUS_PENDENTE) {
            if (mostradas == 0) {
                encomenda_imprimir_cabecalho();
            }
            encomenda_imprimir_linha(&encomendas[i]);
            mostradas++;
        }
    }
    if (mostradas == 0) {
        printf("Nao ha encomendas pendentes.\n");
    } else {
        printf("Total de pendentes: %d\n", mostradas);
    }
    return mostradas;
}

/*
 * encomenda_buscar_por_unidade
 * Objetivo: mostrar as pendentes de uma unidade (US05).
 * Parametros: encomendas = vetor; quantidade = tamanho usado; bloco e
 *   apartamento = unidade procurada.
 * Retorno: quantas pendentes foram mostradas.
 * Logica: igual a listagem, mas filtrando pela unidade.
 */
int encomenda_buscar_por_unidade(const Encomenda encomendas[], int quantidade,
                                 char bloco, int apartamento)
{
    int i;
    int mostradas = 0;

    for (i = 0; i < quantidade; i++) {
        if (encomendas[i].status == STATUS_PENDENTE && encomendas[i].bloco == bloco &&
            encomendas[i].apartamento == apartamento) {
            if (mostradas == 0) {
                encomenda_imprimir_cabecalho();
            }
            encomenda_imprimir_linha(&encomendas[i]);
            mostradas++;
        }
    }
    if (mostradas == 0) {
        printf("Nenhuma encomenda pendente para a unidade %c-%d.\n", bloco, apartamento);
    }
    return mostradas;
}
