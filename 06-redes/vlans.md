# VLANs (Etapa 6)

> Roteiro para o capítulo 7. Endereços de cada VLAN em [`enderecamento-ip.md`](enderecamento-ip.md). O número da VLAN é igual em todos os locais, e o endereço `10.X.Y.0/24` usa Y = número da VLAN.

## 1. Tabela de VLANs

| VLAN | Condomínios | Sede |
|---|---|---|
| 10 | **PORTARIA**: PC da portaria e impressora | **ADMINISTRATIVO**: PCs da gerência e do financeiro |
| 20 | **CFTV**: câmeras e gravador | **ATENDIMENTO**: PCs dos atendentes |
| 30 | **VISITANTES**: Wi-Fi isolado, só internet | **VISITANTES**: Wi-Fi isolado, só internet |
| 99 | **GERENCIA**: switch, ponto de acesso e roteador | **GERENCIA**: switch, ponto de acesso e roteador |

## 2. Por que separar

| VLAN | Motivo |
|---|---|
| 10 PORTARIA / ADMINISTRATIVO | Dados de moradores e de encomendas ficam num segmento controlado |
| 20 CFTV / ATENDIMENTO | No condomínio, o CFTV isolado reduz o risco de câmeras servirem de porta de entrada; na sede, o atendimento tem acesso próprio |
| 30 VISITANTES | Quem usa o Wi-Fi de visitantes só chega à internet, nunca à portaria nem à rede interna |
| 99 GERENCIA | Só quem administra a rede alcança os equipamentos de rede; a configuração não fica exposta aos demais |

## 3. Roteamento entre VLANs

O roteador/firewall de cada local faz o roteamento entre VLANs (router-on-a-stick): o enlace entre o switch e o roteador é um **tronco 802.1Q**, e o roteador tem uma subinterface por VLAN, com o gateway no `.1`. As regras de quem fala com quem ficam nas ACL do roteador (ver [`seguranca-infraestrutura.md`](seguranca-infraestrutura.md)).

Alternativa para a evolução: um switch de camada 3 faria o roteamento interno e deixaria o roteador só com a saída para a WAN. Não é necessário no porte atual.

## 4. Proposta de uso das portas

Proposta do grupo, a ajustar à instalação real. Nos condomínios o switch tem 16 portas.

| Porta | Uso | Modo | VLAN |
|---|---|---|---|
| 1 | Enlace para o roteador | tronco | 10, 20, 30 e 99 |
| 2 | PC da portaria | acesso | 10 |
| 3 | Impressora térmica | acesso | 10 |
| 4 | Gravador de CFTV | acesso | 20 |
| 5 a 12 | Câmeras PoE (até 8; quantidade real [A DEFINIR]) | acesso | 20 |
| 13 | Ponto de acesso (SSID de visitantes) | acesso no laboratório; tronco nas instalações reais com mais de um SSID | 30 |
| 14 a 16 | Reserva, desligadas | desligada | — |

Na sede o switch tem 24 portas. Proposta:

| Porta | Uso | Modo | VLAN |
|---|---|---|---|
| 1 | Enlace para o roteador | tronco | 10, 20, 30 e 99 |
| 2 a 6 | 5 PCs da gerência (gerente e 2 supervisores) e do financeiro (2 analistas) | acesso | 10 |
| 7 | Impressora | acesso | 10 |
| 8 a 10 | 3 PCs dos atendentes | acesso | 20 |
| 11 | Ponto de acesso (visitantes) | acesso | 30 |
| 12 a 24 | Reserva, desligadas | desligada | — |

## 5. Boas práticas a citar

- **Não usar a VLAN 1** para tráfego de dados. O laboratório do Packet Tracer deixa a VLAN nativa padrão para simplificar; numa instalação real, defina a VLAN nativa do tronco como a 99 ou como uma VLAN sem uso.
- **Desligar portas não usadas** e atribuí-las a uma VLAN sem uso.
- **Limitar as VLANs permitidas no tronco** às que existem no local (10, 20, 30 e 99).
- **Gerência só na VLAN 99**, com acesso por SSH, nunca Telnet.
- **Documentar** cada porta e cada endereço fixo; esta página e a de endereçamento são a documentação de referência.
