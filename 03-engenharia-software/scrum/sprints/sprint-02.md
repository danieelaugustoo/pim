# Sprint 2: sistema distribuído

**Datas:** [DATA A DEFINIR]
**Meta:** a portaria cadastra moradores, avisa pelo canal de cada um, continua trabalhando sem internet e envia as operações à central, que as consolida sem duplicar (US07 a US11).

## Histórias

| ID | História | Situação |
|---|---|---|
| US07 | Cadastrar moradores com canal de aviso | Feito (falta revisão do grupo) |
| US08 | Aviso pelo canal do morador | Feito (falta revisão do grupo) |
| US09 | Registrar sem internet | Feito (falta revisão do grupo) |
| US10 | Sincronizar quando a conexão voltar | Feito (falta revisão do grupo) |
| US11 | Consolidar sem duplicidade | Feito (falta revisão do grupo) |

Critérios de aceitação em `scrum/backlog.md`. "Feito" significa implementado, compilando sem warnings e testado; a revisão por outro integrante (definição de pronto) ainda não aconteceu.

## Verificações realizadas (2026-10-29)

- `gcc -std=c99 -Wall -Wextra -pedantic` sem warnings, também com `-O2`, para `portaria` e `central`.
- `make`, `make test`, `make clean` (com e sem `sh` no PATH) e `build.bat`/`build.bat test` funcionando.
- 8 conjuntos de testes passando: os 5 da Sprint 1 e `test_morador`, `test_sincronizacao` e `test_consolidacao`.
- Execução real com os dados de exemplo:
  - **Central rodada duas vezes** com os mesmos logs: 17 operações e 14 encomendas aplicadas na 1ª; na 2ª, 0 aplicadas e 17 já aplicadas, e os arquivos ficaram idênticos byte a byte.
  - **Portaria offline:** 3 registros (A-12 com SMS, D-7 com interfone, Z-1 sem morador) entraram na fila; sincronizar offline informou "3 operações aguardando" e preservou a fila; ao voltar online, as 3 foram enviadas e a fila ficou só com o cabeçalho.
  - **Numeração:** `P01-000011` a `P01-000013`, continuando da sequência do arquivo.
  - **Central depois do envio:** 3 aplicadas e 10 já aplicadas; depois da retirada da encomenda 9, 1 aplicada e 13 já aplicadas.
  - **Moradores:** nome repetido na mesma unidade e contato inválido para SMS foram recusados.
  - **Privacidade:** o arquivo `Pnn-avisos.txt` não contém o código de retirada.
- O relatório da central bate com as consultas do banco de exemplo.

## O que foi entregue

- Módulos novos `morador`, `aviso`, `sincronizacao` e `consolidacao`, e o executável `central` (`src/central.c`).
- `portaria.c` com os menus 6 (moradores), 8 (sincronizar) e 9 (online/offline) e o indicador `[ONLINE]`/`[OFFLINE]`; registro e retirada passam a enfileirar a operação.
- Persistência de moradores; `retirada_registrar` devolve o índice da encomenda; `Makefile` e `build.bat` compilam a central e os 8 testes.
- Dados de exemplo (moradores, sequência e logs `P01.log` e `P02.log`).
- Pseudocódigo e fluxogramas de A4 e A5 em `05-programa-c/algoritmos/`.

## O que não foi entregue / fica para depois

- Pseudocódigo e fluxogramas de A1, A2, A3 e A6: previstos para a Sprint 3 pelo `PLANO.md` (a definição de pronto os pede por história; decisão do grupo pendente).
- Operação DEVOLUCAO gerada pela portaria (US16, opcional, Sprint 3): a central já a entende.
- Aviso e rede reais: seguem simulados.
- Tag `v0.2.0` ao fim da sprint: depende da revisão e do commit.

## Impedimentos e riscos

- Apagar `Pnn-sequencia.txt` sem apagar o log da rede faz a portaria repetir ids de operações já aplicadas, e a central as ignora. Está nas limitações do README; no sistema completo, a chave primária e a API tratam isso.
- Prazo oficial de entrega ainda não confirmado.

## Retrospectiva (a preencher pelo grupo)

- O que funcionou:
- O que melhorar:
- Ações para a próxima sprint:
