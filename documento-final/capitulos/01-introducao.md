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
- Figuras: nenhuma obrigatória; se o grupo quiser, usar o fluxo ponta a ponta (Figura 16) como visão geral.

## Pendências do projeto que afetam este capítulo

- Nome do curso, turma, integrantes e orientador para a capa: `[A DEFINIR]` (preencher `00-projeto/integrantes.md`).
- Deixar claro, na metodologia, que não houve levantamento de campo.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Escrito por último; confira se continua coerente com os capítulos.

# 1 INTRODUÇÃO

A gestão de encomendas nas portarias de condomínios residenciais é um problema cotidiano, que se intensifica em períodos de grande volume de compras on-line, como a Black Friday (MACK, 2024). Quando o controle é feito em caderno, o registro é livre e sem padrão, os volumes ficam sem posição definida, a entrega depende da memória do porteiro e a administradora não tem dados sobre o que acontece em cada portaria. Neste trabalho, esse problema é estudado em um cenário fictício: a Administradora Morada Central, que administra dez condomínios residenciais e cujas portarias controlam encomendas em caderno, o que gera extravios, entregas a pessoas erradas e sobrecarga dos porteiros, além de enfrentar internet instável em parte das portarias.

A pergunta que orienta o trabalho é: como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo dedicado pelos porteiros à gestão de encomendas em uma administradora de condomínios? O objetivo geral é desenvolver e documentar uma solução computacional para a gestão de encomendas nas portarias da administradora. Os objetivos específicos são caracterizar o processo atual, levantar requisitos, modelar o banco de dados, implementar em C o núcleo da portaria e a consolidação central, projetar a rede e a arquitetura distribuída e analisar a segurança, a privacidade e a acessibilidade.

A metodologia combinou pesquisa bibliográfica, análise do cenário, desenvolvimento de um protótipo com o framework Scrum (SCHWABER; SUTHERLAND, 2020) e verificação por testes automatizados, scripts de banco de dados e simulação de rede. O trabalho não incluiu levantamento de campo com usuários; essa limitação é discutida no capítulo 3.

A proposta é um sistema com duas partes. Em cada condomínio, um nó da portaria registra encomendas, indica a posição na estante, gera um código único de retirada, avisa o morador pelo canal que ele escolheu e funciona mesmo sem internet. Uma central da administradora recebe as operações das portarias e as aplica uma única vez cada, sem duplicidade, gerando relatórios consolidados. O protótipo em linguagem C implementa esse núcleo, com a rede e o aviso simulados; o banco de dados relacional e a infraestrutura de rede foram modelados e documentados.

O trabalho está organizado em dez capítulos. O capítulo 2 caracteriza a organização; o 3 apresenta a pesquisa e a fundamentação; o 4 trata da engenharia de software; o 5, do banco de dados; o 6, da programação em C; o 7, das redes e dos sistemas distribuídos; o 8, de segurança, privacidade e acessibilidade; o 9, da integração, implantação, benefícios e limitações; e o 10 traz a conclusão. Todos os dados de moradores, condomínios e encomendas utilizados são fictícios.
