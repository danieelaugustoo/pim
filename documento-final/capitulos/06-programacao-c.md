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
- [ ] Decidir se o código completo vai em apêndice ou só como link (confirmar com o professor se o apêndice conta nas páginas).
- [ ] Decidir sobre o **código de retirada exibido na tela do porteiro** (limitação registrada em `07-.../analise.md`).
- [ ] Revisão por outro integrante.

## Cuidados

- Não copiar o código inteiro no corpo do texto; trechos curtos, com explicação.
- Dizer o que é simulado: rede e aviso.

---

## Texto do grupo

*(escrever aqui)*
