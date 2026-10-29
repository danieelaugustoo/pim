# Benefícios esperados e indicadores (Etapa 8)

> **Roteiro de tópicos** para o capítulo 9. Os benefícios abaixo são **esperados** (hipóteses de projeto), não resultados medidos. Nenhum número real foi coletado: o levantamento de campo foi dispensado (`02-pesquisa/metodologia.md`) e o piloto não existe. A linha de base ("antes") seria medida no piloto, nas primeiras semanas, com o caderno ainda em uso.

## 1. Pergunta de pesquisa que os indicadores respondem

> Como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo dedicado pelos porteiros à gestão de encomendas em uma administradora de condomínios? (`02-pesquisa/problema-e-objetivos.md`)

## 2. Benefícios esperados para a organização

| Benefício esperado | Por que a solução o produz | Recurso do projeto |
|---|---|---|
| Menos extravios | Todo volume tem registro, posição e código; nada depende da memória do porteiro | US01 a US03, A1, A2 |
| Menos entregas erradas | A retirada só ocorre com o código correto, com quem retirou e quando registrados | US04, US05, A3 |
| Menos tempo de busca e de registro | Busca por unidade e posição indicada pelo sistema | US05, A1 |
| Moradores avisados mais rápido | Aviso no canal de cada um, sem depender de ligação | US07, US08 |
| Operação que não para | A portaria funciona sem internet e sincroniza depois | US09, US10, ADR-003 |
| Visão única das 10 portarias | A central consolida sem duplicar | US11, A5 |
| Cobrança de retirada | Alerta de pendências com mais de 7 dias | US13, A6 |
| Dimensionamento da equipe | Pico de entrada por dia e ocupação da estante | US12, US14, A6 |
| Menos conflito com moradores | Comprovante com data, hora e nome | US04 |

## 3. Indicadores

Sem levantamento de campo, o "antes" **não existe hoje**: ele é a linha de base a medir no piloto (com o caderno), e o "depois" é **meta ou estimativa**. O trabalho deve apresentar os dois como planejamento, nunca como resultado.

| Indicador | Como medir | Fonte do dado | Antes (linha de base) | Meta / depois |
|---|---|---|---|---|
| Extravios por mês | Encomendas registradas como não localizadas ÷ mês | Contagem no piloto (antes e depois) | A medir no piloto | `[A DEFINIR]` |
| Tempo médio entre chegada e retirada | Média de (`retirada_em` − `recebida_em`) das retiradas do mês | Registros do sistema | A medir no piloto | `[A DEFINIR]` |
| Moradores avisados em até 15 minutos | Avisos enviados até 15 min após o registro ÷ registros | Registro de avisos | A medir no piloto | `[A DEFINIR]` |
| Tempo de registro por encomenda | Cronometragem de amostra de registros (RNF02: cerca de 30 segundos) | Observação no piloto | A medir no piloto | cerca de 30 s (RNF02) |
| Pendências com mais de 7 dias | Pendências antigas no relatório (US13) | Relatório de pendências antigas | A medir no piloto | `[A DEFINIR]` |

**Como o protótipo já produz parte desses dados:**
- pendências com mais de 7 dias: opção 7 → 1 do menu, e coluna ANTIGAS do relatório da central;
- dia de pico e ocupação: opção 7 → 2 e 3, e coluna PICO do relatório da central;
- tempo entre chegada e retirada: dá para calcular a partir de `recebida_em` e `retirada_em`, mas **ainda não há relatório pronto** para isso (candidato à evolução).

Os indicadores "extravios por mês" e "avisados em 15 minutos" dependem do sistema completo ou de coleta manual: o protótipo simula o aviso e não mede o tempo até a leitura.

## 4. Como apresentar sem exagerar

- Separar sempre **medido** (protótipo, testes), **estimado** (meta) e **a medir** (piloto).
- Não afirmar redução percentual sem o "antes" e o "depois" coletados.
- Dizer com clareza que não houve levantamento de campo e que a linha de base ficaria para o piloto (`08-integracao/implantacao.md`).
- Citar trabalhos relacionados só depois de verificados (`02-pesquisa/fontes.md`, `[FONTE A VERIFICAR]`).

## 5. Custos e retorno

Não há estimativa de custo neste projeto: equipamentos e serviços de nuvem estão como `[A COTAR]` (`06-redes/equipamentos.md`). Se o grupo quiser discutir retorno financeiro, precisa cotar os itens e usar números da administradora; sem isso, tratar o benefício de forma qualitativa.
