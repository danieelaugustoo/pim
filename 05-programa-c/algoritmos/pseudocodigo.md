# Algoritmos em pseudocódigo (Etapa 5)

> Roteiro para o capítulo 6, que o grupo redige. Cada algoritmo tem pseudocódigo aqui, fluxograma em `fluxogramas/` e a indicação de onde está no código.

## Situação

| ID | Algoritmo | Pseudocódigo | Fluxograma | Código |
|---|---|---|---|---|
| A1 | Alocar posição na estante (matriz) | **Pronto** | [`A1.mmd`](fluxogramas/A1.mmd) | `estante_alocar_posicao` |
| A2 | Gerar código único | **Pronto** | [`A2.mmd`](fluxogramas/A2.mmd) | `codigo_gerar_unico` |
| A3 | Registrar retirada | **Pronto** | [`A3.mmd`](fluxogramas/A3.mmd) | `retirada_registrar` |
| A4 | Sincronizar (portaria) | **Pronto** | [`A4.mmd`](fluxogramas/A4.mmd) | `sincronizacao_enviar_pendentes` |
| A5 | Consolidar (central, idempotente) | **Pronto** | [`A5.mmd`](fluxogramas/A5.mmd) | `consolidacao_processar_portaria` |
| A6 | Relatórios | **Pronto** | [`A6.mmd`](fluxogramas/A6.mmd) | `relatorio_*` em `src/relatorio.c` |

Os fluxogramas estão em Mermaid e foram renderizados em PNG em 2026-10-31 (`fluxogramas/A1.png` a `A6.png`; A1 e A5 também em `documento-final/figuras/`). O grupo confere o resultado visualmente.

---

## A1. Alocar posição na estante (matriz)

**Objetivo.** Indicar onde guardar um volume recém-chegado, usando a matriz `estante[NUM_ESTANTES][NUM_PRATELEIRAS]` (RF03, US02).

**Entradas.** A matriz, o bloco da unidade, o tamanho do volume (P, M ou G) e o id da encomenda.

**Saídas.** Posição (estante, prateleira) já marcada como ocupada na matriz; ou "sem vaga".

```
ALGORITMO A1 - Alocar posicao na estante
INICIO
    SE bloco e uma letra ENTAO
        preferida <- (posicao da letra no alfabeto, A = 0) MOD NUM_ESTANTES
    SENAO
        preferida <- 0
    FIM SE
    SE tamanho = 'G' ENTAO
        faixa <- prateleiras de PRATELEIRA_INICIAL_G ate NUM_PRATELEIRAS - 1
    SENAO
        faixa <- prateleiras de 0 ate PRATELEIRA_INICIAL_G - 1
    FIM SE
    PARA k DE 0 ATE NUM_ESTANTES - 1 FACA
        candidata <- (preferida + k) MOD NUM_ESTANTES       // percurso circular
        PARA CADA prateleira da faixa, da menor para a maior FACA
            SE estante[candidata][prateleira] = 0 ENTAO       // 0 = livre
                estante[candidata][prateleira] <- id_encomenda
                RETORNAR a posicao (candidata, prateleira)
            FIM SE
        FIM PARA
    FIM PARA
    RETORNAR "sem vaga"
FIM
```

**Pontos para explicar na apresentação.**
- A matriz guarda o **id da encomenda** em cada célula; `0` significa livre. Assim o mapa da estante (A6) mostra livre/ocupada e o sistema ainda sabe quem está em cada lugar.
- O bloco define a estante preferida, e a busca continua nas outras estantes em ordem circular quando ela está cheia. Volumes G só usam as prateleiras reservadas.
- A matriz não é gravada em arquivo: ao abrir o programa, `estante_reconstruir` a remonta a partir das encomendas pendentes (uma única fonte de verdade).
- Custo: no máximo `NUM_ESTANTES × NUM_PRATELEIRAS` comparações (48 no protótipo).

**Onde está no código.** `estante_alocar_posicao` em `src/estante.c`.

**Testes.** `tests/test_estante.c`: estante do bloco, blocos além de D, volumes G na faixa reservada, transbordo para a estante seguinte, estante cheia, liberação e reconstrução.

---

## A2. Gerar código único

**Objetivo.** Criar o código de retirada de 6 dígitos de uma nova encomenda, que não repita o de nenhuma encomenda pendente (RF04, US03).

**Entradas.** O vetor de encomendas.

**Saídas.** Um código de `CODIGO_MIN` (100000) a `CODIGO_MAX` (999999); ou 0 se não conseguir.

```
ALGORITMO A2 - Gerar codigo unico
INICIO
    PARA tentativa DE 1 ATE LIMITE_DE_SORTEIOS FACA        // LIMITE = 1000
        codigo <- sortear um numero de CODIGO_MIN a CODIGO_MAX
        SE nenhuma encomenda PENDENTE tem esse codigo ENTAO
            RETORNAR codigo
        FIM SE
    FIM PARA
    RETORNAR 0                                              // o chamador recusa o registro
FIM
```

**Pontos para explicar na apresentação.**
- A unicidade vale entre as encomendas **pendentes**: o código de uma encomenda já retirada pode ser reutilizado, e o espaço de 900 000 códigos continua folgado.
- O limite de sorteios garante que o programa nunca trava num laço infinito.
- `rand()` pode entregar só 15 bits em alguns compiladores; por isso o sorteio combina duas chamadas para cobrir os 900 000 valores.
- O código é número sorteado, não derivado de dados do morador. No protótipo ele fica em texto no arquivo (limitação registrada); no sistema completo, o banco guarda só o hash (ver `04-banco-de-dados/`).

**Onde está no código.** `codigo_gerar_unico` (com `codigo_existe_pendente`) em `src/codigo.c`.

**Testes.** `tests/test_codigo.c`: faixa de 6 dígitos, unicidade entre pendentes, reutilização de código de encomenda retirada, conferência do código.

---

## A3. Registrar retirada

**Objetivo.** Entregar o volume somente a quem informa o código correto, registrando quem retirou e quando, e liberando a posição na estante (RF05, US04, US05).

**Entradas.** Unidade, id da encomenda, código digitado (até `MAX_TENTATIVAS` = 3 vezes) e nome de quem retira.

**Saídas.** Encomenda RETIRADA com data, hora e nome, e posição liberada; ou retirada negada, com a encomenda ainda PENDENTE.

```
ALGORITMO A3 - Registrar retirada
INICIO
    ler a unidade (bloco e apartamento)
    SE a unidade nao tem encomenda pendente ENTAO
        ENCERRAR                                       // nada a retirar
    FIM SE
    listar as pendentes da unidade
    ler o id da encomenda
    SE o id nao e uma pendente DESSA unidade ENTAO
        informar e ENCERRAR
    FIM SE
    PARA tentativa DE 1 ATE MAX_TENTATIVAS FACA
        ler o codigo digitado
        SE codigo digitado = codigo da encomenda ENTAO
            ir para CONFIRMADO
        FIM SE
        informar "codigo incorreto (tentativa de MAX_TENTATIVAS)"
    FIM PARA
    informar "retirada negada"                          // a encomenda continua PENDENTE
    ENCERRAR
    CONFIRMADO:
        ler o nome de quem retira
        status <- RETIRADA
        retirada_em <- data e hora atuais
        retirado_por <- nome
        liberar a posicao da encomenda na matriz         // estante[linha][coluna] <- 0
        enfileirar a operacao RETIRADA (feito pela portaria)
FIM
```

**Pontos para explicar na apresentação.**
- A conferência do código é o que impede a entrega ao morador errado (o problema do caderno). Três erros negam a retirada; o morador pode tentar de novo depois.
- O id só vale se a encomenda é **pendente e da unidade informada**: ninguém retira o volume de outra unidade digitando o id dele.
- A função separa a parte interativa (`retirada_registrar`) da regra (`retirada_efetuar`), o que permite testar a regra sem teclado.
- A fila de sincronização só recebe a operação depois de a retirada ser aplicada, e o arquivo de encomendas é salvo antes (A4 cuida do envio).

**Onde está no código.** `retirada_registrar` e `retirada_efetuar` em `src/retirada.c`; chamada na opção 2 de `src/portaria.c`.

**Testes.** `tests/test_encomenda.c` cobre a regra (`retirada_efetuar`: status, data, nome, posição liberada, recusa de encomenda que não está pendente) e `tests/test_codigo.c` cobre a conferência do código. A parte interativa (três tentativas, id de outra unidade) não tem teste automatizado, porque lê o teclado; foi conferida em execução manual: o id de outra unidade foi recusado e, após três códigos errados, a retirada foi negada e a encomenda continuou pendente.

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

---

## A6. Relatórios

**Objetivo.** Transformar os registros em informação para o porteiro e o supervisor: mapa da estante, pendências antigas, pico de entrada por dia e consolidado por portaria (RF07, RF11, RF12, US12, US13, US14).

**Entradas.** A matriz da estante, o vetor de encomendas da portaria (ou o consolidado da central) e a data e hora atuais.

**Saídas.** Os relatórios na tela (portaria) e `dados/central/relatorio-consolidado.txt` (central).

```
ALGORITMO A6.1 - Mapa da estante e ocupacao
INICIO
    PARA CADA estante (linha) FACA
        PARA CADA prateleira (coluna) FACA
            SE estante[linha][coluna] <> 0 ENTAO mostrar "X" SENAO mostrar "."
        FIM PARA
    FIM PARA
    ocupadas <- numero de celulas diferentes de 0
    percentual <- ocupadas / (NUM_ESTANTES * NUM_PRATELEIRAS) * 100
    mostrar ocupadas, total e percentual
FIM

ALGORITMO A6.2 - Pendencias antigas
INICIO
    total <- 0
    PARA CADA encomenda FACA
        SE status = PENDENTE E (dias entre recebida_em e agora) > DIAS_ALERTA ENTAO
            mostrar unidade, destinatario, data e dias parados
            total <- total + 1
        FIM SE
    FIM PARA
    SE total = 0 ENTAO mostrar "nao ha alertas" FIM SE
FIM

ALGORITMO A6.3 - Pico de encomendas por dia
INICIO
    contagem[1..31] <- 0
    PARA CADA encomenda FACA
        SE ano e mes de recebida_em = periodo pedido ENTAO
            contagem[dia] <- contagem[dia] + 1
        FIM SE
    FIM PARA
    pico <- 0
    PARA dia DE 1 ATE 31 FACA
        SE contagem[dia] > contagem[pico] ENTAO pico <- dia      // empate: vence o dia mais cedo
    FIM PARA
    SE pico = 0 ENTAO mostrar "nenhum registro" SENAO mostrar contagem por dia e o pico FIM SE
FIM

ALGORITMO A6.4 - Relatorio consolidado (central)
INICIO
    PARA p DE 1 ATE MAX_PORTARIAS FACA
        contar as encomendas consolidadas da portaria p por status
        antigas <- pendentes de p com mais de DIAS_ALERTA dias
        pico <- data com mais registros de p
        SE p tem encomendas ENTAO escrever a linha de p FIM SE
    FIM PARA
    escrever os totais
FIM
```

**Pontos para explicar na apresentação.**
- **Dias parados** contam dias do calendário (`util_dias_entre`), sem considerar a hora. "Mais de 7 dias" significa 8 ou mais: uma encomenda com exatamente 7 dias ainda não alerta (conforme US13).
- **Só pendentes alertam.** Encomenda retirada ou devolvida nunca entra em "pendências antigas", por mais antiga que seja.
- **Cálculo separado da impressão.** As funções que contam (`relatorio_contar_por_dia`, `relatorio_dia_pico`, `relatorio_pendencia_antiga`) recebem a data como texto e não imprimem nada, então os testes usam datas fixas e não dependem do relógio.
- **Empate no pico** vai para o dia mais cedo, para o resultado ser sempre o mesmo.
- O relatório por mês usa a data de **recebimento**, não a de retirada, porque o objetivo é dimensionar a equipe pela entrada de volumes.
- No sistema completo, os mesmos relatórios viram consultas SQL (ver `04-banco-de-dados/sql/03-consultas.sql`).

**Onde está no código.** `src/relatorio.c`: `relatorio_mapa_estante`, `relatorio_pendencias_antigas`, `relatorio_pico_mensal`, `relatorio_menu` (opção 7 do menu) e as funções da central usadas por `consolidacao_gerar_relatorio` (`src/consolidacao.c`). O mapa é a opção 5 do menu.

**Testes.** `tests/test_relatorio.c`: percentual de ocupação; pendência com 8 dias alerta, com 7 não, retirada e devolvida não alertam, data inválida não alerta; contagem por dia, outro mês e outro ano ignorados, empate no pico, mês vazio; consolidado por portaria (antigas e dia de pico).
