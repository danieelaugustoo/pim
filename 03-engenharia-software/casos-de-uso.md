# Casos de uso (Etapa 3)

> Roteiro de tópicos para o capítulo 4. Diagrama: [`diagramas/casos-de-uso.puml`](diagramas/casos-de-uso.puml).

## 1. Lista

| ID | Caso de uso | Ator principal | Requisitos |
|---|---|---|---|
| UC01 | Registrar encomenda (inclui UC02) | Porteiro | RF01, RF02, RF03 |
| UC02 | Avisar morador | Serviço de avisos (acionado pelo sistema) | RF04 |
| UC03 | Retirar encomenda | Porteiro (com o morador) | RF05 |
| UC04 | Consultar pendências | Porteiro | RF06, RF07 |
| UC05 | Manter moradores | Porteiro | RF08 |
| UC06 | Sincronizar com a central | Porteiro | RF09, RF10 |
| UC07 | Consolidar operações | Supervisor (via Central) | RF10 |
| UC08 | Emitir relatórios | Supervisor | RF11, RF12 |

## 2. Descrição

### UC01 Registrar encomenda

| Campo | Descrição |
|---|---|
| Ator principal | Porteiro |
| Pré-condição | Portaria aberta (online ou offline) |
| Fluxo principal | 1. Porteiro informa bloco, apartamento, destinatário, transportadora e tamanho (P, M ou G). 2. O sistema valida os dados. 3. O sistema indica a posição livre na estante. 4. O sistema gera o código de retirada. 5. O sistema grava a encomenda como PENDENTE. 6. O sistema registra a operação REGISTRO na fila. 7. Inclui UC02. |
| Fluxos alternativos | 2a. Dado inválido: o sistema pede novamente. 3a. Estante cheia: o sistema avisa o porteiro e não grava a encomenda. |
| Pós-condição | Encomenda PENDENTE, com posição e código; operação na fila |

### UC02 Avisar morador

| Campo | Descrição |
|---|---|
| Ator principal | Serviço de avisos (sistema externo) |
| Pré-condição | Encomenda registrada (UC01) |
| Fluxo principal | 1. O sistema consulta o canal do morador da unidade. 2. Se o canal for APP ou SMS, envia o aviso ao contato cadastrado. 3. Se o canal for INTERFONE, gera o código impresso para o porteiro. 4. O sistema registra o aviso. |
| Fluxos alternativos | 1a. Unidade sem morador cadastrado: o sistema sinaliza ao porteiro, que avisa pelo interfone. |
| Pós-condição | Aviso registrado. No protótipo, o envio é simulado e gravado em arquivo |

### UC03 Retirar encomenda

| Campo | Descrição |
|---|---|
| Ator principal | Porteiro (atendendo o morador) |
| Pré-condição | Existe encomenda PENDENTE para a unidade |
| Fluxo principal | 1. Porteiro informa a unidade. 2. O sistema lista as pendências. 3. Porteiro escolhe a encomenda e informa o código dito pelo morador. 4. O sistema confere o código. 5. Porteiro informa o nome de quem retira. 6. O sistema marca a encomenda como RETIRADA com data e hora, libera a posição e registra a operação RETIRADA na fila. |
| Fluxos alternativos | 4a. Código errado: o sistema permite nova tentativa, até 3. 4b. Esgotadas as tentativas: a retirada é negada e a encomenda continua PENDENTE. |
| Pós-condição | Encomenda RETIRADA (ou inalterada, em caso de negativa) |

### UC04 Consultar pendências

| Campo | Descrição |
|---|---|
| Ator principal | Porteiro |
| Pré-condição | Portaria aberta |
| Fluxo principal | 1. Porteiro escolhe listar pendentes, buscar por unidade ou ver o mapa da estante. 2. O sistema exibe o resultado. |
| Fluxos alternativos | 1a. Nenhuma pendência: o sistema informa que a lista está vazia. |
| Pós-condição | Nenhuma alteração de dados |

### UC05 Manter moradores

| Campo | Descrição |
|---|---|
| Ator principal | Porteiro |
| Pré-condição | Portaria aberta |
| Fluxo principal | 1. Porteiro cadastra ou lista moradores. 2. No cadastro, informa nome, bloco, apartamento, canal de aviso e contato. 3. O sistema valida e grava. |
| Fluxos alternativos | 2a. Canal INTERFONE: o contato pode ficar vazio. 2b. Canal APP ou SMS sem contato: o sistema pede o contato. |
| Pós-condição | Morador gravado |

### UC06 Sincronizar com a central

| Campo | Descrição |
|---|---|
| Ator principal | Porteiro |
| Pré-condição | Existem operações na fila |
| Fluxo principal | 1. Porteiro pede a sincronização. 2. Com a portaria online, o sistema envia cada operação da fila à central. 3. O sistema esvazia a fila. |
| Fluxos alternativos | 2a. Portaria offline: o sistema informa quantas operações aguardam e mantém a fila. |
| Pós-condição | Fila vazia (online) ou preservada (offline) |

### UC07 Consolidar operações

| Campo | Descrição |
|---|---|
| Ator principal | Supervisor (aciona a Central) |
| Pré-condição | Portarias enviaram operações |
| Fluxo principal | 1. Para cada portaria, a Central lê as operações recebidas. 2. Se o id da operação já foi aplicado, ignora. 3. Senão, aplica no consolidado e registra o id como aplicado. |
| Fluxos alternativos | 1a. Portaria sem envio: a Central passa para a próxima. |
| Pós-condição | Consolidado atualizado, sem duplicidade |

### UC08 Emitir relatórios

| Campo | Descrição |
|---|---|
| Ator principal | Supervisor |
| Pré-condição | Dados registrados na portaria ou consolidados na Central |
| Fluxo principal | 1. O supervisor pede o relatório. 2. O sistema calcula dia de pico, ocupação da estante e pendências antigas (mais de 7 dias). 3. O sistema exibe ou grava o relatório. |
| Fluxos alternativos | 2a. Sem dados no período: o sistema informa. |
| Pós-condição | Relatório gerado |
