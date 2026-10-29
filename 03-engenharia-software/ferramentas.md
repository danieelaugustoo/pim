# Ferramentas e tecnologias (Etapa 3)

> Corresponde ao item "materiais" que o manual pede no Desenvolvimento. Subseção do capítulo 4.

As versões abaixo precisam ser conferidas pelo grupo nas máquinas usadas. Onde não foi verificada, está marcado `[VERSÃO A VERIFICAR]`.

| Ferramenta | Versão | Finalidade | Situação |
|---|---|---|---|
| gcc (C99; MinGW-w64 no Windows) | [VERSÃO A VERIFICAR] | Compilar o protótipo com `-std=c99 -Wall -Wextra -pedantic` | Não encontrado no PATH da máquina de desenvolvimento em 2026-10-29; instalar antes da Sprint 1 |
| Make | [VERSÃO A VERIFICAR] | Automatizar compilação e testes (`make`, `make test`, `make clean`) | Não encontrado no PATH em 2026-10-29; `build.bat` cobre o Windows sem make |
| Git | 2.54.0.windows.1 | Controle de versão (branches, commits, tags de sprint) | Instalado |
| GitHub | — | Repositório remoto, revisão e quadro de apoio (GitHub Projects) | A confirmar com o grupo |
| MySQL 8 | [VERSÃO A VERIFICAR] | SGBD do modelo físico e dos scripts SQL (trocar se a disciplina usar outro) | A confirmar |
| MySQL Workbench | [VERSÃO A VERIFICAR] | Executar e testar os scripts SQL | A confirmar |
| PlantUML | [VERSÃO A VERIFICAR] | Diagramas UML (`.puml`) | Não encontrado no PATH em 2026-10-29; exportar por extensão do VS Code ou pelo site oficial |
| Mermaid | [VERSÃO A VERIFICAR] | Fluxogramas, organograma, DER e rascunhos (`.mmd`) | Idem |
| Cisco Packet Tracer | [VERSÃO A VERIFICAR] | Simular a topologia de rede (feito pelo grupo) | A confirmar |
| brModelo | [VERSÃO A VERIFICAR] | Modelo conceitual na notação de Chen, se o professor pedir | Opcional |
| Word ou Google Docs | — | Montagem final do trabalho no modelo ABNT da UNIP | A confirmar |
| Trello ou GitHub Projects | — | Quadro Kanban de apoio (A fazer → Fazendo → Em revisão → Pronto) | A escolher |

## Padrões de uso

- Linguagem: C99 e apenas a biblioteca padrão (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `time.h`, `assert.h`).
- Dados do protótipo: CSV separado por `;`, texto em ASCII (ADR-002).
- Diagramas: PlantUML para UML, Mermaid para o restante, exportados em PNG para `documento-final/figuras/` (ADR-005).
