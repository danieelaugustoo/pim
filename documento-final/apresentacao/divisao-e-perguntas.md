# Divisão da apresentação e perguntas prováveis

Proposta para 5 integrantes, em **cerca de 21 minutos** (ajustar ao tempo que a Prof.ª Eliana der). Cada bloco corresponde a uma matéria do PIM II. Os nomes ficam em branco até o grupo escolher.

| Bloco | Matéria e capítulos | Responsável | Tempo | Figuras do trabalho para mostrar |
|---|---|---|---|---|
| 1 | **Organização e pesquisa** (cap. 1, 2 e 3): o caderno, os 7 problemas, a pergunta de pesquisa, a solução e a comparação com o que existe | [a definir] | 3 min | Figuras 2 (processo atual) e 3 (processo proposto) |
| 2 | **Engenharia de software ágil** (cap. 4): Scrum, papéis, requisitos, casos de uso e a sincronização | [a definir] | 3 min | Figuras 4 (casos de uso) e 5 (sequência) |
| 3 | **Banco de dados** (cap. 5): DER, normalização, MySQL e a escolha pelo modelo relacional | [a definir] | 3 min | Figuras 6 (DER) e 7 (consulta SQL) |
| 4 | **Programação em C e demonstração** (cap. 6), com o roteiro de `roteiro-demonstracao.md` | [a definir] | 7 min | Figura 8 (fluxograma do A1) e o programa rodando |
| 5 | **Redes, segurança e fechamento** (cap. 7, 8, 9 e 10): topologia, VLANs, testes, privacidade, acessibilidade, limitações e conclusão | **Daniel** (roteiro em `bloco-5-redes-daniel.md`) | 5 min | Figuras 9 (topologia) e 10 (testes T2 e T6) |

## O que cada bloco precisa dizer

**Bloco 1.** Caderno gera extravios, entregas à pessoa errada e sobrecarga dos porteiros; 10 condomínios, cerca de 960 unidades, 40 porteiros. Pergunta: como uma solução com operação offline e sincronização central pode reduzir isso? Solução: nó em cada portaria que funciona sem internet e central que consolida. Comparação (3.6): aplicativos, armários e portaria remota existem; as páginas consultadas não informam operação sem internet nem consolidação de vários condomínios. Sem levantamento de campo.

**Bloco 2.** Scrum simplificado: Lucas é o Product Owner, Daniel o Scrum Master; 16 histórias, 15 implementadas (a devolução ficou para depois). 12 requisitos funcionais e 8 não funcionais. 8 casos de uso. Decisão mais importante (ADR-003): cada evento vira uma operação com identificador único, e a central ignora os já aplicados, então reenviar não duplica.

**Bloco 3.** 11 entidades, 3ª forma normal, 11 tabelas e 44 restrições nomeadas. O código de retirada fica só como resumo criptográfico (SHA-256). A chave da tabela de operações impede aplicar a mesma operação duas vezes. Os scripts rodaram em MySQL 8.4 (Docker), e os resultados batem com o relatório do programa em C. O protótipo em C usa arquivos e não se conecta ao banco. NoSQL só faria sentido no histórico de avisos, numa evolução futura.

**Bloco 4.** C99, só biblioteca padrão, sem avisos com `-Wall -Wextra -pedantic`; funções pequenas com o nome do módulo como prefixo; `fgets` com validação; 9 conjuntos de testes. Matriz `estante[4][12]`. A1 (alocação na estante), A3 (retirada por código com confirmação), A5 (consolidação idempotente). Depois, a demonstração. **Todos os cinco devem saber explicar** `estante_alocar_posicao`, `retirada_registrar` e `consolidacao_processar_portaria`.

**Bloco 5.** Rede projetada com 44 redes `10.X.Y.0/24`, 4 VLANs (portaria 10, CFTV 20, visitantes 30, gerência 99) e VPN no desenho. No Packet Tracer 9.0.1, 15 testes, todos como esperado (a portaria alcança a central, os visitantes não alcançam a portaria, a rede local continua sem a nuvem). Privacidade: LGPD, dados mínimos, retenção de 90 dias como decisão de projeto. Acessibilidade: interfone com código impresso para quem não usa smartphone; WCAG nível AA para as telas futuras. Limitações e evolução (API real, banco ligado, aplicativo do morador). Conclusão: viabilidade demonstrada, benefícios ainda não medidos, só um piloto mostra.

## Perguntas prováveis e respostas curtas

| Pergunta | Resposta |
|---|---|
| Por que arquivos CSV e não o banco? | Simplificação do protótipo (ADR-002). O MySQL foi modelado e testado à parte. |
| Como evita registrar a mesma operação duas vezes? | Cada operação tem identificador único (como `P01-000011`) e a central anota os já aplicados (A5). |
| E se a internet cair no meio do envio? | A fila só é esvaziada depois de copiada. Se falhar entre as duas etapas, repetir é seguro. |
| O código pode coincidir com o de outra encomenda? | Sim, cerca de 1 em 9.000 com 100 pendentes. Por isso o porteiro confirma unidade e destinatário com o morador, e há 3 tentativas. |
| O código aparece na tela do porteiro. Isso é seguro? | É uma limitação declarada. No sistema completo só o morador receberia o código, e o banco guardaria o resumo criptográfico. |
| O aviso e a rede são reais? | O aviso é simulado (tela e arquivo). A rede foi testada no Packet Tracer com `ping`, sem VPN nem HTTPS. |
| Por que uma matriz para a estante? | Cada linha é a estante de um bloco, cada coluna uma prateleira. Ela é reconstruída das pendentes ao abrir o programa, então há uma única fonte de verdade. |
| Por que MySQL? | Entidades muito relacionadas e regras de integridade (uma retirada por encomenda, uma aplicação por operação). ADR-001. |
| Por que 4 VLANs? | Para separar o tráfego por risco: portaria, CFTV, visitantes e gerência. |
| Os benefícios foram medidos? | Não. São esperados. Seria preciso um piloto, e as metas ficaram "a definir no piloto". |
| Por que não houve pesquisa com porteiros e moradores? | Não era obrigatória. O texto não afirma frequência dos problemas nem preferências dos moradores. |
| A devolução de volumes? | Não foi implementada: depende de um prazo que a administradora precisa definir (US16). |
| Vocês usaram inteligência artificial? | Respondam a verdade: a Prof.ª Eliana autorizou o uso, e o grupo revisou o trabalho e responde pelo conteúdo e pelo código. |
