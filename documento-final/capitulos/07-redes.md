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

> **Rascunho** redigido a partir do roteiro e de `06-redes/` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. **A seção 7.8 (resultados dos testes) está vazia de propósito**: depende de o grupo montar a topologia no Packet Tracer e executar os testes. Os conceitos de redes e nuvem precisam de fontes verificadas.

# 7 REDES DE COMPUTADORES E SISTEMAS DISTRIBUÍDOS

Este capítulo apresenta o projeto da rede que sustenta a solução: a arquitetura e a topologia, o endereçamento, as redes virtuais (VLANs), o uso de computação em nuvem, a comunicação entre os serviços, a escalabilidade e a segurança da infraestrutura, além do laboratório de simulação no Cisco Packet Tracer. A rede é um projeto: o protótipo em C simula a comunicação por arquivos.

## 7.1 Arquitetura e topologia

A rede tem três tipos de local: a sede (local 0), os dez condomínios (locais 1 a 10) e a nuvem. Dentro de cada local a topologia é em estrela: um roteador com função de firewall, um switch gerenciável com VLANs (padrão 802.1Q) e um ponto de acesso Wi-Fi, com todos os equipamentos ligados ao switch `[FONTE A VERIFICAR: referência sobre topologias de rede]`. O roteador é o gateway de cada VLAN, faz o roteamento entre elas, aplica as regras de acesso e é a ponta da rede privada virtual (VPN). Nos condomínios, os equipamentos finais são o computador da portaria, a impressora térmica, o gravador e as câmeras de CFTV; na sede, os computadores e a impressora do administrativo e do atendimento.

Entre os locais, a topologia é hub-and-spoke: a nuvem é o centro e cada local é uma ponta, ligada por uma VPN IPsec sobre a internet do próprio local, o que dá onze túneis. Os locais só precisam falar com a nuvem, e os dados de moradores e de encomendas não trafegam em claro. Um novo condomínio é apenas mais uma ponta, com uma nova faixa de endereços e uma nova VPN, sem mudança no código (escalabilidade). A Figura 13 mostra a topologia.

**[Figura 13 – Topologia da rede. Inserir o print do Packet Tracer; rascunho em `06-redes/diagramas/topologia.mmd`. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-13-topologia.png`]**

A portaria não depende da internet: os dados ficam em arquivo local e as operações esperam na fila. Se a internet, a VPN ou a nuvem caírem, a portaria registra e entrega normalmente, a fila cresce e é reenviada ao voltar a conexão, sem duplicar registros. O ponto de atenção é o aviso por aplicativo ou SMS, que depende da nuvem; nesse caso, o interfone com código impresso cobre a falha. O switch, o roteador e o computador da portaria são pontos únicos de falha, tratados com contingência (troca do equipamento, configuração salva, formulário em papel e nobreak).

## 7.2 Equipamentos

Cada condomínio precisa de um roteador/firewall, um switch gerenciável com alimentação PoE, um ponto de acesso, um computador de portaria, uma impressora, um gravador e câmeras de CFTV, além de nobreak. A sede tem a mesma estrutura sem CFTV, com oito computadores. Os modelos, as quantidades de câmeras e os custos não foram definidos: dependem de cotação `[A COTAR]`, e o trabalho não faz orçamento.

## 7.3 Endereçamento IP

O endereçamento segue o padrão `10.X.Y.0/24`, em que X identifica o local (0 para a sede e 1 a 10 para os condomínios) e Y identifica a VLAN. A máscara é `255.255.255.0`; o gateway termina em `.1`; os equipamentos com endereço fixo usam de `.10` a `.49`; e o DHCP distribui de `.100` a `.199`. Por exemplo, `10.3.10.10` é o computador da portaria do condomínio 3. Com onze locais e quatro VLANs por local, são 44 redes, e foi verificado por script que nenhuma se sobrepõe e que todos os gateways e faixas pertencem à sua rede. A nuvem usa duas sub-redes, `172.16.1.0/24` para a API e `172.16.2.0/24` para o banco. O uso de uma máscara `/24` por VLAN privilegia a clareza do endereço, ao custo de gastar mais endereços do que sub-redes menores `[FONTE A VERIFICAR: VLSM]`.

## 7.4 VLANs

As VLANs separam o tráfego conforme o risco (Quadro 14). O número da VLAN é igual em todos os locais. O roteamento entre VLANs é feito pelo roteador, com uma subinterface por VLAN em um enlace tronco com o switch (router-on-a-stick).

**Quadro 14 – VLANs**

| VLAN | Condomínios | Sede | Motivo da separação |
|---|---|---|---|
| 10 | Portaria | Administrativo | Dados de moradores e encomendas em segmento controlado |
| 20 | CFTV | Atendimento | CFTV isolado reduz o risco de ser porta de entrada |
| 30 | Visitantes | Visitantes | Wi-Fi de visitantes só chega à internet |
| 99 | Gerência | Gerência | Só quem administra alcança os equipamentos de rede |

Fonte: elaborado pelos autores (2026).

## 7.5 Computação em nuvem e sistemas distribuídos

O projeto considerou os modelos IaaS, PaaS e SaaS `[FONTE A VERIFICAR: referência sobre computação em nuvem]`. A proposta é usar o banco MySQL como serviço gerenciado (PaaS), a API central em máquina virtual ou contêiner, e o aviso por SMS ou aplicativo como serviço de terceiros (SaaS). Em comparação com um servidor próprio na sede, a nuvem oferece redundância, manutenção parcialmente gerenciada, escalabilidade sob demanda e um ponto comum para os dez condomínios; o servidor próprio dá mais controle físico, mas exige investimento, energia, manutenção e depende da conexão da sede. Como a administradora não tem equipe de infraestrutura, a nuvem foi a opção proposta; o provedor e o custo ainda não foram definidos.

A solução é um sistema distribuído: nós de portaria independentes e uma central que consolida os dados. A comunicação segue o fluxo: o nó envia à API, por HTTPS dentro da VPN, lotes de operações da fila; a API grava no banco, aplicando cada operação uma única vez; e aciona o serviço de avisos. O contrato do lote de envio foi esboçado como proposta, não implementada. O principal desafio de sistemas distribuídos aqui é a consistência com conexões instáveis, tratado pela sincronização assíncrona com operações idempotentes (capítulo 4).

## 7.6 Segurança da infraestrutura

A segurança segue os princípios do menor privilégio, da defesa em camadas, do padrão "negar" e do registro de eventos. As regras principais, que são proposta do projeto, estão no Quadro 15.

**Quadro 15 – Regras de acesso principais**

| Origem | Pode acessar | Não pode acessar |
|---|---|---|
| VLAN 10 (portaria) | A API na nuvem (HTTPS, pela VPN) | CFTV, visitantes, gerência, outras portarias, internet |
| VLAN 20 (CFTV) | Apenas a própria VLAN | Todo o resto |
| VLAN 30 (visitantes) | A internet | Portaria, gerência, nuvem e rede interna |
| VLAN 99 (gerência) | Equipamentos de rede (acesso por SSH, a partir da sede) | Demais VLANs |
| Locais (via VPN) | Sub-rede da API na nuvem | Sub-rede do banco |

Fonte: elaborado pelos autores (2026).

Complementam essas regras a VPN IPsec entre cada local e a nuvem, o HTTPS/TLS na API, perfis de acesso com senhas fortes e autenticação em dois fatores no painel, gerência de equipamentos por SSH (nunca Telnet) apenas na VLAN de gerência, troca de senhas padrão, atualizações periódicas, logs de auditoria e cópias de segurança pela regra 3-2-1 (três cópias, em duas mídias, uma fora do local). O banco só é acessível pela API. A VPN foi mantida apenas no diagrama, sem configuração no simulador, por decisão do grupo.

## 7.7 Laboratório no Packet Tracer

O laboratório reproduz a sede, dois condomínios representativos (1 e 3) e um servidor que representa a nuvem, com um switch simulando a internet entre os roteadores, em uma faixa de endereços reservada para documentação (203.0.113.0/24) `[FONTE A VERIFICAR: RFC 5737]`. Ele inclui VLANs, roteamento entre VLANs, DHCP, as listas de acesso e as rotas, e um roteiro passo a passo com os comandos de cada equipamento e quinze testes de verificação. Os comandos do roteiro foram conferidos por script quanto aos endereços e às regras, mas **ainda não foram executados no simulador**.

## 7.8 Resultados dos testes

**[A PREENCHER depois de montar o laboratório. Para cada teste do roteiro (T1 a T15), registrar o resultado esperado e o obtido, com print.]** Os testes exigidos pelo plano são dois: a portaria alcança o servidor da central (T2, Figura 14) e o Wi-Fi de visitantes não alcança a portaria (T6, Figura 15). Os demais verificam o roteamento entre VLANs, o DHCP, o isolamento do CFTV e do banco, o segundo condomínio e o comportamento sem a ligação com a nuvem.

**[Figura 14 – Teste T2: a portaria alcança o servidor da central. Figura 15 – Teste T6: o Wi-Fi de visitantes não alcança a portaria. Inserir os prints.]**

## 7.9 Considerações do capítulo

O projeto de rede combina segmentação por VLAN, regras de acesso e VPN com uma nuvem como ponto comum, de modo que a portaria funcione sem internet e a central consolide os dados. Os pontos em aberto são a execução dos testes no simulador, a cotação dos equipamentos e a verificação das referências teóricas.
