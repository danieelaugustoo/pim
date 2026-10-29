# Integração da solução (Etapa 8)

> **Roteiro de tópicos** para o capítulo 9. O grupo redige o texto final. A ideia é seguir **uma encomenda do começo ao fim** e mostrar onde cada disciplina do PIM aparece. O diagrama está em [`diagramas/fluxo-ponta-a-ponta.mmd`](diagramas/fluxo-ponta-a-ponta.mmd) (Mermaid, ainda não renderizado).

## 1. A encomenda de exemplo

> Uma caixa chega à portaria do condomínio P01 para a unidade A-12. A portaria está sem internet.

Os dados de exemplo são fictícios (`05-programa-c/dados/exemplo/`).

## 2. O caminho, passo a passo

| # | O que acontece | Disciplina / etapa | Onde está no projeto |
|---|---|---|---|
| 1 | O problema existe: caderno gera extravio, entrega errada e sobrecarga | Organização e pesquisa (Etapas 1 e 2) | `01-organizacao/`, `02-pesquisa/problema-e-objetivos.md` |
| 2 | A necessidade vira requisito e história de usuário | Engenharia de Software e Scrum (Etapa 3) | `03-engenharia-software/requisitos.md`, `scrum/backlog.md` |
| 3 | O porteiro registra: unidade, destinatário, transportadora, tamanho | Programação em C, validação de entrada (US01) | `05-programa-c/src/encomenda.c` |
| 4 | O sistema escolhe a posição na estante (matriz) | Algoritmo A1 (US02) | `src/estante.c`, `algoritmos/pseudocodigo.md` |
| 5 | O sistema gera um código único de 6 dígitos | Algoritmo A2 (US03) | `src/codigo.c` |
| 6 | O registro é gravado em arquivo; no sistema completo, no banco | Persistência (protótipo) e Banco de Dados (Etapa 4) | `src/persistencia.c`; `04-banco-de-dados/sql/` |
| 7 | O morador é avisado pelo canal que escolheu (app, SMS ou interfone) | Sistema distribuído e acessibilidade (US07, US08) | `src/aviso.c`; `07-.../analise.md`, seção 3 |
| 8 | Sem internet, a operação entra na fila e a portaria segue trabalhando | Sistema distribuído offline (US09, ADR-003) | `src/sincronizacao.c` |
| 9 | Com a conexão de volta, a fila é enviada à central | Redes: VPN, API na nuvem (US10, algoritmo A4) | `06-redes/nuvem-e-sistemas-distribuidos.md`; protótipo simula por arquivos |
| 10 | A central aplica cada operação **uma só vez** | Consolidação idempotente (US11, algoritmo A5, ADR-003) | `src/consolidacao.c` |
| 11 | O morador chega, informa o código; o porteiro confere e entrega | Algoritmo A3 (US04, US05) | `src/retirada.c` |
| 12 | A retirada também sobe à central | A4 e A5 de novo, com a operação RETIRADA | `src/sincronizacao.c`, `src/consolidacao.c` |
| 13 | A posição na estante é liberada | A1 e A3 (matriz) | `src/estante.c` |
| 14 | O supervisor vê pendências antigas, pico e ocupação | Relatórios, algoritmo A6 (US12 a US14) | `src/relatorio.c`; `dados/central/relatorio-consolidado.txt` |
| 15 | Um indicador responde à pergunta de pesquisa | Pesquisa e indicadores | `beneficios-e-indicadores.md` |

Atravessando todo o caminho: segurança e privacidade (`07-.../analise.md`), a infraestrutura de rede (`06-redes/`) e a qualidade (testes, US15).

## 3. Como os componentes se conectam

| Componente | Função | Conversa com |
|---|---|---|
| Nó da portaria (`portaria <n>`) | Funciona sem internet: registra, retira, avisa, guarda fila | Central (via fila de sincronização) |
| Fila de sincronização | Guarda as operações até haver conexão | Nó e rede |
| Rede (protótipo: arquivos em `dados/rede/`; sistema completo: VPN + API HTTPS) | Leva as operações até a central | Nó e central |
| Central (`central`) | Consolida sem duplicar e gera o relatório | Rede e banco |
| Banco de dados (sistema completo) | Guarda o consolidado e o histórico | Só a API |
| Serviço de aviso (simulado no protótipo) | Entrega o aviso ao morador | Nó ou API |

**Decisões de arquitetura que costuram tudo** (`03-engenharia-software/decisoes/`): armazenamento do protótipo em CSV (ADR-002), sincronização assíncrona com fila e idempotência pelo id da operação (ADR-003) e endereçamento 10.X.Y.0/24, que permite incluir um condomínio sem refazer a rede (ADR-006). O grupo deve citar os ADRs pelo número no texto.

## 4. O que é real e o que é simulado

| Parte | No trabalho |
|---|---|
| Registro, estante, código, retirada, fila, consolidação, relatórios | **Funcionando** e testados no protótipo em C |
| Aviso ao morador | **Simulado** (mensagem na tela e registro em arquivo) |
| Rede entre portaria e central | **Simulada** por arquivos |
| Banco MySQL | Scripts **executados** em um MySQL 8.4.13 de teste; o protótipo em C não usa o banco |
| Rede física (VLANs, ACL, VPN) | Projetada; laboratório no Packet Tracer **a montar pelo grupo** |

Essa tabela deve aparecer no texto, de forma clara, para o leitor não achar que tudo foi implantado.

## 5. Pontos para a apresentação

- Mostrar o caminho com a encomenda de exemplo: registrar, ficar offline, sincronizar, rodar a central **duas vezes** e mostrar que nada duplica.
- Mostrar o mapa da estante e o relatório com as pendências antigas.
- Explicar que a mesma regra de negócio aparece em C, em SQL e na rede.
