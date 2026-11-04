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

> **Rascunho** redigido a partir do roteiro e dos arquivos do repositório (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Marcas `[ ... ]` indicam o que ainda precisa de fonte, data ou decisão. Figuras: inserir as imagens exportadas de `figuras/` nos pontos indicados.

# 4 ENGENHARIA DE SOFTWARE

Este capítulo descreve como a solução foi especificada, projetada e organizada para o desenvolvimento: requisitos, casos de uso, modelagem, arquitetura, processo ágil, qualidade e ferramentas.

## 4.1 Requisitos

O levantamento partiu do cenário da Administradora Morada Central (capítulo 2) e dos sete problemas identificados nele: extravios e entregas à pessoa errada (P1), falta de rastreabilidade (P2), sobrecarga do porteiro nos picos (P3), aviso falho ao morador (P4), acúmulo de volumes (P5), ausência de dados para a sede planejar equipe e espaço (P6) e internet instável em parte das portarias (P7). Como não houve levantamento de campo, os requisitos derivam do cenário e da análise do processo atual, não de entrevistas com usuários reais, o que é uma limitação do trabalho.

Foram definidos 12 requisitos funcionais (Quadro 2) e 8 não funcionais.

**Quadro 2 – Requisitos funcionais**

| ID | Requisito |
|---|---|
| RF01 | Registrar encomenda com unidade, destinatário, transportadora e tamanho |
| RF02 | Indicar automaticamente uma posição livre na estante |
| RF03 | Gerar código de retirada único, de 6 dígitos |
| RF04 | Avisar o morador pelo canal cadastrado (aplicativo, SMS ou interfone com código impresso) |
| RF05 | Registrar a retirada conferindo o código, com data, hora e nome de quem retirou |
| RF06 | Listar as pendências e buscar encomendas por unidade |
| RF07 | Exibir o mapa de ocupação da estante |
| RF08 | Cadastrar moradores e o canal de aviso de cada um |
| RF09 | Continuar operando sem conexão, guardando as operações para envio posterior |
| RF10 | Sincronizar as operações com a central sem duplicar registros |
| RF11 | Alertar encomendas pendentes há mais de 7 dias |
| RF12 | Gerar relatórios de dia de pico, ocupação e pendências por condomínio |

Fonte: elaborado pelos autores (2026).

Os não funcionais tratam de disponibilidade (a portaria não depende de internet), usabilidade (registro em cerca de 30 segundos, ainda não medido), privacidade e segurança, portabilidade (C99 com gcc, verificada em Windows e Linux), escalabilidade (incluir um condomínio sem alterar o código), rastreabilidade (toda operação tem identificador, data e hora) e acessibilidade (aviso alternativo para quem não usa smartphone). Uma matriz no repositório liga cada requisito aos problemas, casos de uso e histórias.

## 4.2 Casos de uso

Os requisitos foram agrupados em oito casos de uso: registrar encomenda (UC01), avisar morador (UC02), retirar encomenda (UC03), consultar pendências (UC04), manter moradores (UC05), sincronizar com a central (UC06), consolidar operações (UC07) e emitir relatórios (UC08). Os atores são o porteiro, o morador, o supervisor da administradora e dois sistemas: a central e o serviço de avisos (Figura 4).

**[Figura 4 – Diagrama de casos de uso. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-04-casos-de-uso.png`]**

## 4.3 Modelagem

A modelagem usou a UML `[FONTE A VERIFICAR: referência sobre UML]`. O modelo de domínio (Figura 5) organiza condomínio, bloco, unidade, morador, funcionário e encomenda, com três enumerações: status (pendente, retirada ou devolvida), canal de aviso (aplicativo, SMS ou interfone) e tipo de operação (registro, retirada ou devolução). O diagrama de atividade (Figura 6) mostra o registro: validação, escolha da posição pelo tamanho do volume, geração do código, gravação como pendente, inclusão na fila de sincronização e aviso ao morador. O de sequência (Figura 7) mostra que a portaria só envia a fila quando está online e que a central aplica cada operação uma única vez.

**[Figura 5 – Modelo de domínio. Figura 6 – Atividade: registrar encomenda. Figura 7 – Sequência: sincronização e consolidação. Fonte: elaboradas pelos autores (2026). Arquivos: `figuras/figura-05-classes-dominio.png`, `figura-06-atividade-registrar-encomenda.png`, `figura-07-sequencia-sincronizacao.png`]**

## 4.4 Arquitetura e decisões

O sistema completo tem duas partes: em cada condomínio, um nó de portaria capaz de operar sem internet, com armazenamento local e fila de sincronização; e um servidor central, com API e banco relacional, que recebe as operações em lotes e alimenta o painel da administradora. O protótipo representa essas partes com dois executáveis, `portaria` e `central`, e arquivos no lugar do banco e da rede. O nó é organizado em camadas (console, regras de negócio, persistência e fila), e cada camada só chama a de baixo.

As decisões estão registradas como ADR no repositório: banco MySQL 8 no servidor central (ADR-001), arquivos CSV em ASCII no protótipo (ADR-002), sincronização assíncrona com operações idempotentes (ADR-003), Scrum simplificado (ADR-004), diagramas como código (ADR-005) e endereçamento 10.X.Y.0/24 (ADR-006). A de maior impacto é a ADR-003: como parte das portarias tem internet instável (P7), cada evento vira uma operação com identificador único, guardada na fila, e a central ignora qualquer identificador já aplicado, de modo que reenviar um lote não duplica registros.

## 4.5 Processo de desenvolvimento

O desenvolvimento seguiu o Scrum simplificado, que organiza o trabalho em ciclos iterativos com inspeção e adaptação e define os papéis de Product Owner, Scrum Master e Developers (SCHWABER; SUTHERLAND, 2020). O grupo tem cinco integrantes: Lucas Ribeiro Tomiossi Kribely é o Product Owner e também o líder responsável pela postagem final, Daniel Augusto Amarante da Silva é o Scrum Master, e os demais integram o time de desenvolvimento. A revisão e a retrospectiva de cada sprint são por mensagem escrita no grupo, às sextas, 19h, e consolidadas no arquivo da sprint.

As sprints 0 a 3 foram executadas em um ciclo único em 29/10/2026 (datas do histórico do Git) e produziram a base do projeto, a portaria funcionando, o sistema distribuído e os relatórios com os testes; a sprint 4 vai de 29/10 a 06/11 e a sprint 5, de 07/11 a 13/11, ambas dedicadas ao documento e à entrega. O backlog tem 16 histórias de usuário com critérios Dado, Quando, Então; as 15 primeiras foram implementadas, e a US16, opcional (devolução de volumes), ficou como evolução futura por depender de um prazo ainda não definido.

A definição de pronto exige compilação sem avisos com `-Wall -Wextra -pedantic`, testes passando, funções comentadas, algoritmos com pseudocódigo e fluxograma, critérios de aceitação atendidos, rastreabilidade atualizada e revisão por outro integrante. As histórias estão implementadas e testadas, mas a revisão por pares ainda não foi concluída `[ATUALIZAR após a revisão]`.

## 4.6 Qualidade e testes

O protótipo tem nove conjuntos de testes automatizados, com `assert.h`, que cobrem entrada e datas, estante, código, retirada, persistência, moradores, sincronização, consolidação e relatórios. O `make test` compila e executa todos, e uma asserção que falha interrompe o comando. Na última verificação, a compilação não gerou avisos e os nove conjuntos passaram. Um teste específico processa o mesmo arquivo de operações duas vezes e confirma que nada é duplicado, o que comprova o comportamento da ADR-003.

## 4.7 Ferramentas e tecnologias

O protótipo foi desenvolvido em C (padrão C99) com gcc 16.2.0 e GNU Make 4.4.1, com o script `build.bat` no Windows. Usaram-se Git 2.54.0 para versionamento, MySQL 8.4.13 em contêiner Docker para executar os scripts do banco, PlantUML e Mermaid para os diagramas e o Cisco Packet Tracer 9.0.1 para a rede. O Claude Code foi usado como assistente de programação, com autorização da Prof.ª Eliana `[CONFIRMAR se o grupo quer mencionar]`.

## 4.8 Considerações do capítulo

A especificação partiu de um cenário fictício, sem levantamento de campo, e produziu requisitos, casos de uso, modelos e decisões rastreáveis até as histórias implementadas. A principal decisão técnica, a sincronização assíncrona com operações idempotentes, permite que a portaria funcione sem internet. Restam a revisão por pares das histórias e a conferência dos papéis do Scrum.
