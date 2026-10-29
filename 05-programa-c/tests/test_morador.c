#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tipos.h"
#include "util.h"
#include "morador.h"

/* Preenche os dados que o porteiro digita no cadastro. */
static Morador dados_de(char bloco, int apto, const char *nome, CanalAviso canal, const char *contato)
{
    Morador m;

    memset(&m, 0, sizeof m);
    m.bloco = bloco;
    m.apartamento = apto;
    util_copiar_texto(m.nome, TAM_NOME, nome);
    m.canal = canal;
    util_copiar_texto(m.contato, TAM_CONTATO, contato);
    return m;
}

/* US07: o contato precisa servir para o canal. */
static void testar_contato_valido(void)
{
    assert(morador_contato_valido(CANAL_APP, "app-0001") == 1);
    assert(morador_contato_valido(CANAL_APP, "") == 0);
    assert(morador_contato_valido(CANAL_SMS, "11900000002") == 1);
    assert(morador_contato_valido(CANAL_SMS, "1133334444") == 1);
    assert(morador_contato_valido(CANAL_SMS, "119000000") == 0);
    assert(morador_contato_valido(CANAL_SMS, "119000000021") == 0);
    assert(morador_contato_valido(CANAL_SMS, "1190000000a") == 0);
    assert(morador_contato_valido(CANAL_SMS, "") == 0);
    assert(morador_contato_valido(CANAL_INTERFONE, "") == 1);
}

/* Conversao do canal em texto e de volta. */
static void testar_canal(void)
{
    CanalAviso c = CANAL_APP;

    assert(strcmp(morador_canal_texto(CANAL_APP), "APP") == 0);
    assert(strcmp(morador_canal_texto(CANAL_SMS), "SMS") == 0);
    assert(strcmp(morador_canal_texto(CANAL_INTERFONE), "INTERFONE") == 0);
    assert(morador_canal_de_texto("SMS", &c) == 1 && c == CANAL_SMS);
    assert(morador_canal_de_texto("INTERFONE", &c) == 1 && c == CANAL_INTERFONE);
    assert(morador_canal_de_texto("EMAIL", &c) == 0);
}

/* Cadastro: id, ativo, interfone sem contato, recusas. */
static void testar_criar(void)
{
    static Morador v[MAX_MORADORES];
    int n = 0;
    Morador d;
    int i;

    d = dados_de('A', 12, "Maria Souza", CANAL_APP, "app-0001");
    assert(morador_criar(v, &n, &d) == MOR_OK);
    assert(n == 1 && v[0].id == 1 && v[0].ativo == 1);

    d = dados_de('A', 12, "Joao Souza", CANAL_SMS, "11900000002");
    assert(morador_criar(v, &n, &d) == MOR_OK);
    assert(v[1].id == 2);

    /* interfone: o contato informado e descartado */
    d = dados_de('B', 101, "Carla Mendes", CANAL_INTERFONE, "qualquer coisa");
    assert(morador_criar(v, &n, &d) == MOR_OK);
    assert(v[2].contato[0] == '\0');

    /* contato invalido para o canal */
    d = dados_de('C', 34, "Ana Ribeiro", CANAL_SMS, "123");
    assert(morador_criar(v, &n, &d) == MOR_CONTATO_INVALIDO);
    assert(n == 3);

    /* mesmo nome na mesma unidade, sem diferenciar maiusculas */
    d = dados_de('A', 12, "MARIA SOUZA", CANAL_APP, "app-9999");
    assert(morador_criar(v, &n, &d) == MOR_DUPLICADO);
    assert(n == 3);

    /* mesmo nome em outra unidade e permitido */
    d = dados_de('D', 7, "Maria Souza", CANAL_APP, "app-0007");
    assert(morador_criar(v, &n, &d) == MOR_OK);

    /* vetor cheio */
    for (i = n; i < MAX_MORADORES; i++) {
        d = dados_de('Z', i + 1, "Fulano", CANAL_APP, "app");
        assert(morador_criar(v, &n, &d) == MOR_OK);
    }
    assert(n == MAX_MORADORES);
    d = dados_de('Y', 1, "Alguem", CANAL_APP, "app");
    assert(morador_criar(v, &n, &d) == MOR_VETOR_CHEIO);
}

/* Escolha de quem avisar (US08). */
static void testar_localizar_para_aviso(void)
{
    Morador v[4];
    int n = 0;
    Morador d;

    d = dados_de('A', 12, "Maria Souza", CANAL_APP, "app-0001");
    morador_criar(v, &n, &d);
    d = dados_de('A', 12, "Joao Souza", CANAL_SMS, "11900000002");
    morador_criar(v, &n, &d);
    d = dados_de('B', 101, "Carla Mendes", CANAL_INTERFONE, "");
    morador_criar(v, &n, &d);

    /* acha pelo nome do destinatario, sem diferenciar maiusculas */
    assert(morador_localizar_para_aviso(v, n, 'A', 12, "joao souza") == 1);
    assert(morador_localizar_para_aviso(v, n, 'A', 12, "Maria Souza") == 0);
    /* nome desconhecido: o primeiro ativo da unidade */
    assert(morador_localizar_para_aviso(v, n, 'A', 12, "Outra Pessoa") == 0);
    /* unidade sem morador */
    assert(morador_localizar_para_aviso(v, n, 'C', 34, "Ana Ribeiro") == -1);
    /* morador inativo e ignorado */
    v[2].ativo = 0;
    assert(morador_localizar_para_aviso(v, n, 'B', 101, "Carla Mendes") == -1);
    v[0].ativo = 0;
    assert(morador_localizar_para_aviso(v, n, 'A', 12, "Maria Souza") == 1);
}

int main(void)
{
    testar_contato_valido();
    testar_canal();
    testar_criar();
    testar_localizar_para_aviso();
    printf("test_morador: OK\n");
    return 0;
}
