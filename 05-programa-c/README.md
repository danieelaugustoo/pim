# 05-programa-c

**O que guarda:** o protótipo em C99: o executável `portaria` (nó local de cada portaria) e o executável `central` (consolidador), com Makefile, `build.bat`, testes, dados de exemplo e a documentação dos algoritmos.

**Exigências do manual que atende (Etapa 5):** algoritmos, fluxogramas, pseudocódigo, implementação em C, estruturas condicionais, estruturas de repetição, funções, vetores e matrizes e manipulação de arquivos.

## Como compilar, testar e executar

Sempre a partir desta pasta. Requer `gcc` (MinGW-w64 no Windows) no PATH.

| Comando | O que faz |
|---|---|
| `make` | compila `bin/portaria` e `bin/central` com `gcc -std=c99 -Wall -Wextra -pedantic` |
| `make test` | compila e roda os testes |
| `make clean` | apaga executáveis e objetos de `bin/` |
| `.\build.bat` | compila no Windows sem make |
| `.\build.bat test` | compila e roda os testes no Windows sem make |
| `bin/portaria 1` | abre a portaria P01 (no Windows, `bin\portaria.exe 1`) |
| `bin/central` | consolida os logs de `dados/rede/` e gera o relatório (no Windows, `bin\central.exe`) |

### Demonstração com os dados de exemplo

O programa guarda os dados em `dados/portarias/`, `dados/rede/` e `dados/central/` (pastas ignoradas pelo Git). Para começar com os dados fictícios, no Windows:

```
copy dados\exemplo\P01-encomendas.csv dados\portarias\
copy dados\exemplo\P01-moradores.csv dados\portarias\
copy dados\exemplo\P01-sequencia.txt dados\portarias\
copy dados\exemplo\P01.log dados\rede\
copy dados\exemplo\P02.log dados\rede\
bin\central.exe
bin\portaria.exe 1
```

1. A `central` consolida os dois logs. Rode-a de novo: nada muda, tudo aparece como "já aplicada".
2. Na portaria, use `9` para ficar OFFLINE, registre encomendas (`1`), veja a fila crescer com `8` (informa quantas aguardam), volte a ONLINE com `9` e sincronize com `8`.
3. Rode a `central` outra vez: só as operações novas são aplicadas.

**Importante:** copie o `P01-sequencia.txt` junto com o `P01.log`. A sequência diz qual foi a última operação já enviada (10, no exemplo). Sem ela, a portaria recomeçaria em `P01-000001`, e a central ignoraria as operações novas por já ter aplicado esses ids.

Sem copiar nada, o programa cria os arquivos vazios na primeira execução.

## Situação (Sprints 1 e 2: US01 a US11)

| Menu | Opção | Situação |
|---|---|---|
| 1 | Registrar encomenda | Pronta (US01, US02, US03; guarda a operação na fila e avisa o morador) |
| 2 | Registrar retirada | Pronta (US04; guarda a operação na fila) |
| 3 | Listar pendentes | Pronta (US05) |
| 4 | Buscar por unidade | Pronta (US05) |
| 5 | Mapa da estante | Sprint 3 |
| 6 | Moradores | Pronta (US07: cadastrar e listar, com canal de aviso) |
| 7 | Relatórios | Sprint 3 |
| 8 | Sincronizar com a central | Pronta (US10) |
| 9 | Alternar online/offline | Pronta (US09, simulação) |

O executável `central` consolida sem duplicar (US11).

## Arquivos de dados

| Arquivo | Conteúdo |
|---|---|
| `dados/portarias/Pnn-encomendas.csv` | encomendas da portaria (US06) |
| `dados/portarias/Pnn-moradores.csv` | moradores e canal de aviso |
| `dados/portarias/Pnn-fila.csv` | operações que ainda não foram enviadas |
| `dados/portarias/Pnn-sequencia.txt` | último número de operação usado |
| `dados/portarias/Pnn-avisos.txt` | registro legível dos avisos simulados (sem o código de retirada) |
| `dados/rede/Pnn.log` | operações "transmitidas" pela portaria |
| `dados/central/operacoes-aplicadas.csv` | ids das operações já aplicadas |
| `dados/central/encomendas-consolidadas.csv` | encomendas como a central as conhece |
| `dados/central/relatorio-consolidado.txt` | relatório por portaria |

Nos arquivos de operação, `id_portaria` é numérico (P01 = 1). A matriz da estante não tem arquivo próprio: é reconstruída a partir das encomendas pendentes ao abrir o programa.

## O que cada arquivo faz

| Arquivo | Função |
|---|---|
| `include/tipos.h` | constantes, enums e structs compartilhados |
| `src/util.c` | leitura segura do teclado, conversão validada, datas e separação de campos CSV |
| `src/estante.c` | matriz de posições: alocar (A1), liberar, reconstruir, ocupação |
| `src/codigo.c` | código de retirada de 6 dígitos, único entre as pendentes (A2) |
| `src/encomenda.c` | criar, registrar, listar e buscar encomendas |
| `src/retirada.c` | retirada com conferência do código e até 3 tentativas (A3) |
| `src/morador.c` | cadastro de moradores, validação do contato por canal e escolha de quem avisar |
| `src/aviso.c` | aviso simulado por canal (APP, SMS, INTERFONE) e registro em arquivo |
| `src/sincronizacao.c` | fila de operações, numeração `Pnn-NNNNNN` e envio para a rede (A4) |
| `src/consolidacao.c` | aplicação idempotente das operações na central (A5) e relatório |
| `src/persistencia.c` | leitura e gravação dos CSV de encomendas e moradores |
| `src/portaria.c` | `main` e menu da portaria (só menu e chamadas) |
| `src/central.c` | `main` da central |
| `tests/test_*.c` | testes com `assert.h`: util, estante, código, encomenda/retirada, persistência, morador, sincronização e consolidação |
| `algoritmos/` | pseudocódigo e fluxogramas (A4 e A5 prontos; ver `algoritmos/pseudocodigo.md`) |
| `dados/exemplo/` | dados fictícios de demonstração |

## Limitações

- A rede é simulada por arquivos; o aviso é simulado (nada é enviado de verdade).
- O código de retirada é gravado em texto no CSV de encomendas (no banco central seria hash; ver `PLANO.md`, seção 9.8). O arquivo de avisos não o grava.
- Os arquivos são reescritos por inteiro a cada alteração; se o programa for fechado à força durante a gravação, um arquivo pode ficar incompleto.
- O número da próxima operação vem de `Pnn-sequencia.txt`. Apagar esse arquivo sem apagar o log da rede faz a portaria repetir ids de operações já aplicadas, e a central as ignora. Se o arquivo estiver corrompido, o programa recusa registrar a operação em vez de recomeçar a numeração.
- A central guarda até 20 000 operações aplicadas e 5 000 encomendas (constantes em `tipos.h`) e procura ids por busca sequencial.
- Não há resolução de conflito entre portarias, porque cada encomenda pertence a uma só portaria.
- Prateleiras são numeradas a partir de 0, como as constantes do `PLANO.md` (volumes G ficam nas prateleiras 10 e 11).
- Pseudocódigo e fluxogramas de A1, A2, A3 e A6 ainda não foram escritos (previstos para a Sprint 3).
