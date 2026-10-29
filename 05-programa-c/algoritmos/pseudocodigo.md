# Algoritmos em pseudocódigo (Etapa 5)

> Roteiro para o capítulo 6, que o grupo redige. Cada algoritmo tem pseudocódigo aqui, fluxograma em `fluxogramas/` e a indicação de onde está no código.

## Situação

| ID | Algoritmo | Pseudocódigo | Fluxograma | Código |
|---|---|---|---|---|
| A1 | Alocar posição na estante (matriz) | Pendente (Sprint 3) | Pendente | `estante_alocar_posicao` |
| A2 | Gerar código único | Pendente (Sprint 3) | Pendente | `codigo_gerar_unico` |
| A3 | Registrar retirada | Pendente (Sprint 3) | Pendente | `retirada_registrar` |
| A4 | Sincronizar (portaria) | **Pronto** | [`A4.mmd`](fluxogramas/A4.mmd) | `sincronizacao_enviar_pendentes` |
| A5 | Consolidar (central, idempotente) | **Pronto** | [`A5.mmd`](fluxogramas/A5.mmd) | `consolidacao_processar_portaria` |
| A6 | Relatórios | Pendente (Sprint 3) | Pendente | `relatorio_*` (ainda não implementado) |

---

## A4. Sincronizar (portaria)

**Objetivo.** Enviar à "rede" as operações que a portaria guardou na fila, sem perder nenhuma e sem exigir internet para continuar trabalhando (RF09, RF10, US10, ADR-003).

**Entradas.** Arquivo da fila (`dados/portarias/Pnn-fila.csv`), arquivo do log da rede (`dados/rede/Pnn.log`) e o modo atual (online ou offline).

**Saídas.** Operações copiadas para o log da rede e fila vazia; ou fila intacta, se estiver offline ou se houver falha.

```
ALGORITMO A4 - Sincronizar (portaria)
INICIO
    pendentes <- contar as operacoes da fila
    SE a portaria NAO esta online ENTAO
        informar "N operacoes aguardando envio"
        ENCERRAR                                  // a fila nao muda
    FIM SE
    SE pendentes = 0 ENTAO
        informar "nenhuma operacao pendente"
        ENCERRAR
    FIM SE
    garantir que o log da rede existe (criar com o cabecalho se faltar)
    enviadas <- 0
    PARA CADA linha da fila (depois do cabecalho) FACA
        SE a linha nao esta vazia ENTAO
            copiar a linha para o FINAL do log da rede
            enviadas <- enviadas + 1
        FIM SE
    FIM PARA
    SE a gravacao do log falhou ENTAO
        informar erro
        ENCERRAR                                  // a fila fica preservada
    FIM SE
    esvaziar a fila (deixar so o cabecalho)
    informar "enviadas operacoes enviadas"
FIM
```

**Pontos para explicar na apresentação.**
- A fila é um arquivo, então operações feitas offline sobrevivem ao fechamento do programa.
- A fila só é esvaziada **depois** de o log ser gravado. Se o programa cair entre as duas etapas, o próximo envio repete operações no log. Isso é seguro: a central ignora operações já aplicadas (A5).
- A ordem das operações dentro da portaria é a da sequência (`Pnn-sequencia.txt`), que nunca repete.

**Onde está no código.** `sincronizacao_enviar_pendentes` em `src/sincronizacao.c`; a opção 8 do menu em `src/portaria.c` (`portaria_sincronizar`).

**Testes.** `tests/test_sincronizacao.c`: offline preserva a fila e não cria o log; online copia e esvazia; sem pendências devolve `SINC_VAZIA`; a numeração continua depois do envio.

---

## A5. Consolidar (central, idempotente)

**Objetivo.** Aplicar na central as operações de todas as portarias **uma única vez cada**, mesmo que um log seja lido várias vezes ou que uma operação apareça repetida (RF10, US11, ADR-003).

**Entradas.** Logs `dados/rede/P01.log` a `P10.log` (os que existirem), `dados/central/operacoes-aplicadas.csv` e `dados/central/encomendas-consolidadas.csv`.

**Saídas.** Consolidado atualizado, ids das operações aplicadas registrados e `relatorio-consolidado.txt`.

```
ALGORITMO A5 - Consolidar (central, idempotente)
INICIO
    carregar as operacoes ja aplicadas e as encomendas consolidadas
    PARA p DE 1 ATE MAX_PORTARIAS FACA
        SE existe o log da portaria p ENTAO
            PARA CADA linha do log, NA ORDEM EM QUE ESTA GRAVADA, FACA
                SE a linha esta vazia ou e o cabecalho ENTAO
                    PROXIMA
                SE a linha e invalida OU a operacao e de outra portaria ENTAO
                    contar como invalida
                    PROXIMA
                SE id_operacao ja esta em operacoes-aplicadas ENTAO
                    contar como ja aplicada       // ignora: nada muda
                    PROXIMA
                aceita <- aplicar o efeito da operacao (tabela abaixo)
                SE aceita ENTAO
                    registrar id_operacao como aplicada
                    contar como aplicada
                SENAO
                    contar como rejeitada         // o id NAO e registrado
                FIM SE
            FIM PARA
        FIM SE
    FIM PARA
    salvar as encomendas consolidadas e depois os ids aplicados
    gerar o relatorio consolidado
FIM
```

**Efeito de cada tipo de operação** (função `consolidacao_efeito`):

| Operação | Situação da encomenda na central | Resultado |
|---|---|---|
| REGISTRO | não existe | cria como PENDENTE, com a data da operação |
| REGISTRO | já existe com a mesma data | aceita sem alterar (repetição inofensiva) |
| REGISTRO | já existe com data diferente | rejeita (conflito) |
| RETIRADA | PENDENTE | marca RETIRADA, com a data da operação |
| RETIRADA | RETIRADA com a mesma data | aceita sem alterar |
| RETIRADA | não existe, DEVOLVIDA ou RETIRADA com outra data | rejeita |
| DEVOLUCAO | PENDENTE | marca DEVOLVIDA |
| DEVOLUCAO | DEVOLVIDA | aceita sem alterar |
| DEVOLUCAO | não existe ou RETIRADA | rejeita |

A encomenda é identificada pelo par (portaria, id da encomenda), porque o id só é único dentro da portaria.

**Pontos para explicar na apresentação.**
- **Idempotência pelo id:** processar o mesmo log duas vezes deixa os arquivos idênticos (verificado na execução real e no teste).
- **Operação rejeitada não é registrada como aplicada.** Se uma RETIRADA chegar antes do REGISTRO, ela é rejeitada, mas pode ser aplicada na próxima execução, quando o REGISTRO já tiver chegado.
- **O efeito também é idempotente.** A central grava primeiro as encomendas e depois os ids. Se algo cair entre os dois arquivos, a reexecução reaplica operações cujo efeito já existe, e isso não gera duplicidade.
- **Limitação:** a busca do id aplicado é sequencial, o que basta para o protótipo (até 20 000 operações), mas num sistema grande o banco resolve isso com a chave primária (`operacao_sincronizacao`).

**Onde está no código.** `consolidacao_processar_portaria` e `consolidacao_aplicar_operacao` em `src/consolidacao.c`; o laço de P01 a P10 em `src/central.c`. Versão em SQL: `04-banco-de-dados/sql/03-consultas.sql`, seção 10 (`INSERT IGNORE` + `ROW_COUNT()`).

**Testes.** `tests/test_consolidacao.c`: o mesmo log duas vezes não duplica; vale entre execuções (estado gravado e recarregado); portarias diferentes com o mesmo id de encomenda; linhas inválidas; operação rejeitada aplicada depois; efeito idempotente; relatório.
