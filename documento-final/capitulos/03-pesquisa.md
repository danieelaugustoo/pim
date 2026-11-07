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


As portarias da administradora controlam as encomendas em caderno, o que gera extravios, entregas a pessoas erradas e sobrecarga dos porteiros (capítulo 2). A pergunta do trabalho é: como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo que os porteiros dedicam às encomendas? Extravio é a encomenda recebida que não é localizada nem entregue, e entrega incorreta é a entrega a quem não é o destinatário nem o autorizado. Operação offline é registrar e entregar sem internet, e sincronização é enviar depois as operações à central, sem duplicá-las.

## 3.2 Objetivos

O objetivo geral é desenvolver e documentar uma solução computacional para a gestão de encomendas nas portarias da Administradora Morada Central. Os objetivos específicos são: (1) caracterizar o processo atual e seus problemas; (2) levantar requisitos com pesquisa bibliográfica e análise do cenário; (3) modelar o banco relacional e avaliar o uso de NoSQL; (4) implementar em C o núcleo da portaria e a consolidação central; (5) projetar a infraestrutura de rede e a arquitetura distribuída; (6) analisar a segurança, a privacidade e a acessibilidade da solução.

## 3.3 Justificativa


Do lado social, a solução busca reduzir os conflitos entre moradores, porteiros e síndicos causados por encomendas perdidas ou entregues à pessoa errada, e tornar mais previsível a carga do porteiro, pressionada pelo crescimento das compras on-line (MACK, 2024) `[FONTE A VERIFICAR: dados de crescimento do comércio eletrônico no Brasil]`. Do lado técnico, o problema reúne engenharia de software ágil, banco de dados, programação estruturada, redes e sistemas distribuídos em um caso concreto, e a lacuna explorada é a combinação de funcionamento sem internet, aviso alternativo para quem não usa smartphone e consolidação de vários condomínios (seção 3.6).

## 3.4 Metodologia


A pesquisa é aplicada, de objetivo exploratório e abordagem qualitativa, e os dados quantitativos vêm dos testes e das verificações do protótipo `[FONTE A VERIFICAR: referência metodológica, se o professor exigir]`. Os procedimentos foram a pesquisa bibliográfica, a análise do cenário e do processo atual, o desenvolvimento de um protótipo com Scrum, em sprints registradas em arquivos, e a verificação por testes automatizados, execução com dados de exemplo, scripts SQL e testes de rede. O grupo dispensou o levantamento de campo, que não era obrigatório, e por isso o texto não afirma a frequência dos problemas nem as preferências dos moradores. O "antes" dos indicadores precisaria ser medido em um piloto (capítulo 9).

## 3.5 Fundamentação teórica



O Scrum organiza o trabalho em sprints, com inspeção e adaptação ao fim de cada uma (SCHWABER; SUTHERLAND, 2020). No banco de dados, o modelo relacional usa tabelas, chaves e restrições de integridade, e a normalização elimina a redundância (HEUSER, 2009; ELMASRI; NAVATHE, 2011), enquanto os bancos NoSQL servem a dados de estrutura variável (SADALAGE; FOWLER, 2013). Em C, as estruturas de controle e os algoritmos seguem Deitel e Deitel (2011) e Forbellone e Eberspächer (2005). Em redes, topologias e endereçamento seguem Tanenbaum e Wetherall (2011) e Kurose e Ross (2013), a computação em nuvem segue Mell e Grance (2011) e os sistemas distribuídos, Tanenbaum e Van Steen (2007). Privacidade e acessibilidade apoiam-se na LGPD (BRASIL, 2018), na Lei Brasileira de Inclusão (BRASIL, 2015) e nas diretrizes do W3C (WORLD WIDE WEB CONSORTIUM, 2024).

## 3.6 Trabalhos relacionados



A comparação considera o caderno ou a planilha (a situação atual), os aplicativos de gestão condominial com módulo de encomendas, os armários inteligentes e a portaria remota, a partir de páginas de fornecedores e de portais do setor, sem testar nenhum produto. O aplicativo ALL Condo permite que a portaria receba a encomenda, registre-a por fotos e envie ao morador um QR code para a retirada (UCONDO TECNOLOGIA, [s.d.]). Nos armários inteligentes, o entregador deposita o volume, o morador recebe um código por aplicativo ou SMS e retira sem depender da portaria, com custo de locação, compra ou comodato, e o condomínio precisa oferecer tomada e rede wifi (PEREIRA, 2021), em fonte que é informe publicitário de um portal do setor. Na portaria remota, uma central atende a portaria à distância, e as entregas de encomendas aparecem entre as desvantagens do modelo, que pede apoio presencial local (REZENDE, 2023).

As páginas consultadas não informam o funcionamento sem internet nem a consolidação de vários condomínios, o que não prova que os produtos não o façam. Os diferenciais pretendidos da proposta são a operação offline com sincronização sem duplicidade, a posição na estante definida pelo bloco e pelo tamanho do volume, o aviso em vários canais com código impresso, a consolidação de vários condomínios e os dados de pico para dimensionar a equipe, sem pretensão de exclusividade de mercado.
