#ifndef TIPOS_H
#define TIPOS_H

/*
 * tipos.h
 * Estruturas, enumeracoes e constantes compartilhadas por todos os modulos.
 * Os tamanhos de vetores e matrizes ficam aqui, em constantes.
 */

/* ---------- Constantes de capacidade ---------- */
#define MAX_ENCOMENDAS 500       /* tamanho do vetor de encomendas */
#define MAX_MORADORES 300        /* tamanho do vetor de moradores */
#define NUM_ESTANTES 4           /* linhas da matriz (uma estante por bloco, A a D) */
#define NUM_PRATELEIRAS 12       /* colunas da matriz */
#define PRATELEIRA_INICIAL_G 10  /* prateleiras 10 e 11 ficam reservadas a volumes G */
#define MAX_PORTARIAS 10         /* portarias lidas pela central */
#define MAX_OPERACOES 20000      /* ids de operacoes ja aplicadas, guardados pela central */
#define MAX_CONSOLIDADAS (MAX_PORTARIAS * MAX_ENCOMENDAS) /* encomendas no consolidado */

/* ---------- Regras de negocio ---------- */
#define TAM_CODIGO 6             /* digitos do codigo de retirada */
#define CODIGO_MIN 100000        /* menor codigo de 6 digitos */
#define CODIGO_MAX 999999        /* maior codigo de 6 digitos */
#define MAX_TENTATIVAS 3         /* tentativas de codigo numa retirada */
#define DIAS_ALERTA 7            /* dias a partir dos quais uma pendencia e antiga */
#define APARTAMENTO_MAX 9999     /* maior numero de apartamento aceito */
#define DIAS_NO_MES 31           /* maior numero de dias de um mes (relatorio de pico) */

/* ---------- Tamanhos de texto (incluem o '\0') ---------- */
#define TAM_NOME 41
#define TAM_TRANSPORTADORA 31
#define TAM_CONTATO 41
#define TAM_DATA 17              /* "AAAA-MM-DD HH:MM" */
#define TAM_ID_OPERACAO 12       /* "P01-000123" */
#define TAM_LINHA 512            /* linha lida do teclado ou de arquivo */
#define TAM_CAMINHO 128          /* caminho de arquivo */

/* ---------- Enumeracoes ---------- */
typedef enum {
    STATUS_PENDENTE,
    STATUS_RETIRADA,
    STATUS_DEVOLVIDA
} StatusEncomenda;

typedef enum {
    CANAL_APP,
    CANAL_SMS,
    CANAL_INTERFONE
} CanalAviso;

typedef enum {
    OP_REGISTRO,
    OP_RETIRADA,
    OP_DEVOLUCAO
} TipoOperacao;

/* ---------- Estruturas ---------- */

/* Morador cadastrado em uma unidade (usado a partir da Sprint 2). */
typedef struct {
    int id;
    char nome[TAM_NOME];
    char bloco;                  /* letra maiuscula, de 'A' a 'Z' */
    int apartamento;
    CanalAviso canal;
    char contato[TAM_CONTATO];   /* vazio quando o canal e interfone */
    int ativo;                   /* 1 = ativo, 0 = inativo */
} Morador;

/* Volume recebido na portaria para uma unidade. */
typedef struct {
    int id;
    char bloco;                  /* letra maiuscula, de 'A' a 'Z' */
    int apartamento;
    char destinatario[TAM_NOME];
    char transportadora[TAM_TRANSPORTADORA];
    char tamanho;                /* 'P', 'M' ou 'G' */
    char recebida_em[TAM_DATA];
    int estante;                 /* indice da linha da matriz (0 a NUM_ESTANTES - 1) */
    int prateleira;              /* indice da coluna da matriz (0 a NUM_PRATELEIRAS - 1) */
    int codigo;                  /* codigo de retirada, de CODIGO_MIN a CODIGO_MAX */
    StatusEncomenda status;
    char retirada_em[TAM_DATA];  /* vazio enquanto pendente */
    char retirado_por[TAM_NOME]; /* vazio enquanto pendente */
} Encomenda;

/* Evento da portaria a sincronizar (usado a partir da Sprint 2). */
typedef struct {
    char id_operacao[TAM_ID_OPERACAO]; /* ex.: "P01-000123" */
    int id_portaria;
    char data_hora[TAM_DATA];
    TipoOperacao tipo;
    int id_encomenda;
    char bloco;
    int apartamento;
} Operacao;

/* Encomenda como a central a conhece, montada so a partir das operacoes. */
typedef struct {
    int id_portaria;             /* 1 a MAX_PORTARIAS (P01 = 1) */
    int id_encomenda;            /* id da encomenda no arquivo da portaria */
    char bloco;
    int apartamento;
    StatusEncomenda status;
    char recebida_em[TAM_DATA];
    char retirada_em[TAM_DATA];  /* vazio enquanto pendente ou devolvida */
} EncomendaConsolidada;

#endif /* TIPOS_H */
