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
| Figura 12: print do mapa da estante | executar a opção 5 do menu |
| Figura 11: fluxograma do A5 (consolidação idempotente) | `algoritmos/fluxogramas/A5.mmd` |
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

Este capítulo apresenta o protótipo em C que implementa o núcleo da portaria e a consolidação central: padrões adotados, estruturas de programação, algoritmos, testes, demonstração e limitações.

## 6.1 Visão geral


O protótipo tem dois executáveis. O `portaria` representa o nó de uma portaria (`portaria 1`), e um menu permite registrar encomendas e retiradas, listar e buscar pendências, ver o mapa da estante, cadastrar moradores, gerar relatórios, sincronizar com a central e alternar entre os modos online e offline. O `central` lê os registros enviados pelas portarias, aplica cada operação uma única vez e gera o relatório consolidado. O código é dividido em módulos (`util`, `estante`, `codigo`, `encomenda`, `retirada`, `morador`, `aviso`, `persistencia`, `sincronizacao`, `consolidacao` e `relatorio`) e, em vez de apêndice, está completo no repositório do projeto (https://github.com/danieelaugustoo/pim).

## 6.2 Padrões adotados


O código segue o padrão C99, usa só a biblioteca padrão e compila com `-Wall -Wextra -pedantic` sem nenhum aviso. A programação é estruturada: funções pequenas, com o nome do módulo como prefixo (como `estante_alocar_posicao`), vetores e matrizes estáticos com tamanhos definidos em `tipos.h` e uma função principal que só tem o menu e as chamadas. A entrada do teclado usa `fgets` com conversão validada, os textos do programa e dos arquivos são ASCII, e toda função tem comentário com objetivo, parâmetros, retorno e lógica. Os conceitos de lógica e de estruturas de controle seguem a bibliografia da disciplina (DEITEL; DEITEL, 2011; FORBELLONE; EBERSPÄCHER, 2005).

## 6.3 Estruturas de programação


As condicionais validam as entradas, como o tamanho P, M ou G, e despacham o menu por `switch`, e as repetições mantêm o laço do menu, percorrem os arquivos e a matriz da estante e permitem até três tentativas de código. Os dados ficam em vetores de encomendas (até 500 por portaria) e de moradores (até 300) e na matriz `estante[4][12]`, em que cada linha é a estante de um bloco (A a D), cada coluna é uma prateleira e a célula guarda o identificador da encomenda ou zero. As prateleiras 10 e 11 são reservadas a volumes grandes, e a matriz é reconstruída ao abrir o programa a partir das encomendas pendentes. Os dados persistem em arquivos CSV separados por ponto e vírgula, e, ao sincronizar, a portaria copia a fila de operações para uma pasta de rede simulada, que a central lê. O número de cada operação (como `P01-000123`) nunca se repete.

## 6.4 Algoritmos

Seis algoritmos foram documentados com pseudocódigo e fluxograma em `05-programa-c/algoritmos/`, onde estão os fluxogramas de A2 a A6. A alocação na estante (A1, `estante_alocar_posicao`) parte da estante do bloco da unidade e procura a primeira prateleira livre da faixa adequada ao tamanho do volume. Se essa estante estiver cheia, tenta as seguintes em ordem circular e, se todas estiverem cheias, informa que não há vaga.

**[Figura 8 – Fluxograma do algoritmo A1. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-08-fluxograma-a1.png`]**

Os algoritmos A2 a A4 cuidam do código, da retirada e da sincronização. O código de 6 dígitos é sorteado até não existir em outra encomenda pendente (limite de 1000 tentativas). Na retirada, o porteiro digita o código, o programa acha a encomenda pendente que o usa, em até três tentativas, e mostra a unidade e o destinatário. Se o porteiro confirmar com o morador (S), o programa registra quem retira, a data e a hora e libera a posição, e, se recusar (N) ou as tentativas acabarem, nada muda. Na sincronização, com a portaria online, a fila é copiada para o registro da rede e só depois esvaziada, e repetir a operação após uma falha é seguro, porque a central ignora o que já aplicou.

O A5 (`consolidacao_processar_portaria`) faz a consolidação idempotente: para cada operação do registro, a central confere se o identificador já foi aplicado e, se não foi, aplica o efeito e anota o identificador. Uma operação que não pode ser aplicada, como a retirada de uma encomenda desconhecida, é rejeitada sem ser anotada e pode ser aplicada depois, e a encomenda é identificada pelo par portaria e identificador, porque o identificador só é único dentro da portaria. O A6 reúne os relatórios: o mapa da estante com o percentual de ocupação, as pendências com mais de 7 dias (exatamente 7 não gera alerta), os registros por dia com o dia de pico (em empate, o mais cedo) e o consolidado da central, com funções que recebem a data como texto para serem testadas com datas fixas.

## 6.5 Testes


O protótipo tem nove conjuntos de testes automatizados (`make test`, ou `build.bat` no Windows) que cobrem utilitários, estante, código e retirada, persistência, moradores, sincronização, consolidação e relatórios. A consolidação é testada processando o mesmo arquivo duas vezes e com portarias diferentes usando o mesmo identificador. A compilação não gerou avisos e os nove conjuntos passaram. A parte interativa da retirada foi conferida por execução manual: três códigos sem encomenda pendente negam a retirada, o código de uma encomenda já retirada não serve, a recusa (N) cancela e a confirmação (S) registra a retirada.

## 6.6 Demonstração

A demonstração usa dados de exemplo. Ao executar a central duas vezes sobre os mesmos registros, a primeira aplicou 17 operações e consolidou 14 encomendas. Na segunda, nenhuma foi aplicada, as 17 foram reconhecidas como já aplicadas e os arquivos ficaram idênticos. O relatório está no Quadro 2, e o mapa da estante mostrou seis posições ocupadas de 48 (12,5%), com as encomendas 1 (9 dias) e 4 (14 dias) entre as pendências antigas.

**Quadro 2 – Relatório consolidado com dados de exemplo**

| Portaria | Registradas | Pendentes | Retiradas | Devolvidas | Antigas | Dia de pico |
|---|---|---|---|---|---|---|
| P01 | 8 | 6 | 1 | 1 | 2 | 05/10/2026 (1) |
| P02 | 6 | 5 | 1 | 0 | 0 | 27/10/2026 (3) |
| Total | 14 | 11 | 2 | 1 | 2 | |

Fonte: elaborado pelos autores (2026). Valores gerados em 29/10/2026; a coluna "Antigas" depende da data de execução.

## 6.7 Limitações


A rede e o aviso ao morador são simulados, com arquivos, mensagem na tela e registro em arquivo. O código de retirada é gravado em texto nos arquivos e aparece na tela do porteiro ao registrar a encomenda; no sistema completo, só o morador o receberia e o banco guardaria apenas o resumo criptográfico, e o grupo declara essa limitação. Como a retirada acha a encomenda só pelo código, um código errado pode coincidir com o de outra pendente (cerca de 1 em 9.000 para 100 pendentes), e por isso o porteiro confirma com o morador. A capacidade é fixa (500 encomendas e 300 moradores por portaria), a devolução de volumes não foi implementada e os arquivos são reescritos por inteiro, de modo que fechar o programa à força durante a gravação pode deixar um arquivo incompleto. O programa foi compilado e testado no Windows e também em Linux, com `gcc` (2026-10-31).
