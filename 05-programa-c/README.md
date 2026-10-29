# 05-programa-c

**O que guarda:** o protótipo em C99: o executável `portaria` (nó local de cada portaria) e o executável `central` (consolidador), com Makefile, `build.bat`, testes, dados de exemplo e a documentação dos algoritmos.

**Exigências do manual que atende (Etapa 5):** algoritmos, fluxogramas, pseudocódigo, implementação em C, estruturas condicionais, estruturas de repetição, funções, vetores e matrizes e manipulação de arquivos.

## Como compilar, testar e executar

Sempre a partir desta pasta. Requer `gcc` (MinGW-w64 no Windows) no PATH.

| Comando | O que faz |
|---|---|
| `make` | compila `bin/portaria` com `gcc -std=c99 -Wall -Wextra -pedantic` |
| `make test` | compila e roda os testes |
| `make clean` | apaga executáveis e objetos de `bin/` |
| `.\build.bat` | compila no Windows sem make |
| `.\build.bat test` | compila e roda os testes no Windows sem make |
| `bin/portaria 1` | abre a portaria P01 (no Windows, `bin\portaria.exe 1`) |

O executável `central` entra na Sprint 2.

### Primeira execução com dados de exemplo

O programa guarda os dados em `dados/portarias/` (pasta ignorada pelo Git). Para começar com os dados fictícios de demonstração, copie o exemplo antes de abrir a portaria 1:

```
copy dados\exemplo\P01-encomendas.csv dados\portarias\P01-encomendas.csv
bin\portaria.exe 1
```

Sem copiar nada, o programa cria o arquivo vazio na primeira execução.

## Situação (Sprint 1: US01 a US06)

| Menu | Opção | Situação |
|---|---|---|
| 1 | Registrar encomenda | Pronta (US01, US02, US03) |
| 2 | Registrar retirada | Pronta (US04) |
| 3 | Listar pendentes | Pronta (US05) |
| 4 | Buscar por unidade | Pronta (US05) |
| 5 | Mapa da estante | Sprint 3 |
| 6 | Moradores | Sprint 2 |
| 7 | Relatórios | Sprint 3 |
| 8 | Sincronizar com a central | Sprint 2 |
| 9 | Alternar online/offline | Sprint 2 |

Os dados ficam em `dados/portarias/Pnn-encomendas.csv` (US06). A matriz da estante não tem arquivo próprio: é reconstruída a partir das encomendas pendentes ao abrir o programa.

## O que cada arquivo faz

| Arquivo | Função |
|---|---|
| `include/tipos.h` | constantes, enums e structs compartilhados |
| `src/util.c` | leitura segura do teclado, conversão validada, datas e separação de campos CSV |
| `src/estante.c` | matriz de posições: alocar (A1), liberar, reconstruir, ocupação |
| `src/codigo.c` | código de retirada de 6 dígitos, único entre as pendentes (A2) |
| `src/encomenda.c` | criar, registrar, listar e buscar encomendas |
| `src/retirada.c` | retirada com conferência do código e até 3 tentativas (A3) |
| `src/persistencia.c` | leitura e gravação do CSV de encomendas |
| `src/portaria.c` | `main` e menu (só menu e chamadas) |
| `tests/test_*.c` | testes com `assert.h`: util, estante, código, encomenda/retirada e persistência |
| `dados/exemplo/P01-encomendas.csv` | dados fictícios de demonstração |

## Limitações desta sprint

- O código de retirada é gravado em texto no CSV (no banco central seria hash; ver `PLANO.md`, seção 9.8).
- A operação de retirada e de registro ainda não entra na fila de sincronização (Sprint 2).
- O arquivo de encomendas é reescrito por inteiro a cada alteração; se o programa for fechado à força durante a gravação, o arquivo pode ficar incompleto.
- Prateleiras são numeradas a partir de 0, como as constantes do `PLANO.md` (volumes G ficam nas prateleiras 10 e 11).
- Pseudocódigo e fluxogramas de A1 a A3 ainda não foram escritos (previstos para a Sprint 3).
