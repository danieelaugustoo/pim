#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tipos.h"
#include "util.h"
#include "sincronizacao.h"

#define FILA "bin/teste-fila.tmp.csv"
#define SEQ "bin/teste-seq.tmp.txt"
#define REDE "bin/teste-rede.tmp.log"

/* Apaga os arquivos temporarios do teste. */
static void limpar(void)
{
    remove(FILA);
    remove(SEQ);
    remove(REDE);
}

/* Conta as linhas de um arquivo que comecam com o prefixo (prefixo vazio conta todas). */
static int contar_linhas(const char *caminho, const char *prefixo)
{
    FILE *arq = fopen(caminho, "r");
    char linha[TAM_LINHA];
    int total = 0;

    if (arq == NULL) {
        return -1;
    }
    while (fgets(linha, TAM_LINHA, arq) != NULL) {
        if (strncmp(linha, prefixo, strlen(prefixo)) == 0) {
            total++;
        }
    }
    fclose(arq);
    return total;
}

/* Monta uma encomenda de teste. */
static Encomenda encomenda_de(int id, char bloco, int apto)
{
    Encomenda e;

    memset(&e, 0, sizeof e);
    e.id = id;
    e.bloco = bloco;
    e.apartamento = apto;
    return e;
}

/* Conversoes de tipo e montagem do id. */
static void testar_tipo_e_id(void)
{
    TipoOperacao t = OP_REGISTRO;
    char id[TAM_ID_OPERACAO];

    assert(strcmp(sincronizacao_tipo_texto(OP_REGISTRO), "REGISTRO") == 0);
    assert(strcmp(sincronizacao_tipo_texto(OP_RETIRADA), "RETIRADA") == 0);
    assert(strcmp(sincronizacao_tipo_texto(OP_DEVOLUCAO), "DEVOLUCAO") == 0);
    assert(sincronizacao_tipo_de_texto("RETIRADA", &t) == 1 && t == OP_RETIRADA);
    assert(sincronizacao_tipo_de_texto("DEVOLUCAO", &t) == 1 && t == OP_DEVOLUCAO);
    assert(sincronizacao_tipo_de_texto("OUTRO", &t) == 0);
    sincronizacao_montar_id(id, TAM_ID_OPERACAO, 3, 42);
    assert(strcmp(id, "P03-000042") == 0);
    sincronizacao_montar_id(id, TAM_ID_OPERACAO, 10, 123456);
    assert(strcmp(id, "P10-123456") == 0);
}

/* Linha de operacao: ida e volta e validacoes. */
static void testar_linha(void)
{
    Operacao op;
    Operacao lida;
    char linha[TAM_LINHA];

    memset(&op, 0, sizeof op);
    util_copiar_texto(op.id_operacao, TAM_ID_OPERACAO, "P01-000123");
    op.id_portaria = 1;
    util_copiar_texto(op.data_hora, TAM_DATA, "2026-10-20 09:15");
    op.tipo = OP_RETIRADA;
    op.id_encomenda = 7;
    op.bloco = 'B';
    op.apartamento = 101;
    sincronizacao_operacao_para_linha(&op, linha, TAM_LINHA);
    assert(strcmp(linha, "P01-000123;1;2026-10-20 09:15;RETIRADA;7;B;101") == 0);
    assert(sincronizacao_operacao_de_linha(linha, &lida) == 1);
    assert(strcmp(lida.id_operacao, "P01-000123") == 0 && lida.id_portaria == 1);
    assert(strcmp(lida.data_hora, "2026-10-20 09:15") == 0 && lida.tipo == OP_RETIRADA);
    assert(lida.id_encomenda == 7 && lida.bloco == 'B' && lida.apartamento == 101);

    {
        char ruim1[] = "P01-000001;1;2026-10-20 09:15;REGISTRO;7;B";                 /* faltam campos */
        char ruim2[] = "P01-1;1;2026-10-20 09:15;REGISTRO;7;B;101";                  /* id mal formado */
        char ruim3[] = "P02-000001;1;2026-10-20 09:15;REGISTRO;7;B;101";             /* id de outra portaria */
        char ruim4[] = "P01-000001;1;2026-10-20 09:15;TROCA;7;B;101";                /* tipo desconhecido */
        char ruim5[] = "P01-000001;1;2026-13-20 09:15;REGISTRO;7;B;101";             /* data invalida */
        char ruim6[] = "P01-000001;1;2026-10-20 09:15;REGISTRO;7;b;101";             /* bloco minusculo */
        char ruim7[] = "P01-000001;1;2026-10-20 09:15;REGISTRO;7;B;0";               /* apartamento 0 */
        char ruim8[] = "P01-000001;11;2026-10-20 09:15;REGISTRO;7;B;101";            /* portaria 11 */
        assert(sincronizacao_operacao_de_linha(ruim1, &lida) == 0);
        assert(sincronizacao_operacao_de_linha(ruim2, &lida) == 0);
        assert(sincronizacao_operacao_de_linha(ruim3, &lida) == 0);
        assert(sincronizacao_operacao_de_linha(ruim4, &lida) == 0);
        assert(sincronizacao_operacao_de_linha(ruim5, &lida) == 0);
        assert(sincronizacao_operacao_de_linha(ruim6, &lida) == 0);
        assert(sincronizacao_operacao_de_linha(ruim7, &lida) == 0);
        assert(sincronizacao_operacao_de_linha(ruim8, &lida) == 0);
    }
}

/* Numeracao sequencial que sobrevive ao fechamento do programa. */
static void testar_numeracao(void)
{
    FILE *arq;

    limpar();
    assert(sincronizacao_proximo_numero(SEQ) == 1);
    assert(sincronizacao_proximo_numero(SEQ) == 2);
    assert(sincronizacao_proximo_numero(SEQ) == 3);

    /* arquivo corrompido: devolve erro em vez de recomecar (evita ids repetidos) */
    arq = fopen(SEQ, "w");
    assert(arq != NULL);
    fprintf(arq, "abc\n");
    fclose(arq);
    assert(sincronizacao_proximo_numero(SEQ) == 0);

    /* no limite de 6 digitos */
    arq = fopen(SEQ, "w");
    assert(arq != NULL);
    fprintf(arq, "999999\n");
    fclose(arq);
    assert(sincronizacao_proximo_numero(SEQ) == 0);
    limpar();
}

/* US09 e US10: fila, offline preserva, online envia e esvazia. */
static void testar_fila_e_envio(void)
{
    Encomenda e5 = encomenda_de(5, 'B', 101);
    Encomenda e6 = encomenda_de(6, 'C', 34);
    int enviadas = -1;
    FILE *arq;
    char linha[TAM_LINHA];

    limpar();
    assert(sincronizacao_contar_pendentes(FILA) == 0);
    assert(sincronizacao_registrar_operacao(FILA, SEQ, 1, OP_REGISTRO, &e5) == 1);
    assert(sincronizacao_registrar_operacao(FILA, SEQ, 1, OP_RETIRADA, &e5) == 1);
    assert(sincronizacao_registrar_operacao(FILA, SEQ, 1, OP_REGISTRO, &e6) == 1);
    assert(sincronizacao_contar_pendentes(FILA) == 3);

    /* as linhas da fila sao validas e os ids sao sequenciais */
    arq = fopen(FILA, "r");
    assert(arq != NULL);
    assert(fgets(linha, TAM_LINHA, arq) != NULL);          /* cabecalho */
    {
        Operacao op;
        int numero;
        for (numero = 1; numero <= 3; numero++) {
            char esperado[TAM_ID_OPERACAO];
            assert(fgets(linha, TAM_LINHA, arq) != NULL);
            util_aparar(linha);
            assert(sincronizacao_operacao_de_linha(linha, &op) == 1);
            sincronizacao_montar_id(esperado, TAM_ID_OPERACAO, 1, numero);
            assert(strcmp(op.id_operacao, esperado) == 0);
        }
    }
    fclose(arq);

    /* offline: nada muda e a rede nao recebe nada */
    assert(sincronizacao_enviar_pendentes(FILA, REDE, 0, &enviadas) == SINC_OFFLINE);
    assert(enviadas == 0);
    assert(sincronizacao_contar_pendentes(FILA) == 3);
    assert(fopen(REDE, "r") == NULL);

    /* online: copia as 3 operacoes e esvazia a fila */
    assert(sincronizacao_enviar_pendentes(FILA, REDE, 1, &enviadas) == SINC_OK);
    assert(enviadas == 3);
    assert(sincronizacao_contar_pendentes(FILA) == 0);
    assert(contar_linhas(REDE, "P01-") == 3);
    assert(contar_linhas(REDE, "id_operacao") == 1);

    /* sem pendencias */
    assert(sincronizacao_enviar_pendentes(FILA, REDE, 1, &enviadas) == SINC_VAZIA);
    assert(enviadas == 0);

    /* a numeracao continua depois do envio e o cabecalho do log nao se repete */
    assert(sincronizacao_registrar_operacao(FILA, SEQ, 1, OP_RETIRADA, &e6) == 1);
    assert(sincronizacao_enviar_pendentes(FILA, REDE, 1, &enviadas) == SINC_OK);
    assert(enviadas == 1);
    assert(contar_linhas(REDE, "P01-000004") == 1);
    assert(contar_linhas(REDE, "P01-") == 4);
    assert(contar_linhas(REDE, "id_operacao") == 1);
    limpar();
}

int main(void)
{
    testar_tipo_e_id();
    testar_linha();
    testar_numeracao();
    testar_fila_e_envio();
    printf("test_sincronizacao: OK\n");
    return 0;
}
