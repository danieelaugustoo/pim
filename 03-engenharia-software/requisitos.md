# Requisitos (Etapa 3)

> Roteiro de tópicos para o capítulo 4. Base: `PLANO.md`, seção 9.3.

## 1. Atores

| Ator | Tipo | Papel |
|---|---|---|
| Porteiro | Principal | Opera a portaria: registra, entrega e consulta encomendas |
| Morador | Secundário | Recebe o aviso e retira a encomenda com o código |
| Supervisor da administradora | Secundário | Consolida operações e consulta relatórios |
| Central | Sistema | Servidor que consolida os dados das portarias |
| Serviço de avisos | Sistema externo | Entrega o aviso por app ou SMS |

## 2. Requisitos funcionais

| ID | Requisito | Prioridade |
|---|---|---|
| RF01 | Registrar encomenda com unidade, destinatário, transportadora e tamanho | Alta |
| RF02 | Indicar automaticamente uma posição livre na estante | Alta |
| RF03 | Gerar código de retirada único, de 6 dígitos | Alta |
| RF04 | Avisar o morador pelo canal cadastrado (app, SMS ou interfone com código impresso) | Alta |
| RF05 | Registrar a retirada conferindo o código, com data, hora e nome de quem retirou | Alta |
| RF06 | Listar as pendências e buscar encomendas por unidade | Alta |
| RF07 | Exibir o mapa de ocupação da estante | Média |
| RF08 | Cadastrar moradores e o canal de aviso de cada um | Alta |
| RF09 | Continuar operando sem conexão, guardando as operações para envio posterior | Alta |
| RF10 | Sincronizar as operações com a central sem duplicar registros | Alta |
| RF11 | Alertar encomendas pendentes há mais de 7 dias | Média |
| RF12 | Gerar relatórios de dia de pico, ocupação e pendências por condomínio | Média |

> A prioridade é uma proposta de trabalho, derivada da sprint em que cada história é entregue (Sprints 1 e 2 = Alta; Sprint 3 = Média). O grupo pode ajustar.

## 3. Requisitos não funcionais

| ID | Categoria | Requisito |
|---|---|---|
| RNF01 | Disponibilidade | A operação da portaria não depende de internet |
| RNF02 | Usabilidade | Registrar uma encomenda leva no máximo cerca de 30 segundos |
| RNF03 | Privacidade | Só os dados pessoais necessários, com acesso por perfil (LGPD) |
| RNF04 | Segurança | Código de uso único, não exibido a terceiros |
| RNF05 | Portabilidade | O protótipo compila no Windows e no Linux com gcc (C99) |
| RNF06 | Escalabilidade | Incluir um condomínio sem alterar o código |
| RNF07 | Rastreabilidade | Toda operação tem id único, data, hora e autor |
| RNF08 | Acessibilidade | Aviso alternativo para quem não usa smartphone |

## 4. Matriz de rastreabilidade dos requisitos

Proposta de ligação entre problema da organização, requisito, caso de uso e história. A ligação com os problemas (P1 a P7) é interpretação do grupo e pode ser revista.

| Requisito | Problemas tratados | Casos de uso | Histórias |
|---|---|---|---|
| RF01 | P1, P2 | UC01 | US01 |
| RF02 | P5 | UC01 | US02 |
| RF03 | P1 | UC01 | US03 |
| RF04 | P4 | UC02 | US08 |
| RF05 | P1, P2 | UC03 | US04 |
| RF06 | P2 | UC04 | US05 |
| RF07 | P5 | UC04 | US12 |
| RF08 | P4 | UC05 | US07 |
| RF09 | P7 | UC06 | US06, US09 |
| RF10 | P6, P7 | UC06, UC07 | US10, US11 |
| RF11 | P5 | UC08 | US13 |
| RF12 | P3, P6 | UC08 | US14 |

Requisitos não funcionais atendidos por: RNF01 (US09, ADR-002, ADR-003); RNF05 (US15 e `05-programa-c/`); RNF06 (ADR-006); RNF07 (ADR-003); RNF03, RNF04 e RNF08 (`07-seguranca-privacidade-acessibilidade/`).
