# Modelo conceitual (Etapa 4)

> Roteiro para o capítulo 5, que o grupo redige. O DER está em [`diagramas/der.mmd`](diagramas/der.mmd). Se o professor pedir a notação de Chen, o grupo monta no brModelo a partir desta página.

## 1. Entidades e atributos

| Entidade | Atributos | Identificador | Descrição |
|---|---|---|---|
| Condomínio | nome, cidade | id | Condomínio administrado pela Morada Central |
| Bloco | nome | id | Bloco de um condomínio (A, B, C...) |
| Unidade | número | id | Apartamento de um bloco |
| Morador | nome, canal de aviso, contato, ativo | id | Pessoa cadastrada em uma unidade |
| Funcionário | nome, função | id | Porteiro ou outro funcionário de um condomínio |
| Portaria | descrição | código (P01 a P10) | Nó local de operação de um condomínio |
| Posição de estante | estante, prateleira, tipo de volume | id | Lugar físico para um volume |
| Encomenda | id local, destinatário, transportadora, tamanho, recebida em, código de retirada (hash), status | id | Volume recebido na portaria para uma unidade |
| Retirada | retirado por, retirada em | id | Entrega da encomenda ao morador |
| Aviso | canal, enviado em, situação | id | Comunicação da chegada ao morador |
| Operação de sincronização | tipo, id local, data/hora de origem, aplicada em | código da operação (ex.: P01-000123) | Evento da portaria já aplicado na central |

## 2. Relacionamentos

| # | Relacionamento | Cardinalidade | Observação |
|---|---|---|---|
| R1 | Condomínio **possui** Bloco | 1 : N | Um condomínio tem de 2 a 4 blocos (`PLANO.md`, seção 4) |
| R2 | Bloco **possui** Unidade | 1 : N | |
| R3 | Unidade **abriga** Morador | 1 : N | |
| R4 | Condomínio **emprega** Funcionário | 1 : N | |
| R5 | Condomínio **tem** Portaria | 1 : N | No cenário, uma portaria por condomínio |
| R6 | Portaria **tem** Posição de estante | 1 : N | |
| R7 | Portaria **recebe** Encomenda | 1 : N | |
| R8 | Unidade **é destino de** Encomenda | 1 : N | |
| R9 | Posição de estante **guarda** Encomenda | 1 : N | No máximo uma encomenda pendente por posição (RN04) |
| R10 | Funcionário **registra o recebimento de** Encomenda | 1 : N | |
| R11 | Encomenda **tem** Retirada | 1 : 0..1 | RN03 |
| R12 | Funcionário **entrega** (Retirada) | 1 : N | |
| R13 | Encomenda **gera** Aviso | 1 : N | |
| R14 | Morador **recebe** Aviso | 1 : N | |
| R15 | Portaria **origina** Operação de sincronização | 1 : N | |

## 3. Regras de negócio

| ID | Regra | Onde é garantida |
|---|---|---|
| RN01 | O canal de aviso é APP, SMS ou INTERFONE; APP e SMS exigem contato | `ck_morador_canal`, `ck_morador_contato` |
| RN02 | O status da encomenda é PENDENTE, RETIRADA ou DEVOLVIDA | `ck_encomenda_status` |
| RN03 | Uma encomenda tem no máximo uma retirada | `uq_retirada_encomenda` |
| RN04 | Uma posição guarda no máximo uma encomenda pendente | `uq_encomenda_posicao_pendente` |
| RN05 | O id da encomenda na portaria é único dentro da portaria | `uq_encomenda_portaria_local` |
| RN06 | Cada operação de sincronização é aplicada uma única vez | `pk_operacao_sincronizacao` |
| RN07 | O tamanho do volume é P, M ou G | `ck_encomenda_tamanho` |
| RN08 | Dentro de um bloco, o número da unidade é único | `uq_unidade_bloco_numero` |
| RN09 | A posição é única por portaria, estante e prateleira | `uq_posicao_estante_local` |
| RN10 | O código de retirada nunca é guardado em texto no banco central | coluna `codigo_retirada_hash` |

As regras que ligam tabelas diferentes além de uma FK simples (por exemplo, a posição pertencer à mesma portaria da encomenda) estão em [`modelo-logico.md`](modelo-logico.md), seção 3.

## 4. Ligação com o protótipo em C

`id_local` é o id da encomenda no arquivo da portaria (`Pnn-encomendas.csv`). Junto com `id_portaria`, liga o protótipo ao banco central. Estante e prateleira usam os mesmos números do arquivo (estante 0 a 3 = letras A a D; prateleira 0 a 11).
