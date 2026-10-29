# Definição de pronto (DoD)

Uma história só vai para a coluna **Pronto** quando todos os itens abaixo forem verdadeiros.

## Código

- [ ] Compila sem warnings com `gcc -std=c99 -Wall -Wextra -pedantic`.
- [ ] Todos os testes passam (`make test`).
- [ ] Só biblioteca padrão (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `time.h`, `assert.h`).
- [ ] Entrada do teclado com `fgets` e conversão validada; nenhum `scanf("%s")`.
- [ ] Textos do programa e dos arquivos de dados em ASCII, sem acento.
- [ ] Funções com prefixo do módulo e comentário em português com objetivo, parâmetros, retorno e lógica.

## Documentação

- [ ] Algoritmos principais com pseudocódigo e fluxograma.
- [ ] Critérios de aceitação da história atendidos (ver `backlog.md`).
- [ ] `00-projeto/rastreabilidade.md` atualizada.
- [ ] `sprints/sprint-NN.md` da sprint atual atualizada.

## Processo

- [ ] Revisado por outro integrante antes do merge na `main`.
- [ ] Commit no formato `tipo(escopo): descricao (USxx)`.
- [ ] A `main` continua compilando.

> Itens de código não se aplicam a histórias só de documentação (Sprint 0); os de documentação e de processo continuam valendo.
