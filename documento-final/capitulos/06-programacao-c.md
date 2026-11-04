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
| Figura 9: fluxograma do A1 (alocação na estante) | `algoritmos/fluxogramas/A1.mmd` |
| Figura 12: print do mapa da estante | executar a opção 5 do menu |
| Figura 10: fluxograma do A5 (consolidação idempotente) | `algoritmos/fluxogramas/A5.mmd` |
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

Este capítulo apresenta o protótipo em linguagem C que implementa o núcleo da portaria e a consolidação central: padrões adotados, estruturas de programação, algoritmos principais, testes, demonstração e limitações.

## 6.1 Visão geral

O protótipo tem dois executáveis. O `portaria` representa o nó de uma portaria: abre-se com o número da portaria (`portaria 1`) e um menu permite registrar encomendas e retiradas, listar e buscar pendências, ver o mapa da estante, cadastrar moradores, gerar relatórios, sincronizar com a central e alternar entre os modos online e offline. O `central` lê os registros enviados pelas portarias, aplica cada operação uma única vez e gera o relatório consolidado.

O código é dividido em módulos (`util`, `estante`, `codigo`, `encomenda`, `retirada`, `morador`, `aviso`, `persistencia`, `sincronizacao`, `consolidacao` e `relatorio`), descritos em `05-programa-c/README.md`. O código completo está no repositório do projeto (https://github.com/danieelaugustoo/pim), em vez de apêndice `[CONFERIR: repositório público ou acesso concedido a quem corrige; formatar a referência conforme a ABNT]`.

## 6.2 Padrões adotados

O código segue o padrão C99, usa apenas a biblioteca padrão e compila com `-Wall -Wextra -pedantic` sem nenhum aviso. A programação é estruturada: funções pequenas com o nome do módulo como prefixo (como `estante_alocar_posicao`), vetores e matrizes estáticos com tamanhos em constantes de `tipos.h` e uma função principal que contém apenas o menu e as chamadas. A entrada do teclado usa `fgets` com conversão validada, e os textos do programa e dos arquivos de dados são ASCII, sem acentos. Toda função tem comentário em português com objetivo, parâmetros, retorno e lógica. Os conceitos de lógica e de estruturas de controle seguem a bibliografia da disciplina (DEITEL; DEITEL, 2011; FORBELLONE; EBERSPÄCHER, 2005).

## 6.3 Estruturas de programação

**Estruturas básicas.** As condicionais validam entradas (como o tamanho P, M ou G) e despacham o menu por `switch`; as repetições mantêm o laço do menu, percorrem arquivos linha a linha, varrem a matriz da estante e permitem até três tentativas de código.

**Vetores, matrizes e arquivos.** Há vetores de encomendas (até 500 por portaria) e de moradores (até 300) e a matriz `estante[4][12]`: cada linha é a estante de um bloco (A a D), cada coluna uma prateleira, e a célula guarda o identificador da encomenda ou zero. As prateleiras 10 e 11 são de volumes grandes. A matriz é reconstruída ao abrir o programa a partir das encomendas pendentes, mantendo uma única fonte de verdade. Os dados ficam em arquivos CSV com ponto e vírgula; ao sincronizar, a portaria copia a fila de operações para um registro em pasta de rede simulada, lido pela central. O número da operação (como `P01-000123`) nunca se repete.

## 6.4 Algoritmos

Seis algoritmos foram documentados com pseudocódigo e fluxograma em `05-programa-c/algoritmos/`. Os principais são descritos a seguir.

**A1 – alocação na estante (`estante_alocar_posicao`).** A estante preferida é a do bloco da unidade. O algoritmo procura a primeira prateleira livre da faixa adequada ao tamanho e, se a estante estiver cheia, tenta as seguintes em ordem circular; se todas estiverem cheias, informa que não há vaga.

```
para k de 0 ate NUM_ESTANTES - 1:
    candidata <- (preferida + k) MOD NUM_ESTANTES
    para cada prateleira da faixa, da menor para a maior:
        se estante[candidata][prateleira] = 0:
            estante[candidata][prateleira] <- id_encomenda
            retornar (candidata, prateleira)
retornar "sem vaga"
```

**[Figura 9 – Fluxograma do algoritmo A1. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-09-fluxograma-a1.png`]**

**A2 a A4 – código, retirada e sincronização.** O código de 6 dígitos é sorteado e repetido enquanto existir em uma encomenda pendente (limite de 1000 tentativas). A retirada confere o código em até três tentativas: se confere, registra quem retira, a data e a hora e libera a posição; se não, é negada e a encomenda continua pendente. A sincronização, online, copia a fila para o registro da rede e só então a esvazia; se falhar entre as duas etapas, a repetição é segura porque a central ignora operações já aplicadas.

**A5 – consolidação idempotente (`consolidacao_processar_portaria`).** Para cada operação do registro, a central verifica se o identificador já foi aplicado: se sim, ignora; se não, aplica o efeito e anota o identificador. Operação que não pode ser aplicada, como retirada de encomenda desconhecida, é rejeitada sem ser anotada e pode ser aplicada depois. A encomenda é identificada pelo par portaria e identificador, porque o identificador só é único dentro da portaria.

**[Figura 10 – Fluxograma do algoritmo A5. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-10-fluxograma-a5.png`]**

**A6 – relatórios.** Mapa da estante com percentual de ocupação, pendências com mais de 7 dias (exatamente 7 não alerta), registros por dia com o dia de pico (em empate, o mais cedo) e o relatório consolidado da central. As funções de cálculo recebem a data como texto, o que permite testá-las com datas fixas.

## 6.5 Testes

O protótipo tem nove conjuntos de testes automatizados (`make test`, ou `build.bat` no Windows), que cobrem utilitários, estante, código e retirada, persistência, moradores, sincronização, consolidação e relatórios. A consolidação é testada ao processar o mesmo arquivo duas vezes e com portarias distintas usando o mesmo identificador. A compilação não gerou avisos e os nove conjuntos passaram. A parte interativa da retirada foi conferida por execução manual: identificador de outra unidade recusado e retirada negada após três códigos errados. 

**[Figura 11 – Resultado dos testes automatizados (`.\build.bat test`) no Windows. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-11-testes-automatizados.png`]**

## 6.6 Demonstração

A demonstração usa dados fictícios. Ao executar a central duas vezes sobre os mesmos registros, a primeira aplicou 17 operações e consolidou 14 encomendas; na segunda, nenhuma foi aplicada e as 17 foram reconhecidas como já aplicadas, com arquivos idênticos. O relatório está no Quadro 4.

**Quadro 4 – Relatório consolidado com dados de exemplo (fictícios)**

| Portaria | Registradas | Pendentes | Retiradas | Devolvidas | Antigas | Dia de pico |
|---|---|---|---|---|---|---|
| P01 | 8 | 6 | 1 | 1 | 2 | 05/10/2026 (1) |
| P02 | 6 | 5 | 1 | 0 | 0 | 27/10/2026 (3) |
| Total | 14 | 11 | 2 | 1 | 2 | |

Fonte: elaborado pelos autores (2026). Valores gerados em 29/10/2026; a coluna "Antigas" depende da data de execução.

Em 29/10/2026, o mapa da estante com os mesmos dados mostrou 6 posições ocupadas de 48 (12,5%) e as pendências antigas listaram as encomendas 1 (9 dias) e 4 (14 dias). **[Figura 12 – Mapa da estante com os dados de exemplo (opção 5 do programa). Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-12-mapa-estante.png`]** Na operação offline, três registros entraram na fila e foram enviados ao voltar online.

## 6.7 Limitações

- A rede e o aviso ao morador são simulados (arquivos, mensagem na tela e registro em arquivo).
- O código de retirada é gravado em texto nos arquivos e aparece na tela do porteiro ao registrar a encomenda. No sistema completo, só o morador o receberia e o banco guardaria apenas o resumo criptográfico. O grupo manteve o protótipo assim e declara a limitação.
- A capacidade é fixa (500 encomendas e 300 moradores por portaria) e a devolução de volumes não foi implementada: a central entende a operação, mas a portaria não a gera.
- Os arquivos são reescritos por inteiro; fechar o programa à força durante a gravação pode deixar um arquivo incompleto.
- Compilado e testado no Windows e, também, em Linux com `gcc` (2026-10-31).

## 6.8 Considerações do capítulo

O protótipo implementa o fluxo central (registrar, guardar, avisar, retirar e consolidar) com programação estruturada, vetores e matrizes estáticos e arquivos, verificado por testes e execução. Ficam pendentes os prints, a revisão por pares e a ligação com a API e o banco.
