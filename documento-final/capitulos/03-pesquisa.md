# 3 Pesquisa científica e inovação (roteiro, cerca de 3 páginas, Etapa 2)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo". É o capítulo mais dependente de trabalho do grupo: fontes e trabalhos relacionados. **O levantamento de campo foi dispensado** (decisão do grupo, 2026-10-29), então o capítulo não tem resultados de questionário.

**Fontes no repositório:** `02-pesquisa/problema-e-objetivos.md`, `metodologia.md`, `fundamentacao.md`, `trabalhos-relacionados.md`, `diferenciais.md`, `fontes.md`.

## Tópicos

| # | Tópico | Origem |
|---|---|---|
| 3.1 | Problema de pesquisa e pergunta | `problema-e-objetivos.md`, seção 1 |
| 3.2 | Objetivo geral e específicos | seção 2 |
| 3.3 | Justificativa científica | `problema-e-objetivos.md` |
| 3.4 | Metodologia: classificação da pesquisa, procedimentos, análise dos dados, limitações | `metodologia.md` |
| 3.5 | Fundamentação teórica (temas das fichas) | `fundamentacao.md`, **só com fontes verificadas** |
| 3.6 | Trabalhos relacionados e matriz comparativa | `trabalhos-relacionados.md` |
| 3.7 | Como o problema foi levantado sem pesquisa de campo (cenário e bibliografia) e a limitação que isso traz | `metodologia.md`, seções 2 e 5 |
| 3.8 | Diferenciais e inovação da proposta | `diferenciais.md` |

## Figuras e tabelas

- Tabela: matriz comparativa C1 a C5 × K1 a K6 (`trabalhos-relacionados.md`), com a fonte em cada célula.
- Sem gráficos de questionário. Os resultados do trabalho aparecem nos capítulos 5, 6 e 7 (consultas SQL, testes do protótipo e testes de rede).

## O que bloqueia este capítulo (só o grupo resolve)

- [ ] **Declarar no texto que não houve levantamento de campo** e não afirmar frequência de extravios, volume de encomendas nem preferências dos moradores sem fonte verificada.
- [ ] **Verificar as fontes** F01 a F05 e B01 a B13 em `fontes.md` (todas `[FONTE A VERIFICAR]`) e preencher as fichas de `fundamentacao.md`.
- [ ] **Pesquisar os trabalhos relacionados** (categorias C2 a C4) e preencher a matriz com fonte.

## Cuidados

- Citações diretas curtas, com autor, ano e página; paráfrase com as próprias palavras (a UNIP usa software de similaridade).
- Toda referência usada no texto entra em `referencias.md` no padrão ABNT, e toda referência listada precisa ter sido citada.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro e de `02-pesquisa/` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. **Este é o capítulo mais incompleto**: não houve levantamento de campo, a fundamentação usa só fontes verificadas (`02-pesquisa/fontes.md`, seção 4) e a pesquisa de trabalhos relacionados reais não foi feita. Complete as marcas `[ ... ]`.

# 3 PESQUISA CIENTÍFICA E INOVAÇÃO

Este capítulo apresenta o problema de pesquisa, os objetivos, a justificativa, a metodologia, a fundamentação teórica, os trabalhos relacionados e os diferenciais da proposta.

## 3.1 Problema de pesquisa

O cenário é uma administradora de condomínios cujas portarias controlam encomendas em caderno, o que gera extravios, entregas a pessoas erradas e sobrecarga dos porteiros (capítulo 2). A pergunta do trabalho é: como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo dedicado pelos porteiros à gestão de encomendas em uma administradora de condomínios?

Alguns termos têm sentido específico: *extravio* é a encomenda recebida que não é localizada ou entregue; *entrega incorreta* é a entrega a pessoa diferente da destinatária ou da autorizada; *operação offline* é a capacidade de registrar e entregar sem internet; e *sincronização* é o envio posterior das operações à central, sem duplicá-las.

## 3.2 Objetivos

**Objetivo geral.** Desenvolver e documentar uma solução computacional para a gestão de encomendas nas portarias da Administradora Morada Central.

**Objetivos específicos:** (1) caracterizar o processo atual e seus problemas; (2) levantar requisitos com pesquisa bibliográfica e análise do cenário; (3) modelar o banco relacional e avaliar o uso de NoSQL; (4) implementar em C o núcleo da portaria e a consolidação central; (5) projetar a infraestrutura de rede e a arquitetura distribuída; (6) analisar a segurança, a privacidade e a acessibilidade da solução.

## 3.3 Justificativa

A relevância social está em reduzir conflitos entre moradores, porteiros e síndicos causados por encomendas perdidas ou entregues à pessoa errada e em tornar mais previsível a carga do porteiro. O avanço das compras on-line e a concentração de entregas em períodos como a Black Friday pressionam as portarias (MACK, 2024) `[FONTE A VERIFICAR: dados de crescimento do comércio eletrônico no Brasil]`. A relevância técnica está em integrar, em um problema concreto, engenharia de software ágil, banco de dados, programação estruturada, redes e sistemas distribuídos. A lacuna explorada é a combinação de funcionamento sem internet, aviso alternativo para quem não usa smartphone e consolidação de vários condomínios, cuja ausência nas soluções existentes só pode ser afirmada depois da pesquisa de trabalhos relacionados (seção 3.6). O recorte é viável porque o protótipo em C com rede simulada representa o sistema completo dentro do prazo.

## 3.4 Metodologia

A pesquisa é aplicada, de objetivo exploratório e abordagem qualitativa; os dados quantitativos vêm dos testes e verificações do protótipo `[FONTE A VERIFICAR: referência metodológica, se o professor exigir]`. Os procedimentos foram a pesquisa bibliográfica, a análise do cenário e do processo atual, o desenvolvimento de um protótipo com Scrum, em sprints registradas em arquivos, e a verificação por testes automatizados, execução com dados fictícios, scripts SQL e testes de rede.

O grupo dispensou o **levantamento de campo** (questionário a porteiros e síndicos), por não ser obrigatório. Por isso os requisitos não têm dados de respondentes reais, e o texto não afirma a frequência dos problemas nem as preferências dos moradores; o "antes" dos indicadores seria medido em um piloto (capítulo 9). Também são limitações a organização fictícia, a rede e o aviso simulados e o fato de os benefícios serem esperados, e não medidos.

## 3.5 Fundamentação teórica

Cada tema só é afirmado com fonte verificada. O **Scrum** organiza o trabalho em ciclos iterativos e incrementais, com inspeção e adaptação, e papéis de Product Owner, Scrum Master e Developers (SCHWABER; SUTHERLAND, 2020). Os **bancos de dados** (modelo relacional, normalização e contraponto NoSQL) embasam o capítulo 5 (HEUSER, 2009; ELMASRI; NAVATHE, 2011; SADALAGE; FOWLER, 2013). A **programação estruturada em C** e a construção de algoritmos apoiam-se em Deitel e Deitel (2011) e Forbellone e Eberspächer (2005). **Redes, nuvem e sistemas distribuídos** têm base em Tanenbaum e Wetherall (2011), Kurose e Ross (2013), Mell e Grance (2011) e Tanenbaum e Van Steen (2007); a operação offline e a idempotência, centrais na solução, ainda precisam de uma ficha de leitura da obra de sistemas distribuídos `[FICHAR]`. A **proteção de dados e a acessibilidade** vêm da LGPD (BRASIL, 2018), da Lei Brasileira de Inclusão (BRASIL, 2015) e das diretrizes de acessibilidade web do W3C (WORLD WIDE WEB CONSORTIUM, 2024), tratadas no capítulo 8.

`[O grupo deve ler as obras e escrever, com as próprias palavras, a síntese de cada tema, citando página quando houver citação direta. Este rascunho lista os temas e as fontes, mas ainda não resume o conteúdo das obras.]`

## 3.6 Trabalhos relacionados

Foram definidas quatro categorias de solução para comparação: caderno ou planilha (situação atual), aplicativos de gestão condominial com módulo de encomendas, armários inteligentes e portaria remota, contra a solução proposta. Os critérios são custo, dependência de internet, aviso ao morador, rastreabilidade, alternativa para quem não usa smartphone e visão de vários condomínios. A matriz comparativa está em `02-pesquisa/trabalhos-relacionados.md` e só tem preenchidas a situação atual e a proposta, que vêm do cenário e das decisões do projeto; as demais colunas estão vazias de propósito.

`[PENDENTE: pesquisar produtos reais de cada categoria, preencher a matriz com a fonte de cada informação, inserir a matriz preenchida neste capítulo e só então afirmar o que a proposta tem de diferente. Sem fonte, nenhum produto deve ser citado nem comparado.]`

## 3.7 Diferenciais da proposta

Cinco diferenciais são características **da proposta**, não exclusividades de mercado, o que só poderia ser dito após a pesquisa da seção 3.6: (1) operação offline com sincronização sem duplicidade; (2) endereçamento automático da posição na estante, conforme o bloco e o tamanho do volume; (3) aviso em vários canais, com código impresso para quem não usa smartphone; (4) consolidação de vários condomínios em um relatório único; e (5) dados de pico para dimensionar a equipe. No protótipo, o aviso e a rede são simulados e não há interface gráfica.

## 3.8 Considerações do capítulo

O problema e os objetivos estão definidos, a metodologia foi adaptada sem levantamento de campo e a fundamentação está estruturada em temas com fontes verificadas. Ficam pendentes o resumo escrito das obras e a pesquisa de trabalhos relacionados reais.
