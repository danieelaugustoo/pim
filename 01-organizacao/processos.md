# Processos de negócio: encomendas (Etapa 1)

> Roteiro de tópicos para o capítulo 2. Os diagramas estão em `diagramas/` (Mermaid) e são exportados em PNG para `documento-final/figuras/`.

## 1. Processo atual

Diagrama: [`diagramas/processo-atual.mmd`](diagramas/processo-atual.mmd).

| Passo | Atividade | Responsável | Problema associado |
|---|---|---|---|
| 1 | O entregador chega à portaria | Entregador | — |
| 2 | Anota no caderno data, nome, bloco/apartamento e transportadora | Porteiro | P2, P3 |
| 3 | O pacote vai para uma sala ou armário, sem posição definida | Porteiro | P1, P5 |
| 4 | O morador é avisado pelo interfone, quando o porteiro consegue | Porteiro | P4 |
| 5 | O morador retira e, nem sempre, assina o caderno | Morador | P1, P2 |
| 6 | Extravios e reclamações chegam à sede por telefone ou WhatsApp | Morador, síndico, atendimento | P6 |

## 2. Processo proposto

Diagrama: [`diagramas/processo-proposto.mmd`](diagramas/processo-proposto.mmd).

Fluxo: **registrar → alocar posição → gerar código → avisar → retirar com código → sincronizar → relatórios**.

| Passo | Atividade | Responsável | Requisito |
|---|---|---|---|
| 1 | Registrar a encomenda (unidade, destinatário, transportadora, tamanho) | Porteiro | RF01 |
| 2 | O sistema indica uma posição livre na estante | Sistema | RF02 |
| 3 | O sistema gera o código de retirada de 6 dígitos | Sistema | RF03 |
| 4 | O morador é avisado pelo canal cadastrado (app, SMS ou interfone com código impresso) | Sistema, porteiro | RF04 |
| 5 | O morador retira informando o código; o sistema registra data, hora e quem retirou | Porteiro, morador | RF05 |
| 6 | A operação entra na fila e é enviada à central quando houver conexão | Sistema | RF09, RF10 |
| 7 | A central consolida sem duplicar e gera relatórios | Central, supervisor | RF10, RF12 |

## 3. Comparação atual × proposto

| Aspecto | Atual (caderno) | Proposto |
|---|---|---|
| Registro | Texto livre, sem padrão | Campos obrigatórios e validados |
| Localização do volume | Sem posição definida | Posição na estante indicada pelo sistema |
| Identificação na retirada | Assinatura, nem sempre | Código de uso único |
| Aviso ao morador | Interfone, quando possível | Canal cadastrado, com alternativa para quem não usa smartphone |
| Rastreabilidade | Depende do caderno | Registro com data, hora e autor |
| Funcionamento sem internet | Não depende de internet | Mantido: a portaria opera offline e sincroniza depois |
| Visão da sede | Telefone e WhatsApp | Consolidação e relatórios dos 10 condomínios |
