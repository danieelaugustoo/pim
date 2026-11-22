# Guia de estudo do Daniel: Programação em C e demonstração

Apresentação do PIM II na quarta-feira, 25/11. A ordem é Ysaac, Adilson, Lucas, **você** e Pedro. O seu bloco tem cerca de **7 minutos**: 3 de fala e 4 de demonstração. No deck completo (`slides-pim-apresentacao-completa.pptx`), os seus slides são o **8** (Programação estruturada em C) e o **9** (Demonstração ao vivo). O **12** é a reserva, para usar só se o programa falhar.

Tudo o que está aqui foi conferido no código e no trabalho. A demonstração foi executada de novo em 22/11, e as saídas batem com o roteiro.

## Plano de estudo até quarta

| Quando | O que fazer | Tempo |
|---|---|---|
| Domingo | Ler as partes 1 a 4. Abrir o código e achar cada função citada. | 1 h |
| Segunda | Parte 5 com o código aberto ao lado. Ensaiar a fala da parte 1 em voz alta, com cronômetro, até caber em 3 minutos. Fazer a demonstração completa 2 vezes no notebook. | 2 a 3 h |
| Terça | Partes 7 e 8. Pedir para alguém escolher 5 perguntas da parte 8 e te perguntar sem aviso. Ensaiar com o grupo, se der. À noite, preparar o notebook (parte 6). | 2 a 3 h |
| Quarta | Reler a cola (parte 10). Chegar cedo e preparar a demonstração 10 minutos antes. | 30 min |

Ensaiar em voz alta três vezes ajuda mais do que ler o guia dez vezes.

---

## 1. A sua fala (3 minutos)

Comece agradecendo o Lucas. Fale com as suas palavras; o texto abaixo serve de base.

**Slide 8. O que é (30 s).** "Eu fiquei com a programação em C. São dois programas. O primeiro é a **portaria**, que o porteiro usaria no lugar do caderno: registra a encomenda, diz em que prateleira guardar, gera um código de 6 dígitos para o morador, avisa o morador e registra a retirada. O segundo é a **central**, que fica na administradora: junta o que as portarias enviaram e gera um relatório de todos os condomínios."

**Como foi feito (40 s).** "Usamos o C99, só com a biblioteca padrão da linguagem. Não foi preciso instalar nada, e o mesmo código roda no Windows e no Linux. Compilamos com os avisos do compilador ligados, com as opções `-Wall`, `-Wextra` e `-pedantic`, e o programa não gera nenhum aviso. O código é dividido em módulos: cada arquivo cuida de um assunto, como estante, código ou retirada, e o nome de cada função começa pelo nome do módulo. Toda função tem um comentário com objetivo, parâmetros, retorno e lógica, e toda entrada do teclado é validada antes de ser usada."

**A estante (30 s).** "Os dados ficam em vetores: até 500 encomendas e 300 moradores por portaria. A estante é uma **matriz de 4 linhas por 12 colunas**. Cada linha é a estante de um bloco, de A a D, e cada coluna é uma prateleira. Zero quer dizer livre, e um número é o id da encomenda guardada ali. As prateleiras 10 e 11 ficam para volumes grandes."

**Três algoritmos (60 s, aponte a Figura 8).** "O **A1** escolhe a prateleira: começa pela estante do bloco do morador e pega a primeira prateleira livre do tamanho certo. Se a estante estiver cheia, tenta a próxima, dando a volta, como mostra o fluxograma. O **A3** é a retirada: o porteiro digita o código, o programa mostra a unidade e o nome, e o porteiro confirma com o morador antes de entregar, com até três tentativas. O **A5** fica na central: cada operação tem um número único, e a central anota os números que já aplicou. Se o mesmo arquivo chegar duas vezes, nada é duplicado. Isso se chama consolidação idempotente."

**Testes e passagem (20 s).** "Temos nove conjuntos de testes automáticos, todos passando, e um deles processa o mesmo arquivo duas vezes para provar que nada se duplica. Agora vou mostrar funcionando." (Vá para o slide 9.)

---

## 2. Palavras técnicas explicadas de forma simples

Use a explicação da direita na primeira vez que disser a palavra.

| Termo | Como explicar |
|---|---|
| Linguagem C | Linguagem de programação criada nos anos 1970, próxima da máquina, que gera programas pequenos e rápidos. |
| C99 | A versão da linguagem C padronizada em 1999. O código segue essa versão. |
| Compilar | Traduzir o código que escrevemos para um programa que o computador executa (o `.exe`). Quem faz isso é o compilador, o `gcc`. |
| Aviso (*warning*) | O compilador dizendo "isso parece errado", mesmo quando o programa compila. Nosso código compila com zero avisos. |
| Biblioteca padrão | A caixa de ferramentas que já vem com a linguagem: funções prontas para escrever na tela, ler arquivos, comparar textos e pegar a hora. |
| Arquivo `.h` (cabeçalho) | A lista do que um módulo oferece. O `.c` tem o código, e o `.h` diz quais funções existem. |
| Módulo | Um par `.c` e `.h` que cuida de um assunto, como `estante.c` e `estante.h`. |
| Função | Um pedaço de código com nome que faz uma tarefa, como `estante_alocar_posicao`. |
| Vetor | Uma fileira de variáveis do mesmo tipo, acessadas pelo número: `encomendas[0]`, `encomendas[1]`... |
| Matriz | Um vetor com linhas e colunas, como uma planilha: `estante[linha][coluna]`. |
| `struct` | Uma ficha com vários campos. A `Encomenda` tem bloco, apartamento, destinatário, código, status... |
| `enum` | Uma lista de nomes para valores fixos: `STATUS_PENDENTE`, `STATUS_RETIRADA`, `STATUS_DEVOLVIDA`. |
| Ponteiro | Uma variável que guarda o endereço de outra. Serve para uma função devolver mais de um resultado. |
| Programação estruturada | Programar só com sequência, decisão (`if`, `switch`) e repetição (`for`, `while`), dividindo o problema em funções pequenas. |
| CSV | Uma planilha em texto: cada linha é um registro, e os campos são separados por ponto e vírgula. |
| Fila de sincronização | Funciona como a caixa de saída do e-mail: as operações esperam num arquivo até a internet voltar. |
| Idempotente | Fazer a mesma coisa duas vezes dá o mesmo resultado que fazer uma vez. É como apertar duas vezes o botão do elevador: ele não vem duas vezes. |
| Teste automatizado | Um programa que confere o nosso programa sozinho. Se uma conferência falha, ele para e mostra a linha. |
| Makefile e `build.bat` | A receita de compilação: um comando compila tudo (`make` no Linux, `build.bat` no Windows). |
| Estouro de buffer | Escrever mais texto do que cabe numa variável, invadindo a memória ao lado. O `fgets` com tamanho evita isso. |
| Semente do sorteio | O ponto de partida dos números aleatórios. Usamos a hora atual para os códigos mudarem a cada execução. |

---

## 3. As bibliotecas que o programa usa

Em C, uma biblioteca é um conjunto de funções prontas, incluído com `#include <nome.h>`. O programa usa **só a biblioteca padrão**, que vem com qualquer compilador C. Por isso nada foi instalado, e o mesmo código compila no Windows e no Linux. Bibliotecas como `conio.h` e `windows.h` ficaram de fora porque só existem no Windows.

| Biblioteca | Para que serve | O que usamos dela | Onde |
|---|---|---|---|
| `stdio.h` | Entrada e saída: tela, teclado e arquivos | `printf` (escrever na tela), `fgets` (ler uma linha do teclado ou de um arquivo), `fopen`, `fclose` e `fprintf` (abrir, fechar e gravar os CSV), `snprintf` (montar texto com limite de tamanho), `sscanf` (ler os números de uma data) | Quase todos os módulos |
| `stdlib.h` | Utilidades gerais | `rand` e `srand` (sorteio do código de retirada) | `codigo.c` |
| `string.h` | Texto e memória | `strlen` (tamanho), `strcmp` (comparar), `strchr` (procurar uma letra), `memset` (zerar uma ficha), `memmove` e `memcpy` (copiar trechos) | `util`, `encomenda`, `sincronizacao`, `consolidacao` e outros |
| `ctype.h` | Classificar caracteres | `isdigit` (é dígito?), `isspace` (é espaço?), `isalpha` (é letra?), `toupper` e `tolower` (maiúscula e minúscula) | `util`, `estante`, `morador`, `sincronizacao` |
| `time.h` | Data e hora | `time` (hora atual), `localtime` e `strftime` (formatar como `2026-11-25 14:30`) | `util.c` e `codigo.c` |
| `assert.h` | Testes | `assert(condicao)`: se a condição for falsa, o teste para e mostra a linha | Só na pasta `tests` |

---

## 4. Boas práticas que você pode citar

| Prática | Por que | Onde ver |
|---|---|---|
| C99 e zero avisos com `-Wall -Wextra -pedantic` | Com os avisos ligados, o compilador aponta erros cedo | `Makefile` e `build.bat` (linha das *flags*) |
| Só a biblioteca padrão | Compila em qualquer sistema com `gcc`, sem instalar nada | Os `#include` no topo de cada `.c` |
| Um módulo por assunto | Cada arquivo tem uma responsabilidade, o que facilita achar e testar | `src/` e `include/` |
| Nome do módulo no início da função | Pelo nome você sabe em que arquivo a função está | `estante_alocar_posicao`, `codigo_gerar_unico` |
| Convenção de nomes | Tipos em PascalCase (`Encomenda`), constantes em maiúsculas (`MAX_ENCOMENDAS`), enums com prefixo (`STATUS_`, `CANAL_`, `OP_`) | `tipos.h` |
| Constantes no lugar de números soltos | Para mudar a capacidade, muda-se uma linha | `#define MAX_ENCOMENDAS 500` em `tipos.h` |
| *Header guard* | Impede que o mesmo `.h` seja incluído duas vezes | `#ifndef TIPOS_H` ... `#endif` |
| Vetores e matrizes estáticos, sem `malloc` | Pedido da disciplina; a memória fica previsível e não há vazamento | `portaria.c`, linhas 17 a 21 |
| Leitura com `fgets` e validação | O `fgets` limita o tamanho; depois o texto é convertido e conferido; se for inválido, a pergunta se repete | `util_ler_linha`, `util_ler_inteiro` |
| Nunca `scanf("%s")` | Ele não sabe o tamanho do destino e pode estourar a memória | Regra do projeto |
| Cópia de texto com `snprintf` | Recebe o tamanho do destino e sempre termina o texto com `'\0'` | `util_copiar_texto` |
| Funções auxiliares `static` | Só existem dentro do próprio arquivo, então ninguém de fora as chama por engano | `estante_faixa`, `retirada_confirmar` |
| `const` nos parâmetros só de leitura | O compilador impede alterar o vetor por engano | `const Encomenda encomendas[]` |
| Códigos de retorno com nome | `ENC_OK`, `SINC_OFFLINE` e `CONS_APLICADA` dizem o que aconteceu, melhor que 0, 1 e 2 | `encomenda.h`, `sincronizacao.h`, `consolidacao.h` |
| Conferir erro de arquivo | Se `fopen` ou `fclose` falhar, o programa avisa e não apaga a fila | `portaria_salvar_encomendas`, `sincronizacao_enviar_pendentes` |
| Uma única fonte de verdade | A estante não é gravada em arquivo: é remontada a partir das encomendas pendentes ao abrir | `estante_reconstruir` |
| Comentário padrão em toda função | Objetivo, parâmetros, retorno e lógica | Todas as funções |
| Textos em ASCII, sem acento | Evita letras quebradas no console do Windows e nos arquivos | Mensagens do programa |
| `(unsigned char)` antes de `isdigit` e `toupper` | Essas funções exigem valores positivos, e uma letra com acento pode virar número negativo | `util.c`, `estante.c` |
| Testes automatizados | 9 conjuntos com `assert`, rodados com um comando | `tests/` |

---

## 5. O código por dentro

### 5.1 Mapa dos arquivos (pasta `05-programa-c`)

| Arquivo | O que faz |
|---|---|
| `include/tipos.h` | Constantes (capacidades e regras), enums e structs usados por todos |
| `src/portaria.c` | O programa da portaria: `main`, menu e chamadas |
| `src/central.c` | O programa da central: carrega o estado, processa os logs e grava o relatório |
| `src/util.c` | Leitura validada do teclado, conversões, datas e divisão de linhas do CSV |
| `src/estante.c` | Matriz da estante e algoritmo A1 |
| `src/codigo.c` | Sorteio (A2) e busca do código de retirada |
| `src/encomenda.c` | Registro, listagem e busca de encomendas |
| `src/retirada.c` | Retirada com código e confirmação (A3) |
| `src/morador.c` e `src/aviso.c` | Cadastro de moradores e aviso simulado (app, SMS ou interfone) |
| `src/persistencia.c` | Ler e gravar os CSV da portaria |
| `src/sincronizacao.c` | Fila de operações e envio para a rede simulada (A4) |
| `src/consolidacao.c` | Consolidação idempotente na central (A5) e relatório consolidado |
| `src/relatorio.c` | Mapa da estante, pendências antigas e dia de pico (A6) |
| `tests/` | Os 9 conjuntos de testes |
| `algoritmos/` | Pseudocódigo e fluxogramas dos 6 algoritmos |
| `Makefile` e `build.bat` | Compilação no Linux e no Windows |

São 11 módulos e 2 programas: cerca de 3.300 linhas nos `.c`, 550 nos `.h` e 1.400 nos testes, contando os comentários.

### 5.2 Os dados em memória

A ficha da encomenda (`tipos.h`):

```c
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
```

Os dados da portaria (`portaria.c`):

```c
static Encomenda encomendas[MAX_ENCOMENDAS];
static int quantidade_encomendas = 0;
static Morador moradores[MAX_MORADORES];
static int quantidade_moradores = 0;
static int estante[NUM_ESTANTES][NUM_PRATELEIRAS];
```

O vetor tem 500 posições, e `quantidade_encomendas` diz quantas estão em uso. A matriz tem 4 x 12 = 48 posições.

### 5.3 O caminho de uma encomenda, do registro à central

1. **Menu, opção 1.** `portaria_executar` chama `encomenda_registrar`, que lê bloco, apartamento, destinatário, transportadora e tamanho, todos validados.
2. **`encomenda_criar`.** Define o id (o maior existente mais 1), escolhe a posição (A1), gera o código (A2), grava data e hora e põe o status `PENDENTE`. Se não houver código, devolve a posição à estante.
3. **`portaria_apos_registro`.** Salva o CSV, põe a operação `REGISTRO` na fila (com id como `P01-000011`) e avisa o morador: por app ou SMS (simulado na tela) ou pelo interfone, com o código para imprimir.
4. **Opção 8, online.** O A4 copia a fila para `dados/rede/P01.log` e esvazia a fila.
5. **Programa `central`.** O A5 lê o log, aplica só as operações novas, grava os arquivos da central e o relatório.

### 5.4 Os seis algoritmos

**A1, alocar a posição na estante (`estante_alocar_posicao`, em `estante.c`)**

```c
if (isalpha((unsigned char)bloco)) {
    preferida = (toupper((unsigned char)bloco) - 'A') % NUM_ESTANTES;
}
estante_faixa(tamanho, &inicio, &fim);
for (k = 0; k < NUM_ESTANTES; k++) {
    candidata = (preferida + k) % NUM_ESTANTES;
    prateleira = estante_procurar_livre(estante, candidata, inicio, fim);
    if (prateleira >= 0) {
        estante[candidata][prateleira] = id_encomenda;
        *linha = candidata;
        *coluna = prateleira;
        return 1;
    }
}
return 0;
```

1. **Estante preferida.** A letra do bloco vira número: A = 0, B = 1, C = 2, D = 3. O `%` é o resto da divisão por 4, então o bloco E (4) volta para a estante 0.
2. **Faixa do tamanho.** `estante_faixa`: volume G usa as prateleiras 10 e 11; P e M usam de 0 a 9.
3. **Ordem circular.** O `for` tenta as 4 estantes. `(preferida + k) % 4` faz dar a volta: se a preferida é a D (3), a ordem é D, A, B, C.
4. **Primeira livre.** `estante_procurar_livre` varre a linha da esquerda para a direita e devolve a primeira célula com 0.
5. **Resultado.** Achou: grava o id na célula, devolve linha e coluna pelos ponteiros e retorna 1. Não achou: retorna 0, e a encomenda não é registrada ("Estante cheia para esse tamanho de volume").

Na demonstração, D-7 com tamanho M vai para a estante D, prateleira 0.

**A2, gerar o código único (`codigo_gerar_unico`, em `codigo.c`)**

```c
for (tentativa = 0; tentativa < CODIGO_MAX_SORTEIOS; tentativa++) {
    codigo = codigo_sortear();
    if (!codigo_existe_pendente(encomendas, quantidade, codigo)) {
        return codigo;
    }
}
return 0;
```

Sorteia um número de 100000 a 999999 e repete se alguma encomenda **pendente** já usa esse número, com limite de 1000 sorteios para nunca travar. A semente é a hora atual (`srand(time(NULL))`, ao abrir o programa). Um detalhe que vale citar: em alguns compiladores o `rand()` só vai até 32767, o que daria poucos códigos diferentes. Por isso `codigo_sortear` junta duas chamadas antes de reduzir o número à faixa de 6 dígitos.

**A3, retirada (`retirada_registrar`, em `retirada.c`)**

1. Se não há pendentes, avisa e volta.
2. Pede o código, com até 3 tentativas (`retirada_buscar_codigo`). Cada código sem encomenda pendente mostra "tentativa 1 de 3"; na terceira falha, a retirada é negada e nada muda.
3. Achou a encomenda: mostra a ficha, sem o código, e pergunta S ou N (`retirada_confirmar`).
4. N cancela, e a encomenda continua pendente. S pede o nome de quem retira.
5. `retirada_efetuar` muda o status para `RETIRADA`, grava data, hora e nome e libera a posição na estante.
6. A portaria salva o CSV e põe a operação `RETIRADA` na fila.

A confirmação existe porque um código digitado errado pode, por azar, ser o de outra encomenda pendente (cerca de 1 em 9.000 com 100 pendentes). Se duas pendentes tiverem o mesmo código, o que só acontece se alguém editar o arquivo à mão, a retirada é negada.

**A4, sincronizar (`sincronizacao_enviar_pendentes`, em `sincronizacao.c`)**

- Cada registro ou retirada vira uma operação com id único, como `P01-000011`: a portaria mais um número sequencial. O último número fica em `P01-sequencia.txt`, então não se repete nem depois de fechar o programa.
- A operação entra na fila (`P01-fila.csv`) mesmo com a portaria offline.
- Opção 8 offline: só mostra quantas operações aguardam.
- Opção 8 online: copia cada linha da fila para `dados/rede/P01.log` e **só depois** esvazia a fila. Se o programa cair entre as duas etapas, as operações vão de novo no próximo envio, e a central ignora as repetidas.
- A pasta `dados/rede` faz o papel da internet. No sistema completo seria uma API acessada por HTTPS dentro da VPN.

**A5, consolidar na central (`consolidacao_processar_portaria`, em `consolidacao.c`)**

O coração do A5 é `consolidacao_aplicar_operacao`:

```c
if (consolidacao_operacao_ja_aplicada(estado, operacao->id_operacao)) {
    return CONS_JA_APLICADA;
}
if (estado->qtd_aplicadas >= MAX_OPERACOES || !consolidacao_efeito(estado, operacao)) {
    return CONS_REJEITADA;
}
util_copiar_texto(estado->aplicadas[estado->qtd_aplicadas], TAM_ID_OPERACAO,
                  operacao->id_operacao);
estado->qtd_aplicadas++;
return CONS_APLICADA;
```

1. Ao abrir, a central carrega `operacoes-aplicadas.csv` (os ids já aplicados) e `encomendas-consolidadas.csv`.
2. Para cada linha dos logs de P01 a P10, pula o cabeçalho e valida os 7 campos. Linha mal formada conta como inválida.
3. Id já na lista: ignora ("ja aplicada").
4. Id novo: aplica o efeito. `REGISTRO` cria a encomenda pendente, `RETIRADA` muda o status e grava a data, `DEVOLUCAO` marca como devolvida. Se o efeito não faz sentido, como a retirada de uma encomenda que a central não conhece, a operação é rejeitada e não é anotada, para poder ser aplicada depois.
5. Aplicou: anota o id. No fim, grava os arquivos e o relatório.

Na central, a encomenda é identificada pelo par portaria e id, porque a encomenda 9 pode existir na P01 e na P02.

**A6, relatórios (`relatorio.c`)**

Mapa da estante (X ocupada, ponto livre, e o percentual de ocupação), pendências com mais de 7 dias (exatamente 7 não gera alerta), registros por dia do mês com o dia de pico (em empate, o mais cedo) e o relatório consolidado da central por portaria.

### 5.5 Como a leitura do teclado é protegida

```c
for (;;) {
    if (!util_ler_linha(rotulo, linha, TAM_LINHA)) {
        return 0;
    }
    if (util_converter_inteiro(linha, minimo, maximo, valor)) {
        return 1;
    }
    printf("Valor invalido. Digite um numero entre %d e %d.\n", minimo, maximo);
}
```

- `util_ler_linha` usa o `fgets` com o tamanho da variável e tira o Enter do fim. Se a pessoa digitou mais do que cabe, descarta o resto para não atrapalhar a próxima pergunta.
- `util_converter_inteiro` aceita só dígitos (com sinal opcional), no máximo 9 dígitos para não estourar o `int`, e confere a faixa.
- O `for (;;)` repete até vir um valor válido.
- `util_ler_texto` exige texto não vazio, que caiba no campo, sem `;` (quebraria o CSV) e sem acento.
- `util_ler_letra` aceita uma única letra, converte para maiúscula e confere se está entre as permitidas (`PMG`, `SN` ou de A a Z).

### 5.6 Os arquivos de dados

| Arquivo | O que guarda |
|---|---|
| `dados/portarias/P01-encomendas.csv` | Encomendas da portaria 1 (13 campos por linha) |
| `dados/portarias/P01-moradores.csv` | Moradores e canal de aviso |
| `dados/portarias/P01-fila.csv` | Operações esperando envio |
| `dados/portarias/P01-sequencia.txt` | Último número de operação usado |
| `dados/portarias/P01-avisos.txt` | Registro dos avisos |
| `dados/rede/P01.log` | O que a portaria "enviou pela rede" |
| `dados/central/operacoes-aplicadas.csv` | Ids que a central já aplicou |
| `dados/central/encomendas-consolidadas.csv` | Encomendas como a central as conhece |
| `dados/central/relatorio-consolidado.txt` | Relatório por portaria |
| `dados/exemplo/` | Cópia dos dados de exemplo, para recomeçar a demonstração |

### 5.7 Os nove conjuntos de testes

| Conjunto | O que confere |
|---|---|
| `test_util` | Dias entre datas, conversão de números, divisão do CSV, aparar espaços, data e hora atual |
| `test_estante` | Estante do bloco, volume grande, estante cheia, tudo cheio, liberar, reconstruir |
| `test_codigo` | 6 dígitos, sem repetição entre pendentes, conferência, localizar pelo código |
| `test_encomenda` | Criar, sem vaga, retirada, retirada por código, status |
| `test_persistencia` | Primeira execução sem arquivo, gravar e ler de volta, linha inválida, caminho |
| `test_morador` | Contato válido para o canal, canal, cadastro, quem avisar |
| `test_sincronizacao` | Tipo e id, linha da fila, numeração, fila e envio |
| `test_consolidacao` | Mesmo log duas vezes, entre execuções, duas portarias com o mesmo id, inválidas e rejeitadas, efeito idempotente, relatório |
| `test_relatorio` | Ocupação, pendências antigas, pico mensal, consolidado |

### 5.8 Compilar e rodar

No Windows (PowerShell, dentro de `05-programa-c`):

```
.\build.bat
.\build.bat test
.\bin\portaria.exe 1
.\bin\central.exe
```

O primeiro compila `bin\portaria.exe` e `bin\central.exe`; o segundo compila e roda os 9 testes e termina com "Todos os testes passaram." No Linux, os equivalentes são `make`, `make test`, `bin/portaria 1` e `bin/central`.

---

## 6. A demonstração

### Terça à noite

1. Baixe o projeto numa pasta nova, para ter a versão atual do GitHub sem misturar com cópias antigas:

```
git clone https://github.com/danieelaugustoo/pim.git pim-apresentacao
cd pim-apresentacao\05-programa-c
.\build.bat
.\build.bat test
```

2. Os testes precisam terminar com "Todos os testes passaram." Se o Windows bloquear o `.exe` recém-compilado, repita o comando. Não mexa em configuração de segurança.
3. Faça a demonstração inteira uma vez, do começo ao fim.
4. Deixe o notebook carregado e separe o carregador e o adaptador de vídeo.

### 10 minutos antes

Dentro de `05-programa-c`, no PowerShell, limpe os dados e copie os de exemplo:

```
Remove-Item dados\portarias\*.csv, dados\portarias\*.txt -ea SilentlyContinue
Remove-Item dados\rede\*.log, dados\central\*.csv, dados\central\*.txt -ea SilentlyContinue
Copy-Item dados\exemplo\P01-*.* dados\portarias\
Copy-Item dados\exemplo\P0?.log dados\rede\
```

Abra dois terminais nessa pasta: o **terminal 1** para a portaria e o **terminal 2** para a central. Aumente a fonte (Ctrl + roda do mouse), desligue as notificações e deixe o PDF do trabalho aberto. Tenha papel e caneta para anotar o código.

### Passo a passo (cerca de 4 minutos)

| # | Faça | Vai aparecer | Diga |
|---|---|---|---|
| 1 | Terminal 2: `.\bin\central.exe` | `P01: 10 lida(s), 10 aplicada(s)`, `P02: 7 lida(s), 7 aplicada(s)` e `Total consolidado: 17 operacao(oes), 14 encomenda(s).` | "A central lê o que as duas portarias enviaram e aplica cada operação." |
| 2 | `.\bin\central.exe` de novo | `0 aplicada(s), 10 ja aplicada(s)` e `0 aplicada(s), 7 ja aplicada(s)` | "Rodei de novo com o mesmo arquivo e nada foi duplicado. Isso é a idempotência." |
| 3 | Terminal 1: `.\bin\portaria.exe 1`, opção `3` | 6 pendentes | "Essa é a portaria 1, com as encomendas que estão na estante." |
| 4 | Opção `5` | Mapa e `Ocupadas: 6 de 48 (12.5%)` | "A estante é a matriz 4 por 12. X é ocupado, ponto é livre." |
| 5 | Opção `9` | `Portaria agora OFFLINE.` | "Agora a internet caiu. A portaria continua funcionando." |
| 6 | Opção `1`: `D`, `7`, `Rafael Costa`, `Transp Alfa`, `M` | `Encomenda 9 registrada para D-7.`, `Guardar na estante D, prateleira 0.`, o código e `Aviso: ligar pelo interfone para D-7` | "O sistema escolheu a prateleira, gerou o código e mandou avisar pelo interfone, que é o canal desse morador." **Anote o código.** |
| 7 | Opção `1`: `D`, `15`, `Beatriz Alves`, `Transp Gama`, `P` | `Encomenda 10 registrada para D-15.` e `Aviso simulado por SMS para 11900000007` | "Outro morador, outro canal: SMS." |
| 8 | Opção `8` | `Portaria OFFLINE: 2 operacao(oes) aguardando envio.` | "Sem internet, as operações esperam na fila." |
| 9 | Opção `9` e depois `8` | `Portaria agora ONLINE.` e `2 operacao(oes) enviada(s) para dados/rede/P01.log.` | "A internet voltou, e a fila foi enviada." |
| 10 | Terminal 2: `.\bin\central.exe` | `P01: 12 lida(s), 2 aplicada(s), 10 ja aplicada(s)` e `Total consolidado: 19 operacao(oes), 16 encomenda(s).` | "A central aplicou só as 2 novas." |
| 11 | Terminal 1: opção `2`, código errado `123456` | `Nenhuma encomenda pendente com esse codigo (tentativa 1 de 3).` | "Código errado. São até 3 tentativas." |
| 12 | Digite o código certo | A ficha `9 D-7 Rafael Costa...` e a pergunta S/N | "O código achou a encomenda. Agora o porteiro confere com o morador." |
| 13 | `N` | `Retirada cancelada. A encomenda continua pendente.` | "Se não bater, nada muda." |
| 14 | Opção `2`, código certo, `S`, `Rafael Costa` | `Retirada registrada: encomenda 9, em <data e hora>, por Rafael Costa.` | "Registrou quem retirou e quando, e liberou a prateleira." |
| 15 | Opção `8`; terminal 2: `.\bin\central.exe` | `1 aplicada(s), 12 ja aplicada(s)` e `Total consolidado: 20 operacao(oes), 16 encomenda(s).` | "A retirada também chegou à central." |
| 16 | `notepad dados\central\relatorio-consolidado.txt` | Tabela por portaria | "Esse é o relatório que a administradora vê de todos os condomínios." |

**Versão curta, se o tempo apertar:** passos 1, 2, 5, 6, 8, 9, 10, 14 e 15.

**O que muda no dia:**

- O código de retirada é sorteado: leia o que aparecer na tela.
- A coluna ANTIGAS depende da data. Em 22/11 deu 6 na P01 e 5 na P02. No trabalho (Quadro 2) aparecem 2 e 0 porque o relatório foi gerado em 29/10. Se perguntarem, diga: "o relatório depende da data de hoje".
- O PICO da P01 vai ser o próprio dia da apresentação, com 2 registros.

**Se algo der errado:**

- `.exe` bloqueado pelo Windows: repita o comando uma vez.
- "ERRO: nao foi possivel abrir os arquivos": o terminal não está na pasta `05-programa-c`.
- Digitou algo inválido: o programa pergunta de novo. Siga em frente.
- Travou de vez: vá para o slide 12 (reserva) e explique o fluxo pela Figura 5 (diagrama de sequência).
- Para recomeçar do zero, repita os comandos de "10 minutos antes".

---

## 7. O resto do trabalho: o mínimo que você precisa saber

### 7.1 Organização e pesquisa (Ysaac)

**Em uma frase:** as portarias da Administradora Morada Central controlam as encomendas num caderno, o que gera extravios, entregas à pessoa errada e sobrecarga dos porteiros, e a proposta é um nó em cada portaria que funciona sem internet e uma central que consolida sem duplicar.

- **Números:** 10 condomínios (de 2 a 4 blocos cada), cerca de 960 unidades e 40 porteiros (4 por condomínio, em escala 12x36). Sete problemas: extravio e entrega errada, falta de rastreabilidade, tempo do porteiro, aviso falho, acúmulo de volumes, falta de dados para a sede e internet instável.
- **Pergunta de pesquisa:** como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo que os porteiros gastam com encomendas?
- **Termos:** pesquisa **aplicada** (resolve um problema prático), **exploratória** (organiza um problema pouco estudado) e **qualitativa** (analisa sem medir em números).
- **O que já existe:** aplicativos de condomínio (como o ALL Condo, com fotos e QR code), armários inteligentes e portaria remota. As páginas consultadas não informam operação sem internet nem consolidação de vários condomínios.
- **Cuidado:** não houve levantamento de campo. Não diga que os concorrentes não têm algo; diga que as páginas não informam. Fale em "dados de exemplo".

### 7.2 Engenharia de software (Adilson) e o seu papel

**Em uma frase:** os requisitos viraram casos de uso, histórias e diagramas UML, e a decisão principal foi a sincronização assíncrona com operações de id único (ADR-003), que é exatamente o que o seu A4 e o seu A5 fazem.

- **Números:** 12 requisitos funcionais, 8 não funcionais, 8 casos de uso, 16 histórias de usuário (15 feitas; a US16, devolução de volumes, ficou para o futuro) e 6 decisões de arquitetura (ADR).

| Termo | Como explicar |
|---|---|
| Requisito funcional | O que o sistema faz, como registrar a encomenda (RF01) |
| Requisito não funcional | Como o sistema deve ser: funcionar sem internet, proteger os dados, ser acessível |
| Caso de uso | Uma interação de um ator com o sistema. Atores: porteiro, morador, supervisor, a central e o serviço de avisos |
| História de usuário | "Como porteiro, quero..., para...", com critérios de aceitação no formato Dado, Quando, Então |
| UML | Linguagem padrão de diagramas. Usamos casos de uso, sequência, classes, atividade e estados |
| ADR | Registro de uma decisão com o motivo: 001 banco relacional, 002 CSV no protótipo, 003 sincronização assíncrona, 004 Scrum, 005 diagramas como código, 006 endereçamento IP |
| Scrum | Trabalho em ciclos curtos (sprints), com backlog priorizado, revisão e retrospectiva no fim de cada ciclo |
| Definição de pronto | Compila sem avisos, testes passam, funções comentadas, critérios atendidos e revisão por outro integrante |

**Você é o Scrum Master** (o Lucas é o Product Owner). O Scrum Master facilita as cerimônias e remove impedimentos. Quem decide a prioridade é o Product Owner, e o conteúdo técnico é do time. No projeto, a revisão e a retrospectiva saíram por mensagem escrita no grupo, às sextas, às 19h. Na sprint 5, você fechou introdução, conclusão e resumo e conferiu o limite de páginas, coordenando os cortes.

**Cuidado:** as sprints 0 a 3 rodaram num ciclo único em 29/10 (datas do histórico do Git). Os requisitos vieram do cenário, e não de entrevistas.

### 7.3 Banco de dados (Lucas)

**Em uma frase:** o banco fica no servidor central, em MySQL 8, com 11 tabelas e 44 restrições, normalizado até a 3ª forma normal, e o programa em C usa arquivos CSV e não se conecta a ele (ADR-002).

| Termo | Como explicar |
|---|---|
| Banco relacional | Dados em tabelas ligadas por chaves |
| Chave primária (PK) | Identifica cada linha e não se repete, como o CPF da linha |
| Chave estrangeira (FK) | Aponta para uma linha de outra tabela: a encomenda aponta para a unidade |
| Restrição | Regra que o próprio banco garante. Prefixos `pk_`, `fk_`, `uq_` (valor único) e `ck_` (valor permitido, como P, M ou G) |
| Normalização | Não repetir a mesma informação em vários lugares. **1FN:** cada campo guarda um valor só ("Bloco A apto 12" vira dois campos). **2FN:** cada informação depende da chave inteira. **3FN:** nenhuma informação depende de outra que não seja a chave (os dados do morador ganharam tabela própria) |
| DER | O desenho das entidades e das ligações entre elas (Figura 6) |
| SQL | A linguagem para criar tabelas e consultar o banco |
| Hash SHA-256 | Uma impressão digital do código: dá para conferir se o código digitado bate, mas não dá para descobrir o código a partir dela. Existe só no sistema completo |
| NoSQL | Bancos sem tabelas fixas, como documentos (MongoDB) e chave-valor (Redis). Só faria sentido para o histórico de avisos, no futuro |
| Docker | Um contêiner, ambiente isolado onde o MySQL 8.4 rodou os scripts |

- **Três soluções do modelo:** a chave primária da tabela de operações impede aplicar a mesma operação duas vezes; uma coluna gerada com valor único impede duas pendentes na mesma posição; o código fica guardado só como hash.
- **Resultados:** os scripts rodaram sem erro e batem com o relatório do programa em C: 6 e 5 pendências, 6 de 48 e 5 de 48 posições ocupadas.

### 7.4 Redes (Pedro)

**Em uma frase:** sede, 10 condomínios e a nuvem, cada local em estrela e todos ligados à nuvem por VPN, com endereços `10.X.Y.0/24`, 4 VLANs e listas de acesso, e 15 testes no Packet Tracer, todos com o resultado esperado.

| Termo | Como explicar |
|---|---|
| LAN e WAN | Rede local e rede entre locais |
| Topologia estrela | Todos os aparelhos ligados a um equipamento central. Entre os locais é *hub-and-spoke*: a nuvem no centro |
| Roteador, switch e ponto de acesso | Liga redes diferentes; liga os aparelhos da mesma rede; dá o Wi-Fi |
| Endereço IP e `/24` | O endereço de cada aparelho. `/24` é uma rede de 256 endereços. Em `10.X.Y.0`, X é o local (0 é a sede) e Y é a VLAN: `10.3.10.10` é o computador da portaria do condomínio 3 |
| VLAN | Dividir um switch em redes separadas, como corredores diferentes no mesmo prédio: 10 portaria, 20 CFTV, 30 visitantes e 99 gerência |
| Gateway e DHCP | A porta de saída da rede (termina em `.1`) e o serviço que entrega endereços automaticamente (de `.100` a `.199`) |
| ACL e firewall | Regras de quem pode falar com quem. A portaria só alcança a API, o CFTV só a própria VLAN, os visitantes só a internet, e a gerência entra por SSH a partir da sede |
| VPN (IPsec) | Um túnel criptografado pela internet. São 11 túneis, mas a VPN ficou só no desenho |
| HTTPS e SSH | Comunicação criptografada com a API e acesso remoto seguro aos equipamentos |
| `ping` | O teste "você me ouve?" entre dois aparelhos |
| IaaS, PaaS e SaaS | Alugar a máquina, alugar a plataforma pronta (MySQL gerenciado) ou usar um serviço pronto (SMS) |

- **Números:** 44 redes, 4 VLANs, 15 de 15 testes no Packet Tracer 9.0.1. No T2, a portaria alcança a central; no T6, o Wi-Fi de visitantes não alcança a portaria; no T14 e no T15, sem a nuvem, a rede local continua funcionando.
- **Ligação com o seu código:** é por a rede local continuar sem a nuvem que a fila do programa em C guarda as operações até a conexão voltar.
- **Cuidado:** VPN, HTTPS e desempenho não foram testados.

### 7.5 Segurança, privacidade e acessibilidade (Pedro)

- **LGPD (Lei 13.709/2018):** finalidade, adequação e necessidade, ou seja, usar só o mínimo. O sistema guarda nome, unidade, canal e contato; não guarda o conteúdo da encomenda nem o remetente, e não guarda contato quando o canal é o interfone.
- **Retenção:** 90 dias depois da retirada, com anonimização em seguida. É decisão de projeto do grupo, e não prazo legal.
- **Segurança:** código de 6 dígitos de uso único, 3 tentativas e confirmação do porteiro; id único em cada operação (rastreabilidade); entrada validada.
- **Acessibilidade:** interfone com código impresso para quem não usa smartphone. Para as telas futuras, o nível AA do WCAG (os níveis são A, AA e AAA). A Lei Brasileira de Inclusão (13.146/2015) também é citada.
- **Ética:** os relatórios são por condomínio, sem ranking de funcionários.
- **Cuidado:** o protótipo não tem login nem criptografia, e o código aparece na tela. São limitações declaradas.

### 7.6 Limitações e conclusão (Pedro)

- **Pronto e testado:** o núcleo em C, os scripts do banco e a rede no simulador.
- **Simulado:** o aviso ao morador e a rede entre portaria e central.
- **Só no projeto:** VPN, HTTPS, API, banco ligado ao programa, aplicativo do morador e painel.
- **Benefícios** (menos extravios, menos tempo do porteiro): esperados, ainda não medidos. Só um piloto pode mostrar.
- **Conclusão:** a solução é tecnicamente viável.

---

## 8. Perguntas que podem fazer para você

| Pergunta | Resposta curta |
|---|---|
| Por que C? | A disciplina é de programação estruturada em C. E o C gera um executável pequeno que roda sem instalar nada. |
| O que é C99? | A versão da linguagem padronizada em 1999. Seguir um padrão faz o código compilar igual em qualquer `gcc`. |
| Para que servem `-Wall -Wextra -pedantic`? | Ligam um conjunto amplo de avisos do compilador e cobram o padrão C à risca. Compilamos com zero avisos. |
| Por que `fgets` e não `scanf`? | O `fgets` recebe o tamanho da variável e não escreve além dele. O `scanf("%s")` não sabe o tamanho, pode estourar a memória e deixa o Enter sobrando. Depois do `fgets`, convertemos e validamos. |
| E se eu digitar uma letra onde pede número? | Aparece "Valor invalido. Digite um numero entre X e Y." e a pergunta se repete. |
| Por que não aceita acento nem ponto e vírgula? | O ponto e vírgula é o separador do CSV e quebraria o arquivo. Acento dá problema no console do Windows, então o programa usa só ASCII. |
| Por que vetores estáticos e não `malloc`? | A disciplina pede vetores e matrizes, e o tamanho fixo deixa a memória previsível. Para mudar a capacidade, muda-se uma constante em `tipos.h`. |
| O que acontece na encomenda 501? | "Limite de 500 encomendas atingido. Encomenda NAO registrada." É uma limitação declarada. |
| Por que a matriz da estante não é salva? | Para ter uma única fonte de verdade. A posição já está gravada em cada encomenda, e ao abrir o programa `estante_reconstruir` remonta a matriz com as pendentes. |
| Como o A1 escolhe a estante? | Pela letra do bloco: A vai para a estante 0, B para a 1, e assim por diante. O `% 4` faz o bloco E voltar para a 0. Se estiver cheia, tenta as próximas em ordem circular. |
| Por que duas chamadas de `rand()`? | Em alguns compiladores o `rand()` só vai até 32767, o que daria poucos códigos diferentes. Juntando duas chamadas, o número fica bem maior antes de ser reduzido à faixa de 6 dígitos. |
| O código pode repetir? | Entre pendentes, não: o sorteio se repete até achar um livre (até 1000 vezes). O código de uma encomenda já retirada pode voltar a ser usado. |
| E se digitarem o código de outra pessoa? | Um código errado pode, por azar, ser de outra pendente (cerca de 1 em 9.000 com 100 pendentes). Por isso o programa mostra unidade e nome e o porteiro confirma antes de entregar. |
| O que é idempotente? | Aplicar a mesma operação duas vezes dá o mesmo resultado que aplicar uma. A central anota os ids aplicados e ignora os repetidos. Na demonstração: 17 e depois 0. |
| E se a internet cair no meio do envio? | A fila só é esvaziada depois de copiada. Se cair no meio, as operações vão de novo, e a central ignora as que já aplicou. |
| Por que o id é "P01-000011"? | Junta a portaria e um número sequencial, então é único no sistema todo. O último número fica gravado, e não se repete depois de fechar o programa. |
| O que é ponteiro e onde usaram? | Uma variável que guarda o endereço de outra. O A1 devolve linha e coluna por `int *linha` e `int *coluna`, e as fichas são passadas sem copiar tudo. |
| Por que algumas coisas são `static`? | Variável global `static` só existe naquele arquivo, e função `static` é auxiliar e não pode ser chamada de fora. Na central, o estado tem centenas de KB, então fica em memória estática, e não na pilha, que é pequena. |
| O que é `struct` e `enum`? | `struct` é uma ficha com vários campos (a `Encomenda`). `enum` dá nomes a valores fixos (`STATUS_PENDENTE`), o que é mais legível que 0, 1 e 2. |
| Por que busca sequencial e não binária? | Os vetores são pequenos (até 500) e não estão ordenados pelo código. Percorrer tudo é simples e instantâneo nesse tamanho. |
| Como os dados são salvos? | Em CSV com ponto e vírgula, e a cada alteração o arquivo é reescrito inteiro. Fechar à força durante a gravação pode deixar o arquivo incompleto; é limitação declarada. |
| Como testaram? | Com 9 conjuntos de testes usando `assert.h`, que rodam com `make test` ou `build.bat test`. A parte interativa da retirada foi conferida à mão. |
| O que o Makefile faz? | Compila cada módulo, junta tudo em `bin/portaria` e `bin/central` e, com `make test`, roda os testes. No Windows sem `make`, o `build.bat` faz o mesmo. |
| Funciona no Linux? | Sim. Foi compilado no Windows e testado também no Linux com `gcc`. |
| O aviso por SMS é real? | É simulado: aparece na tela e fica registrado em arquivo. O envio real dependeria de um serviço de SMS na nuvem. |
| O código aparece na tela. É seguro? | Não é o ideal, e o trabalho declara isso como limitação. No sistema completo, só o morador receberia o código, e o banco guardaria apenas o hash. |
| Por que a devolução não foi feita? | Depende de um prazo que a administradora precisa definir (US16). Ficou como evolução futura. |
| Onde está o código? | No GitHub, `github.com/danieelaugustoo/pim`, pasta `05-programa-c`. |

**Se não souber a resposta**, não invente. Diga "isso não foi implementado, e o trabalho declara como limitação" (seções 6.7 e 9.4) ou "não sei com certeza; o que fizemos foi...".

---

## 9. Como se apresentar bem

- Fale para a banca, e não para a tela. Olhe para a professora quando disser um número.
- Explique o termo técnico na primeira vez que usar: "idempotente, ou seja, ...".
- Uma ideia por frase. Faça uma pausa depois de um número importante.
- Na demonstração, diga o que vai fazer antes de apertar Enter ("agora vou derrubar a internet") e leia em voz alta a linha que importa na tela.
- Mantenha a fonte do terminal grande e as notificações desligadas.
- Controle o tempo: se a fala passar de 3 minutos, vá direto para a demonstração; se a demonstração atrasar, use a versão curta.
- Se um colega travar, ajude com uma frase da parte 7 e devolva a palavra.
- No fim, passe a palavra pelo nome: "Agora o Pedro vai falar da rede e da conclusão."

---

## 10. Cola final (para ler na quarta de manhã)

| O quê | Valor |
|---|---|
| Programas | 2 (`portaria` e `central`), 11 módulos |
| Padrão | C99, só biblioteca padrão, zero avisos |
| Bibliotecas | `stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `time.h`, `assert.h` |
| Capacidade | 500 encomendas e 300 moradores por portaria |
| Estante | Matriz 4 x 12 = 48 posições; prateleiras 10 e 11 para volume G |
| Código | 6 dígitos, até 1000 sorteios, 3 tentativas na retirada |
| Algoritmos | A1 estante, A2 código, A3 retirada, A4 sincronizar, A5 consolidar, A6 relatórios |
| Testes | 9 conjuntos, todos passando |
| Demonstração | Central 17, depois 0; offline; 2 registros; fila com 2; central aplica 2; retirada (errado, N, S); central aplica 1; relatório |
| Grupo | 10 condomínios, ~960 unidades, 40 porteiros; 12 RF, 8 RNF, 8 casos de uso, 15 de 16 histórias; 11 tabelas e 44 restrições; 44 redes, 4 VLANs, 15 de 15 testes |

**Três funções que todo o grupo deve saber explicar:** `estante_alocar_posicao` (A1), `retirada_registrar` (A3) e `consolidacao_processar_portaria` (A5).

**Frase de abertura:** "Eu fiquei com a programação em C. São dois programas: a portaria e a central."

**Frase de fechamento:** "Agora o Pedro vai falar da rede e da conclusão."
