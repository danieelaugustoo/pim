# 5 Banco de dados (roteiro, cerca de 4 páginas, Etapa 4)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo".

**Fontes no repositório:** `04-banco-de-dados/` (modelos, normalização, dicionário, DER, scripts SQL, NoSQL).

## Tópicos

| # | Tópico | Origem |
|---|---|---|
| 5.1 | Por que um banco relacional (ADR-001) e o papel do banco na solução (central/nuvem; o protótipo usa CSV) | `03-engenharia-software/decisoes/adr-001-banco-relacional.md`, `adr-002-armazenamento-csv.md` |
| 5.2 | Modelo conceitual: entidades, atributos e relacionamentos | `modelo-conceitual.md` |
| 5.3 | DER | `diagramas/der.mmd` |
| 5.4 | Normalização a partir do caderno da portaria (1FN, 2FN, 3FN) | `normalizacao.md` |
| 5.5 | Modelo lógico (tabelas, chaves, restrições) | `modelo-logico.md` |
| 5.6 | Dicionário de dados | `dicionario-de-dados.md` |
| 5.7 | Modelo físico em MySQL 8: criação, restrições nomeadas, coluna gerada e índice único | `sql/01-criacao-tabelas.sql` |
| 5.8 | Comandos SQL principais: carga, consultas, views e índices | `sql/02-carga-exemplo.sql`, `03-consultas.sql`, `04-views-indices.sql` |
| 5.9 | Resultados: consultas executadas e conferidas (inclusive a consolidação idempotente) | `sql/README.md`, `03-engenharia-software/scrum/sprints/sprint-01.md` (verificação em MySQL 8.4.13) |
| 5.10 | Discussão sobre NoSQL: quando serviria e por que não foi escolhido | `nosql/comparativo.md`, `nosql/exemplo-aviso.json` |

## Figuras e tabelas

| Item | Origem |
|---|---|
| Figura 09: DER | `diagramas/der.mmd` |
| Tabela: entidades e finalidade (11 tabelas) | `modelo-logico.md` |
| Tabela: passos da normalização | `normalizacao.md` |
| Tabela ou trecho de código: 2 ou 3 consultas SQL com o resultado obtido | `sql/03-consultas.sql` |
| Tabela: SQL × NoSQL | `nosql/comparativo.md` |

## Fatos verificados que podem ser citados

- Os 4 scripts foram executados em MySQL 8.4.13 (Docker) sem erro; o modelo físico tem 11 tabelas e 44 restrições nomeadas.
- Os resultados das consultas de relatório conferem com os da central em C.

## O que depende do grupo

- [ ] Confirmar o SGBD da disciplina e se o professor exige o modelo conceitual no **brModelo** (`PLANO.md`, seção 13).
- [ ] Renderizar o DER e exportar o PNG.
- [ ] Rodar os scripts na máquina de apresentação (`sql/README.md` explica) e tirar o print de uma consulta.
- [ ] Citar teoria de normalização e de bancos só com fonte verificada.

---

## Texto do grupo

*(escrever aqui)*
