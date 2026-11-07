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

> **Rascunho** redigido a partir do roteiro e dos arquivos de `01-organizacao/` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo.

# 2 CARACTERIZAÇÃO DA ORGANIZAÇÃO

Este capítulo apresenta a organização estudada, sua estrutura, o processo atual de tratamento de encomendas e os problemas que justificam a solução.

## 2.1 Identificação, ramo e serviços


A Administradora Morada Central Ltda. fica em São Paulo (SP) e administra condomínios residenciais e as equipes de portaria deles. Sua missão é administrar condomínios com organização, transparência e segurança, oferecendo a moradores e funcionários rotinas claras e confiáveis. Os serviços incluem a administração financeira e a prestação de contas aos condôminos, a gestão das equipes de portaria, a gestão de manutenção e de fornecedores e o atendimento ao morador.

## 2.2 Porte, estrutura e público-alvo

A empresa administra dez condomínios, de dois a quatro blocos cada, num total de cerca de 960 unidades. Cada condomínio tem quatro porteiros em escala 12x36, ou seja, 40 porteiros. A sede, sob uma diretoria, tem um gerente de operações, dois supervisores (cinco condomínios cada), três atendentes e dois analistas administrativo-financeiros. O síndico de cada condomínio, eleito pelos condôminos, é o interlocutor da administradora e aparece como relação externa no organograma (Figura 1). O público-alvo reúne moradores de perfis variados, entre eles idosos e pessoas que não usam smartphone, além de síndicos, porteiros e a equipe da sede, o que pesa na escolha do canal de aviso, que não pode depender só de aplicativo.

**[Figura 1 – Organograma da Administradora Morada Central. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-01-organograma.png`]**

## 2.3 Processo atual de encomendas

As encomendas dependem de um caderno (Figura 2). O entregador chega à portaria, e o porteiro anota data, nome, bloco, apartamento e transportadora. O pacote vai para uma sala ou armário, sem posição definida. O morador é avisado pelo interfone quando o porteiro consegue, retira o pacote e nem sempre assina o caderno. Extravios e reclamações chegam à sede por telefone ou aplicativo de mensagens.

**[Figura 2 – Processo atual de encomendas (caderno). Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-02-processo-atual.png`]**

## 2.4 Problemas encontrados

A análise desse processo levou a sete problemas (Quadro 1).

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

Como não houve levantamento de campo, o texto não afirma a frequência desses problemas. Um artigo de opinião do setor associa a Black Friday e o fim de ano ao aumento das entregas e à pressão sobre as portarias (MACK, 2024), e nenhum número do setor é usado neste trabalho.

## 2.5 Justificativa e processo proposto


Os problemas se repetem nos dez condomínios e dependem de registro, rastreabilidade e comunicação, três pontos em que uma solução computacional padroniza o processo, reduz erros e gera dados. A operação offline atende às portarias com internet instável (P7), e a consolidação central dá à administradora uma visão de todos os condomínios (P6). No processo proposto (Figura 3), o porteiro registra a encomenda, o sistema indica a posição na estante e gera o código, o morador é avisado, retira com o código, e as operações são sincronizadas com a central. Em relação ao caderno, o registro passa a ter campos obrigatórios e validados, a retirada exige um código de uso único, o aviso usa o canal cadastrado, com alternativa para quem não usa smartphone, e cada operação guarda data, hora e autor.

**[Figura 3 – Processo proposto. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-03-processo-proposto.png`]**
