#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"
#include "util.h"
#include "estante.h"
#include "codigo.h"
#include "encomenda.h"
#include "retirada.h"
#include "morador.h"
#include "aviso.h"
#include "sincronizacao.h"
#include "persistencia.h"

/* Dados da portaria em memoria: vetores e matriz estaticos (tamanhos em tipos.h). */
static Encomenda encomendas[MAX_ENCOMENDAS];
static int quantidade_encomendas = 0;
static Morador moradores[MAX_MORADORES];
static int quantidade_moradores = 0;
static int estante[NUM_ESTANTES][NUM_PRATELEIRAS];

/* Estado da portaria: numero, modo (simulado) e caminhos dos arquivos de dados. */
static int id_portaria = 1;
static int online = 1;
static char caminho_encomendas[TAM_CAMINHO];
static char caminho_moradores[TAM_CAMINHO];
static char caminho_fila[TAM_CAMINHO];
static char caminho_sequencia[TAM_CAMINHO];
static char caminho_avisos[TAM_CAMINHO];
static char caminho_rede[TAM_CAMINHO];

/*
 * portaria_ler_numero
 * Objetivo: obter o numero da portaria a partir da linha de comando.
 * Parametros: argc e argv = argumentos do programa; id = recebe o numero.
 * Retorno: 1 se argv[1] e um numero de 1 a MAX_PORTARIAS; 0 caso contrario.
 */
static int portaria_ler_numero(int argc, char *argv[], int *id)
{
    return argc == 2 && util_converter_inteiro(argv[1], 1, MAX_PORTARIAS, id);
}

/*
 * portaria_montar_caminhos
 * Objetivo: montar o nome de todos os arquivos da portaria.
 * Parametros: nenhum (usa o numero da portaria).
 * Retorno: nenhum.
 */
static void portaria_montar_caminhos(void)
{
    persistencia_montar_caminho(caminho_encomendas, TAM_CAMINHO, id_portaria, "encomendas.csv");
    persistencia_montar_caminho(caminho_moradores, TAM_CAMINHO, id_portaria, "moradores.csv");
    persistencia_montar_caminho(caminho_fila, TAM_CAMINHO, id_portaria, "fila.csv");
    persistencia_montar_caminho(caminho_sequencia, TAM_CAMINHO, id_portaria, "sequencia.txt");
    persistencia_montar_caminho(caminho_avisos, TAM_CAMINHO, id_portaria, "avisos.txt");
    persistencia_montar_caminho_rede(caminho_rede, TAM_CAMINHO, id_portaria);
}

/*
 * portaria_imprimir_menu
 * Objetivo: mostrar o menu principal, com o modo online/offline.
 */
static void portaria_imprimir_menu(void)
{
    printf("\n=== PORTARIA P%02d - Morada Central ===   [%s]\n", id_portaria,
           online ? "ONLINE" : "OFFLINE");
    printf("1 - Registrar encomenda\n");
    printf("2 - Registrar retirada\n");
    printf("3 - Listar pendentes\n");
    printf("4 - Buscar por unidade\n");
    printf("5 - Mapa da estante\n");
    printf("6 - Moradores\n");
    printf("7 - Relatorios\n");
    printf("8 - Sincronizar com a central\n");
    printf("9 - Alternar online/offline (simulacao)\n");
    printf("0 - Sair\n");
}

/*
 * portaria_salvar_encomendas
 * Objetivo: gravar as encomendas no arquivo depois de uma alteracao.
 * Logica: avisa o porteiro se a gravacao falhar.
 */
static void portaria_salvar_encomendas(void)
{
    if (persistencia_salvar_encomendas(caminho_encomendas, encomendas, quantidade_encomendas) !=
        PERSIST_OK) {
        printf("ERRO: nao foi possivel gravar %s. Os dados desta alteracao podem ser perdidos.\n",
               caminho_encomendas);
    }
}

/*
 * portaria_enfileirar
 * Objetivo: guardar na fila a operacao de uma encomenda, para enviar a central.
 * Parametros: tipo = REGISTRO ou RETIRADA; encomenda = volume da operacao.
 * Logica: a operacao entra na fila mesmo com a portaria offline (US09); se
 *   nao conseguir gravar, avisa claramente que a central nao sera informada.
 */
static void portaria_enfileirar(TipoOperacao tipo, const Encomenda *encomenda)
{
    if (!sincronizacao_registrar_operacao(caminho_fila, caminho_sequencia, id_portaria, tipo,
                                          encomenda)) {
        printf("ERRO: a operacao %s da encomenda %d NAO entrou na fila de sincronizacao.\n",
               sincronizacao_tipo_texto(tipo), encomenda->id);
    }
}

/*
 * portaria_apos_registro
 * Objetivo: o que acontece depois que uma encomenda e registrada: salvar,
 *   enfileirar a operacao e avisar o morador.
 * Logica: usa a ultima encomenda do vetor; escolhe o morador a avisar (pelo
 *   nome do destinatario ou o primeiro da unidade) e simula o aviso.
 */
static void portaria_apos_registro(void)
{
    const Encomenda *nova = &encomendas[quantidade_encomendas - 1];
    int indice;

    portaria_salvar_encomendas();
    portaria_enfileirar(OP_REGISTRO, nova);
    indice = morador_localizar_para_aviso(moradores, quantidade_moradores, nova->bloco,
                                          nova->apartamento, nova->destinatario);
    if (aviso_enviar(caminho_avisos, nova, indice >= 0 ? &moradores[indice] : NULL) == AVISO_ERRO) {
        printf("ERRO: nao foi possivel gravar %s.\n", caminho_avisos);
    }
}

/*
 * portaria_buscar
 * Objetivo: opcao 4 do menu: perguntar a unidade e listar as pendentes dela.
 */
static void portaria_buscar(void)
{
    char bloco;
    int apartamento;

    printf("\n--- Buscar por unidade ---\n");
    if (encomenda_ler_unidade(&bloco, &apartamento)) {
        encomenda_buscar_por_unidade(encomendas, quantidade_encomendas, bloco, apartamento);
    }
}

/*
 * portaria_menu_moradores
 * Objetivo: opcao 6 do menu: cadastrar e listar moradores (US07).
 * Logica: submenu em laco; o cadastro salva o arquivo de moradores.
 */
static void portaria_menu_moradores(void)
{
    int opcao;

    do {
        printf("\n--- Moradores ---\n");
        printf("1 - Cadastrar morador\n");
        printf("2 - Listar moradores\n");
        printf("0 - Voltar\n");
        if (!util_ler_inteiro("Opcao: ", 0, 2, &opcao)) {
            return;
        }
        if (opcao == 1) {
            if (morador_cadastrar(moradores, &quantidade_moradores) &&
                persistencia_salvar_moradores(caminho_moradores, moradores,
                                              quantidade_moradores) != PERSIST_OK) {
                printf("ERRO: nao foi possivel gravar %s.\n", caminho_moradores);
            }
        } else if (opcao == 2) {
            morador_listar(moradores, quantidade_moradores);
        }
    } while (opcao != 0);
}

/*
 * portaria_sincronizar
 * Objetivo: opcao 8 do menu: enviar as operacoes da fila a central (US10).
 * Logica: offline informa quantas operacoes aguardam; online envia e informa
 *   quantas foram enviadas (algoritmo A4 em sincronizacao_enviar_pendentes).
 */
static void portaria_sincronizar(void)
{
    int enviadas = 0;

    printf("\n--- Sincronizar com a central ---\n");
    switch (sincronizacao_enviar_pendentes(caminho_fila, caminho_rede, online, &enviadas)) {
    case SINC_OFFLINE:
        printf("Portaria OFFLINE: %d operacao(oes) aguardando envio.\n",
               sincronizacao_contar_pendentes(caminho_fila));
        break;
    case SINC_VAZIA:
        printf("Nenhuma operacao pendente.\n");
        break;
    case SINC_OK:
        printf("%d operacao(oes) enviada(s) para %s.\n", enviadas, caminho_rede);
        break;
    default:
        printf("ERRO: nao foi possivel enviar. A fila foi preservada.\n");
        break;
    }
}

/*
 * portaria_alternar_modo
 * Objetivo: opcao 9 do menu: alternar entre online e offline (simulacao).
 */
static void portaria_alternar_modo(void)
{
    online = !online;
    printf("\nPortaria agora %s.\n", online ? "ONLINE" : "OFFLINE");
    if (!online) {
        printf("Registros e retiradas continuam normais; as operacoes ficam na fila.\n");
    }
}

/*
 * portaria_em_breve
 * Objetivo: avisar que uma opcao do menu chega em outra sprint.
 * Parametros: sprint = numero da sprint prevista no PLANO.md.
 */
static void portaria_em_breve(int sprint)
{
    printf("Opcao prevista para a Sprint %d. Ainda nao disponivel.\n", sprint);
}

/*
 * portaria_executar
 * Objetivo: executar a opcao escolhida no menu.
 * Parametros: opcao = numero digitado.
 * Logica: switch; opcoes que alteram dados salvam o arquivo e enfileiram a
 *   operacao.
 */
static void portaria_executar(int opcao)
{
    int indice = -1;

    switch (opcao) {
    case 1:
        if (encomenda_registrar(encomendas, &quantidade_encomendas, estante)) {
            portaria_apos_registro();
        }
        break;
    case 2:
        if (retirada_registrar(encomendas, quantidade_encomendas, estante, &indice)) {
            portaria_salvar_encomendas();
            portaria_enfileirar(OP_RETIRADA, &encomendas[indice]);
        }
        break;
    case 3:
        printf("\n--- Encomendas pendentes ---\n");
        encomenda_listar_pendentes(encomendas, quantidade_encomendas);
        break;
    case 4:
        portaria_buscar();
        break;
    case 5:
    case 7:
        portaria_em_breve(3);
        break;
    case 6:
        portaria_menu_moradores();
        break;
    case 8:
        portaria_sincronizar();
        break;
    case 9:
        portaria_alternar_modo();
        break;
    default:
        break;
    }
}

/*
 * main
 * Objetivo: abrir a portaria n (uso: portaria <n>), carregar os dados e
 *   repetir o menu ate o porteiro escolher sair.
 * Logica: valida o argumento; monta os caminhos; carrega encomendas e
 *   moradores; reconstroi a matriz da estante a partir das pendentes; entra
 *   no laco do menu.
 */
int main(int argc, char *argv[])
{
    int opcao;

    if (!portaria_ler_numero(argc, argv, &id_portaria)) {
        printf("Uso: portaria <n>   (n de 1 a %d). Exemplo: bin/portaria 1\n", MAX_PORTARIAS);
        return 1;
    }
    portaria_montar_caminhos();
    if (persistencia_carregar_encomendas(caminho_encomendas, encomendas, MAX_ENCOMENDAS,
                                         &quantidade_encomendas) != PERSIST_OK ||
        persistencia_carregar_moradores(caminho_moradores, moradores, MAX_MORADORES,
                                        &quantidade_moradores) != PERSIST_OK) {
        printf("ERRO: nao foi possivel abrir os arquivos de dados/portarias.\n");
        printf("Execute o programa a partir da pasta 05-programa-c.\n");
        return 1;
    }
    estante_reconstruir(estante, encomendas, quantidade_encomendas);
    codigo_iniciar_aleatorio();

    do {
        portaria_imprimir_menu();
        if (!util_ler_inteiro("Opcao: ", 0, 9, &opcao)) {
            break;
        }
        portaria_executar(opcao);
    } while (opcao != 0);

    printf("Portaria P%02d encerrada.\n", id_portaria);
    return 0;
}
