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
| Materiais | Ferramentas e tecnologias (capítulo 4, seção 4.9) |
| Resultados | Consultas SQL (5), testes e telas do protótipo (6), testes do Packet Tracer (7); sem levantamento de campo |
| Discussão | Benefícios, limitações e comparação com trabalhos relacionados (9) |

## 4. Lista de figuras

Numeração em ordem de aparição. Arquivos finais em `figuras/figura-NN-descricao.png`. Os diagramas Mermaid (figuras 01 a 03, 09, 10, 12 e 16) foram renderizados em 2026-10-31 com o mermaid-cli 11.4.2; **conferir visualmente** antes de usar. Os diagramas PlantUML (figuras 04 a 08) **ainda não foram renderizados**.

| Nº | Figura | Capítulo | Origem | Quem produz |
|---|---|---|---|---|
| 01 | Organograma | 2 | `01-organizacao/diagramas/organograma.mmd` | renderizado (PNG em `figuras/`) |
| 02 | Processo atual (caderno) | 2 | `01-organizacao/diagramas/processo-atual.mmd` | renderizado (PNG em `figuras/`) |
| 03 | Processo proposto | 2 | `01-organizacao/diagramas/processo-proposto.mmd` | renderizado (PNG em `figuras/`) |
| 04 | Casos de uso | 4 | `03-engenharia-software/diagramas/casos-de-uso.puml` | renderizar (PlantUML) |
| 05 | Classes de domínio | 4 | `.../classes-dominio.puml` | renderizar (PlantUML) |
| 06 | Atividade: registrar encomenda | 4 | `.../atividade-registrar-encomenda.puml` | renderizar (PlantUML) |
| 07 | Sequência da sincronização | 4 | `.../sequencia-sincronizacao.puml` | renderizar (PlantUML) |
| 08 | Estados da encomenda (opcional) | 4 | `.../estados-encomenda.puml` | renderizar (PlantUML) |
| 09 | DER | 5 | `04-banco-de-dados/diagramas/der.mmd` | renderizado (PNG em `figuras/`) |
| 10 | Fluxograma do A1 | 6 | `05-programa-c/algoritmos/fluxogramas/A1.mmd` | renderizado (PNG em `figuras/`) |
| 11 | Print do mapa da estante | 6 | executar a opção 5 do programa | **grupo** |
| 12 | Fluxograma do A5 | 6 | `.../fluxogramas/A5.mmd` | renderizado (PNG em `figuras/`) |
| 13 | Topologia no Packet Tracer | 7 | montagem no simulador | **grupo** |
| 14 | Print do teste T2 (portaria alcança a API) | 7 | Packet Tracer | **grupo** |
| 15 | Print do teste T6 (visitantes não alcançam a portaria) | 7 | Packet Tracer | **grupo** |
| 16 | Fluxo ponta a ponta | 9 | `08-integracao/diagramas/fluxo-ponta-a-ponta.mmd` | renderizado (PNG em `figuras/`) |

Fluxogramas A2, A3, A4 e A6 ficam em apêndice ou só no repositório.

## 5. Lista de tabelas (principais)

| Tabela | Capítulo | Origem |
|---|---|---|
| Problemas P1 a P7 | 2 | `01-organizacao/caracterizacao.md` |
| Matriz de trabalhos relacionados | 3 | `02-pesquisa/trabalhos-relacionados.md` |
| Requisitos e rastreabilidade | 4 | `03-engenharia-software/requisitos.md` |
| ADRs resumidos | 4 | `03-engenharia-software/decisoes/` |
| Sprints, metas e entregas | 4 | `scrum/sprints/` |
| Entidades do modelo lógico | 5 | `04-banco-de-dados/modelo-logico.md` |
| Consulta SQL com resultado | 5 | `04-banco-de-dados/sql/03-consultas.sql` |
| SQL × NoSQL | 5 | `04-banco-de-dados/nosql/comparativo.md` |
| Módulos e algoritmos A1 a A6 | 6 | `05-programa-c/README.md`, `algoritmos/pseudocodigo.md` |
| Endereçamento, VLANs e matriz de fluxos | 7 | `06-redes/` |
| Testes T1 a T15 (esperado × obtido) | 7 | `06-redes/packet-tracer/roteiro.md` |
| Dados pessoais × finalidade | 8 | `07-seguranca-privacidade-acessibilidade/analise.md` |
| Indicadores | 9 | `08-integracao/beneficios-e-indicadores.md` |
| Resultados × objetivos | 10 | `02-pesquisa/problema-e-objetivos.md` |

## 6. Ordem sugerida de escrita

1. Capítulos 4, 5 e 6 (o grupo domina o material e ele está pronto).
2. Capítulo 7, depois de montar o Packet Tracer.
3. Capítulos 2, 3 (depois de verificar as fontes), 8 e 9.
4. Introdução e Conclusão.
5. Resumo e Abstract (por último).
6. Referências, conferindo citação × lista.

## 7. Código no documento

Trechos principais no capítulo 6; código completo apenas pelo link do repositório no GitHub, sem apêndice (decisão do grupo, 2026-10-29).

## 8. Tamanho dos rascunhos (conferência de 2026-10-29)

Contagem de palavras da seção "Texto do grupo" de cada rascunho (inclui o aviso do topo, títulos, tabelas e marcas de figura, então é um pouco maior que o texto corrido). Estimativa grosseira: com Times 12, espaçamento 1,5 e as margens do manual, cabem cerca de 300 a 350 palavras por página; **a paginação real só se vê no Word**.

| Capítulo | Palavras | Meta de páginas | Situação |
|---|---|---|---|
| 1 Introdução | 459 | ~2 | dentro |
| 2 Organização | 1.001 | 3 | acima |
| 3 Pesquisa | 1.297 | 3 | acima |
| 4 Engenharia de software | 1.699 | 4 | acima |
| 5 Banco de dados | 1.385 | 4 | um pouco acima |
| 6 Programação em C | 1.944 | 4 | bem acima |
| 7 Redes | 1.488 | 4 | acima |
| 8 Segurança e acessibilidade | 1.134 | 2 | bem acima |
| 9 Integração | 1.406 | 2 | bem acima |
| 10 Conclusão | 561 | ~1,5 | dentro |

O desenvolvimento (capítulos 2 a 9) soma cerca de **11.350 palavras**, o que daria aproximadamente 32 a 38 páginas só de texto, **mais** as figuras. A meta é de 20 a 30 páginas. É preciso cortar, e a decisão sobre o que cortar é do grupo, depois de ver a paginação real.

**Plano de cortes sugerido (do que menos prejudica ao que mais prejudica):**
1. Tirar das tabelas o que repete o texto (por exemplo, Quadro 5 de ADRs, Quadro 7 de ferramentas, Quadro 15 de riscos, Quadro 18 de evoluções): manter no repositório e citar.
2. Reduzir figuras: manter as de maior valor (organograma, casos de uso, DER, fluxograma do A1, topologia, os dois prints do Packet Tracer, fluxo ponta a ponta) e juntar ou cortar as demais.
3. Resumir os capítulos 6, 8 e 9 em subseções de um parágrafo cada.
4. No capítulo 4, deixar o histórico das sprints em uma frase e remeter ao repositório.
5. Se a Introdução e a Conclusão não contarem no limite (confirmar com a Prof.ª Eliana), o ajuste necessário é menor.
