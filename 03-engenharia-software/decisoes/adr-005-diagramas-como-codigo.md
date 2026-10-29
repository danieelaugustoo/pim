# ADR-005: Diagramas como código (PlantUML e Mermaid)

**Status:** aceita

## Contexto

O projeto exige diagramas UML, fluxogramas, organograma, DER e topologia, e o grupo vai revisá-los e atualizá-los várias vezes ao longo das sprints.

## Decisão

Escrever os diagramas como código: **PlantUML** (`.puml`) para UML e **Mermaid** (`.mmd`) para fluxogramas, organograma, DER, topologia e rascunhos. Exportar para PNG em `documento-final/figuras/`, com o nome `figura-NN-descricao.png`.

## Alternativas consideradas

| Alternativa | Avaliação |
|---|---|
| Ferramentas gráficas (ex.: draw.io) | Boas visualmente, mas o arquivo é difícil de comparar e revisar no Git |
| Desenhar direto no Word | Difícil de manter consistente e de versionar |

## Justificativa

- Texto puro: versionável, revisável por diff e fácil de corrigir.
- O Claude Code consegue gerar e ajustar diagramas em texto.

## Consequências

- Os arquivos `.puml` e `.mmd` precisam ser renderizados por extensão do VS Code ou pelos sites oficiais; nem PlantUML nem Mermaid estavam instalados na máquina de desenvolvimento em 2026-10-29.
- Cada diagrama é conferido visualmente após a exportação, antes de entrar no trabalho.
- Para o Packet Tracer (feito pelo grupo), o diagrama Mermaid de topologia é só apoio.
