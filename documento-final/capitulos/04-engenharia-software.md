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

Este capítulo descreve como a solução de gestão de encomendas foi especificada, projetada e organizada para o desenvolvimento. São apresentados os requisitos, os casos de uso, a modelagem, a arquitetura e as decisões que a sustentam, o processo ágil adotado, as histórias de usuário e as ferramentas empregadas.

## 4.1 Requisitos

O levantamento partiu do cenário da Administradora Morada Central, organização fictícia descrita no capítulo 2, e dos sete problemas identificados nele: extravios e entregas à pessoa errada (P1), falta de rastreabilidade (P2), sobrecarga do porteiro nos períodos de pico (P3), aviso falho ao morador (P4), acúmulo de volumes (P5), ausência de dados para a sede planejar equipe e espaço (P6) e internet instável em parte das portarias (P7). Como não foi realizado levantamento de campo, os requisitos derivam do cenário e da análise do processo atual, e não de entrevistas com usuários reais. Essa é uma limitação do trabalho.

Foram definidos 12 requisitos funcionais e 8 não funcionais. Os funcionais estão no Quadro 1.

**Quadro 1 – Requisitos funcionais**

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

Os requisitos não funcionais tratam de disponibilidade (a portaria não depende de internet), usabilidade (registro em cerca de 30 segundos), privacidade e segurança (dados mínimos, acesso por perfil e código de uso único), portabilidade (compilação com gcc em C99), escalabilidade (incluir um condomínio sem alterar o código), rastreabilidade (toda operação tem identificador único, data e hora) e acessibilidade (aviso alternativo para quem não usa smartphone). A meta de 30 segundos ainda não foi medida com usuários, e a portabilidade foi verificada apenas em Windows. Cada requisito foi ligado aos problemas que trata, aos casos de uso e às histórias de usuário em uma matriz de rastreabilidade mantida no repositório.

## 4.2 Casos de uso

Os requisitos foram agrupados em oito casos de uso: registrar encomenda (UC01), avisar morador (UC02), retirar encomenda (UC03), consultar pendências (UC04), manter moradores (UC05), sincronizar com a central (UC06), consolidar operações (UC07) e emitir relatórios (UC08). O registro de encomenda inclui o aviso ao morador. Os atores são o porteiro, que opera a portaria, o morador, que recebe o aviso e retira o volume com o código, o supervisor da administradora, que consulta relatórios, e dois sistemas: a central, que consolida os dados, e o serviço de avisos. A Figura 4 apresenta o diagrama.

**[Figura 4 – Diagrama de casos de uso. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-04-casos-de-uso.png`]**

## 4.3 Modelagem

A modelagem usou a UML `[FONTE A VERIFICAR: referência sobre UML]`. O modelo de domínio (Figura 5) organiza as entidades condomínio, bloco, unidade, morador, funcionário e encomenda, com três enumerações: o status da encomenda (pendente, retirada ou devolvida), o canal de aviso (aplicativo, SMS ou interfone) e o tipo de operação (registro, retirada ou devolução). O diagrama de atividade do registro (Figura 6) mostra o fluxo desde a entrada dos dados até a gravação: validação, escolha da posição na estante conforme o tamanho do volume, geração do código, gravação com status pendente, inclusão da operação na fila de sincronização e aviso ao morador. O diagrama de sequência (Figura 7) mostra a sincronização: a portaria copia as operações da fila para a rede apenas quando está online, e a central aplica cada operação uma única vez. A encomenda passa por um ciclo de vida simples: nasce pendente, ocupa uma posição na estante e termina retirada (com a posição liberada) ou devolvida.

**[Figura 5 – Modelo de domínio. Figura 6 – Atividade: registrar encomenda. Figura 7 – Sequência: sincronização e consolidação. Fonte: elaboradas pelos autores (2026). Arquivos: `figuras/figura-05-classes-dominio.png`, `figura-06-atividade-registro.png`, `figura-07-sequencia-sincronizacao.png`]**

## 4.4 Arquitetura e decisões

O sistema completo foi projetado em duas partes. Em cada condomínio funciona um nó da portaria, capaz de operar sem internet, com armazenamento local e uma fila de sincronização. Um servidor central, com API e banco relacional, recebe as operações em lotes e guarda os dados de todos os condomínios, e um painel da administradora consulta relatórios. O protótipo desenvolvido representa essas partes com dois executáveis, `portaria` e `central`, e com arquivos no lugar do banco e da rede. O nó da portaria é organizado em camadas: interface de console, regras de negócio, persistência e fila de sincronização, e cada camada só chama a de baixo.

As principais decisões foram registradas como decisões de arquitetura (ADR), resumidas no Quadro 2.

**Quadro 2 – Decisões de arquitetura**

| ADR | Decisão |
|---|---|
| ADR-001 | Banco relacional (MySQL 8) no servidor central; bancos NoSQL apenas discutidos |
| ADR-002 | Dados do protótipo em arquivos CSV separados por ponto e vírgula, em ASCII |
| ADR-003 | Sincronização assíncrona com fila de operações idempotentes, identificadas por código único |
| ADR-004 | Scrum com sprints curtas e cerimônias simplificadas |
| ADR-005 | Diagramas escritos como código (PlantUML e Mermaid) |
| ADR-006 | Endereçamento de rede 10.X.Y.0/24 |

Fonte: elaborado pelos autores (2026).

A decisão de maior impacto é a ADR-003. Como parte das portarias tem internet instável (P7), a portaria não pode parar quando a conexão cai. Cada evento vira uma operação com identificador único, guardada na fila, e a central ignora qualquer identificador que já tenha aplicado. Assim, reenviar um lote não duplica registros.

## 4.5 Processo de desenvolvimento

O desenvolvimento seguiu o Scrum, em versão simplificada `[FONTE A VERIFICAR: referência sobre Scrum]`. O trabalho foi organizado em sprints, com backlog de histórias de usuário e critérios de aceitação no formato Dado, Quando, Então. As sprints 0 a 3 produziram, respectivamente, a base do projeto, a portaria funcionando, o sistema distribuído e os relatórios com a qualidade; as sprints 4 e 5 são dedicadas ao documento e à entrega `[DATAS DAS SPRINTS A CONFIRMAR]`. O grupo tem cinco integrantes, com líder responsável pela postagem final, e os papéis de Product Owner e Scrum Master foram adotados de forma simplificada `[TITULARES A DEFINIR]`. A revisão e a retrospectiva de cada sprint são registradas por mensagem escrita no grupo, às sextas-feiras, e consolidadas no arquivo de cada sprint.

O backlog reúne 16 histórias de usuário (US01 a US16). As 15 primeiras foram implementadas; a US16, opcional, que trata da devolução de volumes, ficou como evolução futura por depender de um prazo ainda não definido. O Quadro 3 resume a entrega por sprint.

**Quadro 3 – Histórias por sprint**

| Sprint | Meta | Histórias |
|---|---|---|
| 1 | Portaria funcionando | US01 a US06: registrar, indicar posição, gerar código, retirar, listar e buscar, salvar em arquivo |
| 2 | Sistema distribuído | US07 a US11: moradores, aviso, registro sem internet, sincronização e consolidação sem duplicidade |
| 3 | Relatórios e qualidade | US12 a US15: mapa da estante, pendências antigas, pico e ocupação, testes automatizados |

Fonte: elaborado pelos autores (2026).

A definição de pronto exige: compilação sem avisos com as opções `-Wall -Wextra -pedantic`, testes passando, funções comentadas, algoritmos principais com pseudocódigo e fluxograma, critérios de aceitação atendidos, rastreabilidade atualizada e revisão por outro integrante. Até o momento, as histórias estão implementadas e testadas, mas a revisão por pares ainda não foi concluída `[ATUALIZAR após a revisão]`.

## 4.6 Qualidade e testes

O protótipo possui nove conjuntos de testes automatizados, escritos com a biblioteca `assert.h`, que cobrem utilitários de entrada e datas, alocação na estante, geração e conferência do código, registro e retirada, persistência em arquivo, cadastro de moradores, sincronização, consolidação e relatórios. O comando `make test` compila e executa todos; uma asserção que falha interrompe o comando com erro e indica o teste. Na última verificação, a compilação não gerou avisos e os nove conjuntos passaram. A consolidação tem um teste específico que processa o mesmo arquivo de operações duas vezes e confirma que nada é duplicado, o que comprova o comportamento esperado da ADR-003.

## 4.7 Ferramentas e tecnologias

O Quadro 4 relaciona os materiais utilizados.

**Quadro 4 – Ferramentas e tecnologias**

| Ferramenta | Finalidade |
|---|---|
| Linguagem C (padrão C99) e compilador gcc 16.2.0 | Desenvolvimento do protótipo |
| GNU Make 4.4.1 e script `build.bat` | Compilação e execução dos testes |
| Git 2.54.0 | Controle de versão |
| MySQL 8.4.13 (contêiner Docker) | Execução dos scripts do banco de dados |
| PlantUML e Mermaid | Diagramas como código |
| Cisco Packet Tracer | Simulação da topologia de rede `[VERSÃO A CONFIRMAR]` |
| Claude Code | Assistente de programação usado no desenvolvimento `[CONFIRMAR se o grupo quer mencionar]` |

Fonte: elaborado pelos autores (2026).

## 4.8 Considerações do capítulo

A especificação partiu de um cenário fictício, sem levantamento de campo, e produziu requisitos, casos de uso, modelos e decisões de arquitetura rastreáveis até as histórias implementadas. A principal decisão técnica, a sincronização assíncrona com operações idempotentes, permite que a portaria funcione sem internet. As pendências são a revisão por pares das histórias e a definição formal dos papéis do Scrum.
