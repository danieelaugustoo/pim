# Endereçamento IP (Etapa 6)

> Roteiro para o capítulo 7, que o grupo redige. Decisão: [ADR-006](../03-engenharia-software/decisoes/adr-006-enderecamento-ip.md). As tabelas abaixo foram **geradas por script** a partir da regra e conferidas (nenhuma rede se sobrepõe, todo gateway pertence à sua rede, todas as faixas cabem no `/24`).

## 1. Regra

| Item | Definição |
|---|---|
| Padrão | `10.X.Y.0/24` |
| X | local: `0` = sede, `1` a `10` = condomínios |
| Y | número da VLAN (10, 20, 30 ou 99) |
| Máscara | `255.255.255.0` (`/24`, 254 endereços úteis) |
| Gateway | final `.1` |
| IPs fixos | de `.10` a `.49` |
| DHCP | de `.100` a `.199` |
| Reservado | `.2` a `.9` (futuro), `.50` a `.99` (futuro) e `.200` a `.254` (futuro) |
| Broadcast | final `.255` |

O `/24` por VLAN privilegia a clareza: o endereço diz o local e a VLAN. O texto do trabalho pode comentar que sub-redes menores (VLSM) economizariam endereços, ao custo de uma tabela mais difícil de ler.

Exemplo: `10.3.10.10` é o PC da portaria (VLAN 10) do condomínio 3.

## 2. Tabela completa: sede e 10 condomínios

São 11 locais × 4 VLANs = 44 redes. Em todas: máscara `255.255.255.0`, gateway `.1`, DHCP `.100` a `.199`, broadcast `.255`.

| Local | X | VLAN | Nome da VLAN | Rede | Gateway | IPs fixos (.última parte) |
|---|---|---|---|---|---|---|
| Sede | 0 | 10 | ADMINISTRATIVO | 10.0.10.0/24 | 10.0.10.1 | 10 a 49 (impressora .20) |
| Sede | 0 | 20 | ATENDIMENTO | 10.0.20.0/24 | 10.0.20.1 | 10 a 49 |
| Sede | 0 | 30 | VISITANTES | 10.0.30.0/24 | 10.0.30.1 | nenhum (só DHCP) |
| Sede | 0 | 99 | GERENCIA | 10.0.99.0/24 | 10.0.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 1 | 1 | 10 | PORTARIA | 10.1.10.0/24 | 10.1.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 1 | 1 | 20 | CFTV | 10.1.20.0/24 | 10.1.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 1 | 1 | 30 | VISITANTES | 10.1.30.0/24 | 10.1.30.1 | nenhum (só DHCP) |
| Condomínio 1 | 1 | 99 | GERENCIA | 10.1.99.0/24 | 10.1.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 2 | 2 | 10 | PORTARIA | 10.2.10.0/24 | 10.2.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 2 | 2 | 20 | CFTV | 10.2.20.0/24 | 10.2.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 2 | 2 | 30 | VISITANTES | 10.2.30.0/24 | 10.2.30.1 | nenhum (só DHCP) |
| Condomínio 2 | 2 | 99 | GERENCIA | 10.2.99.0/24 | 10.2.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 3 | 3 | 10 | PORTARIA | 10.3.10.0/24 | 10.3.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 3 | 3 | 20 | CFTV | 10.3.20.0/24 | 10.3.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 3 | 3 | 30 | VISITANTES | 10.3.30.0/24 | 10.3.30.1 | nenhum (só DHCP) |
| Condomínio 3 | 3 | 99 | GERENCIA | 10.3.99.0/24 | 10.3.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 4 | 4 | 10 | PORTARIA | 10.4.10.0/24 | 10.4.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 4 | 4 | 20 | CFTV | 10.4.20.0/24 | 10.4.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 4 | 4 | 30 | VISITANTES | 10.4.30.0/24 | 10.4.30.1 | nenhum (só DHCP) |
| Condomínio 4 | 4 | 99 | GERENCIA | 10.4.99.0/24 | 10.4.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 5 | 5 | 10 | PORTARIA | 10.5.10.0/24 | 10.5.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 5 | 5 | 20 | CFTV | 10.5.20.0/24 | 10.5.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 5 | 5 | 30 | VISITANTES | 10.5.30.0/24 | 10.5.30.1 | nenhum (só DHCP) |
| Condomínio 5 | 5 | 99 | GERENCIA | 10.5.99.0/24 | 10.5.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 6 | 6 | 10 | PORTARIA | 10.6.10.0/24 | 10.6.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 6 | 6 | 20 | CFTV | 10.6.20.0/24 | 10.6.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 6 | 6 | 30 | VISITANTES | 10.6.30.0/24 | 10.6.30.1 | nenhum (só DHCP) |
| Condomínio 6 | 6 | 99 | GERENCIA | 10.6.99.0/24 | 10.6.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 7 | 7 | 10 | PORTARIA | 10.7.10.0/24 | 10.7.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 7 | 7 | 20 | CFTV | 10.7.20.0/24 | 10.7.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 7 | 7 | 30 | VISITANTES | 10.7.30.0/24 | 10.7.30.1 | nenhum (só DHCP) |
| Condomínio 7 | 7 | 99 | GERENCIA | 10.7.99.0/24 | 10.7.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 8 | 8 | 10 | PORTARIA | 10.8.10.0/24 | 10.8.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 8 | 8 | 20 | CFTV | 10.8.20.0/24 | 10.8.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 8 | 8 | 30 | VISITANTES | 10.8.30.0/24 | 10.8.30.1 | nenhum (só DHCP) |
| Condomínio 8 | 8 | 99 | GERENCIA | 10.8.99.0/24 | 10.8.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 9 | 9 | 10 | PORTARIA | 10.9.10.0/24 | 10.9.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 9 | 9 | 20 | CFTV | 10.9.20.0/24 | 10.9.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 9 | 9 | 30 | VISITANTES | 10.9.30.0/24 | 10.9.30.1 | nenhum (só DHCP) |
| Condomínio 9 | 9 | 99 | GERENCIA | 10.9.99.0/24 | 10.9.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |
| Condomínio 10 | 10 | 10 | PORTARIA | 10.10.10.0/24 | 10.10.10.1 | 10 a 49 (PC da portaria .10, impressora .20) |
| Condomínio 10 | 10 | 20 | CFTV | 10.10.20.0/24 | 10.10.20.1 | 10 a 49 (gravador .10, câmeras a partir de .11) |
| Condomínio 10 | 10 | 30 | VISITANTES | 10.10.30.0/24 | 10.10.30.1 | nenhum (só DHCP) |
| Condomínio 10 | 10 | 99 | GERENCIA | 10.10.99.0/24 | 10.10.99.1 | 10 a 49 (switch .10, ponto de acesso .11) |

## 3. Resumo por local

| Local | Prefixo agregado | Redes |
|---|---|---|
| Sede | `10.0.0.0/16` | 10.0.10.0/24, 10.0.20.0/24, 10.0.30.0/24, 10.0.99.0/24 |
| Condomínio 1 | `10.1.0.0/16` | 10.1.10.0/24, 10.1.20.0/24, 10.1.30.0/24, 10.1.99.0/24 |
| Condomínio 2 | `10.2.0.0/16` | 10.2.10.0/24, 10.2.20.0/24, 10.2.30.0/24, 10.2.99.0/24 |
| Condomínio 3 | `10.3.0.0/16` | 10.3.10.0/24, 10.3.20.0/24, 10.3.30.0/24, 10.3.99.0/24 |
| Condomínio 4 | `10.4.0.0/16` | 10.4.10.0/24, 10.4.20.0/24, 10.4.30.0/24, 10.4.99.0/24 |
| Condomínio 5 | `10.5.0.0/16` | 10.5.10.0/24, 10.5.20.0/24, 10.5.30.0/24, 10.5.99.0/24 |
| Condomínio 6 | `10.6.0.0/16` | 10.6.10.0/24, 10.6.20.0/24, 10.6.30.0/24, 10.6.99.0/24 |
| Condomínio 7 | `10.7.0.0/16` | 10.7.10.0/24, 10.7.20.0/24, 10.7.30.0/24, 10.7.99.0/24 |
| Condomínio 8 | `10.8.0.0/16` | 10.8.10.0/24, 10.8.20.0/24, 10.8.30.0/24, 10.8.99.0/24 |
| Condomínio 9 | `10.9.0.0/16` | 10.9.10.0/24, 10.9.20.0/24, 10.9.30.0/24, 10.9.99.0/24 |
| Condomínio 10 | `10.10.0.0/16` | 10.10.10.0/24, 10.10.20.0/24, 10.10.30.0/24, 10.10.99.0/24 |

O prefixo agregado `10.X.0.0/16` é o que os roteadores da nuvem usam para encaminhar de volta a cada local.

## 4. Nuvem

| Sub-rede | Rede | Uso | Gateway | Exemplos |
|---|---|---|---|---|
| Pública | 172.16.1.0/24 | API central (recebe os lotes das portarias e as consultas do painel) | 172.16.1.1 | API 172.16.1.10 |
| Privada | 172.16.2.0/24 | Banco MySQL gerenciado; só a API o acessa | 172.16.2.1 | Banco 172.16.2.10 |

Os números `.10` acima são os usados no laboratório do Packet Tracer. Em produção, o endereço do banco gerenciado é dado pelo provedor. [A DEFINIR]

## 5. Equipamentos com IP fixo em cada local

Padrão repetido nos 10 condomínios (X = número do condomínio):

| Equipamento | VLAN | Endereço |
|---|---|---|
| Roteador/firewall (gateway) | 99 e demais | `10.X.99.1`, `10.X.10.1`, `10.X.20.1`, `10.X.30.1` |
| Switch (gerência) | 99 | `10.X.99.10` |
| Ponto de acesso (gerência) | 99 | `10.X.99.11` |
| PC da portaria | 10 | `10.X.10.10` |
| Impressora térmica (código impresso) | 10 | `10.X.10.20` |
| Gravador de CFTV | 20 | `10.X.20.10` |
| Câmeras (já existentes) | 20 | `10.X.20.11` em diante; quantidade [A DEFINIR] |
| Clientes Wi-Fi de visitantes | 30 | DHCP `10.X.30.100` a `.199` |

Na sede (X = 0): impressora `10.0.10.20`, switch `10.0.99.10`, ponto de acesso `10.0.99.11`; os PCs recebem DHCP na VLAN 10 (administrativo) e na VLAN 20 (atendimento).

## 6. WAN do laboratório do Packet Tracer

No simulador, a "internet" é um switch que liga os roteadores de cada local ao roteador da nuvem (o hub). O enlace usa a faixa `203.0.113.0/24`, reservada para documentação [FONTE A VERIFICAR: RFC 5737], para não confundir com endereços reais. **Esta tabela vale só para o laboratório.**

| Roteador | Interface WAN | Endereço | Máscara |
|---|---|---|---|
| R-NUVEM | Gi0/0 | 203.0.113.1 | 255.255.255.0 |
| R-SEDE | Gi0/0 | 203.0.113.10 | 255.255.255.0 |
| R-C01 | Gi0/0 | 203.0.113.11 | 255.255.255.0 |
| R-C03 | Gi0/0 | 203.0.113.13 | 255.255.255.0 |

Em produção, o endereço público de cada roteador vem do provedor de internet, e o tráfego entre locais e nuvem segue dentro do túnel VPN IPsec. [A DEFINIR com o provedor]

Rotas no laboratório (hub-and-spoke): cada roteador de local tem rota padrão para `203.0.113.1` (a nuvem); o roteador da nuvem tem uma rota por prefixo agregado `10.X.0.0/16` para o roteador de cada local. Detalhes em [`packet-tracer/roteiro.md`](packet-tracer/roteiro.md).

