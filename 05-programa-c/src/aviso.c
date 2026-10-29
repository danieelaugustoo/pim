#include <stdio.h>

#include "tipos.h"
#include "util.h"
#include "morador.h"
#include "aviso.h"

/*
 * aviso_gravar (auxiliar interna)
 * Objetivo: acrescentar uma linha ao registro legivel de avisos.
 * Parametros: caminho = arquivo de avisos da portaria; encomenda = volume
 *   avisado; canal = texto do canal; destino = contato ou "-"; situacao =
 *   texto descrevendo o que foi feito.
 * Retorno: 1 se gravou; 0 se falhou.
 * Logica: abre o arquivo para acrescentar e escreve data e hora, encomenda,
 *   unidade, canal, destino e situacao. O codigo de retirada NAO e gravado
 *   (RNF04).
 */
static int aviso_gravar(const char *caminho, const Encomenda *encomenda, const char *canal,
                        const char *destino, const char *situacao)
{
    FILE *arq = fopen(caminho, "a");
    char agora[TAM_DATA];

    if (arq == NULL) {
        return 0;
    }
    util_data_hora_atual(agora, TAM_DATA);
    fprintf(arq, "%s | encomenda %d | %c-%d | %s | %s | %s\n", agora, encomenda->id,
            encomenda->bloco, encomenda->apartamento, canal, destino, situacao);
    return fclose(arq) == 0;
}

/*
 * aviso_enviar
 * Objetivo: simular o aviso da chegada ao morador (US08).
 * Parametros: caminho_registro = arquivo de avisos da portaria; encomenda =
 *   volume que chegou; morador = quem sera avisado, ou NULL se a unidade nao
 *   tem morador cadastrado.
 * Retorno: AVISO_ENVIADO, AVISO_MANUAL ou AVISO_ERRO.
 * Logica: sem morador, orienta o porteiro a avisar manualmente. Com morador,
 *   APP e SMS mostram a mensagem simulada para o contato cadastrado (o codigo
 *   iria dentro da mensagem e nao e mostrado nem gravado aqui); INTERFONE
 *   orienta o porteiro a ligar e mostra o codigo para impressao. Em todos os
 *   casos grava o registro do aviso.
 */
int aviso_enviar(const char *caminho_registro, const Encomenda *encomenda, const Morador *morador)
{
    int gravou;

    if (morador == NULL) {
        printf("Aviso: a unidade %c-%d nao tem morador cadastrado. Avisar manualmente.\n",
               encomenda->bloco, encomenda->apartamento);
        gravou = aviso_gravar(caminho_registro, encomenda, "-", "-",
                              "SEM MORADOR CADASTRADO - AVISAR MANUALMENTE");
        return gravou ? AVISO_MANUAL : AVISO_ERRO;
    }
    if (morador->canal == CANAL_INTERFONE) {
        printf("Aviso: ligar pelo interfone para %c-%d (%s).\n", encomenda->bloco,
               encomenda->apartamento, morador->nome);
        printf("Codigo para impressao: %0*d\n", TAM_CODIGO, encomenda->codigo);
        gravou = aviso_gravar(caminho_registro, encomenda, "INTERFONE", "-",
                              "AVISAR PELO INTERFONE (codigo impresso)");
    } else {
        printf("Aviso simulado por %s para %s: encomenda %d chegou para %c-%d.\n",
               morador_canal_texto(morador->canal), morador->contato, encomenda->id,
               encomenda->bloco, encomenda->apartamento);
        gravou = aviso_gravar(caminho_registro, encomenda, morador_canal_texto(morador->canal),
                              morador->contato, "ENVIADO (codigo na mensagem)");
    }
    return gravou ? AVISO_ENVIADO : AVISO_ERRO;
}
