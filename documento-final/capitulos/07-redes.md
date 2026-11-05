# 7 Redes de computadores e sistemas distribuídos (roteiro, cerca de 4 páginas, Etapa 6)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo". Os resultados dos testes de rede dependem do grupo montar a topologia no Packet Tracer.

**Fontes no repositório:** `06-redes/`.

## Tópicos

| # | Tópico | Origem |
|---|---|---|
| 7.1 | Arquitetura da rede e topologia (estrela em cada local, WAN hub-and-spoke, o que acontece quando algo cai) | `arquitetura-e-topologia.md` |
| 7.2 | Equipamentos por local | `equipamentos.md` (itens `[MODELO A DEFINIR]`/`[A COTAR]`) |
| 7.3 | Endereçamento IP (10.X.Y.0/24, 11 locais × 4 VLANs = 44 redes) e justificativa (ADR-006) | `enderecamento-ip.md` |
| 7.4 | VLANs (10, 20, 30, 99) e uso das portas | `vlans.md` |
| 7.5 | Comunicação entre serviços: contrato de envio de lote (proposta) e sequência | `nuvem-e-sistemas-distribuidos.md` |
| 7.6 | Computação em nuvem: IaaS, PaaS, SaaS; nuvem × servidor próprio | `nuvem-e-sistemas-distribuidos.md` |
| 7.7 | Arquitetura distribuída e escalabilidade (incluir um condomínio) | `nuvem-e-sistemas-distribuidos.md` |
| 7.8 | Segurança da infraestrutura: matriz de fluxos, VPN, 2FA, backup 3-2-1, logs | `seguranca-infraestrutura.md` |
| 7.9 | Laboratório no Packet Tracer e resultados dos testes T1 a T15 | `packet-tracer/roteiro.md` |

## Figuras e tabelas

| Item | Origem |
|---|---|
| Figura 13: topologia (print do Packet Tracer) | montagem do grupo; rascunho em `diagramas/topologia.mmd` |
| Figura 14: print do teste "portaria alcança o servidor central" | `packet-tracer/roteiro.md` (teste T2, `print-t02-portaria-api.png`) |
| Figura 15: print do teste "Wi-Fi de visitantes não alcança a portaria" | `packet-tracer/roteiro.md` (teste T6, `print-t06-visitante-portaria.png`) |
| Tabela: resumo do endereçamento (sede, condomínio-modelo, nuvem) | `enderecamento-ip.md` |
| Tabela: VLANs | `vlans.md` |
| Tabela: matriz de fluxos permitidos | `seguranca-infraestrutura.md` |
| Tabela: resultados dos testes T1 a T15 (esperado × obtido) | preencher após rodar |

## O que bloqueia este capítulo (só o grupo resolve)

- [ ] **Montar a topologia no Packet Tracer e executar os comandos do roteiro.** Os comandos foram conferidos por script (endereços e regras), mas **não foram executados no simulador**. Se algum for recusado na versão de vocês, anotem o comando e a mensagem.
- [ ] Tirar os prints dos testes e salvar o `.pkt`.
- [x] VPN IPsec: decisão do grupo (2026-10-29) de deixar só no diagrama, sem configurar no Packet Tracer.
- [ ] Confirmar com o professor de redes o que se espera do Packet Tracer (`PLANO.md`, seção 13).
- [ ] Cotar equipamentos e escolher o provedor de nuvem, ou declarar que o trabalho não faz orçamento.

## Cuidados

- Conceitos de nuvem, VLAN, ACL e VPN só com fonte verificada (`[FONTE A VERIFICAR]`, inclusive a RFC citada para o bloco 203.0.113.0/24).
- Deixar claro que as regras de firewall são **proposta** do projeto.
- Aviso por app/SMS depende da nuvem; o interfone cobre a falha de internet.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro e de `06-redes/` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Os resultados da seção 7.7 vêm dos testes executados pelo grupo em 2026-11-04 no Packet Tracer 9.0.1, e as Figuras 13 a 15 já estão em `figuras/`. Os conceitos de redes e nuvem precisam de fontes verificadas.

# 7 REDES DE COMPUTADORES E SISTEMAS DISTRIBUÍDOS

Este capítulo apresenta o projeto da rede que sustenta a solução: topologia, endereçamento, VLANs, nuvem, comunicação entre serviços, segurança e o laboratório no Cisco Packet Tracer. A rede é um projeto, e o protótipo em C simula a comunicação por arquivos.

## 7.1 Arquitetura e topologia

A rede tem três tipos de local: a sede (local 0), os dez condomínios (locais 1 a 10) e a nuvem. Dentro de cada local a topologia é em estrela, com um roteador que também faz o papel de firewall, um switch gerenciável com VLANs (802.1Q) e um ponto de acesso Wi-Fi (TANENBAUM; WETHERALL, 2011; KUROSE; ROSS, 2013). O roteador é o gateway de cada VLAN, roteia entre elas, aplica as regras de acesso e é a ponta da rede privada virtual (VPN).

Entre os locais, a topologia é hub-and-spoke. A nuvem é o centro, e cada local é uma ponta ligada a ela por uma VPN IPsec sobre a internet do próprio local, o que dá onze túneis. Os dados não trafegam em claro, e um condomínio novo é só mais uma ponta, com faixa de endereços e VPN próprias, sem mudar o código. A Figura 13 mostra a topologia montada no simulador.

**[Figura 13 – Topologia da rede no Packet Tracer 9.0.1. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-13-topologia.png`]**

A portaria não depende da internet: os dados ficam em arquivo local e as operações esperam na fila até a conexão voltar. O aviso por aplicativo ou SMS depende da nuvem, e então o interfone com código impresso cobre a falha. O switch, o roteador e o computador da portaria são pontos únicos de falha, tratados com contingência (troca do equipamento, configuração salva, formulário em papel e nobreak).

## 7.2 Equipamentos

Cada condomínio precisa de roteador e firewall, switch gerenciável com PoE, ponto de acesso, computador de portaria, impressora térmica, gravador, câmeras de CFTV e nobreak. A sede tem a mesma estrutura, sem CFTV, e oito computadores. Modelos, quantidade de câmeras e custos dependem de cotação `[A COTAR]`, e o trabalho não inclui orçamento.

## 7.3 Endereçamento IP e VLANs

O endereçamento segue o padrão `10.X.Y.0/24`, em que X identifica o local (0 para a sede, 1 a 10 para os condomínios) e Y, a VLAN. A máscara é `255.255.255.0`, o gateway termina em `.1`, os endereços fixos vão de `.10` a `.49` e o DHCP distribui de `.100` a `.199`. Por exemplo, `10.3.10.10` é o computador da portaria do condomínio 3. São 44 redes, onze locais com quatro VLANs cada, e um script verificou que nenhuma se sobrepõe. A nuvem usa `172.16.1.0/24` para a API e `172.16.2.0/24` para o banco. Usar uma máscara `/24` por VLAN deixa o endereço fácil de ler, ao custo de gastar mais endereços do que sub-redes menores `[FONTE A VERIFICAR: VLSM]`.

As VLANs separam o tráfego conforme o risco e têm o mesmo número em todos os locais: 10 para a portaria (administrativo, na sede), 20 para o CFTV (atendimento), 30 para visitantes e 99 para gerência. O roteador faz o roteamento entre elas, com uma subinterface por VLAN em um enlace tronco com o switch, no modelo router-on-a-stick.

## 7.4 Computação em nuvem e sistemas distribuídos

Entre os modelos de serviço IaaS, PaaS e SaaS (MELL; GRANCE, 2011), a proposta usa o MySQL como serviço gerenciado (PaaS), a API central em máquina virtual ou contêiner e o aviso por SMS ou aplicativo como serviço de terceiros (SaaS). Frente a um servidor próprio na sede, a nuvem oferece redundância, manutenção parcialmente gerenciada e escalabilidade sob demanda, enquanto o servidor próprio dá mais controle físico, mas exige investimento. Como a administradora não tem equipe de infraestrutura, a nuvem foi a opção proposta, e provedor e custo não foram definidos.

A solução é um sistema distribuído (TANENBAUM; VAN STEEN, 2007), com nós de portaria independentes e uma central que consolida os dados. O nó envia à API, por HTTPS dentro da VPN, lotes de operações da fila. A API grava no banco, aplica cada operação uma única vez e aciona o serviço de avisos. O contrato do lote é uma proposta e não foi implementado. O desafio principal é a consistência com conexões instáveis, tratado pela sincronização assíncrona com operações idempotentes (capítulo 4).

## 7.5 Segurança da infraestrutura

A segurança segue os princípios do menor privilégio, da defesa em camadas, do padrão "negar" e do registro de eventos. Pelas regras de acesso propostas, a portaria (VLAN 10) só alcança a API na nuvem, por HTTPS pela VPN, e não alcança o CFTV, os visitantes, a gerência, outras portarias nem a internet. O CFTV (VLAN 20) fala apenas com a própria VLAN, os visitantes (VLAN 30) só chegam à internet, e a gerência (VLAN 99) administra os equipamentos de rede por SSH, a partir da sede.

O projeto prevê ainda a VPN IPsec entre cada local e a nuvem, HTTPS/TLS na API, autenticação em dois fatores no painel, gerência por SSH (nunca Telnet) restrita à VLAN de gerência, logs de auditoria e cópias de segurança pela regra 3-2-1. O banco só é acessível pela API. A VPN ficou apenas no diagrama, sem configuração no simulador, por decisão do grupo.

## 7.6 Laboratório no Packet Tracer

O laboratório reproduz a sede, dois condomínios (1 e 3) e um servidor que representa a nuvem. Um switch simula a internet entre os roteadores, numa faixa de endereços reservada para documentação (203.0.113.0/24), definida na RFC 5737 (ARKKO; COTTON; VEGODA, 2010). Há VLANs, roteamento entre VLANs, DHCP, listas de acesso e rotas. Dispositivos, cabos, endereços fixos e switches foram criados por um script gerado do roteiro (extensão PTBuilder), e os roteadores foram configurados direto no CLI, porque o script perdeu os comandos que selecionam a interface.

## 7.7 Resultados dos testes

Os quinze testes do roteiro foram executados em 04/11/2026 e todos deram o resultado esperado (Quadro 5). Eles usam o `ping`, portanto verificam conectividade e regras de acesso, e não aplicações.

**Quadro 5 – Resultado dos testes no Packet Tracer**

| Grupo | Testes | Resultado |
|---|---|---|
| Comunicação permitida | T1, T2, T8, T10, T11 | Todos responderam |
| Tráfego barrado | T3, T4, T6, T7 | Todos inalcançáveis |
| DHCP | T5, T12 | `10.1.30.100` e `10.0.20.100`, dentro da faixa `.100` a `.199` |
| Regras combinadas | T9, T13 | CFTV: gateway sim, API não. Portaria C03: API sim, portaria C01 não |
| Sem o enlace WAN | T14, T15 | T14: API inalcançável. T15: impressora e gateway responderam |

Fonte: elaborado pelos autores (2026), a partir da execução no Packet Tracer 9.0.1.

Nos testes em que se esperava falta de resposta, a mensagem *Destination host unreachable* veio do próprio gateway do local, sinal de que as listas de acesso barraram o tráfego. O Wi-Fi de visitantes alcança o gateway, mas não a portaria nem a nuvem (T6 a T8), e o CFTV só fala com o seu gateway (T9). Os dois testes exigidos pelo plano passaram: a portaria alcança o servidor da central (T2, à esquerda na Figura 14) e o Wi-Fi de visitantes não alcança a portaria (T6, à direita). No teste de continuidade (T14 e T15), a rede local da portaria continuou funcionando sem a nuvem, que é o comportamento em que o nó em C se apoia ao guardar as operações na fila até a conexão voltar (ADR-003). O enlace foi religado ao fim.

**[Figura 14 – Testes T2 (à esquerda: a portaria do condomínio 1 alcança o servidor da central) e T6 (à direita: o Wi-Fi de visitantes do condomínio 1 não alcança a portaria). Fonte: elaborado pelos autores (2026), Packet Tracer 9.0.1. Arquivo: `figuras/figura-14-testes-t2-t6.png`]**

Os testes T5 a T8 foram feitos só no laptop de visitante do condomínio 1. A VPN, o HTTPS da API e o desempenho não foram testados, e a simulação não substitui equipamentos reais.
