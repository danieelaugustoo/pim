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

> **Rascunho** redigido a partir do roteiro e de `02-pesquisa/` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Não houve levantamento de campo e a pesquisa de trabalhos relacionados reais ainda não foi feita. Complete as marcas `[ ... ]`.

# 3 PESQUISA CIENTÍFICA E INOVAÇÃO

Este capítulo apresenta o problema de pesquisa, os objetivos, a justificativa, a metodologia, a fundamentação teórica, os trabalhos relacionados e os diferenciais da proposta.

## 3.1 Problema de pesquisa

As portarias da administradora controlam as encomendas em caderno, o que gera extravios, entregas a pessoas erradas e sobrecarga dos porteiros (capítulo 2). A pergunta do trabalho é: como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo que os porteiros dedicam às encomendas em uma administradora de condomínios?

Neste trabalho, extravio é a encomenda recebida que não é localizada nem entregue, e entrega incorreta é a entrega a quem não é o destinatário nem o autorizado. Operação offline é registrar e entregar sem internet, e sincronização é enviar depois as operações à central, sem duplicá-las.

## 3.2 Objetivos

O objetivo geral é desenvolver e documentar uma solução computacional para a gestão de encomendas nas portarias da Administradora Morada Central. Os objetivos específicos são: (1) caracterizar o processo atual e seus problemas; (2) levantar requisitos com pesquisa bibliográfica e análise do cenário; (3) modelar o banco relacional e avaliar o uso de NoSQL; (4) implementar em C o núcleo da portaria e a consolidação central; (5) projetar a infraestrutura de rede e a arquitetura distribuída; (6) analisar a segurança, a privacidade e a acessibilidade da solução.

## 3.3 Justificativa

Do lado social, a solução busca reduzir os conflitos entre moradores, porteiros e síndicos causados por encomendas perdidas ou entregues à pessoa errada, e tornar mais previsível a carga do porteiro. O crescimento das compras on-line e a concentração de entregas em datas como a Black Friday pressionam as portarias (MACK, 2024) `[FONTE A VERIFICAR: dados de crescimento do comércio eletrônico no Brasil]`. Do lado técnico, o problema reúne engenharia de software ágil, banco de dados, programação estruturada, redes e sistemas distribuídos em um caso concreto. A lacuna explorada é a combinação de funcionamento sem internet, aviso alternativo para quem não usa smartphone e consolidação de vários condomínios. Só se pode afirmar que as soluções existentes não a oferecem depois da pesquisa de trabalhos relacionados (seção 3.6). O recorte é viável no prazo porque um protótipo em C, com rede simulada, representa o sistema completo.

## 3.4 Metodologia

A pesquisa é aplicada, de objetivo exploratório e abordagem qualitativa, e os dados quantitativos vêm dos testes e das verificações do protótipo `[FONTE A VERIFICAR: referência metodológica, se o professor exigir]`. Os procedimentos foram a pesquisa bibliográfica, a análise do cenário e do processo atual, o desenvolvimento de um protótipo com Scrum, em sprints registradas em arquivos, e a verificação por testes automatizados, execução com dados de exemplo, scripts SQL e testes de rede.

O grupo dispensou o levantamento de campo (questionário a porteiros e síndicos), que não era obrigatório. Por isso os requisitos não têm dados de respondentes reais, e o texto não afirma a frequência dos problemas nem as preferências dos moradores. O "antes" dos indicadores precisaria ser medido em um piloto (capítulo 9). Também limitam o trabalho a rede e o aviso simulados e o fato de os benefícios serem esperados, e não medidos.

## 3.5 Fundamentação teórica

O Scrum organiza o trabalho em ciclos curtos, as sprints, com inspeção e adaptação ao fim de cada uma, e define os papéis de Product Owner, Scrum Master e Developers (SCHWABER; SUTHERLAND, 2020).

No banco de dados, o modelo relacional guarda os dados em tabelas ligadas por chaves e protegidas por restrições de integridade, e a normalização elimina a redundância por meio das formas normais (HEUSER, 2009; ELMASRI; NAVATHE, 2011). Os bancos NoSQL, de documentos ou de chave-valor, servem a dados de estrutura variável (SADALAGE; FOWLER, 2013). Essa base sustenta o capítulo 5.

Para o programa em C, os conceitos de estruturas de controle e funções vêm de Deitel e Deitel (2011), e a construção de algoritmos, de Forbellone e Eberspächer (2005).

Em redes, topologias, endereçamento e redes locais seguem Tanenbaum e Wetherall (2011) e Kurose e Ross (2013). Na computação em nuvem, Mell e Grance (2011) definem os modelos de serviço IaaS, PaaS e SaaS, e um sistema distribuído é formado por componentes independentes que cooperam trocando mensagens (TANENBAUM; VAN STEEN, 2007).

A proteção de dados pessoais e a acessibilidade apoiam-se na LGPD (BRASIL, 2018), na Lei Brasileira de Inclusão (BRASIL, 2015) e nas diretrizes de acessibilidade web do W3C (WORLD WIDE WEB CONSORTIUM, 2024), aplicadas no capítulo 8.

## 3.6 Trabalhos relacionados

A comparação considera quatro categorias de solução: caderno ou planilha (a situação atual), aplicativos de gestão condominial com módulo de encomendas, armários inteligentes e portaria remota. A solução proposta é comparada a elas em seis critérios: custo, dependência de internet, aviso ao morador, rastreabilidade, alternativa para quem não usa smartphone e visão de vários condomínios. A matriz está em `02-pesquisa/trabalhos-relacionados.md`. Só a situação atual e a proposta estão preenchidas, a partir do cenário e das decisões do projeto, e as demais colunas ficam vazias até haver fonte.

`[PENDENTE: pesquisar produtos reais de cada categoria, preencher a matriz com a fonte de cada informação, inserir a matriz preenchida neste capítulo e só então afirmar o que a proposta tem de diferente. Sem fonte, nenhum produto deve ser citado nem comparado.]`

## 3.7 Diferenciais da proposta

Os diferenciais abaixo são características da proposta, e não exclusividades de mercado, o que só poderia ser dito depois da seção 3.6: operação offline com sincronização sem duplicidade; posição na estante definida automaticamente pelo bloco e pelo tamanho do volume; aviso em vários canais, com código impresso para quem não usa smartphone; consolidação de vários condomínios em um relatório único; e dados de pico para dimensionar a equipe. No protótipo, o aviso e a rede são simulados e não há interface gráfica.
