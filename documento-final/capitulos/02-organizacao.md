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

Este capítulo apresenta a organização escolhida como cenário do trabalho, sua estrutura, o processo atual de tratamento de encomendas e os problemas que justificam a solução. A organização é fictícia, criada para este trabalho, e todos os números são hipóteses de cenário, mantidas coerentes entre código, banco de dados, rede e texto.

## 2.1 Identificação, ramo e serviços

A Administradora Morada Central Ltda. é uma empresa fictícia sediada em São Paulo (SP) que atua na administração condominial e na gestão de equipes de portaria para condomínios residenciais. Sua missão é administrar condomínios residenciais com organização, transparência e segurança, oferecendo a moradores e funcionários rotinas claras e confiáveis. Seus serviços são a administração financeira e a prestação de contas aos condôminos, a gestão das equipes de portaria (contratação, escalas e treinamento), a gestão de manutenção e de fornecedores e o atendimento ao morador com registro de ocorrências.

## 2.2 Porte, estrutura e público-alvo

No cenário, a empresa administra 10 condomínios, com 2 a 4 blocos cada, somando cerca de 960 unidades. Cada condomínio tem quatro porteiros em escala 12x36, totalizando 40 porteiros. A sede tem um gerente de operações, dois supervisores (cinco condomínios cada), três atendentes e dois analistas administrativo-financeiros, sob uma diretoria. O síndico de cada condomínio, eleito pelos condôminos, é o interlocutor da administradora e aparece como relação externa no organograma (Figura 1).

**[Figura 1 – Organograma da Administradora Morada Central (fictícia). Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-01-organograma.png`]**

O público-alvo são os moradores, de perfis variados, incluindo idosos e quem não usa smartphone, os síndicos, os porteiros e a equipe da sede. A diversidade dos moradores importa para o canal de aviso, que não pode depender só de aplicativo.

## 2.3 Processo atual de encomendas

Hoje, as encomendas dependem de um caderno (Figura 2): o entregador chega à portaria; o porteiro anota data, nome, bloco e apartamento e transportadora; o pacote vai para uma sala ou armário, sem posição definida; o morador é avisado pelo interfone, quando o porteiro consegue; o morador retira o pacote e, nem sempre, assina o caderno; e extravios e reclamações chegam à sede por telefone ou aplicativo de mensagens.

**[Figura 2 – Processo atual de encomendas (caderno). Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-02-processo-atual.png`]**

## 2.4 Problemas encontrados

A análise do processo levou a sete problemas (Quadro 1).

**Quadro 1 – Problemas do processo atual**

| ID | Problema |
|---|---|
| P1 | Extravios e entregas à pessoa errada (guarda sem posição, retirada sem conferência) |
| P2 | Falta de rastreabilidade: quem recebeu, onde está, quem retirou |
| P3 | Tempo do porteiro consumido por encomendas, com picos em novembro e dezembro |
| P4 | Aviso ao morador falho ou inexistente, por dependência do interfone |
| P5 | Acúmulo de volumes e falta de espaço, sem controle de ocupação |
| P6 | Nenhum dado para a sede planejar equipe e espaço |
| P7 | Internet instável em parte das portarias, o que inviabiliza uma solução só online |

Fonte: elaborado pelos autores (2026).

Esses problemas são o cenário do trabalho. Como não houve levantamento de campo, o texto não afirma a frequência com que ocorrem. A literatura do setor associa períodos como a Black Friday e o fim de ano ao aumento das entregas e à pressão sobre as portarias (MACK, 2024); qualquer número do setor só pode ser citado com fonte verificada `[FONTE A VERIFICAR: dados do setor]`.

## 2.5 Justificativa e processo proposto

O problema se repete nos 10 condomínios e depende de registro, rastreabilidade e comunicação, em que uma solução computacional ajuda ao padronizar o processo, reduzir erros e gerar dados. A operação offline atende às portarias com internet instável (P7) e a consolidação central dá à administradora a visão de todos os condomínios (P6).

O processo proposto (Figura 3) segue o fluxo: registrar a encomenda, alocar posição na estante, gerar o código, avisar o morador, retirar com o código, sincronizar com a central e gerar relatórios. Em relação ao caderno, o registro passa a ter campos obrigatórios e validados; o volume ganha posição na estante; a retirada exige um código de uso único; o aviso usa o canal cadastrado, com alternativa para quem não usa smartphone; cada operação tem data, hora e autor; a portaria continua operando sem internet; e a sede ganha a consolidação e os relatórios dos 10 condomínios.

**[Figura 3 – Processo proposto. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-03-processo-proposto.png`]**

## 2.6 Considerações do capítulo

A Administradora Morada Central é um cenário fictício de 10 condomínios cujo processo manual de encomendas gera sete problemas, de extravios à falta de dados para a sede. O processo proposto troca o caderno por um fluxo registrado, rastreável e que funciona sem internet, objeto dos capítulos seguintes.
