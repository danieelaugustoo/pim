# Backlog do produto

> Histórias de usuário (`PLANO.md`, seção 9.3), com critérios de aceitação no formato Dado / Quando / Então. Os critérios são uma proposta técnica e podem ser refinados no planejamento de cada sprint.

## Visão geral

| ID | História | Requisitos | Sprint | Estado |
|---|---|---|---|---|
| US01 | Registrar encomenda | RF01 | 1 | A fazer |
| US02 | Indicar posição na estante | RF02 | 1 | A fazer |
| US03 | Código único de retirada | RF03 | 1 | A fazer |
| US04 | Registrar retirada conferindo o código | RF05 | 1 | A fazer |
| US05 | Listar pendências e buscar por unidade | RF06 | 1 | A fazer |
| US06 | Dados salvos em arquivo | RF09 (base) | 1 | A fazer |
| US07 | Cadastrar moradores com canal de aviso | RF08 | 2 | A fazer |
| US08 | Aviso pelo canal do morador | RF04 | 2 | A fazer |
| US09 | Registrar sem internet | RF09 | 2 | A fazer |
| US10 | Sincronizar quando a conexão voltar | RF10 | 2 | A fazer |
| US11 | Consolidar sem duplicidade | RF10 | 2 | A fazer |
| US12 | Mapa de ocupação da estante | RF07 | 3 | A fazer |
| US13 | Alerta de volumes parados há mais de 7 dias | RF11 | 3 | A fazer |
| US14 | Relatórios de pico e ocupação | RF12 | 3 | A fazer |
| US15 | Testes automatizados | RNF05 (apoio) | 3 | A fazer |
| US16 | (Opcional) Marcar volume como devolvido | — | 3 | A fazer |

## Sprint 1: portaria funcionando

### US01 Registrar encomenda
**Como** porteiro, **quero** registrar uma encomenda com unidade, destinatário, transportadora e tamanho, **para** não depender do caderno.

- **Dado** que o porteiro abriu o registro, **quando** informa bloco, apartamento, destinatário, transportadora e tamanho (P, M ou G) válidos, **então** a encomenda é gravada com status PENDENTE, data e hora.
- **Dado** um campo obrigatório vazio, tamanho diferente de P, M ou G ou texto com `;`, **quando** o porteiro confirma, **então** o sistema recusa e pede o dado novamente, sem gravar nada.

### US02 Indicar posição na estante
**Como** porteiro, **quero** que o sistema indique a posição na estante, **para** guardar e achar o volume rápido.

- **Dado** uma encomenda de bloco B e tamanho M, **quando** é registrada, **então** o sistema indica a primeira posição livre na estante preferida do bloco (B = 1) dentro da faixa de volumes P e M (prateleiras anteriores à 10).
- **Dado** uma encomenda de tamanho G, **quando** é registrada, **então** a posição fica a partir da prateleira 10.
- **Dado** que a estante preferida está cheia, **quando** uma encomenda é registrada, **então** o sistema usa outra estante; se todas estiverem cheias, avisa o porteiro e não grava.

### US03 Código único de retirada
**Como** morador, **quero** um código único de retirada, **para** que só eu ou quem eu autorizar retire o volume.

- **Dado** uma nova encomenda, **quando** é registrada, **então** recebe um código de 6 dígitos (100000 a 999999).
- **Dado** que existem encomendas pendentes com códigos, **quando** um novo código é gerado, **então** ele é diferente de todos os códigos de encomendas pendentes.

### US04 Registrar retirada conferindo o código
**Como** porteiro, **quero** registrar a retirada conferindo o código, **para** saber quem retirou e quando.

- **Dado** uma encomenda PENDENTE, **quando** o porteiro informa o código correto e o nome de quem retira, **então** o status passa a RETIRADA, com data, hora e nome, e a posição na estante é liberada.
- **Dado** um código errado, **quando** o porteiro tenta, **então** o sistema permite nova tentativa, até 3 no total.
- **Dado** 3 tentativas erradas, **quando** a última falha, **então** a retirada é negada e a encomenda continua PENDENTE.

### US05 Listar pendências e buscar por unidade
**Como** porteiro, **quero** listar as pendências e buscar por unidade, **para** atender o morador no balcão.

- **Dado** encomendas PENDENTES, **quando** o porteiro lista as pendentes, **então** vê cada uma com unidade, destinatário, transportadora, posição e data de recebimento.
- **Dado** um bloco e um apartamento, **quando** o porteiro busca, **então** vê somente as encomendas daquela unidade.
- **Dado** nenhuma pendência, **quando** o porteiro lista ou busca, **então** o sistema informa que não há resultados.

### US06 Dados salvos em arquivo
**Como** administradora, **quero** os dados salvos em arquivo, **para** não perder registros ao fechar o programa.

- **Dado** encomendas registradas, **quando** o programa é fechado e aberto de novo, **então** todas as encomendas continuam disponíveis com o mesmo status.
- **Dado** que o programa abre, **quando** carrega as encomendas pendentes, **então** a matriz da estante é reconstruída com as posições ocupadas.
- **Dado** um arquivo inexistente na primeira execução, **quando** o programa abre, **então** ele cria os arquivos com cabeçalho sem falhar.

## Sprint 2: sistema distribuído

### US07 Cadastrar moradores com canal de aviso
**Como** porteiro, **quero** cadastrar moradores com o canal de aviso preferido, **para** avisar cada um do jeito certo.

- **Dado** nome, bloco, apartamento e canal APP ou SMS com contato, **quando** o porteiro cadastra, **então** o morador é gravado como ativo.
- **Dado** o canal INTERFONE, **quando** o porteiro cadastra sem contato, **então** o cadastro é aceito.
- **Dado** o canal APP ou SMS sem contato, **quando** o porteiro confirma, **então** o sistema recusa e pede o contato.

### US08 Aviso pelo canal do morador
**Como** morador, **quero** ser avisado pelo meu canal, **para** retirar logo.

- **Dado** um morador com canal APP ou SMS, **quando** uma encomenda é registrada para a unidade, **então** o aviso simulado é gravado em `Pnn-avisos.txt` com o canal e o contato.
- **Dado** um morador com canal INTERFONE, **quando** uma encomenda é registrada, **então** o sistema gera o código para impressão e orienta o porteiro a avisar pelo interfone.
- **Dado** uma unidade sem morador cadastrado, **quando** a encomenda é registrada, **então** o sistema sinaliza ao porteiro que o aviso deve ser feito manualmente.

### US09 Registrar sem internet
**Como** porteiro, **quero** continuar registrando sem internet, **para** a portaria não parar.

- **Dado** a portaria em modo offline, **quando** o porteiro registra uma encomenda ou uma retirada, **então** a operação é concluída normalmente e entra na fila.
- **Dado** que o menu mostra o modo atual, **quando** o porteiro alterna online/offline (simulação), **então** o indicador muda entre `[ONLINE]` e `[OFFLINE]`.

### US10 Sincronizar quando a conexão voltar
**Como** porteiro, **quero** sincronizar as operações quando a conexão voltar, **para** a central ficar atualizada.

- **Dado** a portaria offline, **quando** o porteiro pede a sincronização, **então** o sistema informa quantas operações aguardam e mantém a fila.
- **Dado** a portaria online, **quando** o porteiro pede a sincronização, **então** cada operação é copiada para `dados/rede/Pnn.log` e a fila é esvaziada.
- **Dado** que cada operação tem id `Pnn-NNNNNN`, **quando** várias operações são geradas, **então** os ids são sequenciais e únicos na portaria, mesmo após fechar e reabrir o programa.

### US11 Consolidar sem duplicidade
**Como** supervisor, **quero** consolidar as operações de todas as portarias sem duplicidade, **para** ter uma visão única.

- **Dado** logs de portarias em `dados/rede/`, **quando** a central é executada, **então** cada operação é aplicada no consolidado e seu id registrado em `operacoes-aplicadas.csv`.
- **Dado** que a central já processou um log, **quando** é executada de novo com o mesmo log, **então** nada é duplicado nem alterado.
- **Dado** uma portaria sem log, **quando** a central percorre P01 a P10, **então** a portaria é ignorada sem erro.

## Sprint 3: relatórios e qualidade

### US12 Mapa de ocupação da estante
**Como** porteiro, **quero** ver o mapa de ocupação da estante, **para** saber se há espaço.

- **Dado** a matriz da estante, **quando** o porteiro abre o mapa, **então** vê cada estante e prateleira marcada como livre ou ocupada.
- **Dado** o mapa exibido, **quando** o porteiro olha o resumo, **então** vê o percentual de ocupação (ocupadas ÷ total × 100).

### US13 Alerta de volumes parados há mais de 7 dias
**Como** supervisor, **quero** alertas de volumes parados há mais de 7 dias, **para** cobrar a retirada.

- **Dado** encomendas PENDENTES, **quando** o relatório de pendências antigas é gerado, **então** aparecem as que passaram de `DIAS_ALERTA` (7) dias desde o recebimento.
- **Dado** nenhuma pendência antiga, **quando** o relatório é gerado, **então** o sistema informa que não há alertas.

### US14 Relatórios de pico e ocupação
**Como** supervisor, **quero** relatórios de pico e ocupação por condomínio, **para** dimensionar a equipe.

- **Dado** encomendas de um mês, **quando** o relatório é gerado, **então** mostra a contagem por dia do mês e identifica o dia de pico.
- **Dado** o consolidado da central, **quando** o relatório é gerado, **então** mostra os dados por portaria.

### US15 Testes automatizados
**Como** equipe, **queremos** testes automatizados das funções principais, **para** alterar o código com segurança.

- **Dado** o código compilado, **quando** `make test` é executado, **então** `test_estante`, `test_codigo`, `test_util` e `test_consolidacao` rodam e passam.
- **Dado** uma falha de asserção, **quando** `make test` é executado, **então** o comando termina com erro e indica o teste que falhou.

### US16 (Opcional) Marcar volume como devolvido
**Como** porteiro, **quero** marcar um volume como devolvido após o prazo, **para** liberar espaço.

- **Dado** uma encomenda PENDENTE além do prazo, **quando** o porteiro marca como devolvida, **então** o status passa a DEVOLVIDA, a posição é liberada e a operação DEVOLUCAO entra na fila.
- **Dado** uma encomenda já RETIRADA ou DEVOLVIDA, **quando** o porteiro tenta devolver, **então** o sistema recusa.

> Só entra na Sprint 3 se sobrar tempo. O prazo exato da devolução ainda não está definido no plano: **a confirmar com o grupo**.
