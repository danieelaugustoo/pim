# 4 Engenharia de software (roteiro, cerca de 4 páginas, Etapa 3)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo". Este capítulo também abriga os **métodos** (Scrum) e os **materiais** (ferramentas) exigidos pelo manual.

**Fontes no repositório:** `03-engenharia-software/` (requisitos, casos de uso, arquitetura, ferramentas, decisões, Scrum, sprints, diagramas).

## Tópicos

| # | Tópico | Origem |
|---|---|---|
| 4.1 | Levantamento e requisitos funcionais e não funcionais (RF01 a RF12, RNF01 a RNF08) | `requisitos.md` |
| 4.2 | Casos de uso (UC01 a UC08) | `casos-de-uso.md` |
| 4.3 | Arquitetura: nó de portaria, central, camadas e fluxo de dados | `arquitetura.md` |
| 4.4 | Decisões de arquitetura (ADR-001 a ADR-006), resumidas em tabela | `decisoes/` |
| 4.5 | Modelagem UML (casos de uso, classes, atividade, sequência, estados) | `diagramas/*.puml` |
| 4.6 | Processo Scrum: papéis, cerimônias, sprints de 1 semana, definição de pronto | `scrum/papeis-e-cerimonias.md`, `scrum/definicao-de-pronto.md` |
| 4.7 | Backlog e histórias de usuário (US01 a US16) com critérios de aceitação | `scrum/backlog.md` |
| 4.8 | Execução das sprints 0 a 3 (entregas e verificações) | `scrum/sprints/sprint-00.md` a `sprint-03.md` |
| 4.9 | Ferramentas e tecnologias usadas (materiais) | `ferramentas.md` |
| 4.10 | Qualidade: testes automatizados e rastreabilidade | `sprint-03.md`, `00-projeto/rastreabilidade.md` |

## Figuras e tabelas

| Item | Arquivo de origem |
|---|---|
| Figura 04: diagrama de casos de uso | `diagramas/casos-de-uso.puml` |
| Figura 05: classes de domínio | `diagramas/classes-dominio.puml` |
| Figura 06: atividade de registro da encomenda | `diagramas/atividade-registrar-encomenda.puml` |
| Figura 07: sequência da sincronização | `diagramas/sequencia-sincronizacao.puml` |
| Figura 08 (opcional): estados da encomenda | `diagramas/estados-encomenda.puml` |
| Tabela: requisitos × histórias (rastreabilidade) | `requisitos.md`, seção de rastreabilidade |
| Tabela: sprints, metas e entregas | `scrum/sprints/` |
| Tabela: ADRs (decisão e motivo) | `decisoes/` |

## O que depende do grupo

- [ ] **Integrantes, Product Owner e Scrum Master**: `papeis-e-cerimonias.md` tem 11 campos `[A DEFINIR]`.
- [ ] **Datas reais das sprints** (`[DATA A DEFINIR]` em todas) e a **retrospectiva** de cada uma.
- [ ] **Revisão por outro integrante** das histórias US01 a US15 (a definição de pronto exige; hoje estão "Feito, falta revisão").
- [ ] Renderizar os diagramas PlantUML e exportar os PNG.
- [ ] Decidir se o histórico do Git (commits e tags) entra como evidência.

## Cuidados

- Não afirmar que o Scrum foi praticado com cerimônias reais se o grupo não as fez; descrever como foi adaptado.
- Citar Scrum e UML só com fonte verificada.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro e dos arquivos do repositório (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Marcas `[ ... ]` indicam o que ainda precisa de fonte, data ou decisão.

# 4 ENGENHARIA DE SOFTWARE

Este capítulo descreve como a solução foi especificada, projetada e organizada para o desenvolvimento: requisitos, casos de uso, modelagem, arquitetura, processo ágil, qualidade e ferramentas.

## 4.1 Requisitos


O levantamento partiu do cenário da Administradora Morada Central e dos sete problemas identificados no capítulo 2 (P1 a P7). Sem levantamento de campo, os requisitos derivam do cenário e da análise do processo atual, e não de entrevistas com usuários, o que limita o trabalho.

Foram definidos 12 requisitos funcionais e 8 não funcionais. Os funcionais cobrem o registro da encomenda (RF01), a posição na estante (RF02), o código de retirada de 6 dígitos (RF03), o aviso ao morador (RF04), a retirada com confirmação do porteiro (RF05), as pendências e a busca por unidade (RF06), o mapa da estante (RF07), o cadastro de moradores (RF08), a operação sem conexão (RF09), a sincronização sem duplicar registros (RF10), o alerta de pendências com mais de 7 dias (RF11) e os relatórios (RF12). Os não funcionais tratam de disponibilidade (a portaria não depende de internet), usabilidade (registro em cerca de 30 segundos, ainda não medido), privacidade e segurança, portabilidade (C99 com gcc, verificada em Windows e Linux), escalabilidade, rastreabilidade (toda operação tem identificador, data e hora) e acessibilidade (aviso alternativo para quem não usa smartphone).

## 4.2 Casos de uso


Os requisitos se agrupam em oito casos de uso: registrar encomenda, avisar morador, retirar encomenda, consultar pendências, manter moradores, sincronizar com a central, consolidar operações e emitir relatórios. Os atores são o porteiro, o morador, o supervisor e dois sistemas, a central e o serviço de avisos (Figura 4).

## 4.3 Modelagem

A modelagem usou a UML `[FONTE A VERIFICAR: referência sobre UML]`. O diagrama de sequência (Figura 5) mostra que a portaria só envia a fila quando está online e que a central aplica cada operação uma única vez. O modelo de domínio, com condomínio, bloco, unidade, morador, funcionário e encomenda, e o diagrama de atividade do registro de encomenda estão em `03-engenharia-software/diagramas/`, no repositório do projeto.

**[Figura 4 – Diagrama de casos de uso. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-04-casos-de-uso.png`]**

**[Figura 5 – Diagrama de sequência: sincronização e consolidação. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-05-sequencia-sincronizacao.png`]**

## 4.4 Arquitetura e decisões


O sistema completo tem duas partes: em cada condomínio, um nó de portaria que opera sem internet, com armazenamento local e fila de sincronização, e um servidor central, com API e banco relacional, que recebe as operações em lotes e alimenta o painel da administradora. O protótipo representa essas partes com os executáveis `portaria` e `central` e usa arquivos no lugar do banco e da rede. As decisões de projeto foram registradas como ADR no repositório, e a mais importante é a ADR-003: como parte das portarias tem internet instável, cada evento vira uma operação de identificador único, guardada na fila, e a central ignora os identificadores já aplicados, de modo que reenviar um lote não duplica registros.

## 4.5 Processo de desenvolvimento


O desenvolvimento seguiu o Scrum simplificado (SCHWABER; SUTHERLAND, 2020). Dos cinco integrantes, Lucas Ribeiro Tomiossi Kribely é o Product Owner e o líder responsável pela postagem final, Daniel Augusto Amarante da Silva é o Scrum Master, e os demais formam o time de desenvolvimento. A revisão e a retrospectiva de cada sprint saem por mensagem escrita no grupo, às sextas, às 19h. As sprints 0 a 3 rodaram em um ciclo único em 29/10/2026 (datas do histórico do Git), e as sprints 4 e 5 foram dedicadas ao documento e à entrega. Das 16 histórias de usuário do backlog, 15 foram implementadas, e a US16, que trata da devolução de volumes, ficou como evolução futura porque depende de um prazo ainda não definido. A definição de pronto exige compilação sem avisos, testes passando, funções comentadas, critérios de aceitação atendidos e revisão por outro integrante, que ainda não terminou `[ATUALIZAR após a revisão]`.

## 4.6 Qualidade, testes e ferramentas


Os nove conjuntos de testes automatizados, escritos com `assert.h`, rodam com `make test` e foram aprovados (capítulo 6), e um deles confirma que processar o mesmo arquivo de operações duas vezes não duplica nada (ADR-003). O protótipo foi escrito em C99, compilado com gcc 16.2.0 e GNU Make 4.4.1, com `build.bat` para o Windows. O Git 2.54.0 controlou as versões, o MySQL 8.4.13, em contêiner Docker, executou os scripts do banco, PlantUML e Mermaid geraram os diagramas e o Cisco Packet Tracer 9.0.1 simulou a rede.
