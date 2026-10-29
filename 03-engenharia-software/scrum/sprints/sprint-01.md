# Sprint 1: portaria funcionando

**Datas:** [DATA A DEFINIR]
**Meta:** o nó da portaria registra, localiza e entrega encomendas, guardando os dados em arquivo (US01 a US06).

## Histórias

| ID | História | Situação |
|---|---|---|
| US01 | Registrar encomenda | Feito (falta revisão do grupo) |
| US02 | Indicar posição na estante | Feito (falta revisão do grupo) |
| US03 | Código único de retirada | Feito (falta revisão do grupo) |
| US04 | Registrar retirada conferindo o código | Feito (falta revisão do grupo) |
| US05 | Listar pendências e buscar por unidade | Feito (falta revisão do grupo) |
| US06 | Dados salvos em arquivo | Feito (falta revisão do grupo) |

Critérios de aceitação em `scrum/backlog.md`. "Feito" significa implementado, compilando sem warnings e testado; a revisão por outro integrante (definição de pronto) ainda não aconteceu.

## Verificações realizadas (2026-10-29)

- `gcc -std=c99 -Wall -Wextra -pedantic` sem warnings, também com `-O2`.
- `make`, `make test` e `make clean` funcionando com e sem `sh` no PATH (Git Bash e PowerShell).
- `build.bat` e `build.bat test` funcionando.
- 5 conjuntos de testes passando: `test_util`, `test_estante`, `test_codigo`, `test_encomenda`, `test_persistencia`.
- Execução manual com dados de exemplo: listar, buscar, registrar (volume G na faixa reservada), retirar com código errado e certo, negativa após 3 erros, reabrir o programa e conferir os dados.

## O que foi entregue

- `05-programa-c/`: `tipos.h`, módulos `util`, `estante`, `codigo`, `encomenda`, `retirada`, `persistencia`, `portaria.c`, Makefile, `build.bat`, 5 arquivos de teste e `dados/exemplo/P01-encomendas.csv`.

## O que não foi entregue / fica para depois

- Pseudocódigo e fluxogramas de A1, A2 e A3: previstos para a Sprint 3 pelo `PLANO.md`, mas a definição de pronto os pede por história. **Decisão do grupo pendente:** escrever agora ou manter na Sprint 3.
- A operação REGISTRO/RETIRADA na fila de sincronização (parte final do A3): entra na Sprint 2 com a sincronização.
- Tag `v0.1.0` ao fim da sprint: depende da revisão e do commit.

## Impedimentos e riscos

- O Windows bloqueou de forma intermitente a execução de `test_encomenda.exe` recém-compilado ("política de Controle de Aplicativo", erro 4551). Em outras execuções o mesmo código rodou e passou. Nenhuma configuração de segurança foi alterada. Se acontecer no grupo, é preciso verificar a proteção do Windows de cada máquina.
- Prazo oficial de entrega ainda não confirmado.

## Retrospectiva (a preencher pelo grupo)

- O que funcionou:
- O que melhorar:
- Ações para a próxima sprint:
