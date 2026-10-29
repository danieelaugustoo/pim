# Roteiro do Packet Tracer (Etapa 6)

> Roteiro passo a passo para o **grupo montar** a topologia no Cisco Packet Tracer. A montagem, os testes e os prints são do grupo (`PLANO.md`, seção 3). Os comandos abaixo foram gerados a partir da regra `10.X.Y.0/24` e conferidos contra [`../enderecamento-ip.md`](../enderecamento-ip.md); **não foram executados no Packet Tracer** (não está instalado nesta máquina de desenvolvimento), então teste cada bloco e anote o que precisar de ajuste.

## 1. O que será montado

Sede, **dois condomínios representativos** (1 e 3; o 3 é o do exemplo do plano), a internet simulada e um servidor que representa a central, com VLANs, roteamento entre VLANs e DHCP.

| Teste exigido pelo plano | Como aparece aqui |
|---|---|
| A portaria alcança o servidor central | Teste T2 |
| O Wi-Fi de visitantes não alcança a portaria (ACL) | Teste T6 |

A **VPN IPsec** aparece só no diagrama (`../diagramas/topologia.mmd`). No simulador, a "internet" é um switch ligando os roteadores ao roteador da nuvem; o tráfego entre locais e nuvem passa por ele como se fosse o túnel. Se o grupo quiser tentar uma VPN IPsec, a seção 11 explica; não é necessária.

## 2. Dispositivos

Modelos sugeridos; **confira a disponibilidade na versão instalada** (versão do grupo: [A DEFINIR]) e troque por equivalentes se faltar algum.

| Nome | Tipo no Packet Tracer | Local |
|---|---|---|
| R-NUVEM | Router 2911 | Nuvem |
| SRV-API | Server-PT | Nuvem |
| SRV-BD | Server-PT | Nuvem |
| SW-INTERNET | Switch 2960-24TT | Internet simulada |
| R-SEDE | Router 2911 | Sede |
| SW-SEDE | Switch 2960-24TT | Sede |
| PC-ADM-SEDE | PC | Sede (VLAN 10) |
| PC-ATD-SEDE | PC | Sede (VLAN 20) |
| AP-SEDE | AccessPoint-PT | Sede (VLAN 30) |
| LAP-VIS-SEDE | Laptop | Sede (visitante) |
| R-C01, R-C03 | Router 2911 | Condomínios 1 e 3 |
| SW-C01, SW-C03 | Switch 2960-24TT | Condomínios 1 e 3 |
| PC-PORT-C01, PC-PORT-C03 | PC | Portaria (VLAN 10) |
| IMP-C01, IMP-C03 | Printer | Impressora térmica (VLAN 10) |
| NVR-C01, NVR-C03 | PC | Representa o gravador de CFTV (VLAN 20) |
| AP-C01, AP-C03 | AccessPoint-PT | Wi-Fi de visitantes (VLAN 30) |
| LAP-VIS-C01, LAP-VIS-C03 | Laptop | Visitante |

Os laptops precisam de placa sem fio: desligue o laptop, troque o módulo de rede por um módulo Wi-Fi (por exemplo, WPC300N) e ligue de novo.

## 3. Cabeamento

Cabo direto (copper straight-through) entre roteador e switch, entre PC e switch; cabo cruzado (copper cross-over) entre roteador e servidor. Se preferir, use a opção "Automatically Choose Connection Type".

| De | Porta | Para | Porta | Cabo |
|---|---|---|---|---|
| R-NUVEM | Gi0/0 | SW-INTERNET | Fa0/1 | direto |
| R-SEDE | Gi0/0 | SW-INTERNET | Fa0/2 | direto |
| R-C01 | Gi0/0 | SW-INTERNET | Fa0/3 | direto |
| R-C03 | Gi0/0 | SW-INTERNET | Fa0/4 | direto |
| R-NUVEM | Gi0/1 | SRV-API | Fa0 | cruzado |
| R-NUVEM | Gi0/2 | SRV-BD | Fa0 | cruzado |
| R-SEDE | Gi0/1 | SW-SEDE | Fa0/1 | direto |
| SW-SEDE | Fa0/2 | PC-ADM-SEDE | Fa0 | direto |
| SW-SEDE | Fa0/3 | PC-ATD-SEDE | Fa0 | direto |
| SW-SEDE | Fa0/11 | AP-SEDE | Port 0 | direto |
| R-C01 | Gi0/1 | SW-C01 | Fa0/1 | direto |
| SW-C01 | Fa0/2 | PC-PORT-C01 | Fa0 | direto |
| SW-C01 | Fa0/3 | IMP-C01 | Fa0 | direto |
| SW-C01 | Fa0/4 | NVR-C01 | Fa0 | direto |
| SW-C01 | Fa0/13 | AP-C01 | Port 0 | direto |
| R-C03 | Gi0/1 | SW-C03 | Fa0/1 | direto |
| SW-C03 | Fa0/2 | PC-PORT-C03 | Fa0 | direto |
| SW-C03 | Fa0/3 | IMP-C03 | Fa0 | direto |
| SW-C03 | Fa0/4 | NVR-C03 | Fa0 | direto |
| SW-C03 | Fa0/13 | AP-C03 | Port 0 | direto |

Os laptops de visitantes não têm cabo: conectam-se pelo Wi-Fi ao ponto de acesso do seu local.

## 4. Endereços do laboratório

| Dispositivo | Interface | Endereço | Máscara | Gateway |
|---|---|---|---|---|
| R-NUVEM | Gi0/0 | 203.0.113.1 | 255.255.255.0 | |
| R-NUVEM | Gi0/1 | 172.16.1.1 | 255.255.255.0 | |
| R-NUVEM | Gi0/2 | 172.16.2.1 | 255.255.255.0 | |
| SRV-API | Fa0 | 172.16.1.10 | 255.255.255.0 | 172.16.1.1 |
| SRV-BD | Fa0 | 172.16.2.10 | 255.255.255.0 | 172.16.2.1 |
| R-SEDE | Gi0/0 | 203.0.113.10 | 255.255.255.0 | |
| R-SEDE | Gi0/1.10 / .20 / .30 / .99 | 10.0.10.1 / 10.0.20.1 / 10.0.30.1 / 10.0.99.1 | 255.255.255.0 | |
| PC-ADM-SEDE, PC-ATD-SEDE, LAP-VIS-SEDE | | DHCP (VLANs 10, 20 e 30) | | |
| SW-SEDE | VLAN 99 | 10.0.99.10 | 255.255.255.0 | 10.0.99.1 |
| R-C01 | Gi0/0 | 203.0.113.11 | 255.255.255.0 | |
| R-C01 | Gi0/1.10 / .20 / .30 / .99 | 10.1.10.1 / 10.1.20.1 / 10.1.30.1 / 10.1.99.1 | 255.255.255.0 | |
| PC-PORT-C01 | Fa0 | 10.1.10.10 | 255.255.255.0 | 10.1.10.1 |
| IMP-C01 | Fa0 | 10.1.10.20 | 255.255.255.0 | 10.1.10.1 |
| NVR-C01 | Fa0 | 10.1.20.10 | 255.255.255.0 | 10.1.20.1 |
| LAP-VIS-C01 | Wi-Fi | DHCP (VLAN 30) | | |
| SW-C01 | VLAN 99 | 10.1.99.10 | 255.255.255.0 | 10.1.99.1 |
| R-C03 | Gi0/0 | 203.0.113.13 | 255.255.255.0 | |
| R-C03 | Gi0/1.10 / .20 / .30 / .99 | 10.3.10.1 / 10.3.20.1 / 10.3.30.1 / 10.3.99.1 | 255.255.255.0 | |
| PC-PORT-C03 | Fa0 | 10.3.10.10 | 255.255.255.0 | 10.3.10.1 |
| IMP-C03 | Fa0 | 10.3.10.20 | 255.255.255.0 | 10.3.10.1 |
| NVR-C03 | Fa0 | 10.3.20.10 | 255.255.255.0 | 10.3.20.1 |
| LAP-VIS-C03 | Wi-Fi | DHCP (VLAN 30) | | |
| SW-C03 | VLAN 99 | 10.3.99.10 | 255.255.255.0 | 10.3.99.1 |

O DHCP segue a regra do plano: concede de `.100` a `.199` e exclui `.1` a `.99` e `.200` a `.254`.

## 5. Ordem de configuração

1. Switches (VLANs e tronco).
2. Roteadores (subinterfaces, DHCP, rotas e ACL).
3. `SW-INTERNET`: **sem configuração** (todas as portas na VLAN 1).
4. Servidores e equipamentos fixos (endereço, máscara, gateway).
5. Pontos de acesso e laptops (Wi-Fi e DHCP).
6. Testes.

Clique no dispositivo → aba **CLI** → pressione Enter. Cole os comandos de cada bloco. Se algum comando for recusado, anote qual e a mensagem. Senhas de acesso (`enable secret`) e de console: o grupo define as de laboratório; **não reutilize senhas reais**.

## 6. Switches

### 6.1 SW-C01 (condomínio 1)

```
enable
configure terminal
hostname SW-C01
no ip domain-lookup
vlan 10
 name PORTARIA
vlan 20
 name CFTV
vlan 30
 name VISITANTES
vlan 99
 name GERENCIA
interface FastEthernet0/1
 description TRONCO PARA R-C01
 switchport mode trunk
 switchport trunk allowed vlan 10,20,30,99
interface FastEthernet0/2
 description PC DA PORTARIA
 switchport mode access
 switchport access vlan 10
interface FastEthernet0/3
 description IMPRESSORA TERMICA
 switchport mode access
 switchport access vlan 10
interface FastEthernet0/4
 description GRAVADOR CFTV
 switchport mode access
 switchport access vlan 20
interface FastEthernet0/13
 description PONTO DE ACESSO (VISITANTES)
 switchport mode access
 switchport access vlan 30
interface vlan 99
 ip address 10.1.99.10 255.255.255.0
 no shutdown
exit
ip default-gateway 10.1.99.1
end
write memory
```

### 6.2 SW-C03 (condomínio 3)

Igual ao bloco anterior, trocando o número do local:

```
enable
configure terminal
hostname SW-C03
no ip domain-lookup
vlan 10
 name PORTARIA
vlan 20
 name CFTV
vlan 30
 name VISITANTES
vlan 99
 name GERENCIA
interface FastEthernet0/1
 description TRONCO PARA R-C03
 switchport mode trunk
 switchport trunk allowed vlan 10,20,30,99
interface FastEthernet0/2
 description PC DA PORTARIA
 switchport mode access
 switchport access vlan 10
interface FastEthernet0/3
 description IMPRESSORA TERMICA
 switchport mode access
 switchport access vlan 10
interface FastEthernet0/4
 description GRAVADOR CFTV
 switchport mode access
 switchport access vlan 20
interface FastEthernet0/13
 description PONTO DE ACESSO (VISITANTES)
 switchport mode access
 switchport access vlan 30
interface vlan 99
 ip address 10.3.99.10 255.255.255.0
 no shutdown
exit
ip default-gateway 10.3.99.1
end
write memory
```

### 6.3 SW-SEDE

```
enable
configure terminal
hostname SW-SEDE
no ip domain-lookup
vlan 10
 name ADMINISTRATIVO
vlan 20
 name ATENDIMENTO
vlan 30
 name VISITANTES
vlan 99
 name GERENCIA
interface FastEthernet0/1
 description TRONCO PARA R-SEDE
 switchport mode trunk
 switchport trunk allowed vlan 10,20,30,99
interface FastEthernet0/2
 description PC ADMINISTRATIVO
 switchport mode access
 switchport access vlan 10
interface FastEthernet0/3
 description PC ATENDIMENTO
 switchport mode access
 switchport access vlan 20
interface FastEthernet0/11
 description PONTO DE ACESSO (VISITANTES)
 switchport mode access
 switchport access vlan 30
interface vlan 99
 ip address 10.0.99.10 255.255.255.0
 no shutdown
exit
ip default-gateway 10.0.99.1
end
write memory
```

Verifique em cada switch: `show vlan brief` (VLANs 10, 20, 30 e 99 criadas, portas nas VLANs certas) e `show interfaces trunk` (Fa0/1 como tronco com as VLANs 10, 20, 30 e 99). O laboratório mantém a VLAN nativa padrão para simplificar; ver `../vlans.md`, seção 5.

## 7. Roteadores

A interface física `Gi0/1` fica sem endereço e ligada (`no shutdown`); os endereços ficam nas subinterfaces. Se a subinterface aparecer "down", confira se a física está ligada e se o tronco do switch está certo.

### 7.1 R-C01

```
enable
configure terminal
hostname R-C01
no ip domain-lookup
interface GigabitEthernet0/0
 description WAN (simula o enlace com a nuvem)
 ip address 203.0.113.11 255.255.255.0
 no shutdown
interface GigabitEthernet0/1
 description TRONCO PARA SW-C01
 no shutdown
interface GigabitEthernet0/1.10
 description VLAN 10 PORTARIA
 encapsulation dot1Q 10
 ip address 10.1.10.1 255.255.255.0
 ip access-group ACL-PORTARIA-ENTRADA in
interface GigabitEthernet0/1.20
 description VLAN 20 CFTV
 encapsulation dot1Q 20
 ip address 10.1.20.1 255.255.255.0
 ip access-group ACL-CFTV-ENTRADA in
interface GigabitEthernet0/1.30
 description VLAN 30 VISITANTES
 encapsulation dot1Q 30
 ip address 10.1.30.1 255.255.255.0
 ip access-group ACL-VISITANTES-ENTRADA in
interface GigabitEthernet0/1.99
 description VLAN 99 GERENCIA
 encapsulation dot1Q 99
 ip address 10.1.99.1 255.255.255.0
exit
ip route 0.0.0.0 0.0.0.0 203.0.113.1
ip dhcp excluded-address 10.1.30.1 10.1.30.99
ip dhcp excluded-address 10.1.30.200 10.1.30.254
ip dhcp pool VISITANTES-C01
 network 10.1.30.0 255.255.255.0
 default-router 10.1.30.1
exit
ip access-list extended ACL-PORTARIA-ENTRADA
 permit icmp 10.1.10.0 0.0.0.255 host 10.1.10.1
 permit icmp 10.1.10.0 0.0.0.255 host 172.16.1.10
 permit tcp 10.1.10.0 0.0.0.255 host 172.16.1.10 eq 443
 deny ip any any
ip access-list extended ACL-CFTV-ENTRADA
 permit icmp 10.1.20.0 0.0.0.255 host 10.1.20.1
 deny ip any any
ip access-list extended ACL-VISITANTES-ENTRADA
 permit icmp 10.1.30.0 0.0.0.255 host 10.1.30.1
 deny ip 10.1.30.0 0.0.0.255 10.0.0.0 0.255.255.255
 deny ip 10.1.30.0 0.0.0.255 172.16.0.0 0.15.255.255
 permit ip any any
end
write memory
```

### 7.2 R-C03

Igual ao bloco anterior, trocando o número do local e o endereço WAN:

```
enable
configure terminal
hostname R-C03
no ip domain-lookup
interface GigabitEthernet0/0
 description WAN (simula o enlace com a nuvem)
 ip address 203.0.113.13 255.255.255.0
 no shutdown
interface GigabitEthernet0/1
 description TRONCO PARA SW-C03
 no shutdown
interface GigabitEthernet0/1.10
 description VLAN 10 PORTARIA
 encapsulation dot1Q 10
 ip address 10.3.10.1 255.255.255.0
 ip access-group ACL-PORTARIA-ENTRADA in
interface GigabitEthernet0/1.20
 description VLAN 20 CFTV
 encapsulation dot1Q 20
 ip address 10.3.20.1 255.255.255.0
 ip access-group ACL-CFTV-ENTRADA in
interface GigabitEthernet0/1.30
 description VLAN 30 VISITANTES
 encapsulation dot1Q 30
 ip address 10.3.30.1 255.255.255.0
 ip access-group ACL-VISITANTES-ENTRADA in
interface GigabitEthernet0/1.99
 description VLAN 99 GERENCIA
 encapsulation dot1Q 99
 ip address 10.3.99.1 255.255.255.0
exit
ip route 0.0.0.0 0.0.0.0 203.0.113.1
ip dhcp excluded-address 10.3.30.1 10.3.30.99
ip dhcp excluded-address 10.3.30.200 10.3.30.254
ip dhcp pool VISITANTES-C03
 network 10.3.30.0 255.255.255.0
 default-router 10.3.30.1
exit
ip access-list extended ACL-PORTARIA-ENTRADA
 permit icmp 10.3.10.0 0.0.0.255 host 10.3.10.1
 permit icmp 10.3.10.0 0.0.0.255 host 172.16.1.10
 permit tcp 10.3.10.0 0.0.0.255 host 172.16.1.10 eq 443
 deny ip any any
ip access-list extended ACL-CFTV-ENTRADA
 permit icmp 10.3.20.0 0.0.0.255 host 10.3.20.1
 deny ip any any
ip access-list extended ACL-VISITANTES-ENTRADA
 permit icmp 10.3.30.0 0.0.0.255 host 10.3.30.1
 deny ip 10.3.30.0 0.0.0.255 10.0.0.0 0.255.255.255
 deny ip 10.3.30.0 0.0.0.255 172.16.0.0 0.15.255.255
 permit ip any any
end
write memory
```

### 7.3 R-SEDE

```
enable
configure terminal
hostname R-SEDE
no ip domain-lookup
interface GigabitEthernet0/0
 description WAN (simula o enlace com a nuvem)
 ip address 203.0.113.10 255.255.255.0
 no shutdown
interface GigabitEthernet0/1
 description TRONCO PARA SW-SEDE
 no shutdown
interface GigabitEthernet0/1.10
 description VLAN 10 ADMINISTRATIVO
 encapsulation dot1Q 10
 ip address 10.0.10.1 255.255.255.0
interface GigabitEthernet0/1.20
 description VLAN 20 ATENDIMENTO
 encapsulation dot1Q 20
 ip address 10.0.20.1 255.255.255.0
interface GigabitEthernet0/1.30
 description VLAN 30 VISITANTES
 encapsulation dot1Q 30
 ip address 10.0.30.1 255.255.255.0
 ip access-group ACL-VISITANTES-ENTRADA in
interface GigabitEthernet0/1.99
 description VLAN 99 GERENCIA
 encapsulation dot1Q 99
 ip address 10.0.99.1 255.255.255.0
exit
ip route 0.0.0.0 0.0.0.0 203.0.113.1
ip dhcp excluded-address 10.0.10.1 10.0.10.99
ip dhcp excluded-address 10.0.10.200 10.0.10.254
ip dhcp excluded-address 10.0.20.1 10.0.20.99
ip dhcp excluded-address 10.0.20.200 10.0.20.254
ip dhcp excluded-address 10.0.30.1 10.0.30.99
ip dhcp excluded-address 10.0.30.200 10.0.30.254
ip dhcp pool ADMINISTRATIVO
 network 10.0.10.0 255.255.255.0
 default-router 10.0.10.1
ip dhcp pool ATENDIMENTO
 network 10.0.20.0 255.255.255.0
 default-router 10.0.20.1
ip dhcp pool VISITANTES-SEDE
 network 10.0.30.0 255.255.255.0
 default-router 10.0.30.1
exit
ip access-list extended ACL-VISITANTES-ENTRADA
 permit icmp 10.0.30.0 0.0.0.255 host 10.0.30.1
 deny ip 10.0.30.0 0.0.0.255 10.0.0.0 0.255.255.255
 deny ip 10.0.30.0 0.0.0.255 172.16.0.0 0.15.255.255
 permit ip any any
end
write memory
```

### 7.4 R-NUVEM (hub)

```
enable
configure terminal
hostname R-NUVEM
no ip domain-lookup
interface GigabitEthernet0/0
 description WAN (hub: recebe os locais)
 ip address 203.0.113.1 255.255.255.0
 ip access-group ACL-NUVEM-ENTRADA in
 no shutdown
interface GigabitEthernet0/1
 description SUB-REDE PUBLICA (API)
 ip address 172.16.1.1 255.255.255.0
 no shutdown
interface GigabitEthernet0/2
 description SUB-REDE PRIVADA (BANCO)
 ip address 172.16.2.1 255.255.255.0
 no shutdown
exit
ip route 10.0.0.0 255.255.0.0 203.0.113.10
ip route 10.1.0.0 255.255.0.0 203.0.113.11
ip route 10.3.0.0 255.255.0.0 203.0.113.13
ip access-list extended ACL-NUVEM-ENTRADA
 deny ip any 172.16.2.0 0.0.0.255
 permit ip any any
end
write memory
```

O que cada regra faz:

| Regra | Efeito |
|---|---|
| `ACL-PORTARIA-ENTRADA` | A VLAN 10 só fala com o gateway e com a API (ping e HTTPS); o resto é negado (portaria não alcança outras portarias, nem o CFTV, nem o banco) |
| `ACL-CFTV-ENTRADA` | O CFTV só fala com o próprio gateway; não sai para lugar nenhum |
| `ACL-VISITANTES-ENTRADA` | Os visitantes alcançam o próprio gateway e a internet, e são impedidos de chegar a qualquer rede `10.0.0.0/8` (sede e condomínios) e à nuvem `172.16.0.0/12` |
| `ACL-NUVEM-ENTRADA` | Nenhum local alcança a sub-rede do banco; só a rede da API chega a ela, por não passar por esta interface |
| Rotas | Cada local tem rota padrão para a nuvem (`203.0.113.1`); a nuvem tem uma rota por prefixo agregado de cada local |

Verifique: `show ip interface brief` (todas as interfaces up/up), `show ip route` (rota padrão ou as três rotas `10.X.0.0/16` conforme o roteador), `show access-lists` (os contadores sobem durante os testes).

## 8. Servidores e equipamentos finais

| Dispositivo | O que fazer |
|---|---|
| SRV-API | Desktop → IP Configuration → Static: 172.16.1.10, 255.255.255.0, gateway 172.16.1.1. Em Services, deixe HTTP e HTTPS ligados |
| SRV-BD | Static: 172.16.2.10, 255.255.255.0, gateway 172.16.2.1 |
| PC-PORT-C01 / C03 | Static: `10.X.10.10`, 255.255.255.0, gateway `10.X.10.1` |
| IMP-C01 / C03 | Static: `10.X.10.20`, 255.255.255.0, gateway `10.X.10.1` |
| NVR-C01 / C03 | Static: `10.X.20.10`, 255.255.255.0, gateway `10.X.20.1` |
| PC-ADM-SEDE, PC-ATD-SEDE | DHCP |
| AP-C01, AP-C03, AP-SEDE | Aba Config → Port 1 → SSID: `VISITANTES-C01`, `VISITANTES-C03` e `VISITANTES-SEDE`. No laboratório a rede fica sem senha; **numa instalação real, use WPA2 ou WPA3 com senha forte** |
| LAP-VIS-* | Config → Wireless → o SSID do seu local; IP por DHCP |

## 9. Testes e prints

Faça cada teste em Desktop → Command Prompt (`ping`) e tire o print com o resultado. Nomeie o arquivo como na última coluna e salve em `06-redes/packet-tracer/`; os prints que forem para o trabalho são copiados para `documento-final/figuras/` como `figura-NN-descricao.png`. Na primeira vez, o primeiro `ping` pode dar tempo esgotado por causa do ARP; repita antes de concluir que falhou.

| # | Origem | Teste | Esperado | O que prova | Print |
|---|---|---|---|---|---|
| T1 | PC-PORT-C01 | `ping 10.1.10.1` | **Responde** | Roteamento e VLAN 10 funcionando | `print-t01-gateway.png` |
| T2 | PC-PORT-C01 | `ping 172.16.1.10` | **Responde** | A portaria alcança o servidor central (exigência do plano) | `print-t02-portaria-api.png` |
| T3 | PC-PORT-C01 | `ping 172.16.2.10` | **Não responde** | O banco não é alcançável pelos locais | `print-t03-portaria-banco.png` |
| T4 | PC-PORT-C01 | `ping 10.3.10.10` | **Não responde** | A portaria só fala com a API, não com outras portarias | `print-t04-portaria-portaria.png` |
| T5 | LAP-VIS-C01 | Verificar o IP recebido (Desktop → IP Configuration) | **Endereço `10.1.30.100` a `.199`**, gateway `10.1.30.1` | DHCP na VLAN 30 com a faixa do plano | `print-t05-dhcp-visitante.png` |
| T6 | LAP-VIS-C01 | `ping 10.1.10.10` | **Não responde** | O Wi-Fi de visitantes não alcança a portaria (exigência do plano, ACL) | `print-t06-visitante-portaria.png` |
| T7 | LAP-VIS-C01 | `ping 172.16.1.10` | **Não responde** | Os visitantes não alcançam a nuvem | `print-t07-visitante-api.png` |
| T8 | LAP-VIS-C01 | `ping 10.1.30.1` | **Responde** | O visitante alcança o próprio gateway (ligação sem fio funciona) | `print-t08-visitante-gateway.png` |
| T9 | NVR-C01 | `ping 10.1.20.1` e depois `ping 172.16.1.10` | Gateway **responde**; API **não responde** | O CFTV está isolado | `print-t09-cftv.png` |
| T10 | PC-ADM-SEDE | `ping 172.16.1.10` | **Responde** | A sede alcança a API (painel) | `print-t10-sede-api.png` |
| T11 | SRV-API | `ping 172.16.2.10` | **Responde** | A API alcança o banco pela sub-rede privada | `print-t11-api-banco.png` |
| T12 | PC-ATD-SEDE | Verificar o IP recebido | **`10.0.20.100` a `.199`** | DHCP na VLAN 20 da sede | `print-t12-dhcp-sede.png` |
| T13 | PC-PORT-C03 | `ping 172.16.1.10` e `ping 10.1.10.10` | API **responde**; portaria do condomínio 1 **não responde** | Mesmo comportamento no segundo condomínio | `print-t13-condominio3.png` |

### Teste de continuidade (RNF01)

Mostra que a portaria continua operando sem a conexão com a nuvem. Em `R-C01`, derrube o enlace WAN:

```
configure terminal
interface GigabitEthernet0/0
 shutdown
end
```

| # | Origem | Teste | Esperado | Print |
|---|---|---|---|---|
| T14 | PC-PORT-C01 | `ping 172.16.1.10` | **Não responde** (sem conexão com a nuvem) | `print-t14-sem-wan-api.png` |
| T15 | PC-PORT-C01 | `ping 10.1.10.20` (impressora) e `ping 10.1.10.1` (gateway) | **Respondem** (a rede local continua) | `print-t15-sem-wan-local.png` |

Depois religue: `no shutdown` na `Gi0/0`. Relacione o resultado com o comportamento do nó em C: sem conexão, as operações ficam na fila e são enviadas depois (ADR-003).

### Comandos de apoio para os prints

| Dispositivo | Comando | Mostra |
|---|---|---|
| Switches | `show vlan brief`, `show interfaces trunk` | VLANs e tronco |
| Roteadores | `show ip interface brief`, `show ip route`, `show access-lists` | Interfaces, rotas e contadores das ACL |
| R-C01 | `show ip dhcp binding` | Endereços concedidos aos visitantes |

## 10. Entregáveis

- Arquivo `06-redes/packet-tracer/morada-central.pkt` com a topologia configurada.
- Print geral da topologia (`print-topologia.png`) e os prints T1 a T15.
- Uma frase por teste dizendo o resultado obtido e se bateu com o esperado (insumo para o capítulo 7).
- Os problemas encontrados e como foram resolvidos (vale como discussão no capítulo).

## 11. Se der problema

| Sintoma | Causa provável | O que fazer |
|---|---|---|
| Subinterface `down` | Interface física `Gi0/1` desligada, ou tronco do switch fora do ar | `no shutdown` na física; `show interfaces trunk` no switch |
| Visitante sem endereço DHCP | Laptop sem módulo Wi-Fi, SSID diferente do ponto de acesso, ou porta do ponto de acesso na VLAN errada | Conferir o módulo, o SSID e `switchport access vlan 30` |
| Visitante recebe endereço `169.254.x.x` | O DHCP não respondeu | `show ip dhcp pool` no roteador e o `excluded-address` do pool |
| Tudo responde, inclusive o que deveria ser bloqueado | ACL não aplicada ou na direção errada | `show ip interface Gi0/1.30`: a linha "Inbound access list" deve citar a ACL |
| Nada passa para a nuvem | Rota padrão ou rotas de retorno ausentes | `show ip route` nos spokes e no hub |
| O primeiro ping falha e os outros funcionam | ARP | Normal |
| Um comando é recusado | Modelo ou versão diferente | Anote o comando e a mensagem e adapte |

### VPN IPsec (opcional)

Algumas versões do Packet Tracer aceitam IPsec site-to-site em roteadores ISR, mas o suporte varia. Como o plano permite, a VPN fica no diagrama; se tentar, faça só entre `R-C01` e `R-NUVEM` depois de os testes T1 a T15 funcionarem, e anote o resultado.

