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
| Resultados | Pesquisa de campo (3), consultas SQL (5), testes e telas do protótipo (6), testes do Packet Tracer (7) |
| Discussão | Benefícios, limitações e comparação com trabalhos relacionados (9) |

## 4. Lista de figuras

Numeração em ordem de aparição. Arquivos finais em `figuras/figura-NN-descricao.png`. Pré-requisito de várias figuras: **renderizar** o diagrama (Mermaid e PlantUML ainda não foram renderizados).

| Nº | Figura | Capítulo | Origem | Quem produz |
|---|---|---|---|---|
| 01 | Organograma | 2 | `01-organizacao/diagramas/organograma.mmd` | renderizar |
| 02 | Processo atual (caderno) | 2 | `01-organizacao/diagramas/processo-atual.mmd` | renderizar |
| 03 | Processo proposto | 2 | `01-organizacao/diagramas/processo-proposto.mmd` | renderizar |
| 04 | Casos de uso | 4 | `03-engenharia-software/diagramas/casos-de-uso.puml` | renderizar |
| 05 | Classes de domínio | 4 | `.../classes-dominio.puml` | renderizar |
| 06 | Atividade: registrar encomenda | 4 | `.../atividade-registrar-encomenda.puml` | renderizar |
| 07 | Sequência da sincronização | 4 | `.../sequencia-sincronizacao.puml` | renderizar |
| 08 | Estados da encomenda (opcional) | 4 | `.../estados-encomenda.puml` | renderizar |
| 09 | DER | 5 | `04-banco-de-dados/diagramas/der.mmd` | renderizar |
| 10 | Fluxograma do A1 | 6 | `05-programa-c/algoritmos/fluxogramas/A1.mmd` | renderizar |
| 11 | Print do mapa da estante | 6 | executar a opção 5 do programa | **grupo** |
| 12 | Fluxograma do A5 | 6 | `.../fluxogramas/A5.mmd` | renderizar |
| 13 | Topologia no Packet Tracer | 7 | montagem no simulador | **grupo** |
| 14 | Print do teste T2 (portaria alcança a API) | 7 | Packet Tracer | **grupo** |
| 15 | Print do teste T6 (visitantes não alcançam a portaria) | 7 | Packet Tracer | **grupo** |
| 16 | Fluxo ponta a ponta | 9 | `08-integracao/diagramas/fluxo-ponta-a-ponta.mmd` | renderizar |

Gráficos de resultados do questionário (capítulo 3) entram quando a pesquisa for aplicada. Fluxogramas A2, A3, A4 e A6 ficam em apêndice ou só no repositório.

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
3. Capítulos 2, 3 (depois da pesquisa de campo), 8 e 9.
4. Introdução e Conclusão.
5. Resumo e Abstract (por último).
6. Referências, conferindo citação × lista.

## 7. Código no documento

Trechos principais no capítulo 6; código completo no repositório (link) ou em apêndice. Decisão pendente com o professor.
