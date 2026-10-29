# CLAUDE.md — PIM II: Gestão de Encomendas em Condomínios

## Contexto
Projeto acadêmico do PIM II (curso de ADS da UNIP), feito em grupo. Organização fictícia: Administradora Morada Central, com 10 condomínios residenciais. Problema: as portarias controlam encomendas em caderno, o que gera extravios, entregas erradas e sobrecarga dos porteiros. Solução: um nó em cada portaria que funciona sem internet e um consolidador central da administradora. Tema aprovado pelo professor.

**Leia o `PLANO.md` antes de qualquer tarefa.** Ele define o escopo (seção 5), as decisões de arquitetura (seção 6), a estrutura de pastas (seção 7), as convenções e o glossário (seção 8), o que cada etapa do manual exige (seção 9), as sprints (seção 10) e as exigências do documento final (seção 11).

## Regras
1. Siga a estrutura de pastas e as convenções do `PLANO.md`. Não crie pastas fora dela sem perguntar.
2. Trabalhe em entregas pequenas (uma história ou um grupo pequeno delas). Antes de codar, mostre o plano em poucas linhas; depois implemente, compile, teste e resuma o que mudou.
3. Código C: padrão C99 e apenas a biblioteca padrão (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `time.h`, `assert.h`). Sem C++, `conio.h`, `windows.h` ou bibliotecas externas. Precisa compilar sem warnings com `gcc -std=c99 -Wall -Wextra -pedantic`.
4. Programação estruturada: funções pequenas com o prefixo do módulo; vetores e matrizes estáticos, com tamanhos em constantes de `tipos.h`; `main` só com menu e chamadas.
5. Textos do programa e dos arquivos de dados em ASCII, sem acento.
6. Entrada do teclado com `fgets` e conversão validada. Nunca `scanf("%s")`.
7. Toda função tem comentário em português com objetivo, parâmetros, retorno e lógica. O grupo precisa explicar o código na apresentação.
8. Nunca invente referências, autores, estatísticas ou dados. Onde faltar fonte, escreva `[FONTE A VERIFICAR]`.
9. Os capítulos do trabalho (`documento-final/capitulos/`) são redigidos pelo grupo, porque o manual exige texto autoral. Você pode criar roteiros de tópicos, revisar e sugerir, mas não redige o texto final.
10. Dados de exemplo são sempre fictícios.
11. Quando alguém do grupo disser que quer aprender ou fazer uma parte sozinho, explique o conceito e dê pistas antes de entregar código pronto.
12. Ao concluir uma tarefa, atualize `00-projeto/rastreabilidade.md` e a `sprint-NN.md` da sprint atual.
13. Se algo no plano estiver ambíguo ou conflitar com o manual do PIM, pare e pergunte.

## Comandos (rodar dentro de `05-programa-c/`)
- `make`: compila `bin/portaria` e `bin/central`
- `make test`: compila e roda os testes
- `make clean`: apaga executáveis e objetos
- `build.bat`: compila no Windows sem make
- `bin/portaria 1`: abre a portaria P01; `bin/central`: consolida e gera o relatório

## Convenções rápidas
- Pastas e arquivos: minúsculas com hífen; prefixo numérico quando há ordem.
- C: funções `modulo_acao`, tipos em PascalCase, constantes em MAIÚSCULAS, enums com prefixo (`STATUS_`, `CANAL_`, `OP_`), header guard `NOME_H`.
- SQL (MySQL 8): tabelas no singular com `_`, PK `id_<tabela>`, restrições nomeadas (`pk_`, `fk_`, `uq_`, `ck_`).
- IDs: RF01, RNF01, UC01, US01, ADR-001, A1.
- Commits: `tipo(escopo): descricao (USxx)`, com `feat`, `fix`, `docs`, `test`, `refactor` e `chore`. Tag ao fim de cada sprint (`v0.1.0`…; entrega `v1.0.0`).
- Diagramas: PlantUML para UML, Mermaid para fluxogramas e rascunhos; PNG exportado em `documento-final/figuras/figura-NN-descricao.png`.
- Use os termos do glossário (`PLANO.md`, seção 8.7) no texto, no código e no banco.

## Definição de pronto
Compila sem warnings; testes passam; funções comentadas; algoritmos principais com pseudocódigo e fluxograma; critérios de aceitação atendidos; rastreabilidade e sprint atualizadas.
