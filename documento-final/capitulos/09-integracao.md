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
| Figura 16: fluxo ponta a ponta | `08-integracao/diagramas/fluxo-ponta-a-ponta.mmd` |
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

Este capítulo reúne o que foi desenvolvido nos capítulos anteriores seguindo o caminho de uma encomenda, e apresenta o plano de implantação, os benefícios esperados com seus indicadores, as limitações e a evolução futura.

## 9.1 Como os componentes se integram

Acompanha-se uma encomenda fictícia que chega à unidade A-12 de um condomínio quando a portaria está sem internet (Figura 16).

1. **Necessidade.** O problema do caderno (capítulo 2) virou requisitos e histórias de usuário (capítulo 4).
2. **Registro.** O porteiro informa unidade, destinatário, transportadora e tamanho. O sistema escolhe a posição na estante (A1) e gera o código único (A2) (capítulo 6).
3. **Gravação e aviso.** O registro é gravado em arquivo no protótipo e, no sistema completo, no banco relacional (capítulo 5). O morador é avisado pelo canal escolhido: aplicativo, SMS ou interfone com código impresso (capítulo 8).
4. **Operação offline e sincronização.** Sem internet, a operação entra na fila e a portaria continua trabalhando. Quando a conexão volta, a fila é enviada à central (A4), por VPN e API em HTTPS no sistema completo (capítulo 7), e a central aplica cada operação uma única vez (A5).
5. **Retirada.** O morador informa o código; o porteiro o confere em até três tentativas, registra quem retirou, a data e a hora, e a posição é liberada (A3). A retirada também sobe à central.
6. **Relatórios.** O supervisor vê as pendências com mais de 7 dias, o dia de pico e a ocupação (A6), que alimentam os indicadores.

**[Figura 16 – Fluxo ponta a ponta de uma encomenda. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-16-fluxo-ponta-a-ponta.png`]**

O Quadro 7 deixa claro o que foi construído e o que é simulado ou projetado.

**Quadro 7 – O que é real e o que é simulado**

| Parte | Situação |
|---|---|
| Registro, estante, código, retirada, fila, consolidação e relatórios | Funcionando e testados no protótipo em C |
| Aviso ao morador e rede entre portaria e central | Simulados (tela, arquivos) |
| Banco MySQL | Scripts executados em servidor de teste; o protótipo não se conecta a ele |
| Rede física (VLANs, ACL) | Projetada e testada no Packet Tracer 9.0.1 (15 testes, todos como esperado) |
| VPN | Apenas no diagrama |

Fonte: elaborado pelos autores (2026).

## 9.2 Plano de implantação

Propõe-se uma implantação em ondas, com um condomínio-piloto por duas semanas antes de levar a solução aos dez condomínios; piloto, prazos e responsáveis são decisões da administradora. A preparação inclui a infraestrutura mínima (computador com nobreak, rede conforme as VLANs, acesso à central e cópias de segurança), o cadastro de moradores e canais de aviso e, no primeiro dia, o lançamento das pendências do caderno, para que a estante e o sistema comecem iguais. Nos primeiros dias, com o caderno ainda em uso, mede-se a linha de base dos indicadores.

O treinamento dos porteiros é curto, com uma cartilha de uma página: registrar, conferir o aviso, retirar com código e nome, ver o mapa e as pendências antigas e continuar normalmente se a internet cair. Os moradores recebem um comunicado sobre o código, o canal de aviso e a alternativa para quem não usa smartphone. Se o computador falhar, os registros vão para formulário de papel e são lançados depois. A expansão só ocorre se, ao fim do piloto, os porteiros registrarem sem recorrer ao caderno, a estante e o mapa coincidirem e os indicadores não piorarem.

## 9.3 Benefícios esperados e indicadores

Os benefícios são esperados, não medidos: menos extravios e entregas erradas, menos tempo de busca e de registro, moradores avisados mais rápido, operação contínua sem internet, visão única dos dez condomínios, cobrança de retirada pelos alertas de pendências antigas e melhor dimensionamento da equipe. Os indicadores propostos estão no Quadro 8. Sem levantamento de campo, a linha de base ("antes") seria medida no piloto, e as metas ainda precisam ser definidas.

**Quadro 8 – Indicadores propostos**

| Indicador | Como medir | Antes | Meta |
|---|---|---|---|
| Extravios por mês | Encomendas registradas como não localizadas | A medir no piloto | `[A DEFINIR]` |
| Tempo entre chegada e retirada | Média de (retirada − recebimento) | A medir no piloto | `[A DEFINIR]` |
| Moradores avisados em até 15 minutos | Avisos em até 15 min ÷ registros | A medir no piloto | `[A DEFINIR]` |
| Pendências com mais de 7 dias | Relatório de pendências antigas | A medir no piloto | `[A DEFINIR]` |

Fonte: elaborado pelos autores (2026).

O protótipo já produz as pendências antigas, o dia de pico e a ocupação; com dados fictícios, o relatório consolidado de 29/10/2026 mostrou 2 pendências antigas e 11 pendentes entre 14 encomendas, usados só para demonstração.

## 9.4 Discussão

A comparação com soluções existentes (aplicativos de gestão condominial, armários inteligentes e portaria remota) depende de pesquisa com fontes verificadas `[A PREENCHER após verificar as fontes e preencher a matriz de trabalhos relacionados]`. O diferencial pretendido é reunir a operação sem internet, o aviso alternativo para quem não usa smartphone e a consolidação de vários condomínios, mas isso só pode ser afirmado em relação a produtos reais depois dessa pesquisa.

## 9.5 Limitações

No protótipo, a rede e o aviso são simulados, não há interface gráfica, login nem perfis, o código de retirada fica em texto e é visível na tela do porteiro, a capacidade é fixa e os dados são fictícios. No projeto, a rede foi testada só no simulador (sem a VPN), equipamentos e custos não foram cotados, não houve levantamento de campo e a devolução de volumes não foi implementada.

## 9.6 Evolução futura

As evoluções possíveis, cada uma com seu pré-requisito, são: API real em HTTPS no lugar dos arquivos (servidor na nuvem); conexão ao banco MySQL, com hash do código; aplicativo do morador e avisos por aplicativo de mensagens (API, autenticação e consentimento); painel de indicadores; perfis, login e autenticação em dois fatores; devolução de volumes (prazo definido pela administradora); telas acessíveis (WCAG); e armários inteligentes, com revisão de privacidade.

## 9.7 Considerações do capítulo

A solução integra requisitos, regras de negócio em C, banco relacional, comunicação assíncrona entre portaria e central e cuidados de privacidade e acessibilidade em um fluxo, com partes funcionando e partes simuladas ou projetadas. Os benefícios são hipóteses, e medi-los depende de um piloto.
