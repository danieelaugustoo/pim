# Sprint 1: portaria funcionando

**Datas:** 29/10/2026 (ciclo único registrado no repositório; ver `00-projeto/cronograma.md`)
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

## Banco de dados (Etapa 4, Prompt 5)

Entregue junto com a sprint (o plano reparte a Etapa 4 entre as Sprints 1 e 2):

| Entrega | Situação |
|---|---|
| Modelo conceitual, DER (Mermaid), modelo lógico, normalização, dicionário de dados | Feito (falta revisão do grupo; DER não renderizado) |
| Comparativo NoSQL e exemplo JSON de aviso | Feito (falta revisão do grupo; citar só após conferir B04–B06) |
| Scripts SQL 01 a 04 (previstos para a Sprint 2) | Feito e **executado** em MySQL 8.4.13 (contêiner Docker descartável, 2026-10-29) |

Verificação (2026-10-29), em MySQL 8.4.13 pelo Docker (`mysql:8.4`):
- Scripts 01 a 04 rodaram sem erro, de primeira: 11 tabelas, 44 restrições, 96 posições, 14 encomendas, 17 operações.
- As 8 consultas de `03-consultas.sql` devolveram os valores esperados dos comentários (6 e 5 pendentes; pendências antigas de 14 e 9 dias; pico de Bela Vista em 27/10 com 3; ocupação 12,5% e 10,4%; auditoria de consistência sem violações). As views `vw_pendentes` e `vw_indicadores_condominio` funcionam e o índice `idx_encomenda_unidade` substituiu o automático da chave estrangeira.
- Testes das restrições, numa transação desfeita no fim: o banco recusou retirada repetida, operação repetida, duas pendentes na mesma posição, APP sem contato, status inválido, portaria `P11` e `p03`, hash inválido, tamanho `X`, prefixo de operação trocado, apartamento 0 e repetido, FK inexistente e `(portaria, id_local)` repetido; aceitou o reaproveitamento da posição de uma encomenda já retirada; `INSERT IGNORE` inseriu 1 linha na primeira vez e 0 na segunda.
- Antes disso, um script em Python já tinha conferido a coerência dos dados de exemplo com o CSV do protótipo.

O roteiro de testes das restrições foi feito num arquivo temporário fora do repositório; os comandos principais estão comentados na seção 9 de `03-consultas.sql`.

## O que não foi entregue / fica para depois

- Teste no MySQL Workbench e em MySQL 8.0 (só foi testado na 8.4.13). As funções usadas existem desde a 8.0.16.

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
