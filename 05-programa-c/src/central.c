#include <stdio.h>

#include "tipos.h"
#include "persistencia.h"
#include "consolidacao.h"

/* Estado da central: tem varios KB, entao fica em memoria estatica, nao na pilha. */
static EstadoCentral estado;

/*
 * central_processar_logs
 * Objetivo: consolidar o log de cada portaria de P01 a P10.
 * Parametros: nenhum (usa o estado estatico da central).
 * Retorno: numero de logs encontrados.
 * Logica: para cada portaria monta o caminho do log, processa se existir e
 *   mostra os contadores; portarias sem log sao ignoradas sem erro.
 */
static int central_processar_logs(void)
{
    char caminho[TAM_CAMINHO];
    ResumoConsolidacao resumo;
    int p;
    int encontrados = 0;

    for (p = 1; p <= MAX_PORTARIAS; p++) {
        persistencia_montar_caminho_rede(caminho, TAM_CAMINHO, p);
        if (consolidacao_processar_portaria(&estado, p, caminho, &resumo)) {
            encontrados++;
            printf("P%02d: %d lida(s), %d aplicada(s), %d ja aplicada(s), %d rejeitada(s), "
                   "%d invalida(s)\n",
                   p, resumo.lidas, resumo.aplicadas, resumo.ja_aplicadas, resumo.rejeitadas,
                   resumo.invalidas);
        }
    }
    return encontrados;
}

/*
 * main
 * Objetivo: consolidar as operacoes enviadas pelas portarias, sem duplicar, e
 *   gerar o relatorio consolidado (uso: central).
 * Logica: carrega o que ja foi aplicado, processa os logs, grava o estado e o
 *   relatorio. Rodar duas vezes seguidas nao altera o resultado.
 */
int main(void)
{
    int logs;

    if (!consolidacao_carregar_estado(&estado, CAMINHO_APLICADAS, CAMINHO_CONSOLIDADAS)) {
        printf("ERRO: nao foi possivel abrir os arquivos de dados/central.\n");
        printf("Execute o programa a partir da pasta 05-programa-c.\n");
        return 1;
    }
    printf("=== CENTRAL - Morada Central ===\n");
    printf("Estado anterior: %d operacao(oes) aplicada(s), %d encomenda(s) consolidada(s).\n",
           estado.qtd_aplicadas, estado.qtd_consolidadas);

    logs = central_processar_logs();
    if (logs == 0) {
        printf("Nenhum log encontrado em dados/rede.\n");
    }
    if (!consolidacao_salvar_estado(&estado, CAMINHO_APLICADAS, CAMINHO_CONSOLIDADAS)) {
        printf("ERRO: nao foi possivel gravar os arquivos de dados/central.\n");
        return 1;
    }
    if (!consolidacao_gerar_relatorio(&estado, CAMINHO_RELATORIO)) {
        printf("ERRO: nao foi possivel gravar %s.\n", CAMINHO_RELATORIO);
        return 1;
    }
    printf("Total consolidado: %d operacao(oes), %d encomenda(s).\n", estado.qtd_aplicadas,
           estado.qtd_consolidadas);
    printf("Relatorio gravado em %s\n", CAMINHO_RELATORIO);
    return 0;
}
