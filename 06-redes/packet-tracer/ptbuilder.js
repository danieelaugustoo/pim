// PTBuilder: monta o laboratorio "Morada Central" (06-redes/packet-tracer/roteiro.md).
// GERADO a partir do roteiro; NAO foi testado no Packet Tracer. Veja o README desta pasta.
// Etapas: 1 dispositivos, 2 cabos, 3 enderecos dos equipamentos, 4 configuracao IOS.

// 1. Dispositivos
addDevice("R-NUVEM", "2911", 500, 60);
addDevice("SRV-API", "Server-PT", 380, 60);
addDevice("SRV-BD", "Server-PT", 620, 60);
addDevice("SW-INTERNET", "2960-24TT", 500, 200);
addDevice("R-SEDE", "2911", 120, 320);
addDevice("SW-SEDE", "2960-24TT", 120, 440);
addDevice("PC-ADM-SEDE", "PC-PT", 40, 560);
addDevice("PC-ATD-SEDE", "PC-PT", 140, 560);
addDevice("AP-SEDE", "AccessPoint-PT", 230, 540);
addDevice("LAP-VIS-SEDE", "Laptop-PT", 230, 640);
addDevice("R-C01", "2911", 500, 320);
addDevice("SW-C01", "2960-24TT", 500, 440);
addDevice("PC-PORT-C01", "PC-PT", 400, 560);
addDevice("IMP-C01", "Printer-PT", 480, 560);
addDevice("NVR-C01", "PC-PT", 560, 560);
addDevice("AP-C01", "AccessPoint-PT", 640, 540);
addDevice("LAP-VIS-C01", "Laptop-PT", 640, 640);
addDevice("R-C03", "2911", 880, 320);
addDevice("SW-C03", "2960-24TT", 880, 440);
addDevice("PC-PORT-C03", "PC-PT", 780, 560);
addDevice("IMP-C03", "Printer-PT", 860, 560);
addDevice("NVR-C03", "PC-PT", 940, 560);
addDevice("AP-C03", "AccessPoint-PT", 1020, 540);
addDevice("LAP-VIS-C03", "Laptop-PT", 1020, 640);

// 2. Cabos (os laptops nao levam cabo: conectam por Wi-Fi)
addLink("R-NUVEM", "GigabitEthernet0/0", "SW-INTERNET", "FastEthernet0/1", "straight");
addLink("R-SEDE", "GigabitEthernet0/0", "SW-INTERNET", "FastEthernet0/2", "straight");
addLink("R-C01", "GigabitEthernet0/0", "SW-INTERNET", "FastEthernet0/3", "straight");
addLink("R-C03", "GigabitEthernet0/0", "SW-INTERNET", "FastEthernet0/4", "straight");
addLink("R-NUVEM", "GigabitEthernet0/1", "SRV-API", "FastEthernet0", "cross");
addLink("R-NUVEM", "GigabitEthernet0/2", "SRV-BD", "FastEthernet0", "cross");
addLink("R-SEDE", "GigabitEthernet0/1", "SW-SEDE", "FastEthernet0/1", "straight");
addLink("SW-SEDE", "FastEthernet0/2", "PC-ADM-SEDE", "FastEthernet0", "straight");
addLink("SW-SEDE", "FastEthernet0/3", "PC-ATD-SEDE", "FastEthernet0", "straight");
addLink("SW-SEDE", "FastEthernet0/11", "AP-SEDE", "Port 0", "straight");
addLink("R-C01", "GigabitEthernet0/1", "SW-C01", "FastEthernet0/1", "straight");
addLink("SW-C01", "FastEthernet0/2", "PC-PORT-C01", "FastEthernet0", "straight");
addLink("SW-C01", "FastEthernet0/3", "IMP-C01", "FastEthernet0", "straight");
addLink("SW-C01", "FastEthernet0/4", "NVR-C01", "FastEthernet0", "straight");
addLink("SW-C01", "FastEthernet0/13", "AP-C01", "Port 0", "straight");
addLink("R-C03", "GigabitEthernet0/1", "SW-C03", "FastEthernet0/1", "straight");
addLink("SW-C03", "FastEthernet0/2", "PC-PORT-C03", "FastEthernet0", "straight");
addLink("SW-C03", "FastEthernet0/3", "IMP-C03", "FastEthernet0", "straight");
addLink("SW-C03", "FastEthernet0/4", "NVR-C03", "FastEthernet0", "straight");
addLink("SW-C03", "FastEthernet0/13", "AP-C03", "Port 0", "straight");

// 3. Enderecos (servidores, PCs, impressoras e gravadores; os PCs da sede usam DHCP)
configurePcIp("SRV-API", false, "172.16.1.10", "255.255.255.0", "172.16.1.1");
configurePcIp("SRV-BD", false, "172.16.2.10", "255.255.255.0", "172.16.2.1");
configurePcIp("PC-PORT-C01", false, "10.1.10.10", "255.255.255.0", "10.1.10.1");
configurePcIp("IMP-C01", false, "10.1.10.20", "255.255.255.0", "10.1.10.1");
configurePcIp("NVR-C01", false, "10.1.20.10", "255.255.255.0", "10.1.20.1");
configurePcIp("PC-PORT-C03", false, "10.3.10.10", "255.255.255.0", "10.3.10.1");
configurePcIp("IMP-C03", false, "10.3.10.20", "255.255.255.0", "10.3.10.1");
configurePcIp("NVR-C03", false, "10.3.20.10", "255.255.255.0", "10.3.20.1");
configurePcIp("PC-ADM-SEDE", true);
configurePcIp("PC-ATD-SEDE", true);

// 4. Configuracao dos switches e roteadores (comandos do roteiro, secoes 6 e 7)
configureIosDevice("SW-C01", "enable\nconfigure terminal\nhostname SW-C01\nno ip domain-lookup\nvlan 10\n name PORTARIA\nvlan 20\n name CFTV\nvlan 30\n name VISITANTES\nvlan 99\n name GERENCIA\ninterface FastEthernet0/1\n description TRONCO PARA R-C01\n switchport mode trunk\n switchport trunk allowed vlan 10,20,30,99\ninterface FastEthernet0/2\n description PC DA PORTARIA\n switchport mode access\n switchport access vlan 10\ninterface FastEthernet0/3\n description IMPRESSORA TERMICA\n switchport mode access\n switchport access vlan 10\ninterface FastEthernet0/4\n description GRAVADOR CFTV\n switchport mode access\n switchport access vlan 20\ninterface FastEthernet0/13\n description PONTO DE ACESSO (VISITANTES)\n switchport mode access\n switchport access vlan 30\ninterface vlan 99\n ip address 10.1.99.10 255.255.255.0\n no shutdown\nexit\nip default-gateway 10.1.99.1\nend\nwrite memory");

configureIosDevice("SW-C03", "enable\nconfigure terminal\nhostname SW-C03\nno ip domain-lookup\nvlan 10\n name PORTARIA\nvlan 20\n name CFTV\nvlan 30\n name VISITANTES\nvlan 99\n name GERENCIA\ninterface FastEthernet0/1\n description TRONCO PARA R-C03\n switchport mode trunk\n switchport trunk allowed vlan 10,20,30,99\ninterface FastEthernet0/2\n description PC DA PORTARIA\n switchport mode access\n switchport access vlan 10\ninterface FastEthernet0/3\n description IMPRESSORA TERMICA\n switchport mode access\n switchport access vlan 10\ninterface FastEthernet0/4\n description GRAVADOR CFTV\n switchport mode access\n switchport access vlan 20\ninterface FastEthernet0/13\n description PONTO DE ACESSO (VISITANTES)\n switchport mode access\n switchport access vlan 30\ninterface vlan 99\n ip address 10.3.99.10 255.255.255.0\n no shutdown\nexit\nip default-gateway 10.3.99.1\nend\nwrite memory");

configureIosDevice("SW-SEDE", "enable\nconfigure terminal\nhostname SW-SEDE\nno ip domain-lookup\nvlan 10\n name ADMINISTRATIVO\nvlan 20\n name ATENDIMENTO\nvlan 30\n name VISITANTES\nvlan 99\n name GERENCIA\ninterface FastEthernet0/1\n description TRONCO PARA R-SEDE\n switchport mode trunk\n switchport trunk allowed vlan 10,20,30,99\ninterface FastEthernet0/2\n description PC ADMINISTRATIVO\n switchport mode access\n switchport access vlan 10\ninterface FastEthernet0/3\n description PC ATENDIMENTO\n switchport mode access\n switchport access vlan 20\ninterface FastEthernet0/11\n description PONTO DE ACESSO (VISITANTES)\n switchport mode access\n switchport access vlan 30\ninterface vlan 99\n ip address 10.0.99.10 255.255.255.0\n no shutdown\nexit\nip default-gateway 10.0.99.1\nend\nwrite memory");

configureIosDevice("R-C01", "enable\nconfigure terminal\nhostname R-C01\nno ip domain-lookup\ninterface GigabitEthernet0/0\n description WAN (simula o enlace com a nuvem)\n ip address 203.0.113.11 255.255.255.0\n no shutdown\ninterface GigabitEthernet0/1\n description TRONCO PARA SW-C01\n no shutdown\ninterface GigabitEthernet0/1.10\n description VLAN 10 PORTARIA\n encapsulation dot1Q 10\n ip address 10.1.10.1 255.255.255.0\n ip access-group ACL-PORTARIA-ENTRADA in\ninterface GigabitEthernet0/1.20\n description VLAN 20 CFTV\n encapsulation dot1Q 20\n ip address 10.1.20.1 255.255.255.0\n ip access-group ACL-CFTV-ENTRADA in\ninterface GigabitEthernet0/1.30\n description VLAN 30 VISITANTES\n encapsulation dot1Q 30\n ip address 10.1.30.1 255.255.255.0\n ip access-group ACL-VISITANTES-ENTRADA in\ninterface GigabitEthernet0/1.99\n description VLAN 99 GERENCIA\n encapsulation dot1Q 99\n ip address 10.1.99.1 255.255.255.0\nexit\nip route 0.0.0.0 0.0.0.0 203.0.113.1\nip dhcp excluded-address 10.1.30.1 10.1.30.99\nip dhcp excluded-address 10.1.30.200 10.1.30.254\nip dhcp pool VISITANTES-C01\n network 10.1.30.0 255.255.255.0\n default-router 10.1.30.1\nexit\nip access-list extended ACL-PORTARIA-ENTRADA\n permit icmp 10.1.10.0 0.0.0.255 host 10.1.10.1\n permit icmp 10.1.10.0 0.0.0.255 host 172.16.1.10\n permit tcp 10.1.10.0 0.0.0.255 host 172.16.1.10 eq 443\n deny ip any any\nip access-list extended ACL-CFTV-ENTRADA\n permit icmp 10.1.20.0 0.0.0.255 host 10.1.20.1\n deny ip any any\nip access-list extended ACL-VISITANTES-ENTRADA\n permit icmp 10.1.30.0 0.0.0.255 host 10.1.30.1\n deny ip 10.1.30.0 0.0.0.255 10.0.0.0 0.255.255.255\n deny ip 10.1.30.0 0.0.0.255 172.16.0.0 0.15.255.255\n permit ip any any\nend\nwrite memory");

configureIosDevice("R-C03", "enable\nconfigure terminal\nhostname R-C03\nno ip domain-lookup\ninterface GigabitEthernet0/0\n description WAN (simula o enlace com a nuvem)\n ip address 203.0.113.13 255.255.255.0\n no shutdown\ninterface GigabitEthernet0/1\n description TRONCO PARA SW-C03\n no shutdown\ninterface GigabitEthernet0/1.10\n description VLAN 10 PORTARIA\n encapsulation dot1Q 10\n ip address 10.3.10.1 255.255.255.0\n ip access-group ACL-PORTARIA-ENTRADA in\ninterface GigabitEthernet0/1.20\n description VLAN 20 CFTV\n encapsulation dot1Q 20\n ip address 10.3.20.1 255.255.255.0\n ip access-group ACL-CFTV-ENTRADA in\ninterface GigabitEthernet0/1.30\n description VLAN 30 VISITANTES\n encapsulation dot1Q 30\n ip address 10.3.30.1 255.255.255.0\n ip access-group ACL-VISITANTES-ENTRADA in\ninterface GigabitEthernet0/1.99\n description VLAN 99 GERENCIA\n encapsulation dot1Q 99\n ip address 10.3.99.1 255.255.255.0\nexit\nip route 0.0.0.0 0.0.0.0 203.0.113.1\nip dhcp excluded-address 10.3.30.1 10.3.30.99\nip dhcp excluded-address 10.3.30.200 10.3.30.254\nip dhcp pool VISITANTES-C03\n network 10.3.30.0 255.255.255.0\n default-router 10.3.30.1\nexit\nip access-list extended ACL-PORTARIA-ENTRADA\n permit icmp 10.3.10.0 0.0.0.255 host 10.3.10.1\n permit icmp 10.3.10.0 0.0.0.255 host 172.16.1.10\n permit tcp 10.3.10.0 0.0.0.255 host 172.16.1.10 eq 443\n deny ip any any\nip access-list extended ACL-CFTV-ENTRADA\n permit icmp 10.3.20.0 0.0.0.255 host 10.3.20.1\n deny ip any any\nip access-list extended ACL-VISITANTES-ENTRADA\n permit icmp 10.3.30.0 0.0.0.255 host 10.3.30.1\n deny ip 10.3.30.0 0.0.0.255 10.0.0.0 0.255.255.255\n deny ip 10.3.30.0 0.0.0.255 172.16.0.0 0.15.255.255\n permit ip any any\nend\nwrite memory");

configureIosDevice("R-SEDE", "enable\nconfigure terminal\nhostname R-SEDE\nno ip domain-lookup\ninterface GigabitEthernet0/0\n description WAN (simula o enlace com a nuvem)\n ip address 203.0.113.10 255.255.255.0\n no shutdown\ninterface GigabitEthernet0/1\n description TRONCO PARA SW-SEDE\n no shutdown\ninterface GigabitEthernet0/1.10\n description VLAN 10 ADMINISTRATIVO\n encapsulation dot1Q 10\n ip address 10.0.10.1 255.255.255.0\ninterface GigabitEthernet0/1.20\n description VLAN 20 ATENDIMENTO\n encapsulation dot1Q 20\n ip address 10.0.20.1 255.255.255.0\ninterface GigabitEthernet0/1.30\n description VLAN 30 VISITANTES\n encapsulation dot1Q 30\n ip address 10.0.30.1 255.255.255.0\n ip access-group ACL-VISITANTES-ENTRADA in\ninterface GigabitEthernet0/1.99\n description VLAN 99 GERENCIA\n encapsulation dot1Q 99\n ip address 10.0.99.1 255.255.255.0\nexit\nip route 0.0.0.0 0.0.0.0 203.0.113.1\nip dhcp excluded-address 10.0.10.1 10.0.10.99\nip dhcp excluded-address 10.0.10.200 10.0.10.254\nip dhcp excluded-address 10.0.20.1 10.0.20.99\nip dhcp excluded-address 10.0.20.200 10.0.20.254\nip dhcp excluded-address 10.0.30.1 10.0.30.99\nip dhcp excluded-address 10.0.30.200 10.0.30.254\nip dhcp pool ADMINISTRATIVO\n network 10.0.10.0 255.255.255.0\n default-router 10.0.10.1\nip dhcp pool ATENDIMENTO\n network 10.0.20.0 255.255.255.0\n default-router 10.0.20.1\nip dhcp pool VISITANTES-SEDE\n network 10.0.30.0 255.255.255.0\n default-router 10.0.30.1\nexit\nip access-list extended ACL-VISITANTES-ENTRADA\n permit icmp 10.0.30.0 0.0.0.255 host 10.0.30.1\n deny ip 10.0.30.0 0.0.0.255 10.0.0.0 0.255.255.255\n deny ip 10.0.30.0 0.0.0.255 172.16.0.0 0.15.255.255\n permit ip any any\nend\nwrite memory");

configureIosDevice("R-NUVEM", "enable\nconfigure terminal\nhostname R-NUVEM\nno ip domain-lookup\ninterface GigabitEthernet0/0\n description WAN (hub: recebe os locais)\n ip address 203.0.113.1 255.255.255.0\n ip access-group ACL-NUVEM-ENTRADA in\n no shutdown\ninterface GigabitEthernet0/1\n description SUB-REDE PUBLICA (API)\n ip address 172.16.1.1 255.255.255.0\n no shutdown\ninterface GigabitEthernet0/2\n description SUB-REDE PRIVADA (BANCO)\n ip address 172.16.2.1 255.255.255.0\n no shutdown\nexit\nip route 10.0.0.0 255.255.0.0 203.0.113.10\nip route 10.1.0.0 255.255.0.0 203.0.113.11\nip route 10.3.0.0 255.255.0.0 203.0.113.13\nip access-list extended ACL-NUVEM-ENTRADA\n deny ip any 172.16.2.0 0.0.0.255\n permit ip any any\nend\nwrite memory");
