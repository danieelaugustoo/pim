# ADR-004: Scrum com sprints de 1 semana

**Status:** aceita

## Contexto

Grupo pequeno (até 6 integrantes), prazo curto e escopo que precisa ser entregue em partes verificáveis. O manual aceita Scrum, XP ou Kanban como planejamento.

## Decisão

Usar **Scrum** com sprints de 1 semana, cerimônias simplificadas e um quadro Kanban de apoio. A duração real das sprints depende do prazo de entrega, a confirmar (`00-projeto/cronograma.md`).

## Alternativas consideradas

| Alternativa | Avaliação |
|---|---|
| Kanban puro | Bom para fluxo contínuo, mas não marca entregas nem metas por período |
| XP | Práticas úteis (testes), porém mais exigente para um grupo iniciante e sem programação em par garantida |
| Cascata | Pouca flexibilidade para ajustar o escopo ao prazo |

## Justificativa

- Metas semanais tornam o avanço visível e a entrega final menos arriscada.
- Os registros de cada sprint (`sprint-NN.md`) servem de evidência na Etapa 3.
- A definição de pronto padroniza a qualidade (compila sem warnings, testes, comentários, rastreabilidade).

## Consequências

- Papéis, cerimônias, backlog e definição de pronto em `scrum/`.
- Uma tag de versão ao fim de cada sprint (`v0.1.0`, `v0.2.0`, `v0.3.0`; entrega `v1.0.0`).
- Sprints 0 a 4, conforme o `PLANO.md`, seção 10.
