#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"
#include "util.h"
#include "estante.h"
#include "codigo.h"
#include "encomenda.h"
#include "retirada.h"
#include "persistencia.h"

/* Dados da portaria em memoria: vetores e matriz estaticos (tamanhos em tipos.h). */
static Encomenda encomendas[MAX_ENCOMENDAS];
static int quantidade_encomendas = 0;
static int estante[NUM_ESTANTES][NUM_PRATELEIRAS];

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
 * portaria_imprimir_menu
 * Objetivo: mostrar o menu principal.
 * Parametros: id = numero da portaria.
 */
static void portaria_imprimir_menu(int id)
{
    printf("\n=== PORTARIA P%02d - Morada Central ===\n", id);
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
 * portaria_salvar
 * Objetivo: gravar as encomendas no arquivo depois de uma alteracao.
 * Parametros: caminho = arquivo de encomendas da portaria.
 * Logica: avisa o porteiro se a gravacao falhar.
 */
static void portaria_salvar(const char *caminho)
{
    if (persistencia_salvar_encomendas(caminho, encomendas, quantidade_encomendas) != PERSIST_OK) {
        printf("ERRO: nao foi possivel gravar %s. Os dados desta alteracao podem ser perdidos.\n",
               caminho);
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
 * Parametros: opcao = numero digitado; caminho = arquivo de encomendas.
 * Logica: switch; opcoes que alteram dados salvam o arquivo em seguida.
 */
static void portaria_executar(int opcao, const char *caminho)
{
    switch (opcao) {
    case 1:
        if (encomenda_registrar(encomendas, &quantidade_encomendas, estante)) {
            portaria_salvar(caminho);
        }
        break;
    case 2:
        if (retirada_registrar(encomendas, quantidade_encomendas, estante)) {
            portaria_salvar(caminho);
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
    case 8:
    case 9:
        portaria_em_breve(2);
        break;
    default:
        break;
    }
}

/*
 * main
 * Objetivo: abrir a portaria n (uso: portaria <n>), carregar os dados e
 *   repetir o menu ate o porteiro escolher sair.
 * Logica: valida o argumento; monta o caminho do arquivo; carrega as
 *   encomendas; reconstroi a matriz da estante a partir das pendentes; entra
 *   no laco do menu.
 */
int main(int argc, char *argv[])
{
    int id_portaria;
    int opcao;
    char caminho[TAM_CAMINHO];

    if (!portaria_ler_numero(argc, argv, &id_portaria)) {
        printf("Uso: portaria <n>   (n de 1 a %d). Exemplo: bin/portaria 1\n", MAX_PORTARIAS);
        return 1;
    }
    persistencia_montar_caminho(caminho, TAM_CAMINHO, id_portaria, "encomendas.csv");
    if (persistencia_carregar_encomendas(caminho, encomendas, MAX_ENCOMENDAS,
                                         &quantidade_encomendas) != PERSIST_OK) {
        printf("ERRO: nao foi possivel abrir %s.\n", caminho);
        printf("Execute o programa a partir da pasta 05-programa-c.\n");
        return 1;
    }
    estante_reconstruir(estante, encomendas, quantidade_encomendas);
    codigo_iniciar_aleatorio();

    do {
        portaria_imprimir_menu(id_portaria);
        if (!util_ler_inteiro("Opcao: ", 0, 9, &opcao)) {
            break;
        }
        portaria_executar(opcao, caminho);
    } while (opcao != 0);

    printf("Portaria P%02d encerrada.\n", id_portaria);
    return 0;
}
