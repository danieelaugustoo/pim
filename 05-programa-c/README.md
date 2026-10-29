# 05-programa-c

**O que guarda:** o protótipo em C99: o executável `portaria` (nó local de cada portaria) e o executável `central` (consolidador), com Makefile, `build.bat`, testes, dados de exemplo e a documentação dos algoritmos.

**Exigências do manual que atende (Etapa 5):** algoritmos, fluxogramas, pseudocódigo, implementação em C, estruturas condicionais, estruturas de repetição, funções, vetores e matrizes e manipulação de arquivos.

## Como compilar, testar e executar

Sempre a partir desta pasta:

| Comando | O que faz |
|---|---|
| `make` | compila `bin/portaria` e `bin/central` com `gcc -std=c99 -Wall -Wextra -pedantic` |
| `make test` | compila e roda os testes |
| `make clean` | apaga executáveis e objetos |
| `build.bat` | compila no Windows sem make (MinGW-w64) |
| `bin/portaria 1` | abre a portaria P01 (no Windows, `bin\portaria.exe 1`) |
| `bin/central` | consolida as operações e gera o relatório |

**Situação:** o código ainda não foi escrito (Sprint 1 em diante). O `Makefile` e o `build.bat` serão criados junto com ele.
