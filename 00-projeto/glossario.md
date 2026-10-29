# Glossário

Os mesmos nomes valem no texto, no código C e no banco de dados (`PLANO.md`, seção 8.7).

| Termo | Significado | No C | No banco |
|---|---|---|---|
| Encomenda | Volume recebido na portaria para uma unidade | `Encomenda` | `encomenda` |
| Unidade | Apartamento (bloco + número) | campos `bloco` e `apartamento` | `unidade` |
| Morador | Pessoa cadastrada em uma unidade | `Morador` | `morador` |
| Destinatário | Nome que consta na etiqueta | `destinatario` | `destinatario` |
| Portaria | Nó local de operação, identificado de P01 a P10 | `id_portaria` | `portaria` |
| Central | Servidor da administradora que consolida os dados | executável `central` | — |
| Estante, prateleira e posição | Matriz física de armazenamento; posição = estante + prateleira | `estante[][]` | `posicao_estante` |
| Código de retirada | 6 dígitos, uso único | `codigo` | `codigo_retirada_hash` |
| Retirada | Entrega ao morador mediante o código | módulo `retirada` | `retirada` |
| Aviso | Comunicação da chegada ao morador | módulo `aviso` | `aviso` |
| Canal de aviso | APP, SMS ou INTERFONE (com código impresso) | `CanalAviso` | `canal_aviso` |
| Operação | Evento da portaria a sincronizar: REGISTRO, RETIRADA ou DEVOLUCAO | `Operacao` | `operacao_sincronizacao` |
| Fila de sincronização | Operações ainda não enviadas à central | módulo `sincronizacao` | — |
| Consolidação | Aplicação das operações na central, sem duplicar | módulo `consolidacao` | — |
| Status | PENDENTE, RETIRADA ou DEVOLVIDA | `StatusEncomenda` | `status` |
