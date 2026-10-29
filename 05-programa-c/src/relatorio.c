#include <stdio.h>
#include <string.h>

#include "tipos.h"
#include "util.h"
#include "estante.h"
#include "relatorio.h"

#define TAM_DATA_CURTA 11 /* "AAAA-MM-DD" com o '\0' */

/*
 * relatorio_ler_data (auxiliar interna)
 * Objetivo: extrair ano, mes e dia do inicio de uma data "AAAA-MM-DD ...".
 * Parametros: texto = data; ano, mes e dia = recebem os numeros.
 * Retorno: 1 se o inicio do texto tem o formato AAAA-MM-DD com mes de 1 a 12
 *   e dia de 1 a DIAS_NO_MES; 0 caso contrario.
 * Logica: confere digito por digito (posicoes 4 e 7 devem ser '-') e monta os
 *   numeros. Nao valida dias de cada mes: basta para agrupar por dia.
 */
static int relatorio_ler_data(const char *texto, int *ano, int *mes, int *dia)
{
    int i;

    if (strlen(texto) < 10 || texto[4] != '-' || texto[7] != '-') {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && (texto[i] < '0' || texto[i] > '9')) {
            return 0;
        }
    }
    *ano = (texto[0] - '0') * 1000 + (texto[1] - '0') * 100 + (texto[2] - '0') * 10 + (texto[3] - '0');
    *mes = (texto[5] - '0') * 10 + (texto[6] - '0');
    *dia = (texto[8] - '0') * 10 + (texto[9] - '0');
    return *mes >= 1 && *mes <= 12 && *dia >= 1 && *dia <= DIAS_NO_MES;
}

/*
 * relatorio_percentual_ocupacao
 * Objetivo: calcular quanto da estante esta ocupado.
 * Parametros: estante = matriz de posicoes.
 * Retorno: ocupadas / total * 100 (0.0 a 100.0).
 * Logica: usa estante_ocupacao e divide pelo total de posicoes da matriz.
 */
double relatorio_percentual_ocupacao(int estante[][NUM_PRATELEIRAS])
{
    return estante_ocupacao(estante) * 100.0 / (NUM_ESTANTES * NUM_PRATELEIRAS);
}

/*
 * relatorio_mapa_estante
 * Objetivo: mostrar ao porteiro o mapa da estante (US12).
 * Parametros: estante = matriz de posicoes.
 * Retorno: nenhum.
 * Logica: uma linha por estante (letra A, B, ...) e uma coluna por prateleira,
 *   com '.' para livre e 'X' para ocupada; no fim, o resumo com o percentual.
 */
void relatorio_mapa_estante(int estante[][NUM_PRATELEIRAS])
{
    int i;
    int j;

    printf("\n--- Mapa da estante ---\n");
    printf("Legenda: . livre   X ocupada   (prateleiras %d a %d: volumes G)\n", PRATELEIRA_INICIAL_G,
           NUM_PRATELEIRAS - 1);
    printf("Prateleira ");
    for (j = 0; j < NUM_PRATELEIRAS; j++) {
        printf("%3d", j);
    }
    printf("\n");
    for (i = 0; i < NUM_ESTANTES; i++) {
        printf("Estante %c  ", 'A' + i);
        for (j = 0; j < NUM_PRATELEIRAS; j++) {
            printf("  %c", estante[i][j] != 0 ? 'X' : '.');
        }
        printf("\n");
    }
    printf("Ocupadas: %d de %d (%.1f%%)\n", estante_ocupacao(estante), NUM_ESTANTES * NUM_PRATELEIRAS,
           relatorio_percentual_ocupacao(estante));
}

/*
 * relatorio_ocupacao_por_estante (auxiliar interna)
 * Objetivo: mostrar quantas posicoes cada estante tem ocupadas.
 * Parametros: estante = matriz de posicoes.
 * Logica: conta as celulas diferentes de 0 em cada linha e imprime com o percentual.
 */
static void relatorio_ocupacao_por_estante(int estante[][NUM_PRATELEIRAS])
{
    int i;
    int j;
    int ocupadas;

    printf("\n--- Ocupacao por estante ---\n");
    for (i = 0; i < NUM_ESTANTES; i++) {
        ocupadas = 0;
        for (j = 0; j < NUM_PRATELEIRAS; j++) {
            if (estante[i][j] != 0) {
                ocupadas++;
            }
        }
        printf("Estante %c: %2d de %d (%.1f%%)\n", 'A' + i, ocupadas, NUM_PRATELEIRAS,
               ocupadas * 100.0 / NUM_PRATELEIRAS);
    }
    printf("Total: %d de %d (%.1f%%)\n", estante_ocupacao(estante), NUM_ESTANTES * NUM_PRATELEIRAS,
           relatorio_percentual_ocupacao(estante));
}

/*
 * relatorio_pendencia_antiga
 * Objetivo: dizer se uma encomenda e uma pendencia antiga (US13).
 * Parametros: encomenda = volume a avaliar; agora = data atual
 *   "AAAA-MM-DD HH:MM"; dias = recebe os dias desde o recebimento.
 * Retorno: 1 se esta PENDENTE e passaram mais de DIAS_ALERTA dias; 0 caso
 *   contrario (inclui datas invalidas).
 * Logica: so pendentes entram; usa util_dias_entre (dias do calendario).
 *   Exatamente DIAS_ALERTA dias ainda nao alerta.
 */
int relatorio_pendencia_antiga(const Encomenda *encomenda, const char *agora, int *dias)
{
    int passados;

    if (encomenda->status != STATUS_PENDENTE ||
        !util_dias_entre(encomenda->recebida_em, agora, &passados) || passados <= DIAS_ALERTA) {
        return 0;
    }
    *dias = passados;
    return 1;
}

/*
 * relatorio_contar_antigas
 * Objetivo: contar as pendencias antigas.
 * Parametros: encomendas = vetor; quantidade = tamanho usado; agora = data atual.
 * Retorno: quantidade de pendencias antigas.
 */
int relatorio_contar_antigas(const Encomenda encomendas[], int quantidade, const char *agora)
{
    int i;
    int dias;
    int total = 0;

    for (i = 0; i < quantidade; i++) {
        if (relatorio_pendencia_antiga(&encomendas[i], agora, &dias)) {
            total++;
        }
    }
    return total;
}

/*
 * relatorio_pendencias_antigas
 * Objetivo: listar as pendencias com mais de DIAS_ALERTA dias (US13).
 * Parametros: encomendas = vetor; quantidade = tamanho usado; agora = data atual.
 * Retorno: quantas pendencias antigas foram listadas.
 * Logica: percorre o vetor e imprime unidade, destinatario, data de
 *   recebimento e dias parados; sem nenhuma, informa que nao ha alertas.
 */
int relatorio_pendencias_antigas(const Encomenda encomendas[], int quantidade, const char *agora)
{
    int i;
    int dias;
    int total = 0;

    printf("\n--- Pendencias com mais de %d dias ---\n", DIAS_ALERTA);
    for (i = 0; i < quantidade; i++) {
        if (relatorio_pendencia_antiga(&encomendas[i], agora, &dias)) {
            if (total == 0) {
                printf("%-4s %-8s %-24s %-17s %s\n", "ID", "UNIDADE", "DESTINATARIO", "RECEBIDA EM",
                       "DIAS");
            }
            printf("%-4d %c-%-6d %-24s %-17s %d\n", encomendas[i].id, encomendas[i].bloco,
                   encomendas[i].apartamento, encomendas[i].destinatario, encomendas[i].recebida_em,
                   dias);
            total++;
        }
    }
    if (total == 0) {
        printf("Nenhum alerta: nao ha pendencias com mais de %d dias.\n", DIAS_ALERTA);
    } else {
        printf("Total: %d pendencia(s) para cobrar a retirada.\n", total);
    }
    return total;
}

/*
 * relatorio_contar_por_dia
 * Objetivo: contar os registros de encomendas de cada dia de um mes (US14).
 * Parametros: encomendas = vetor; quantidade = tamanho usado; ano e mes =
 *   periodo; contagem = vetor com DIAS_NO_MES + 1 posicoes (o indice e o dia).
 * Retorno: total de registros do mes.
 * Logica: zera o vetor e soma 1 no dia de cada encomenda cuja data de
 *   recebimento cai no ano e mes pedidos (qualquer status).
 */
int relatorio_contar_por_dia(const Encomenda encomendas[], int quantidade, int ano, int mes,
                             int contagem[DIAS_NO_MES + 1])
{
    int i;
    int a;
    int m;
    int d;
    int total = 0;

    for (i = 0; i <= DIAS_NO_MES; i++) {
        contagem[i] = 0;
    }
    for (i = 0; i < quantidade; i++) {
        if (relatorio_ler_data(encomendas[i].recebida_em, &a, &m, &d) && a == ano && m == mes) {
            contagem[d]++;
            total++;
        }
    }
    return total;
}

/*
 * relatorio_dia_pico
 * Objetivo: achar o dia de maior movimento.
 * Parametros: contagem = registros por dia (indice = dia).
 * Retorno: o dia com mais registros (o mais cedo, em caso de empate); 0 se o
 *   mes nao tem registros.
 */
int relatorio_dia_pico(const int contagem[DIAS_NO_MES + 1])
{
    int dia;
    int pico = 0;

    for (dia = 1; dia <= DIAS_NO_MES; dia++) {
        if (contagem[dia] > contagem[pico]) {
            pico = dia;
        }
    }
    return pico;
}

/*
 * relatorio_pico_mensal
 * Objetivo: mostrar a contagem por dia de um mes e o dia de pico (US14).
 * Parametros: encomendas = vetor; quantidade = tamanho usado; ano e mes = periodo.
 * Logica: conta por dia, imprime so os dias com registro (com barras de '#') e
 *   termina com o total e o pico.
 */
void relatorio_pico_mensal(const Encomenda encomendas[], int quantidade, int ano, int mes)
{
    int contagem[DIAS_NO_MES + 1];
    int total = relatorio_contar_por_dia(encomendas, quantidade, ano, mes, contagem);
    int pico = relatorio_dia_pico(contagem);
    int dia;
    int k;

    printf("\n--- Encomendas recebidas por dia (%04d-%02d) ---\n", ano, mes);
    if (total == 0) {
        printf("Nenhum registro neste mes.\n");
        return;
    }
    for (dia = 1; dia <= DIAS_NO_MES; dia++) {
        if (contagem[dia] > 0) {
            printf("Dia %02d: %2d ", dia, contagem[dia]);
            for (k = 0; k < contagem[dia]; k++) {
                printf("#");
            }
            printf("\n");
        }
    }
    printf("Total no mes: %d\n", total);
    printf("Dia de pico: %02d (%d encomenda(s))\n", pico, contagem[pico]);
}

/*
 * relatorio_menu
 * Objetivo: submenu de relatorios da portaria (opcao 7 do menu principal).
 * Parametros: encomendas = vetor; quantidade = tamanho usado; estante = matriz.
 * Logica: laco com tres relatorios: pendencias antigas (em relacao a hoje),
 *   pico de um ano e mes informados e ocupacao por estante.
 */
void relatorio_menu(const Encomenda encomendas[], int quantidade, int estante[][NUM_PRATELEIRAS])
{
    char agora[TAM_DATA];
    int ano;
    int mes;
    int opcao;

    do {
        printf("\n--- Relatorios ---\n");
        printf("1 - Pendencias com mais de %d dias\n", DIAS_ALERTA);
        printf("2 - Pico de encomendas por dia (mes)\n");
        printf("3 - Ocupacao por estante\n");
        printf("0 - Voltar\n");
        if (!util_ler_inteiro("Opcao: ", 0, 3, &opcao)) {
            return;
        }
        util_data_hora_atual(agora, TAM_DATA);
        if (opcao == 1) {
            relatorio_pendencias_antigas(encomendas, quantidade, agora);
        } else if (opcao == 2) {
            if (util_ler_inteiro("Ano (ex.: 2026): ", 2000, 2100, &ano) &&
                util_ler_inteiro("Mes (1 a 12): ", 1, 12, &mes)) {
                relatorio_pico_mensal(encomendas, quantidade, ano, mes);
            }
        } else if (opcao == 3) {
            relatorio_ocupacao_por_estante(estante);
        }
    } while (opcao != 0);
}

/*
 * relatorio_contar_antigas_consolidadas
 * Objetivo: contar as pendencias antigas de uma portaria no consolidado da central.
 * Parametros: consolidadas = vetor da central; quantidade = tamanho usado;
 *   id_portaria = portaria (1 a MAX_PORTARIAS); agora = data atual.
 * Retorno: quantidade de pendencias com mais de DIAS_ALERTA dias.
 * Logica: so conta as PENDENTES da portaria cuja data de recebimento e valida.
 */
int relatorio_contar_antigas_consolidadas(const EncomendaConsolidada consolidadas[], int quantidade,
                                          int id_portaria, const char *agora)
{
    int i;
    int dias;
    int total = 0;

    for (i = 0; i < quantidade; i++) {
        if (consolidadas[i].id_portaria == id_portaria &&
            consolidadas[i].status == STATUS_PENDENTE &&
            util_dias_entre(consolidadas[i].recebida_em, agora, &dias) && dias > DIAS_ALERTA) {
            total++;
        }
    }
    return total;
}

/*
 * relatorio_pico_consolidado
 * Objetivo: achar o dia de maior movimento de uma portaria no consolidado.
 * Parametros: consolidadas = vetor da central; quantidade = tamanho usado;
 *   id_portaria = portaria; data = recebe "AAAA-MM-DD"; tam_data = tamanho de
 *   data (pelo menos TAM_DATA_CURTA); registros = recebe a quantidade do dia.
 * Retorno: 1 se a portaria tem registros; 0 se nao tem.
 * Logica: para cada encomenda da portaria conta quantas tem a mesma data
 *   (10 primeiros caracteres) e guarda a maior contagem; em empate, vence a
 *   data mais antiga. Custo quadratico, aceitavel para MAX_ENCOMENDAS.
 */
int relatorio_pico_consolidado(const EncomendaConsolidada consolidadas[], int quantidade,
                               int id_portaria, char *data, int tam_data, int *registros)
{
    int i;
    int j;
    int contagem;
    int melhor = 0;
    int indice_melhor = -1;

    if (tam_data < TAM_DATA_CURTA) {
        return 0;
    }
    for (i = 0; i < quantidade; i++) {
        if (consolidadas[i].id_portaria != id_portaria || strlen(consolidadas[i].recebida_em) < 10) {
            continue;
        }
        contagem = 0;
        for (j = 0; j < quantidade; j++) {
            if (consolidadas[j].id_portaria == id_portaria &&
                strncmp(consolidadas[j].recebida_em, consolidadas[i].recebida_em, 10) == 0) {
                contagem++;
            }
        }
        if (contagem > melhor ||
            (contagem == melhor && strncmp(consolidadas[i].recebida_em,
                                           consolidadas[indice_melhor].recebida_em, 10) < 0)) {
            melhor = contagem;
            indice_melhor = i;
        }
    }
    if (indice_melhor < 0) {
        return 0;
    }
    memcpy(data, consolidadas[indice_melhor].recebida_em, 10);
    data[10] = '\0';
    *registros = melhor;
    return 1;
}
