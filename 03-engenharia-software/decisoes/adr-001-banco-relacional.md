# ADR-001: Banco relacional (MySQL 8) no servidor central

**Status:** aceita

## Contexto

O servidor central consolida encomendas, retiradas e operações de 10 portarias. As entidades (condomínio, bloco, unidade, morador, portaria, posição, encomenda, retirada, aviso) são estáveis e muito relacionadas. Há regras que o próprio banco deve garantir.

## Decisão

Usar um banco **relacional** (MySQL 8) no servidor central. NoSQL fica apenas discutido, em `04-banco-de-dados/nosql/`.

## Alternativas consideradas

| Alternativa | Avaliação |
|---|---|
| Banco de documentos (ex.: MongoDB) | Flexível, mas as relações e restrições do domínio ficariam na aplicação. Faz sentido só para o histórico de avisos, cujos campos variam conforme o canal |
| Chave-valor (ex.: Redis) | Adequado a cache e consultas por chave; fraco para consultas de relatório e integridade entre entidades |
| Continuar só com arquivos | Serve ao protótipo (ADR-002), mas não oferece integridade nem consultas para a visão consolidada |

## Justificativa

- Uma encomenda tem no máximo uma retirada: `UNIQUE (id_encomenda)` na tabela `retirada`.
- Cada operação sincronizada é aplicada uma única vez: chave primária em `operacao_sincronizacao` (base da idempotência do ADR-003).
- Integridade entre unidade, encomenda e posição por chaves estrangeiras.
- Os relatórios (pendências, pico, ocupação) são consultas relacionais.

## Consequências

- Modelagem completa em `04-banco-de-dados/` (conceitual, lógico, normalização, físico).
- O protótipo em C não se liga ao MySQL; o banco é testado com scripts SQL à parte.
- Um banco de documentos pode ser reavaliado como evolução, para o histórico de avisos.
