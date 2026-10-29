# 2 Caracterização da organização (roteiro, cerca de 3 páginas, Etapa 1)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo".

**Fonte principal:** `01-organizacao/caracterizacao.md` e `01-organizacao/processos.md`.

## Tópicos

| # | Tópico | Origem |
|---|---|---|
| 2.1 | Identificação e ramo de atuação | `caracterizacao.md`, seção 1 |
| 2.2 | Missão | seção 2 |
| 2.3 | Produtos e serviços | seção 3 |
| 2.4 | Porte e estrutura organizacional | seções 4 e 5 |
| 2.5 | Público-alvo | seção 7 |
| 2.6 | Processos de negócio: como a encomenda é tratada hoje | `processos.md` |
| 2.7 | Problemas encontrados (P1 a P7) | `caracterizacao.md`, seção 8 |
| 2.8 | Justificativa da solução proposta | seção 9 |
| 2.9 | Processo proposto (visão resumida; o detalhe fica nos capítulos seguintes) | `processos.md` |

## Figuras e tabelas

| Item | Arquivo de origem |
|---|---|
| Figura 01: organograma | `01-organizacao/diagramas/organograma.mmd` |
| Figura 02: processo atual (caderno) | `01-organizacao/diagramas/processo-atual.mmd` |
| Figura 03: processo proposto | `01-organizacao/diagramas/processo-proposto.mmd` |
| Tabela: problemas P1 a P7 com o efeito de cada um | `caracterizacao.md`, seção 8 |

## Cuidados

- A organização é **fictícia**: dizer isso uma vez, com clareza, e descrever como cenário do trabalho.
- Não inventar números reais (funcionários, faturamento). Usar apenas o que consta na caracterização, marcado como cenário.
- Figuras só entram depois de renderizadas (Mermaid ainda não renderizado) e exportadas para `figuras/`.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro e dos arquivos de `01-organizacao/` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Todos os dados da organização são fictícios.

# 2 CARACTERIZAÇÃO DA ORGANIZAÇÃO

Este capítulo apresenta a organização escolhida como cenário do trabalho, seus serviços, sua estrutura, o processo atual de tratamento de encomendas e os problemas que justificam a solução proposta. A organização é fictícia, criada para este trabalho, e todos os números apresentados são hipóteses de cenário, mantidas coerentes entre código, banco de dados, rede e texto.

## 2.1 Identificação e ramo de atuação

A Administradora Morada Central Ltda. é uma empresa fictícia sediada em São Paulo (SP) que atua na administração condominial e na gestão de equipes de portaria para condomínios residenciais. Sua missão é administrar condomínios residenciais com organização, transparência e segurança, oferecendo a moradores e funcionários rotinas claras e confiáveis.

## 2.2 Produtos e serviços

A administradora oferece administração financeira e prestação de contas aos condôminos, gestão das equipes de portaria (contratação, escalas e treinamento), gestão de manutenção e de fornecedores, e atendimento ao morador com registro de ocorrências.

## 2.3 Porte e estrutura organizacional

No cenário, a empresa administra 10 condomínios, com 2 a 4 blocos cada, somando cerca de 960 unidades. Cada condomínio tem quatro porteiros em escala 12x36, o que totaliza 40 porteiros. A sede conta com um gerente de operações, dois supervisores (cada um responsável por cinco condomínios), três atendentes e dois analistas administrativo-financeiros. O síndico de cada condomínio é eleito pelos condôminos e é o interlocutor da administradora, aparecendo como relação externa no organograma (Figura 1). A estrutura é composta por uma diretoria, a gerência de operações, que coordena os supervisores, os porteiros e o atendimento ao morador, e o setor administrativo-financeiro.

**[Figura 1 – Organograma da Administradora Morada Central (fictícia). Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-01-organograma.png`]**

## 2.4 Público-alvo

O trabalho considera quatro grupos: os moradores, com perfis variados, incluindo idosos e pessoas que não usam smartphone; os síndicos; os porteiros; e a equipe da sede. A diversidade de perfis dos moradores é relevante para o canal de aviso da solução, que não pode depender apenas de aplicativo.

## 2.5 Processo atual de encomendas

Hoje, o tratamento de encomendas nas portarias depende de um caderno. O processo, representado na Figura 2, segue seis passos:

1. o entregador chega à portaria;
2. o porteiro anota no caderno a data, o nome, o bloco e apartamento e a transportadora;
3. o pacote vai para uma sala ou armário, sem posição definida;
4. o morador é avisado pelo interfone, quando o porteiro consegue;
5. o morador retira o pacote e, nem sempre, assina o caderno;
6. extravios e reclamações chegam à sede por telefone ou aplicativo de mensagens.

**[Figura 2 – Processo atual de encomendas (caderno). Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-02-processo-atual.png`]**

## 2.6 Problemas encontrados

A análise do processo atual levou a sete problemas, apresentados no Quadro 1.

**Quadro 1 – Problemas do processo atual**

| ID | Problema | Passo do processo em que aparece |
|---|---|---|
| P1 | Extravios e entregas à pessoa errada | Guarda sem posição definida; retirada sem conferência |
| P2 | Falta de rastreabilidade (quem recebeu, onde está, quem retirou) | Registro livre no caderno; assinatura nem sempre feita |
| P3 | Tempo do porteiro consumido por encomendas, com picos em novembro e dezembro | Registro e atendimento manuais |
| P4 | Aviso ao morador falho ou inexistente | Dependência do interfone |
| P5 | Acúmulo de volumes e falta de espaço | Guarda sem controle de ocupação |
| P6 | Nenhum dado para a sede planejar equipe e espaço | Informações só no caderno de cada portaria |
| P7 | Internet instável em parte das portarias | Inviabiliza uma solução que só funcione online |

Fonte: elaborado pelos autores (2026).

Esses problemas são o cenário do trabalho. Como não foi realizado levantamento de campo, o texto não afirma a frequência com que ocorrem. Qualquer número do setor, como o percentual do turno gasto com encomendas, só pode ser citado com fonte verificada `[FONTE A VERIFICAR: dados do setor de condomínios e do crescimento das entregas]`.

## 2.7 Justificativa e processo proposto

O problema se repete nos 10 condomínios e depende de registro, rastreabilidade e comunicação, funções em que uma solução computacional ajuda ao padronizar o processo, reduzir erros e gerar dados. A operação offline atende às portarias com internet instável (P7), e a consolidação central dá à administradora a visão de todos os condomínios (P6).

O processo proposto (Figura 3) segue o fluxo: registrar a encomenda, alocar posição na estante, gerar o código, avisar o morador, retirar com o código, sincronizar com a central e gerar relatórios. O Quadro 2 compara os dois processos.

**Quadro 2 – Processo atual e processo proposto**

| Aspecto | Atual (caderno) | Proposto |
|---|---|---|
| Registro | Texto livre, sem padrão | Campos obrigatórios e validados |
| Localização do volume | Sem posição definida | Posição na estante indicada pelo sistema |
| Identificação na retirada | Assinatura, nem sempre | Código de uso único |
| Aviso ao morador | Interfone, quando possível | Canal cadastrado, com alternativa para quem não usa smartphone |
| Rastreabilidade | Depende do caderno | Registro com data, hora e autor |
| Funcionamento sem internet | Independe de internet | Mantido: a portaria opera offline e sincroniza depois |
| Visão da sede | Telefone e mensagens | Consolidação e relatórios dos 10 condomínios |

Fonte: elaborado pelos autores (2026).

**[Figura 3 – Processo proposto. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-03-processo-proposto.png`]**

## 2.8 Considerações do capítulo

A Administradora Morada Central é um cenário fictício de 10 condomínios cujo processo manual de encomendas gera sete problemas, desde extravios até a falta de dados para a sede. O processo proposto troca o caderno por um fluxo registrado, rastreável e que funciona sem internet, objeto dos capítulos seguintes.
