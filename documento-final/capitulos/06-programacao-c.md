# 6 Programação estruturada em C (roteiro, cerca de 4 páginas, Etapa 5)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo". O grupo precisa saber **explicar o código** na apresentação: este capítulo é o apoio.

**Fontes no repositório:** `05-programa-c/` (código, testes, README) e `05-programa-c/algoritmos/` (A1 a A6).

## Tópicos

| # | Tópico | Origem |
|---|---|---|
| 6.1 | Visão geral do protótipo: dois executáveis (`portaria`, `central`) e os módulos | `05-programa-c/README.md` |
| 6.2 | Padrões adotados: C99, só biblioteca padrão, funções com prefixo do módulo, vetores e matrizes estáticos, entrada com `fgets` validada | `CLAUDE.md` (regras 3 a 7), `include/tipos.h` |
| 6.3 | Estruturas condicionais, de repetição e funções: onde aparecem | `src/` (exemplos: validação em `util.c`, `switch` do menu em `portaria.c`) |
| 6.4 | Vetores e matrizes: vetor de encomendas, matriz da estante | `include/tipos.h`, `src/estante.c` |
| 6.5 | Manipulação de arquivos: CSV, fila de operações, log da rede | `src/persistencia.c`, `sincronizacao.c`, `consolidacao.c` |
| 6.6 | Algoritmos A1 a A6: objetivo, pseudocódigo e fluxograma de cada um | `algoritmos/pseudocodigo.md`, `algoritmos/fluxogramas/` |
| 6.7 | Sincronização e consolidação idempotente (A4 e A5) como ponto central | `algoritmos/pseudocodigo.md`, ADR-003 |
| 6.8 | Testes automatizados (9 conjuntos) e resultado de `make test` | `tests/`, `sprint-03.md` |
| 6.9 | Demonstração: telas do menu, mapa da estante, relatórios e central rodada duas vezes | README, seção "Demonstração" |
| 6.10 | Limitações do protótipo | `05-programa-c/README.md`, seção "Limitações" |

## Figuras e tabelas

| Item | Origem |
|---|---|
| Figura 10: fluxograma do A1 (alocação na estante) | `algoritmos/fluxogramas/A1.mmd` |
| Figura 11: print do mapa da estante | executar a opção 5 do menu |
| Figura 12: fluxograma do A5 (consolidação idempotente) | `algoritmos/fluxogramas/A5.mmd` |
| Tabela: módulos e funções principais | `05-programa-c/README.md`, "O que cada arquivo faz" |
| Tabela: algoritmos A1 a A6 e onde estão no código | `algoritmos/pseudocodigo.md`, "Situação" |
| Trechos de código: 1 ou 2 funções curtas (por exemplo, `estante_alocar_posicao`) | `src/estante.c` |
| Print do resultado de `make test` | executar na máquina do grupo |

Os demais fluxogramas (A2, A3, A4, A6) podem ir em apêndice ou só no repositório, conforme o limite de páginas.

## O que depende do grupo

- [ ] Compilar e rodar no computador de cada integrante (o grupo precisa dominar o código).
- [ ] Tirar os prints (menu, mapa, relatórios, `make test`).
- [ ] Renderizar os fluxogramas e exportar os PNG.
- [x] Código completo: só o link do GitHub, sem apêndice (decisão do grupo, 2026-10-29).
- [x] Código de retirada na tela do porteiro: manter e declarar a limitação (decisão de 2026-10-29, `07-.../analise.md`).
- [ ] Revisão por outro integrante.

## Cuidados

- Não copiar o código inteiro no corpo do texto; trechos curtos, com explicação.
- Dizer o que é simulado: rede e aviso.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro, do código de `05-programa-c/` e dos documentos de algoritmos (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo, e precisa saber explicar o código. Marcas `[ ... ]` indicam o que ainda precisa de print, fonte ou decisão.

# 6 PROGRAMAÇÃO ESTRUTURADA EM C

Este capítulo apresenta o protótipo desenvolvido em linguagem C, que implementa o núcleo da portaria e a consolidação central. São descritos os padrões adotados, as estruturas de programação empregadas, os algoritmos principais com pseudocódigo e fluxograma, os testes e a demonstração, além das limitações do protótipo.

## 6.1 Visão geral

O protótipo é composto por dois executáveis. O `portaria` representa o nó de uma portaria: abre-se com o número da portaria (por exemplo, `portaria 1`), apresenta um menu e permite registrar encomendas e retiradas, listar e buscar pendências, ver o mapa da estante, cadastrar moradores, gerar relatórios e sincronizar com a central, além de alternar entre os modos online e offline para simulação. O `central` lê os registros enviados pelas portarias, aplica cada operação uma única vez e gera um relatório consolidado.

O código está dividido em módulos, cada um com seu arquivo de cabeçalho e de implementação, conforme o Quadro 9.

**Quadro 9 – Módulos do protótipo**

| Módulo | Responsabilidade |
|---|---|
| `util` | Leitura segura do teclado, conversão validada de números, datas e separação de campos |
| `estante` | Matriz de posições: alocar (A1), liberar, reconstruir e contar ocupação |
| `codigo` | Código de retirada de 6 dígitos, único entre as pendentes (A2) |
| `encomenda` | Criar, registrar, listar e buscar encomendas |
| `retirada` | Retirada com conferência do código e até três tentativas (A3) |
| `morador` e `aviso` | Cadastro de moradores e aviso simulado por canal |
| `persistencia` | Leitura e gravação dos arquivos CSV |
| `sincronizacao` | Fila de operações, numeração e envio para a rede (A4) |
| `consolidacao` | Aplicação idempotente das operações na central (A5) |
| `relatorio` | Mapa da estante, pendências antigas, pico por dia e dados do relatório central (A6) |

Fonte: elaborado pelos autores (2026).

## 6.2 Padrões adotados

O código segue o padrão C99 e usa apenas a biblioteca padrão, compilado com as opções `-Wall -Wextra -pedantic`, sem nenhum aviso. A programação é estruturada: funções pequenas, com o nome do módulo como prefixo (por exemplo, `estante_alocar_posicao`), vetores e matrizes estáticos cujos tamanhos estão em constantes de um único arquivo (`tipos.h`), e uma função principal que contém apenas o menu e as chamadas. A entrada do teclado é lida por `fgets` e convertida com validação, sem uso de `scanf` para textos. Os textos do programa e dos arquivos de dados são escritos em ASCII, sem acentos. Toda função tem um comentário em português com objetivo, parâmetros, retorno e lógica. A linguagem C e os conceitos de lógica e de estruturas de controle seguem a bibliografia da disciplina (DEITEL; DEITEL, 2011; FORBELLONE; EBERSPÄCHER, 2005).

## 6.3 Estruturas de programação

**Estruturas condicionais.** São usadas na validação de entradas (por exemplo, tamanho do volume P, M ou G), na escolha da faixa de prateleiras conforme o tamanho e no `switch` que despacha as opções do menu.

**Estruturas de repetição.** O laço do menu repete até o porteiro sair; a leitura de arquivos percorre linha a linha; a busca por posição varre a matriz da estante; e a conferência do código permite até três tentativas.

**Funções.** O programa é organizado em funções com responsabilidade única, agrupadas por módulo. Funções auxiliares internas são declaradas `static`.

**Vetores e matrizes.** Há um vetor de encomendas (até 500 por portaria), um vetor de moradores (até 300) e a matriz `estante[4][12]`, em que cada linha é uma estante (uma por bloco, de A a D) e cada coluna é uma prateleira. Cada célula guarda o identificador da encomenda que a ocupa, ou zero se estiver livre. As prateleiras 10 e 11 são reservadas a volumes grandes. A matriz não é gravada em arquivo: ao abrir o programa, é reconstruída a partir das encomendas pendentes, de modo que há uma única fonte de verdade.

**Manipulação de arquivos.** Os dados são guardados em arquivos CSV separados por ponto e vírgula, com cabeçalho. Cada portaria tem um arquivo de encomendas, um de moradores, uma fila de operações e um arquivo com o último número de operação usado. Ao sincronizar, a portaria copia as operações da fila para um arquivo de registro na pasta de rede simulada, e a central lê esses arquivos. O número da operação (como `P01-000123`) nunca se repete.

## 6.4 Algoritmos

Seis algoritmos foram documentados com pseudocódigo e fluxograma (Quadro 10).

**Quadro 10 – Algoritmos principais**

| ID | Algoritmo | Função no código |
|---|---|---|
| A1 | Alocar posição na estante | `estante_alocar_posicao` |
| A2 | Gerar código único | `codigo_gerar_unico` |
| A3 | Registrar retirada | `retirada_registrar` |
| A4 | Sincronizar (portaria) | `sincronizacao_enviar_pendentes` |
| A5 | Consolidar (central, idempotente) | `consolidacao_processar_portaria` |
| A6 | Relatórios | funções do módulo `relatorio` |

Fonte: elaborado pelos autores (2026).

**A1 – alocação na estante.** A estante preferida é a do bloco da unidade (A para a primeira estante, B para a segunda, e assim por diante, de forma circular). O algoritmo procura a primeira prateleira livre da faixa adequada ao tamanho do volume e, se a estante estiver cheia, tenta as seguintes em ordem circular; se todas estiverem cheias, informa que não há vaga. O pseudocódigo é:

```
para k de 0 ate NUM_ESTANTES - 1:
    candidata <- (preferida + k) MOD NUM_ESTANTES
    para cada prateleira da faixa, da menor para a maior:
        se estante[candidata][prateleira] = 0:
            estante[candidata][prateleira] <- id_encomenda
            retornar (candidata, prateleira)
retornar "sem vaga"
```

**[Figura 10 – Fluxograma do algoritmo A1. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-10-fluxograma-a1.png`]**

**A2 – código único.** Sorteia-se um número de 100000 a 999999 e repete-se o sorteio enquanto ele já existir em uma encomenda pendente, com limite de 1000 tentativas para que o programa nunca fique preso. Códigos de encomendas já retiradas podem ser reutilizados. Como `rand()` pode entregar apenas 15 bits, o sorteio combina duas chamadas para cobrir todos os valores.

**A3 – retirada.** O porteiro informa a unidade, o programa lista as pendências dela e pede o identificador da encomenda, que só vale se for pendente e daquela unidade. O código é conferido em até três tentativas. Se confere, registra-se o nome de quem retira, a data e a hora, e a posição é liberada; se não, a retirada é negada e a encomenda continua pendente.

**A4 – sincronização.** Com a portaria offline, o programa apenas informa quantas operações aguardam. Online, copia cada operação da fila para o arquivo de registro da rede e só então esvazia a fila. Se o programa falhar entre as duas etapas, a próxima sincronização repete operações no registro, o que é seguro porque a central ignora as já aplicadas.

**A5 – consolidação idempotente.** Para cada portaria, a central lê o registro e, para cada operação, verifica se o identificador já foi aplicado; se foi, ignora; se não, aplica o efeito (o registro cria a encomenda, a retirada e a devolução alteram o status) e anota o identificador. Uma operação que não pode ser aplicada, como uma retirada de encomenda desconhecida, é rejeitada sem ser anotada, e pode ser aplicada numa execução posterior. A encomenda é identificada pelo par portaria e identificador, porque o identificador só é único dentro da portaria.

**[Figura 12 – Fluxograma do algoritmo A5. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-12-fluxograma-a5.png`]**

**A6 – relatórios.** Compreendem o mapa da estante (livre ou ocupada, com o percentual de ocupação), a lista de pendências com mais de 7 dias (a regra exige mais de 7: exatamente 7 não alerta), a contagem de registros por dia de um mês com o dia de pico (em caso de empate, vence o mais cedo) e o relatório consolidado da central, que acrescenta as colunas de pendências antigas e de dia de pico por portaria. As funções que calculam não imprimem nada e recebem a data como texto, o que permite testá-las com datas fixas.

## 6.5 Testes

O protótipo tem nove conjuntos de testes automatizados, executados por um único comando (`make test` ou o `build.bat` no Windows). Eles cobrem utilitários, alocação na estante (estante do bloco, volume grande, estante cheia, liberação e reconstrução), geração e conferência do código, regra de retirada, persistência, moradores, sincronização, consolidação e relatórios. A consolidação é testada ao processar o mesmo arquivo duas vezes, entre execuções diferentes e com portarias distintas usando o mesmo identificador de encomenda. Na última verificação, a compilação não gerou avisos e os nove conjuntos passaram. A parte interativa da retirada, que lê o teclado, não tem teste automatizado e foi conferida por execução manual: um identificador de outra unidade foi recusado e, após três códigos errados, a retirada foi negada. **[Inserir print do resultado de `make test` na máquina do grupo.]**

## 6.6 Demonstração

A demonstração usa dados fictícios. Ao executar a central duas vezes sobre os mesmos registros, a primeira aplicou 17 operações e consolidou 14 encomendas; na segunda, nenhuma foi aplicada e as 17 foram reconhecidas como já aplicadas, e os arquivos permaneceram idênticos. O relatório produzido está no Quadro 11.

**Quadro 11 – Relatório consolidado com dados de exemplo (fictícios)**

| Portaria | Registradas | Pendentes | Retiradas | Devolvidas | Antigas | Dia de pico |
|---|---|---|---|---|---|---|
| P01 | 8 | 6 | 1 | 1 | 2 | 05/10/2026 (1) |
| P02 | 6 | 5 | 1 | 0 | 0 | 27/10/2026 (3) |
| Total | 14 | 11 | 2 | 1 | 2 | |

Fonte: elaborado pelos autores (2026). Valores gerados em 29/10/2026; a coluna "Antigas" depende da data de execução.

Na portaria, o mapa da estante com os mesmos dados mostrou 6 posições ocupadas de 48 (12,5%), e o relatório de pendências antigas listou as encomendas 1 (9 dias) e 4 (14 dias). Em P01 o dia de pico é a primeira data, pois todos os dias empatam com um registro. **[Figura 11 – Print do mapa da estante. Inserir após executar a opção 5 do programa.]**

Também foi testada a operação offline: três registros feitos com a portaria offline entraram na fila, a sincronização offline informou três operações aguardando e preservou a fila e, ao voltar online, as três foram enviadas e a fila ficou vazia.

## 6.7 Limitações

- A rede é simulada por arquivos, e o aviso ao morador é simulado (mensagem na tela e registro em arquivo).
- O código de retirada é gravado em texto nos arquivos do protótipo e é mostrado na tela do porteiro ao registrar a encomenda, para qualquer canal de aviso. No sistema completo, apenas o morador receberia o código, e o banco guardaria só o resumo criptográfico. O grupo optou por manter o protótipo assim e declarar a limitação.
- Os arquivos são reescritos por inteiro a cada alteração; se o programa for fechado à força durante a gravação, um arquivo pode ficar incompleto.
- A capacidade é fixa (500 encomendas por portaria e 300 moradores) e a busca de identificadores é sequencial, o que basta para o protótipo.
- A devolução de volumes (história opcional) não foi implementada: o status "devolvida" existe e a central entende a operação, mas a portaria não a gera.
- O programa foi compilado e testado apenas no Windows.

## 6.8 Considerações do capítulo

O protótipo implementa o fluxo central do problema (registrar, guardar, avisar, retirar e consolidar) com programação estruturada, vetores e matrizes estáticos e manipulação de arquivos, e foi verificado por testes automatizados e por execução. As principais pendências são os prints de demonstração, a revisão por pares do código e a ligação com a API e o banco, que ficam como evolução futura.
