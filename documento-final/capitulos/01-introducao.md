# 1 Introdução (roteiro, cerca de 2 páginas)

> **ROTEIRO, não é o texto.** O grupo escreve a introdução e **substitui** este conteúdo na seção "Texto do grupo".

**Exigência do manual:** objetivo da pesquisa, metodologia, breve apresentação da empresa e visão geral da proposta.

## Tópicos

| # | Tópico | Onde buscar no repositório |
|---|---|---|
| 1.1 | Contexto: encomendas em condomínios e por que a portaria virou ponto crítico | `01-organizacao/caracterizacao.md` (seção 8), `02-pesquisa/fundamentacao.md` (só com fonte verificada) |
| 1.2 | Problema e pergunta de pesquisa | `02-pesquisa/problema-e-objetivos.md` |
| 1.3 | Objetivo geral e objetivos específicos (resumidos) | `02-pesquisa/problema-e-objetivos.md`, seção 2 |
| 1.4 | Metodologia em poucas linhas: pesquisa, Scrum em sprints, protótipo, banco, rede | `02-pesquisa/metodologia.md`, `03-engenharia-software/scrum/` |
| 1.5 | Apresentação breve da Administradora Morada Central (fictícia) | `01-organizacao/caracterizacao.md`, seção 1 |
| 1.6 | Visão geral da proposta: nó de portaria offline + central | `03-engenharia-software/arquitetura.md` |
| 1.7 | Organização do trabalho (um parágrafo dizendo o que há em cada capítulo) | `../estrutura-e-paginas.md` |

## Cuidados

- Declarar logo no início que a organização é **fictícia** e que os dados de exemplo são fictícios.
- Não adiantar resultados: a introdução apresenta, não conclui.
- Toda estatística ou afirmação sobre o mercado precisa de fonte (`[FONTE A VERIFICAR]` até conferir).
- Figuras: nenhuma obrigatória; se o grupo quiser, usar o fluxo ponta a ponta (Figura 17) como visão geral.

## Pendências do projeto que afetam este capítulo

- Nome do curso, turma, integrantes e orientador para a capa: `[A DEFINIR]` (preencher `00-projeto/integrantes.md`).
- Deixar claro, na metodologia, que não houve levantamento de campo.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Escrito por último; confira se continua coerente com os capítulos.

# 1 INTRODUÇÃO

Quem mora em condomínio conhece o caderno da portaria: o porteiro anota a encomenda que chegou, guarda o volume onde houver espaço e avisa o morador quando consegue. Em períodos de muitas compras on-line, como a Black Friday, esse método perde o controle (MACK, 2024). O registro é livre, os volumes não têm posição definida, a entrega depende da memória de quem está de plantão e a administradora não sabe o que acontece em cada portaria.

Este trabalho trata desse problema na Administradora Morada Central, que administra dez condomínios residenciais. Todas as portarias controlam as encomendas em caderno, o que gera extravios, entregas a pessoas erradas e sobrecarga dos porteiros, e parte delas tem internet instável.

A pergunta que orienta o trabalho é: como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo que os porteiros gastam com encomendas em uma administradora de condomínios? O objetivo geral é desenvolver e documentar essa solução. Os objetivos específicos são caracterizar o processo atual, levantar requisitos, modelar o banco de dados, implementar em C o núcleo da portaria e a consolidação central, projetar a rede e a arquitetura distribuída e analisar a segurança, a privacidade e a acessibilidade.

A metodologia combinou pesquisa bibliográfica, análise do cenário, desenvolvimento de um protótipo com Scrum (SCHWABER; SUTHERLAND, 2020) e verificação por testes automatizados, scripts de banco de dados e simulação de rede. Não houve levantamento de campo com usuários, limitação discutida no capítulo 3.

A proposta tem duas partes. Em cada condomínio, um nó da portaria registra a encomenda, indica a posição na estante, gera um código único de retirada, avisa o morador pelo canal que ele escolheu e continua funcionando sem internet. Uma central da administradora recebe as operações das portarias, aplica cada uma uma única vez e gera relatórios consolidados. O protótipo em C implementa esse núcleo, com a rede e o aviso simulados. O banco de dados relacional e a infraestrutura de rede foram modelados e documentados.

O capítulo 2 caracteriza a organização e o 3 apresenta a pesquisa. Os capítulos 4 a 7 tratam de engenharia de software, banco de dados, programação em C e redes, o 8 analisa segurança, privacidade e acessibilidade, o 9 integra as partes, e o 10 traz a conclusão. Os dados usados nos testes e na demonstração são dados de exemplo.
