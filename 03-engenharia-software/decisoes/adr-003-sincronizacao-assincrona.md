# ADR-003: Sincronização assíncrona com fila de operações idempotentes

**Status:** aceita

## Contexto

Parte das portarias tem internet instável (P7). A portaria não pode parar quando a conexão cai (RNF01), e a central precisa receber as operações sem duplicá-las (RF10), mesmo que o envio seja repetido.

## Decisão

Cada evento da portaria (REGISTRO, RETIRADA, DEVOLUCAO) vira uma **operação** com id único (ex.: `P01-000123`) e entra numa **fila**. O envio à central é **assíncrono** e a aplicação na central é **idempotente**: se o id já foi aplicado, a operação é ignorada.

## Alternativas consideradas

| Alternativa | Avaliação |
|---|---|
| Sincronização síncrona (a portaria só opera online) | Viola RNF01 e P7 |
| Substituir os dados da central pelos da portaria a cada envio | Perde histórico e gera conflito se duas fontes divergirem |
| Reenvio sem id de operação | Reenvios duplicariam registros |

## Justificativa

- Consistência eventual: a central converge para o estado das portarias quando as operações chegam.
- Id único por operação garante que reenviar não duplica.
- A ordem é garantida dentro de cada portaria pelo número de sequência (`Pnn-sequencia.txt`).
- A queda da internet ou da nuvem não para a portaria.

## Consequências

- Módulos `sincronizacao` (portaria) e `consolidacao` (central); algoritmos A4 e A5.
- No banco, `operacao_sincronizacao` tem chave primária no id da operação.
- Teste obrigatório: processar o mesmo log duas vezes não duplica nada (`test_consolidacao.c`).
- Não há resolução de conflitos entre portarias porque cada encomenda pertence a uma só portaria.
