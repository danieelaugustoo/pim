# ADR-006: Endereçamento 10.X.Y.0/24

**Status:** aceita

## Contexto

A rede tem a sede, 10 condomínios e a nuvem, e cada local precisa de VLANs separadas (portaria, CFTV, visitantes, gerência). O esquema de endereços deve ser legível e permitir novos condomínios sem redesenho.

## Decisão

Usar o padrão **`10.X.Y.0/24`**, em que **X** identifica o local (0 = sede, 1 a 10 = condomínios) e **Y** identifica a VLAN. Gateway no `.1`, equipamentos com IP fixo de `.10` a `.49` e DHCP de `.100` a `.199`.

## Alternativas consideradas

| Alternativa | Avaliação |
|---|---|
| VLSM com sub-redes menores | Economiza endereços, mas é mais difícil de ler e de explicar |
| Faixa única para todos os locais | Mistura locais e VLANs; dificulta regras de firewall |

## Justificativa

- Legibilidade: o endereço revela o local e a VLAN (exemplo: `10.3.10.10` é o PC da portaria do condomínio 3).
- Escalabilidade: o esquema comporta até 254 locais sem redesenho (RNF06).
- Um novo condomínio exige apenas uma nova faixa `10.X.0.0` e uma nova VPN, sem alterar o código.

## Consequências

- Tabela completa de sede e condomínios em `06-redes/enderecamento-ip.md`.
- O `/24` por VLAN privilegia a clareza; o texto do trabalho pode comentar que o VLSM economizaria endereços.
- Nuvem fora do padrão 10.X: sub-redes `172.16.1.0/24` (pública, API) e `172.16.2.0/24` (privada, banco), como no `PLANO.md`.
