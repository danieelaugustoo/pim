# 06-redes/packet-tracer

**O que guarda:** o roteiro passo a passo da montagem no Cisco Packet Tracer ([`roteiro.md`](roteiro.md)) e, depois que o grupo montar, o arquivo `.pkt` e os prints da simulação (sede, dois condomínios representativos e um servidor que representa a central).

**Exigências do manual que atende (Etapa 6):** topologia (print do Packet Tracer) e os resultados dos testes de rede apresentados no capítulo de redes.

**Situação (2026-11-04):** laboratório montado no Packet Tracer 9.0.1 e testes T1 a T15 executados, todos como esperado (resultados em `documento-final/capitulos/07-redes.md`). Faltam salvar o `.pkt` e os prints no repositório. Nomes sugeridos: `morada-central.pkt` e `print-t01-gateway.png` a `print-t15-sem-wan-local.png` (lista completa no roteiro). Os prints que entrarem no trabalho são copiados para `documento-final/figuras/`.

## Atalho opcional: script PTBuilder (`ptbuilder.js`)

O `ptbuilder.js` cria no Packet Tracer os 24 dispositivos, os 20 cabos, os endereços dos equipamentos fixos e a configuração dos 7 switches e roteadores, usando os mesmos comandos do `roteiro.md` (o script é **gerado a partir do roteiro**). Serve para ganhar tempo, mas **não foi testado no Packet Tracer** e depende de uma extensão de terceiros, o [PTBuilder](https://github.com/kimmknight/PTBuilder). Se der erro, siga o roteiro à mão.

**Como usar (confira também o README do PTBuilder)**
1. Baixe o `Builder.pts` no repositório do PTBuilder (GitHub, kimmknight/PTBuilder).
2. No Packet Tracer: **Extensions → Scripting → Configure PT Script Modules → Add** e escolha o `Builder.pts`.
3. Abra **Extensions → Builder Code Editor**, cole o conteúdo do `ptbuilder.js` e execute (Run).
4. Espere terminar (alguns segundos a poucos minutos, pois ele digita os comandos nos roteadores) e salve como `morada-central.pkt`.

**O que continua manual**
- Trocar o módulo de rede dos 3 laptops pelo **WPC300N** (Physical → desligar → trocar → ligar).
- Nos 3 pontos de acesso: Config → Port 1 → SSID `VISITANTES-SEDE`, `VISITANTES-C01` e `VISITANTES-C03` (roteiro, seção 8).
- Nos 3 laptops: Config → Wireless → o SSID do local, e IP por DHCP.
- Nos servidores: Services → HTTP e HTTPS ligados.
- `SW-INTERNET` fica sem configuração.
- Conferir, em cada roteador, `show ip interface brief` (todas up/up) e `show ip route` antes dos testes T1 a T15.

**Resultado da primeira execução (2026-11-04, Packet Tracer 9.0.1):** o PTBuilder funcionou para **dispositivos, cabos, endereços dos PCs/servidores e switches**, mas rodado de uma vez o script travou e, nos **roteadores**, perdeu os comandos `interface` (os três endereços foram parar na mesma porta). Por isso: rode em partes (dispositivos, cabos, endereços, switches) e **cole os blocos dos roteadores direto no CLI** (seções 7.1 a 7.4 do roteiro), respondendo `no` à pergunta de configuração inicial na primeira vez. Depois do `write memory`, não digite mais nada no CLI (comandos como `end` e `do` fora do modo de configuração travam a tela com "Translating").

O gerador não está no repositório: se o roteiro mudar, o `ptbuilder.js` precisa ser refeito.
