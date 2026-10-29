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

Este capítulo reúne o que foi desenvolvido nos capítulos anteriores seguindo o caminho de uma encomenda, apresenta o plano de implantação proposto, os benefícios esperados e seus indicadores, e discute as limitações e as possibilidades de evolução.

## 9.1 Como os componentes se integram

Para mostrar a integração, acompanha-se uma encomenda fictícia que chega à portaria de um condomínio, na unidade A-12, quando a portaria está sem internet (Figura 16).

1. **Necessidade.** O problema do caderno (capítulo 2) virou requisitos e histórias de usuário (capítulo 4).
2. **Registro.** O porteiro informa unidade, destinatário, transportadora e tamanho, com entrada validada. O sistema escolhe a posição na estante pelo algoritmo A1 e gera o código único pelo A2 (capítulo 6).
3. **Gravação e aviso.** O registro é gravado em arquivo no protótipo e, no sistema completo, no banco relacional (capítulo 5). O morador é avisado pelo canal escolhido: aplicativo, SMS ou interfone com código impresso (capítulo 8).
4. **Operação offline.** Sem internet, a operação de registro entra na fila de sincronização e a portaria continua trabalhando.
5. **Sincronização.** Quando a conexão volta, a fila é enviada à central (algoritmo A4); no sistema completo, o envio seria feito por VPN e API em HTTPS (capítulo 7). A central aplica cada operação uma única vez (A5), de modo que reenviar não duplica nada.
6. **Retirada.** O morador informa o código; o porteiro o confere em até três tentativas, registra quem retirou, a data e a hora, e a posição é liberada (A3). A retirada também sobe à central.
7. **Relatórios.** O supervisor vê as pendências com mais de 7 dias, o dia de pico e a ocupação (A6), dados que alimentam os indicadores.

**[Figura 16 – Fluxo ponta a ponta de uma encomenda. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-16-fluxo-ponta-a-ponta.png`]**

Os componentes são o nó da portaria, a fila de sincronização, a rede, a central, o banco de dados e o serviço de aviso. Três decisões de arquitetura os conectam: o armazenamento em CSV do protótipo, a sincronização assíncrona com operações idempotentes e o endereçamento de rede 10.X.Y.0/24 (capítulo 4).

O Quadro 16 deixa claro o que foi efetivamente construído e o que é simulado ou projetado.

**Quadro 16 – O que é real e o que é simulado**

| Parte | Situação |
|---|---|
| Registro, estante, código, retirada, fila, consolidação e relatórios | Funcionando e testados no protótipo em C |
| Aviso ao morador | Simulado (mensagem na tela e registro em arquivo) |
| Rede entre portaria e central | Simulada por arquivos |
| Banco MySQL | Scripts executados em um servidor de teste; o protótipo em C não se conecta a ele |
| Rede física (VLANs, ACL) | Projetada; laboratório no Packet Tracer `[ATUALIZAR após a montagem]` |
| VPN | Apenas no diagrama |

Fonte: elaborado pelos autores (2026).

## 9.2 Plano de implantação

Propõe-se uma implantação em ondas, começando por um condomínio-piloto por duas semanas, para aprender com poucos usuários antes de levar a solução aos dez condomínios. A escolha do piloto, os prazos e os responsáveis são decisões da administradora. A preparação inclui a infraestrutura mínima (computador da portaria com nobreak, rede local conforme as VLANs, acesso à central e cópias de segurança), o cadastro dos moradores e de seus canais de aviso e, no primeiro dia, o lançamento das pendências que ainda estão no caderno, para que a estante e o sistema comecem iguais. Nos primeiros dias, ainda com o caderno em uso, mede-se a linha de base dos indicadores.

O treinamento dos porteiros é curto e prático, com uma cartilha de uma página com cinco passos: registrar a encomenda, conferir o aviso, retirar com código e nome, ver o mapa e as pendências antigas, e continuar normalmente se a internet cair. Os moradores recebem um comunicado explicando o código de retirada, o canal de aviso e a alternativa para quem não usa smartphone. O plano de contingência prevê que, se o computador da portaria falhar, os registros sejam feitos em formulário de papel e lançados depois. A expansão para os demais condomínios só ocorre se, ao fim do piloto, os porteiros registrarem sem recorrer ao caderno, a estante física e o mapa coincidirem e os indicadores não piorarem.

## 9.3 Benefícios esperados e indicadores

Os benefícios abaixo são esperados, e não resultados medidos. Esperam-se menos extravios e entregas erradas, graças ao registro, à posição e ao código; menos tempo de busca e de registro; moradores avisados mais rápido; operação contínua mesmo sem internet; visão única dos dez condomínios; cobrança de retirada por meio dos alertas de pendências antigas; e melhor dimensionamento da equipe, pelo dia de pico e pela ocupação.

Os indicadores propostos estão no Quadro 17. Como não foi realizado levantamento de campo, a linha de base ("antes") não existe hoje e seria medida no piloto; as metas ("depois") ainda precisam ser definidas e devem ser apresentadas como metas.

**Quadro 17 – Indicadores propostos**

| Indicador | Como medir | Antes | Meta |
|---|---|---|---|
| Extravios por mês | Encomendas registradas como não localizadas por mês | A medir no piloto | `[A DEFINIR]` |
| Tempo médio entre chegada e retirada | Média de (retirada − recebimento) das retiradas do mês | A medir no piloto | `[A DEFINIR]` |
| Moradores avisados em até 15 minutos | Avisos enviados em até 15 minutos ÷ registros | A medir no piloto | `[A DEFINIR]` |
| Tempo de registro por encomenda | Cronometragem de amostra | A medir no piloto | Cerca de 30 segundos |
| Pendências com mais de 7 dias | Relatório de pendências antigas | A medir no piloto | `[A DEFINIR]` |

Fonte: elaborado pelos autores (2026).

O protótipo já produz as pendências antigas, o dia de pico e a ocupação. O tempo entre chegada e retirada pode ser calculado com os dados registrados, mas ainda não há relatório pronto para isso. Com dados de exemplo fictícios, o relatório consolidado mostrou 2 pendências antigas e 11 pendentes entre 14 encomendas, valores usados apenas para demonstração.

## 9.4 Discussão

A comparação com soluções existentes (aplicativos de gestão condominial, armários inteligentes e portaria remota) depende de pesquisa com fontes verificadas `[A PREENCHER após verificar as fontes e preencher a matriz de trabalhos relacionados]`. O diferencial pretendido da proposta é reunir, em uma só solução, a operação sem internet, o aviso alternativo para quem não usa smartphone e a consolidação de vários condomínios, mas isso só pode ser afirmado em relação a produtos reais depois dessa pesquisa.

## 9.5 Limitações

A solução tem limitações que precisam ser declaradas. No protótipo, a rede e o aviso são simulados, não há interface gráfica, o programa é de console, sem login nem perfis, o código de retirada fica em texto e é visível na tela do porteiro, a capacidade é fixa e os dados são fictícios. No projeto, os comandos da rede ainda precisam ser testados no simulador, os equipamentos e custos não foram cotados, não houve levantamento de campo, a revisão por pares ainda está em andamento e a devolução de volumes não foi implementada.

## 9.6 Evolução futura

O Quadro 18 relaciona evoluções possíveis e seus pré-requisitos.

**Quadro 18 – Evoluções possíveis**

| Evolução | Pré-requisito |
|---|---|
| API real em HTTPS no lugar dos arquivos | Servidor na nuvem e contrato da API |
| Conexão do sistema ao banco MySQL, com hash do código | API e scripts do banco |
| Aplicativo do morador | API e autenticação |
| Avisos por aplicativo de mensagens | Contrato com provedor e consentimento |
| Painel de indicadores | Banco e relatórios |
| Perfis, login e autenticação em dois fatores | Módulo de usuários |
| Devolução de volumes após o prazo | Definição do prazo pela administradora |
| Telas acessíveis (WCAG) | Interface gráfica ou web |
| Armários inteligentes e leitura automática da etiqueta | Integração com fabricante e revisão de privacidade |

Fonte: elaborado pelos autores (2026).

## 9.7 Considerações do capítulo

A solução integra requisitos, regras de negócio em C, banco relacional, comunicação assíncrona entre portaria e central e cuidados de privacidade e acessibilidade em um único fluxo, com partes funcionando e partes simuladas ou projetadas. Os benefícios são hipóteses, e a medição deles depende de um piloto.
