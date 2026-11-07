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

**Situação em 2026-11-04, depois da reescrita e dos cortes:** cerca de 10.100 palavras no texto (introdução, capítulos 2 a 9 e conclusão) e cerca de **30 páginas** da introdução à conclusão no teste com o LibreOffice (16 figuras). Confirmar no Word.

**Apresentação (2026-11-07):** roteiro da demonstração e divisão em 5 blocos em `documento-final/apresentacao/`. Falta o grupo definir quem apresenta cada bloco; o Canva e o banner são do grupo.

**Situação em 2026-11-07 (limite de 30 páginas para o arquivo inteiro):** o grupo confirmou que as 30 páginas contam tudo. Depois de cortar cerca de 1.600 palavras, dois quadros e quatro figuras, o PDF de teste tem **29 páginas no total** (capa, folha de rosto, resumo, abstract, sumário de 1 página, 23 páginas da introdução à conclusão e 1 de referências). A frase de ênfase foi retirada por ser opcional. Margem de 1 página: conferir no Word.

**Situação em 2026-11-07 (modelo da UNIP):** o rascunho foi montado no modelo da UNIP (capa com logo, folha de rosto, frase de ênfase, resumo, abstract, sumário e rodapé "Elaborado pelos alunos da UNIP…" nas páginas iniciais; numeração a partir da introdução). Da introdução à conclusão: **28,8 páginas** no LibreOffice (limite de 30). Arquivos em `versoes/` e scripts em `montagem/`. A frase de ênfase é a do próprio modelo (Viktor Frankl) e o orientador está como "Prof.ª Eliana": o grupo confirma os dois.

**Situação em 2026-11-05 (cortes pedidos pelo Daniel):** a tabela de regras de acesso (cap. 7) virou frase, o quadro dos testes de rede foi agrupado em 5 linhas, os prints T2 e T6 viraram uma só figura (14), o fluxo ponta a ponta passou a ser a Figura 15 e foram enxutos os capítulos 2 a 10, perto de 700 palavras a menos. Como as figuras agora são desenhadas em tamanho legível (até 16 cm de largura), o teste do LibreOffice mostra **cerca de 29 páginas** da introdução à conclusão, com as quatro figuras UML ainda como caixas de 11,5 x 7 cm. Margem pequena: confirmar no Word.

**Esclarecido em 2026-11-04 (Prof.ª Eliana):** a Introdução e a Conclusão **entram** na contagem das 20 a 30 páginas. Com a introdução (cap. 1), os capítulos 2 a 9 e a conclusão (cap. 10), o texto tem cerca de **10.465 palavras** (aproximadamente 32 a 35 páginas só de texto, antes das 17 figuras), então **é preciso cortar** para caber em 30 páginas. Meta: cerca de 8.000 palavras no total. A paginação real só se vê no Word.

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

Numeração em ordem de aparição (renumerada em 2026-11-07, quando o grupo decidiu que **o limite de 30 páginas conta o arquivo inteiro**: capa, resumo, sumário e referências incluídos). Para caber, saíram do documento as figuras de classes e de atividade (UML), o print dos testes automatizados, o mapa da estante e o fluxo ponta a ponta. Elas continuam no repositório (`03-engenharia-software/diagramas/` e `figuras/extras/`). O manual pede casos de uso, classes "quando aplicável" e atividade **ou** sequência, e o documento traz casos de uso e sequência.

| Nº | Figura | Capítulo | Arquivo |
|---|---|---|---|
| 01 | Organograma | 2 | `figura-01-organograma.png` |
| 02 | Processo atual (caderno) | 2 | `figura-02-processo-atual.png` |
| 03 | Processo proposto | 2 | `figura-03-processo-proposto.png` |
| 04 | Casos de uso | 4 | `figura-04-casos-de-uso.png` |
| 05 | Sequência da sincronização | 4 | `figura-05-sequencia-sincronizacao.png` |
| 06 | DER | 5 | `figura-06-der.png` |
| 07 | Print de consulta SQL | 5 | `figura-07-consulta-sql.png` |
| 08 | Fluxograma do A1 | 6 | `figura-08-fluxograma-a1.png` |
| 09 | Topologia no Packet Tracer | 7 | `figura-09-topologia.png` |
| 10 | Prints dos testes T2 e T6, lado a lado | 7 | `figura-10-testes-t2-t6.png` |

Fluxogramas das Figuras 2, 3, 8: versões gradeadas geradas por `figuras/fontes/fluxogramas_grade.py` (as verticais do Mermaid ficavam ilegíveis). Os fluxogramas A2 a A6 ficam em `05-programa-c/algoritmos/fluxogramas/`.

**Tamanhos usados no teste de páginas:** organograma 10 x 6,8 cm; processos e A1 com 14 cm de largura e 6,5 a 7,6 cm de altura; casos de uso 9,8 x 9 cm; sequência 12,5 x 11,8 cm; DER 16 x 10 cm; topologia 13 x 7,4 cm.

## 5. Lista de quadros

Quadro 1: problemas do processo atual (cap. 2). Quadro 2: relatório consolidado com dados de exemplo (cap. 6). Quadro 3: resultado dos testes no Packet Tracer (cap. 7). Quadro 4: indicadores propostos (cap. 9). Os quadros de requisitos, de consultas SQL e de "construído x simulado" viraram texto em 2026-11-07.

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
