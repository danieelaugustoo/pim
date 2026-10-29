# Papéis e cerimônias (Scrum)

> Decisão ADR-004. Os nomes dos integrantes ficam em `00-projeto/integrantes.md`.

## Papéis

| Papel | Responsabilidade | Quem |
|---|---|---|
| Product Owner | Priorizar o backlog e decidir o que entra em cada sprint | [A DEFINIR] |
| Scrum Master | Facilitar as cerimônias e remover impedimentos | [A DEFINIR] |
| Time de desenvolvimento | Entregar as histórias de cada sprint | [A DEFINIR] (todos os integrantes) |
| Líder do grupo | Fazer a postagem final e cadastrar os demais no sistema da UNIP | Lucas Ribeiro Tomiossi Kribely |

O Claude Code apoia o time de desenvolvimento, mas não ocupa nenhum papel.

## Cerimônias simplificadas

| Cerimônia | Quando | Duração | Registro |
|---|---|---|---|
| Planejamento da sprint | Início da sprint | 30 minutos | Meta e histórias em `sprints/sprint-NN.md` |
| Daily assíncrona | Todo dia útil, no grupo de mensagens | Poucas linhas por pessoa: o que fiz, o que farei, impedimentos | Não precisa de arquivo |
| Revisão da sprint | Fim da sprint, às sextas, 19h, por mensagem escrita no grupo | Uma mensagem | O que foi entregue e o que não foi, em `sprint-NN.md` |
| Retrospectiva | Fim da sprint, às sextas, 19h, por mensagem escrita no grupo | Uma mensagem | O que melhorar, em `sprint-NN.md` |

## Quadro de apoio

Quadro Kanban (GitHub Projects ou Trello, a escolher) com as colunas **A fazer → Fazendo → Em revisão → Pronto**. Cada cartão é uma história do backlog.

## Fluxo de uma história

1. Sai do backlog para a sprint no planejamento.
2. Passa por A fazer → Fazendo, em uma branch `feature/USxx-descricao` (ou `docs/...`).
3. Em revisão: outro integrante confere contra a [definição de pronto](definicao-de-pronto.md).
4. Pronto: merge na `main`, `rastreabilidade.md` e `sprint-NN.md` atualizadas.

## Sprints

| Sprint | Meta | Datas |
|---|---|---|
| 0 | Base do projeto | [DATA A DEFINIR] |
| 1 | Portaria funcionando | [DATA A DEFINIR] |
| 2 | Sistema distribuído | [DATA A DEFINIR] |
| 3 | Relatórios e qualidade | [DATA A DEFINIR] |
| 4 | Documento e entrega | [DATA A DEFINIR] |

As datas dependem do prazo oficial de entrega, ainda a confirmar (`PLANO.md`, seção 13).
