# Arquitetura e topologia da rede (Etapa 6)

> Roteiro para o capítulo 7, que o grupo redige. Diagrama: [`diagramas/topologia.mmd`](diagramas/topologia.mmd). O print da montagem no Packet Tracer fica em `packet-tracer/` (roteiro em [`packet-tracer/roteiro.md`](packet-tracer/roteiro.md)).

## 1. Locais

| Local | Quantidade | Função | Endereços |
|---|---|---|---|
| Sede (local 0) | 1 | Gerência, supervisão, atendimento e administrativo-financeiro | `10.0.Y.0/24` |
| Condomínios (locais 1 a 10) | 10 | Portaria com o nó local de encomendas, CFTV e Wi-Fi de visitantes | `10.X.Y.0/24` |
| Nuvem | 1 | API central, banco MySQL gerenciado e backup | `172.16.1.0/24` e `172.16.2.0/24` |

Tabelas completas em [`enderecamento-ip.md`](enderecamento-ip.md) e [`vlans.md`](vlans.md).

## 2. Topologia dentro de cada local: estrela

Em cada local há um roteador/firewall, um switch gerenciável com VLANs (802.1Q) e um ponto de acesso Wi-Fi. Todos os dispositivos do local se ligam ao switch (estrela), e o switch se liga ao roteador por um enlace tronco (trunk) com as VLANs do local.

| Componente | Papel |
|---|---|
| Roteador/firewall | Gateway de cada VLAN, roteamento entre VLANs, regras de acesso (ACL) e ponta da VPN IPsec |
| Switch gerenciável | Separa as VLANs; no condomínio é PoE para alimentar câmeras e ponto de acesso |
| Ponto de acesso Wi-Fi | Rede de visitantes isolada (VLAN 30) |
| Equipamentos finais | PC da portaria, impressora térmica, gravador e câmeras de CFTV (condomínio); PCs e impressora (sede) |

Vantagem da estrela: a falha de um cabo ou de uma porta afeta só o equipamento daquela porta. Desvantagem: o switch e o roteador do local são pontos únicos de falha (ver seção 5).

## 3. Topologia entre os locais: hub-and-spoke

A nuvem é o centro (hub) e cada local é uma ponta (spoke). Cada roteador fecha uma **VPN IPsec** com a nuvem pela internet do próprio local.

| Aspecto | Escolha | Motivo |
|---|---|---|
| Forma | hub-and-spoke (11 túneis, um por local) | Os locais só precisam falar com a nuvem; a comunicação entre locais passa pelo hub se for necessária |
| Transporte | VPN IPsec sobre a internet | Dados de moradores e de encomendas não trafegam em claro (privacidade, LGPD) |
| Serviço usado | HTTPS (REST com JSON) dentro do túnel | Camada extra de proteção e padrão de integração com a API |
| Novo condomínio | mais uma ponta, com nova faixa `10.X.0.0/16` e nova VPN | Escalabilidade sem mudar o código (RNF06) |

## 4. Fluxo do dado de uma encomenda na rede

1. O porteiro registra a encomenda no nó local, que grava em arquivo local (VLAN 10).
2. A operação entra na fila de sincronização.
3. Quando há conexão, o nó envia um lote da fila à API (`172.16.1.0/24`) por HTTPS, dentro da VPN.
4. A API grava no banco (`172.16.2.0/24`), aplicando cada operação uma única vez.
5. A API aciona o serviço de avisos (app ou SMS); o painel da administradora consulta a mesma API.

No protótipo em C, a rede é simulada por arquivos (`dados/rede/`); ver `03-engenharia-software/arquitetura.md`.

## 5. O que acontece quando algo cai (RNF01)

A operação da portaria não depende da internet: os dados ficam em arquivo local e as operações esperam na fila.

| Falha | Efeito na portaria | Efeito no restante | Contingência |
|---|---|---|---|
| Internet do condomínio | Registra, guarda e entrega encomendas normalmente | Fila cresce; a sede vê dados desatualizados | Reenvio automático ao voltar, sem duplicar (ADR-003) |
| VPN | Igual à queda da internet | Igual | Igual |
| Nuvem ou API fora do ar | Igual | A sede não consolida | Fila preservada nas portarias |
| Aviso por app ou SMS | O aviso depende do serviço de avisos, que fica na nuvem: não sai sem conexão | Morador não recebe o aviso digital | Aviso por interfone com código impresso, que funciona offline (RNF08). [A confirmar com o grupo se o nó local também envia SMS] |
| Switch do condomínio | O PC da portaria continua funcionando com os arquivos locais, mas perde impressora de rede e envio | Fila cresce | Anotar o código à mão; trocar o switch |
| Roteador/firewall | Igual à queda da internet | Igual | Trocar o equipamento; configuração salva |
| PC da portaria | A portaria perde o sistema | A fila fica no PC | Formulário em papel e lançamento depois (`PLANO.md`, seção 9.8) |
| Energia | Nobreak mantém PC, switch e roteador por tempo limitado | Depois disso, tudo para | Autonomia do nobreak: [A DEFINIR] |

## 6. Segurança em uma frase por camada

Detalhes em [`seguranca-infraestrutura.md`](seguranca-infraestrutura.md): VLANs separam os tipos de tráfego; ACL no roteador limita quem fala com quem; VPN protege o transporte; HTTPS protege a API; backups e logs sustentam a recuperação e a auditoria.
