# Sprint 3: relatórios e qualidade

**Datas:** 29/10/2026 (ciclo único registrado no repositório; ver `00-projeto/cronograma.md`)
**Meta:** o porteiro vê o mapa da estante, o supervisor recebe alertas de pendências antigas e relatórios de pico e ocupação, os algoritmos A1 a A6 ficam documentados e as Etapas 7 e 8 têm roteiro (US12 a US15; US16 opcional).

## Histórias

| ID | História | Situação |
|---|---|---|
| US12 | Mapa de ocupação da estante | Feito (falta revisão do grupo) |
| US13 | Alerta de volumes parados há mais de 7 dias | Feito (falta revisão do grupo) |
| US14 | Relatórios de pico e ocupação | Feito (falta revisão do grupo) |
| US15 | Testes automatizados | Feito (falta revisão do grupo) |
| US16 | (Opcional) Marcar volume como devolvido | **Não iniciada**: o prazo da devolução não está definido no plano (decisão do grupo) |

Critérios de aceitação em `scrum/backlog.md`. "Feito" significa implementado, compilando sem warnings e testado; a revisão por outro integrante (definição de pronto) ainda não aconteceu.

## Verificações realizadas (2026-10-29)

- `gcc -std=c99 -Wall -Wextra -pedantic` sem warnings, com `build.bat` e com `make`, e também com `-O2` (verificação de sintaxe de todos os `.c`).
- **9 conjuntos de testes passando** com `build.bat test` e com `make test`: os 8 anteriores e o novo `test_relatorio`.
- `test_relatorio` cobre: percentual de ocupação (0%, 25%, 100%); pendência com 8 dias alerta e com 7 não; retirada, devolvida e data inválida não alertam; contagem por dia, outro mês e outro ano ignorados, empate no pico, mês vazio; central (antigas e dia de pico por portaria).
- **Falha de asserção derruba o `make`:** conferido com um teste descartável fora do repositório (a asserção falhou, o `make` terminou com erro e a linha seguinte não rodou). A regra do `Makefile` é a mesma dos testes reais.
- **Execução real com os dados de exemplo** (data do sistema 2026-10-29):
  - mapa: 6 posições ocupadas de 48 (12,5%), coerente com as 6 pendentes do arquivo;
  - pendências antigas: encomendas 1 (9 dias) e 4 (14 dias); as de 2, 3, 5 e 8 não alertam, e as retirada/devolvida não entram;
  - central rodada duas vezes: na 1ª, 17 operações aplicadas; na 2ª, 0 aplicadas e 17 já aplicadas; relatório com ANTIGAS 2 e 0, e PICO por portaria;
  - retirada: id de outra unidade recusado; três códigos errados negam a retirada e a encomenda continua pendente.
- Pseudocódigo conferido contra o código de `estante.c`, `codigo.c`, `retirada.c` e `relatorio.c`; afirmações sobre testes conferidas contra os testes existentes.

## O que foi entregue

- Módulo novo `relatorio` (`include/relatorio.h`, `src/relatorio.c`): mapa da estante com percentual, pendências antigas, contagem por dia com dia de pico, ocupação por estante e as funções usadas pelo relatório da central.
- Portaria: opção 5 (mapa) e opção 7 (submenu de relatórios).
- Relatório da central com as colunas ANTIGAS e PICO.
- `Makefile` e `build.bat` com o módulo e o teste novos; constante `DIAS_NO_MES` em `tipos.h`.
- Pseudocódigo de **A1, A2, A3 e A6** e fluxogramas **A1 a A3 e A6** (`algoritmos/`); A4 e A5 já estavam prontos.
- **Etapa 7:** `07-seguranca-privacidade-acessibilidade/analise.md` (roteiro de tópicos).
- **Etapa 8:** `08-integracao/` com `integracao.md`, `implantacao.md`, `beneficios-e-indicadores.md`, `limitacoes-e-evolucao.md` e `diagramas/fluxo-ponta-a-ponta.mmd`.

## O que não foi entregue / fica para depois

- **US16 (devolução):** depende do prazo definido pelo grupo; a central já entende a operação DEVOLUCAO.
- **Renderização** dos fluxogramas e diagramas (Mermaid e PlantUML não estão instalados) e exportação dos PNG para `documento-final/figuras/`.
- **Packet Tracer:** montagem, testes e prints são do grupo (Sprint 2).
- **Capítulos** do trabalho: textos autorais do grupo.
- **Relatório de tempo médio entre chegada e retirada**, que alimentaria um indicador: candidato à evolução.
- Tag `v0.3.0`: depende da revisão e do commit.

## Impedimentos e riscos

- **Código de retirada visível na tela do porteiro** para qualquer canal: contraria o RNF04 para app e SMS. Está em `07-.../analise.md` (seção 2) e no README do programa; o grupo decide se ajusta ou declara como limitação.
- **Levantamento de campo dispensado pelo grupo (decidido depois desta sprint, em 2026-10-29):** os indicadores de `08-integracao/beneficios-e-indicadores.md` não têm "antes" medido; a linha de base fica para o piloto.
- Leis e normas citadas na Etapa 7 estão marcadas `[FONTE A VERIFICAR]` e precisam ser conferidas nos textos oficiais.
- **Incidente de processo (sem impacto no resultado):** durante a sprint, uma edição por script deixou `src/consolidacao.c` vazio por engano; o arquivo foi restaurado do último commit e a alteração refeita com a ferramenta de edição. Os testes foram todos executados depois disso.
- Prazo oficial de entrega ainda não confirmado.

## Retrospectiva (a preencher pelo grupo)

- O que funcionou:
- O que melhorar:
- Ações para a próxima sprint:
