# Estrutura do trabalho e orçamento de páginas

Baseado no `PLANO.md`, seção 11. O Desenvolvimento deve ficar **entre 20 e 30 páginas** (manual do PIM). Os números abaixo são metas de planejamento, não medidas: o grupo confere a contagem real no documento montado no modelo da UNIP.

## 1. Sumário planejado

| Parte | Conteúdo | Etapa | Páginas (meta) | Roteiro |
|---|---|---|---|---|
| Capa | Modelo da UNIP | — | — | — |
| Resumo | Até 500 palavras + palavras-chave | — | — | [`00-resumo.md`](capitulos/00-resumo.md) |
| Abstract | Idioma a definir + keywords | — | — | [`00-abstract.md`](capitulos/00-abstract.md) |
| Sumário | Gerado no editor | — | — | — |
| 1 Introdução | Objetivo, metodologia, empresa, visão geral | — | ~2 | [`01-introducao.md`](capitulos/01-introducao.md) |
| 2 Caracterização da organização | | 1 | 3 | [`02-organizacao.md`](capitulos/02-organizacao.md) |
| 3 Pesquisa científica e inovação | | 2 | 3 | [`03-pesquisa.md`](capitulos/03-pesquisa.md) |
| 4 Engenharia de software | | 3 | 4 | [`04-engenharia-software.md`](capitulos/04-engenharia-software.md) |
| 5 Banco de dados | | 4 | 4 | [`05-banco-de-dados.md`](capitulos/05-banco-de-dados.md) |
| 6 Programação estruturada em C | | 5 | 4 | [`06-programacao-c.md`](capitulos/06-programacao-c.md) |
| 7 Redes e sistemas distribuídos | | 6 | 4 | [`07-redes.md`](capitulos/07-redes.md) |
| 8 Direitos humanos, inclusão e segurança | | 7 | 2 | [`08-seguranca-privacidade-acessibilidade.md`](capitulos/08-seguranca-privacidade-acessibilidade.md) |
| 9 Integração da solução | | 8 | 2 | [`09-integracao.md`](capitulos/09-integracao.md) |
| 10 Conclusão | Resultados × objetivos | — | ~1,5 | [`10-conclusao.md`](capitulos/10-conclusao.md) |
| Referências | ABNT, só fontes usadas | — | — | `referencias.md` (o grupo cria) |

**Desenvolvimento (capítulos 2 a 9): 3 + 3 + 4 + 4 + 4 + 4 + 2 + 2 = 26 páginas**, dentro da faixa de 20 a 30, com 4 páginas de folga para ajuste.

**Dúvida a esclarecer:** se a Introdução e a Conclusão entram na contagem do "Desenvolvimento". Pelo manual, o Desenvolvimento é a parte entre elas; se o professor contar tudo, o total seria de cerca de 29,5 páginas. Confirmar com o professor.

## 2. Riscos de tamanho

- São **16 figuras** previstas para 26 páginas. Figuras grandes consomem página: reduzir a largura, juntar prints menores numa única figura ou mover para apêndice o que não for essencial.
- Capítulos 4 e 6 são os mais difíceis de comprimir (muito material no repositório). Escolher o que é específico do projeto e remeter o resto ao repositório.
- O capítulo 8 tem só 2 páginas: uma tabela grande já ocupa meia página.
- Apêndices (código, scripts SQL, comandos do Packet Tracer): **confirmar com o professor se contam nas páginas** (`PLANO.md`, seção 11).

## 3. Mapa de onde cada exigência do manual aparece

| O manual pede no Desenvolvimento | Onde aparece |
|---|---|
| Pesquisa e fundamentação | Capítulo 3 |
| Métodos | Metodologia (capítulo 3) e processo Scrum (capítulo 4) |
| Materiais | Ferramentas e tecnologias (capítulo 4, seção 4.7) |
| Resultados | Consultas SQL (5), testes e telas do protótipo (6), testes do Packet Tracer (7); sem levantamento de campo |
| Discussão | Benefícios, limitações e comparação com trabalhos relacionados (9) |

## 4. Lista de figuras

Numeração em ordem de aparição no texto (renumerada em 2026-11-04). Arquivos finais em `figuras/figura-NN-descricao.png`. Os diagramas Mermaid foram renderizados em 2026-10-31 com o mermaid-cli 11.4.2; **conferir visualmente** antes de usar. Os diagramas PlantUML (figuras 04 a 07) **ainda não foram renderizados**. O diagrama de estados da encomenda (`estados-encomenda.puml`) é opcional e **não é citado** no capítulo 4; se for incluído, todas as figuras seguintes precisam ser renumeradas.

| Nº | Figura | Capítulo | Origem | Situação |
|---|---|---|---|---|
| 01 | Organograma | 2 | `01-organizacao/diagramas/organograma.mmd` | renderizado |
| 02 | Processo atual (caderno) | 2 | `01-organizacao/diagramas/processo-atual.mmd` | renderizado |
| 03 | Processo proposto | 2 | `01-organizacao/diagramas/processo-proposto.mmd` | renderizado |
| 04 | Casos de uso | 4 | `03-engenharia-software/diagramas/casos-de-uso.puml` | renderizar (PlantUML) |
| 05 | Classes de domínio | 4 | `.../classes-dominio.puml` | renderizar (PlantUML) |
| 06 | Atividade: registrar encomenda | 4 | `.../atividade-registrar-encomenda.puml` | renderizar (PlantUML) |
| 07 | Sequência da sincronização | 4 | `.../sequencia-sincronizacao.puml` | renderizar (PlantUML) |
| 08 | DER | 5 | `04-banco-de-dados/diagramas/der.mmd` | renderizado (`figura-08-der.png`) |
| 09 | Fluxograma do A1 | 6 | `05-programa-c/algoritmos/fluxogramas/A1.mmd` | renderizado (`figura-09-fluxograma-a1.png`) |
| 10 | Fluxograma do A5 | 6 | `.../fluxogramas/A5.mmd` | renderizado (`figura-10-fluxograma-a5.png`) |
| 11 | Print dos testes automatizados | 6 | `.\build.bat test` | feito (`figura-11-testes-automatizados.png`) |
| 12 | Print do mapa da estante | 6 | opção 5 do programa | feito (`figura-12-mapa-estante.png`) |
| 13 | Topologia no Packet Tracer | 7 | montagem no simulador | feito (`figura-13-topologia.png`) |
| 14 | Print do teste T2 (portaria alcança a API) | 7 | Packet Tracer | feito (`figura-14-teste-t2.png`) |
| 15 | Print do teste T6 (visitantes não alcançam a portaria) | 7 | Packet Tracer | feito (`figura-15-teste-t6.png`) |
| 16 | Fluxo ponta a ponta | 9 | `08-integracao/diagramas/fluxo-ponta-a-ponta.mmd` | renderizado |

Fluxogramas A2, A3, A4 e A6 ficam em apêndice ou só no repositório.

## 5. Lista de quadros

Numeração em ordem de aparição (renumerados em 2026-11-03, após os cortes).

| Quadro | Capítulo | Origem |
|---|---|---|
| 1 Problemas do processo atual (P1 a P7) | 2 | `01-organizacao/caracterizacao.md` |
| 2 Requisitos funcionais | 4 | `03-engenharia-software/requisitos.md` |
| 3 Resultados de consultas SQL (dados fictícios) | 5 | `04-banco-de-dados/sql/03-consultas.sql` |
| 4 Relatório consolidado (dados fictícios) | 6 | `05-programa-c/` (central) |
| 5 Regras de acesso principais | 7 | `06-redes/seguranca-infraestrutura.md` |
| 6 Resultado dos testes no Packet Tracer (T1 a T15) | 7 | `06-redes/packet-tracer/roteiro.md` |
| 7 O que é real e o que é simulado | 9 | `08-integracao/` |
| 8 Indicadores propostos | 9 | `08-integracao/beneficios-e-indicadores.md` |

Ficam só no repositório, citados no texto: matriz de trabalhos relacionados (`02-pesquisa/trabalhos-relacionados.md`), ADRs, módulos e algoritmos, VLANs, testes T1 a T15 (se couberem, entram no capítulo 7 com o resultado esperado × obtido) e dados pessoais × finalidade.

## 6. Ordem sugerida de escrita

1. Capítulos 4, 5 e 6 (o grupo domina o material e ele está pronto).
2. Capítulo 7, depois de montar o Packet Tracer.
3. Capítulos 2, 3 (depois de verificar as fontes), 8 e 9.
4. Introdução e Conclusão.
5. Resumo e Abstract (por último).
6. Referências, conferindo citação × lista.

## 7. Código no documento

Trechos principais no capítulo 6; código completo apenas pelo link do repositório no GitHub, sem apêndice (decisão do grupo, 2026-10-29).

## 8. Tamanho dos rascunhos (conferência de 2026-11-03, após os cortes)

Contagem de palavras da seção "Texto do grupo" de cada capítulo (inclui o aviso do topo, títulos, tabelas, marcas de figura e pseudocódigo, então é um pouco maior que o texto corrido). Estimativa grosseira: com Times 12, espaçamento 1,5 e as margens do manual, cabem cerca de 300 a 350 palavras por página; **a paginação real só se vê no Word**.

| Capítulo | Antes dos cortes (2026-10-29) | Depois dos cortes (2026-11-03) | Meta de páginas |
|---|---|---|---|
| 1 Introdução | 459 | 463 | ~2 |
| 2 Organização | 1.001 | 818 | 3 |
| 3 Pesquisa | 1.297 | 1.049 | 3 |
| 4 Engenharia de software | 1.699 | 1.279 | 4 |
| 5 Banco de dados | 1.385 | 1.129 | 4 |
| 6 Programação em C | 1.944 | 1.258 | 4 |
| 7 Redes | 1.488 | 1.634 | 4 |
| 8 Segurança e acessibilidade | 1.134 | 866 | 2 |
| 9 Integração | 1.406 | 1.082 | 2 |
| 10 Conclusão | 561 | 565 | ~1,5 |

O desenvolvimento (capítulos 2 a 9) passou de cerca de **11.350** para cerca de **9.140 palavras** (aproximadamente 28 a 30 páginas de texto, **mais** as figuras; o capítulo 7 cresceu com os resultados dos testes do Packet Tracer). Ainda pode passar de 30 páginas depois de inseridas as 16 figuras: confirmar no Word. Nos cortes, o texto dos capítulos foi reescrito de forma mais curta, **sem tirar fatos nem números**, e cinco quadros que repetiam o que está no repositório viraram frase (módulos e algoritmos do cap. 6, ADRs, sprints e ferramentas do cap. 4, VLANs e riscos e dados pessoais do cap. 8, matriz de trabalhos relacionados do cap. 3 e evoluções do cap. 9). Os quadros foram renumerados de 1 a 8. Nenhuma figura foi retirada.

**Cortes ainda possíveis, se o Word mostrar mais de 30 páginas (decisão do grupo):**
1. Reduzir figuras: manter as de maior valor (organograma, casos de uso, DER, fluxograma do A1, topologia, os dois prints do Packet Tracer, fluxo ponta a ponta) e juntar ou cortar as demais, renumerando as figuras restantes.
2. Resumir os capítulos 6 e 9 em subseções de um parágrafo cada.
3. Se a Introdução e a Conclusão não contarem no limite (confirmar com a Prof.ª Eliana), o ajuste necessário é menor.
