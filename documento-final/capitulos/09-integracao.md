# 9 Integração da solução (roteiro, cerca de 2 páginas, Etapa 8)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo". Este capítulo também abriga a **discussão** exigida pelo manual (benefícios, limitações e comparação com os trabalhos relacionados).

**Fontes no repositório:** `08-integracao/`.

## Tópicos

| # | Tópico | Origem |
|---|---|---|
| 9.1 | Como os componentes se integram: a jornada de uma encomenda, da chegada à retirada | `integracao.md` |
| 9.2 | O que é real e o que é simulado | `integracao.md`, seção 4 |
| 9.3 | Plano de implantação: piloto, treinamento, comunicação, contingência, critérios de expansão | `implantacao.md` |
| 9.4 | Benefícios esperados e indicadores (apresentados como metas, não resultados) | `beneficios-e-indicadores.md` |
| 9.5 | Discussão: comparação com os trabalhos relacionados | `02-pesquisa/trabalhos-relacionados.md` (depende da pesquisa) |
| 9.6 | Limitações da solução | `limitacoes-e-evolucao.md`, seção 1 |
| 9.7 | Possibilidades de evolução futura | `limitacoes-e-evolucao.md`, seção 2 |

## Figuras e tabelas

| Item | Origem |
|---|---|
| Figura 15: fluxo ponta a ponta | `08-integracao/diagramas/fluxo-ponta-a-ponta.mmd` |
| Tabela: indicadores (como medir, fonte, antes, meta) | `beneficios-e-indicadores.md`, seção 3 |
| Tabela: real × simulado | `integracao.md`, seção 4 |
| Tabela: limitações × evolução | `limitacoes-e-evolucao.md` |

## O que depende do grupo

- [ ] Apresentar o "antes" dos indicadores como linha de base a medir no piloto (não há levantamento de campo).
- [ ] Definir metas realistas, sempre rotuladas como meta ou estimativa.
- [ ] Decidir piloto, prazos e responsáveis, ou apresentar a implantação como proposta genérica.
- [ ] Preencher a comparação com trabalhos relacionados (depende de fontes verificadas).

## Cuidados

- Não afirmar redução de extravios ou de tempo sem dados medidos.
- Ligar cada limitação a uma evolução possível.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro e de `08-integracao/` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. A comparação com trabalhos relacionados depende de fontes verificadas e está marcada como pendente.

# 9 INTEGRAÇÃO DA SOLUÇÃO

Este capítulo reúne o que foi desenvolvido nos capítulos anteriores seguindo o caminho de uma encomenda. Depois apresenta o plano de implantação, os benefícios esperados e seus indicadores, as limitações e a evolução futura.

## 9.1 Como os componentes se integram

Considere uma encomenda que chega à unidade A-12 de um condomínio quando a portaria está sem internet (Figura 13).

1. O problema do caderno (capítulo 2) virou requisitos e histórias de usuário (capítulo 4).
2. O porteiro informa unidade, destinatário, transportadora e tamanho. O sistema escolhe a posição na estante (A1) e gera o código único (A2) (capítulo 6).
3. O registro é gravado em arquivo no protótipo e, no sistema completo, no banco relacional (capítulo 5). O morador é avisado pelo canal escolhido: aplicativo, SMS ou interfone com código impresso (capítulo 8).
4. Sem internet, a operação entra na fila e a portaria continua trabalhando. Quando a conexão volta, a fila é enviada à central (A4), por VPN e API em HTTPS no sistema completo (capítulo 7), e a central aplica cada operação uma única vez (A5).
5. O morador mostra o código. O sistema acha a encomenda pendente que o usa, o porteiro confirma com o morador (em até três tentativas), registra quem retirou, a data e a hora, e a posição é liberada (A3). A retirada também sobe à central.
6. O supervisor vê as pendências com mais de 7 dias, o dia de pico e a ocupação (A6), que alimentam os indicadores.

**[Figura 13 – Fluxo ponta a ponta de uma encomenda. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-13-fluxo-ponta-a-ponta.png`]**

O Quadro 6 separa o que foi construído do que é simulado ou projetado.

**Quadro 6 – O que está construído e o que é simulado**

| Parte | Situação |
|---|---|
| Registro, estante, código, retirada, fila, consolidação e relatórios | Funcionando e testados no protótipo em C |
| Aviso ao morador e rede entre portaria e central | Simulados (tela e arquivos) |
| Banco MySQL | Scripts executados em servidor de teste; o protótipo não se conecta a ele |
| Rede física (VLANs e listas de acesso) | Projetada e testada no Packet Tracer 9.0.1 (15 testes, todos como esperado) |
| VPN | Apenas no diagrama |

Fonte: elaborado pelos autores (2026).

## 9.2 Plano de implantação

Propõe-se uma implantação em ondas, com um condomínio-piloto por duas semanas antes de levar a solução aos dez condomínios. A escolha do piloto, os prazos e os responsáveis cabem à administradora. A preparação inclui a infraestrutura mínima (computador com nobreak, rede conforme as VLANs, acesso à central e cópias de segurança) e o cadastro dos moradores e de seus canais de aviso. No primeiro dia, as pendências do caderno são lançadas no sistema, e nos primeiros dias, com o caderno ainda em uso, mede-se a linha de base dos indicadores.

O treinamento dos porteiros é curto, com uma cartilha de uma página, e os moradores recebem um comunicado sobre o código, o canal de aviso e a alternativa para quem não usa smartphone. Se o computador falhar, os registros vão para um formulário de papel. A expansão só acontece se, ao fim do piloto, os porteiros registrarem sem recorrer ao caderno, a estante e o mapa coincidirem e os indicadores não piorarem.

## 9.3 Benefícios esperados e indicadores

Os benefícios são esperados e não foram medidos: menos extravios e entregas erradas, menos tempo de busca e de registro, moradores avisados mais rápido, operação contínua sem internet, uma visão única dos dez condomínios, cobrança de retirada pelos alertas de pendências antigas e melhor dimensionamento da equipe. O Quadro 7 traz os indicadores propostos. Sem levantamento de campo, a linha de base seria medida no piloto, e as metas ainda precisam ser definidas.

**Quadro 7 – Indicadores propostos**

| Indicador | Como medir | Antes | Meta |
|---|---|---|---|
| Extravios por mês | Encomendas registradas como não localizadas | A medir no piloto | A definir no piloto |
| Tempo entre chegada e retirada | Média de (retirada − recebimento) | A medir no piloto | A definir no piloto |
| Moradores avisados em até 15 minutos | Avisos em até 15 min ÷ registros | A medir no piloto | A definir no piloto |
| Pendências com mais de 7 dias | Relatório de pendências antigas | A medir no piloto | A definir no piloto |

Fonte: elaborado pelos autores (2026).

O protótipo já produz as pendências antigas, o dia de pico e a ocupação (capítulo 6).

## 9.4 Discussão

Em relação às categorias da seção 3.6, os aplicativos e os armários inteligentes oferecem recursos que a proposta não tem, como a foto da encomenda, o QR code e a retirada sem depender da portaria. A proposta foi desenhada para três pontos que a pesquisa não encontrou descritos nas páginas consultadas: a operação da portaria sem internet, o aviso alternativo para quem não usa smartphone e a consolidação de vários condomínios em um relatório da administradora. Isso não permite afirmar que os produtos existentes não os ofereçam. A comparação tem poucas fontes, todas de divulgação comercial, e nenhum produto foi testado.

## 9.5 Limitações

No protótipo, a rede e o aviso são simulados, não há interface gráfica, login nem perfis, o código de retirada fica em texto na tela do porteiro, a capacidade é fixa e os testes usaram dados de exemplo. No projeto, a rede foi testada só no simulador e sem a VPN, equipamentos e custos não foram cotados, não houve levantamento de campo e a devolução de volumes não foi implementada.

## 9.6 Evolução futura

Entre as evoluções possíveis, cada uma com seu pré-requisito, estão uma API real em HTTPS no lugar dos arquivos (exige um servidor na nuvem), a conexão ao banco MySQL, com o hash do código, e o aplicativo do morador, com avisos por aplicativo de mensagens e um QR code no aviso para agilizar a leitura do código (exigem API, autenticação e consentimento). Também ficam o painel de indicadores, os perfis com login e autenticação em dois fatores, a devolução de volumes (depende de um prazo que a administradora precisa definir), telas acessíveis (WCAG) e armários inteligentes, com revisão de privacidade.
