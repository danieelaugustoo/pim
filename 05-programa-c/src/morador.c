#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tipos.h"
#include "util.h"
#include "encomenda.h"
#include "morador.h"

/*
 * morador_canal_texto
 * Objetivo: obter o nome do canal para mostrar e gravar em arquivo.
 * Parametros: canal = valor do enum.
 * Retorno: "APP", "SMS" ou "INTERFONE".
 * Logica: switch sobre o enum.
 */
const char *morador_canal_texto(CanalAviso canal)
{
    switch (canal) {
    case CANAL_APP:
        return "APP";
    case CANAL_SMS:
        return "SMS";
    case CANAL_INTERFONE:
        return "INTERFONE";
    }
    return "INTERFONE";
}

/*
 * morador_canal_de_texto
 * Objetivo: converter o texto lido do arquivo em canal.
 * Parametros: texto = "APP", "SMS" ou "INTERFONE"; canal = recebe o valor.
 * Retorno: 1 se o texto e conhecido; 0 caso contrario.
 */
int morador_canal_de_texto(const char *texto, CanalAviso *canal)
{
    if (strcmp(texto, "APP") == 0) {
        *canal = CANAL_APP;
    } else if (strcmp(texto, "SMS") == 0) {
        *canal = CANAL_SMS;
    } else if (strcmp(texto, "INTERFONE") == 0) {
        *canal = CANAL_INTERFONE;
    } else {
        return 0;
    }
    return 1;
}

/*
 * morador_so_digitos (auxiliar interna)
 * Objetivo: conferir se um texto tem apenas digitos.
 * Parametros: texto = texto a conferir.
 * Retorno: 1 se todos os caracteres sao digitos; 0 caso contrario.
 */
static int morador_so_digitos(const char *texto)
{
    size_t i;

    for (i = 0; texto[i] != '\0'; i++) {
        if (!isdigit((unsigned char)texto[i])) {
            return 0;
        }
    }
    return 1;
}

/*
 * morador_contato_valido
 * Objetivo: validar o contato conforme o canal escolhido (US07).
 * Parametros: canal = canal de aviso; contato = texto informado.
 * Retorno: 1 se o contato serve para o canal; 0 caso contrario.
 * Logica: APP exige um identificador nao vazio; SMS exige um celular com 10
 *   ou 11 digitos; INTERFONE nao usa contato, entao sempre serve.
 */
int morador_contato_valido(CanalAviso canal, const char *contato)
{
    size_t n = strlen(contato);

    switch (canal) {
    case CANAL_APP:
        return n > 0;
    case CANAL_SMS:
        return (n == 10 || n == 11) && morador_so_digitos(contato);
    case CANAL_INTERFONE:
        return 1;
    }
    return 0;
}

/*
 * morador_proximo_id
 * Objetivo: escolher o id do proximo morador.
 * Parametros: moradores = vetor; quantidade = tamanho usado.
 * Retorno: maior id existente mais 1 (ou 1 se o vetor estiver vazio).
 */
int morador_proximo_id(const Morador moradores[], int quantidade)
{
    int i;
    int maior = 0;

    for (i = 0; i < quantidade; i++) {
        if (moradores[i].id > maior) {
            maior = moradores[i].id;
        }
    }
    return maior + 1;
}

/*
 * morador_texto_igual (auxiliar interna)
 * Objetivo: comparar dois textos ignorando maiusculas e minusculas.
 * Parametros: a e b = textos.
 * Retorno: 1 se forem iguais; 0 caso contrario.
 * Logica: compara caractere a caractere depois de converter para minuscula.
 */
static int morador_texto_igual(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

/*
 * morador_criar
 * Objetivo: aplicar as regras de um novo cadastro (US07).
 * Parametros: moradores = vetor; quantidade = tamanho usado (aumenta em 1 se
 *   der certo); dados = morador com bloco, apartamento, nome, canal e contato
 *   preenchidos.
 * Retorno: MOR_OK, MOR_VETOR_CHEIO, MOR_CONTATO_INVALIDO ou MOR_DUPLICADO.
 * Logica: confere capacidade e contato; recusa o mesmo nome (sem diferenciar
 *   maiusculas) na mesma unidade; define o id e marca como ativo. No canal
 *   INTERFONE o contato fica vazio.
 */
int morador_criar(Morador moradores[], int *quantidade, const Morador *dados)
{
    Morador novo = *dados;
    int i;

    if (*quantidade >= MAX_MORADORES) {
        return MOR_VETOR_CHEIO;
    }
    if (!morador_contato_valido(novo.canal, novo.contato)) {
        return MOR_CONTATO_INVALIDO;
    }
    for (i = 0; i < *quantidade; i++) {
        if (moradores[i].bloco == novo.bloco && moradores[i].apartamento == novo.apartamento &&
            morador_texto_igual(moradores[i].nome, novo.nome)) {
            return MOR_DUPLICADO;
        }
    }
    if (novo.canal == CANAL_INTERFONE) {
        novo.contato[0] = '\0';
    }
    novo.id = morador_proximo_id(moradores, *quantidade);
    novo.ativo = 1;
    moradores[*quantidade] = novo;
    (*quantidade)++;
    return MOR_OK;
}

/*
 * morador_ler_contato (auxiliar interna)
 * Objetivo: pedir o contato ate ele servir para o canal.
 * Parametros: canal = canal escolhido (APP ou SMS); dest = recebe o contato.
 * Retorno: 1 se leu um contato valido; 0 se a entrada acabou.
 */
static int morador_ler_contato(CanalAviso canal, char *dest)
{
    const char *pergunta = canal == CANAL_APP ? "Identificador no app: "
                                              : "Celular (10 ou 11 digitos): ";

    for (;;) {
        if (!util_ler_texto(pergunta, dest, TAM_CONTATO)) {
            return 0;
        }
        if (morador_contato_valido(canal, dest)) {
            return 1;
        }
        printf("Contato invalido para o canal %s.\n", morador_canal_texto(canal));
    }
}

/*
 * morador_cadastrar (interativa)
 * Objetivo: cadastrar um morador com o canal de aviso preferido (US07).
 * Parametros: moradores = vetor; quantidade = tamanho usado.
 * Retorno: 1 se cadastrou (o chamador deve salvar); 0 caso contrario.
 * Logica: le unidade, nome e canal; pede o contato so quando o canal exige;
 *   chama morador_criar e explica o motivo se for recusado.
 */
int morador_cadastrar(Morador moradores[], int *quantidade)
{
    Morador dados;
    int opcao;
    int resultado;

    memset(&dados, 0, sizeof dados);
    printf("\n--- Cadastrar morador ---\n");
    if (!encomenda_ler_unidade(&dados.bloco, &dados.apartamento) ||
        !util_ler_texto("Nome: ", dados.nome, TAM_NOME) ||
        !util_ler_inteiro("Canal de aviso (1 - APP, 2 - SMS, 3 - INTERFONE): ", 1, 3, &opcao)) {
        return 0;
    }
    dados.canal = (CanalAviso)(opcao - 1);
    if (dados.canal != CANAL_INTERFONE && !morador_ler_contato(dados.canal, dados.contato)) {
        return 0;
    }
    resultado = morador_criar(moradores, quantidade, &dados);
    if (resultado == MOR_VETOR_CHEIO) {
        printf("Limite de %d moradores atingido. Morador NAO cadastrado.\n", MAX_MORADORES);
    } else if (resultado == MOR_CONTATO_INVALIDO) {
        printf("Contato invalido. Morador NAO cadastrado.\n");
    } else if (resultado == MOR_DUPLICADO) {
        printf("Ja existe um morador com esse nome nessa unidade. Morador NAO cadastrado.\n");
    }
    if (resultado != MOR_OK) {
        return 0;
    }
    printf("Morador %d cadastrado em %c-%d (canal %s).\n", moradores[*quantidade - 1].id,
           dados.bloco, dados.apartamento, morador_canal_texto(dados.canal));
    return 1;
}

/*
 * morador_listar
 * Objetivo: mostrar os moradores cadastrados.
 * Parametros: moradores = vetor; quantidade = tamanho usado.
 * Retorno: quantos moradores foram mostrados.
 * Logica: percorre o vetor imprimindo uma linha por morador; se estiver vazio,
 *   avisa.
 */
int morador_listar(const Morador moradores[], int quantidade)
{
    int i;
    char unidade[16];

    if (quantidade == 0) {
        printf("Nenhum morador cadastrado.\n");
        return 0;
    }
    printf("%-4s %-7s %-24s %-10s %-13s %s\n", "ID", "UNIDADE", "NOME", "CANAL", "CONTATO", "ATIVO");
    for (i = 0; i < quantidade; i++) {
        snprintf(unidade, sizeof unidade, "%c-%d", moradores[i].bloco, moradores[i].apartamento);
        printf("%-4d %-7s %-24.24s %-10s %-13.13s %s\n", moradores[i].id, unidade,
               moradores[i].nome, morador_canal_texto(moradores[i].canal),
               moradores[i].contato[0] == '\0' ? "-" : moradores[i].contato,
               moradores[i].ativo ? "sim" : "nao");
    }
    printf("Total de moradores: %d\n", quantidade);
    return quantidade;
}

/*
 * morador_localizar_para_aviso
 * Objetivo: escolher quem avisar quando chega uma encomenda (US08).
 * Parametros: moradores = vetor; quantidade = tamanho usado; bloco e
 *   apartamento = unidade da encomenda; destinatario = nome na etiqueta.
 * Retorno: indice do morador escolhido, ou -1 se a unidade nao tem morador
 *   ativo cadastrado.
 * Logica: primeiro procura o morador ativo da unidade cujo nome e o do
 *   destinatario; se nao achar, usa o primeiro morador ativo da unidade.
 */
int morador_localizar_para_aviso(const Morador moradores[], int quantidade, char bloco,
                                 int apartamento, const char *destinatario)
{
    int i;
    int primeiro = -1;

    for (i = 0; i < quantidade; i++) {
        if (moradores[i].ativo && moradores[i].bloco == bloco &&
            moradores[i].apartamento == apartamento) {
            if (morador_texto_igual(moradores[i].nome, destinatario)) {
                return i;
            }
            if (primeiro < 0) {
                primeiro = i;
            }
        }
    }
    return primeiro;
}
