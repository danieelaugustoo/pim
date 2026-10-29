#ifndef AVISO_H
#define AVISO_H

#include "tipos.h"

/*
 * aviso.h
 * Aviso simulado ao morador, conforme o canal cadastrado. Nada e enviado de
 * verdade: o texto aparece na tela e o registro e gravado em arquivo.
 */

/* Resultados de aviso_enviar */
#define AVISO_ENVIADO 0   /* APP, SMS ou INTERFONE tratados */
#define AVISO_MANUAL 1    /* unidade sem morador cadastrado: avisar manualmente */
#define AVISO_ERRO 2      /* nao foi possivel gravar o registro do aviso */

/* Simula o aviso e grava o registro. 'morador' pode ser NULL. */
int aviso_enviar(const char *caminho_registro, const Encomenda *encomenda, const Morador *morador);

#endif /* AVISO_H */
