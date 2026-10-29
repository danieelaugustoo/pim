# Equipamentos (Etapa 6)

> Roteiro para o capítulo 7. **Nenhum modelo comercial, preço ou quantidade de câmeras foi inventado:** onde o plano não define, está `[MODELO A DEFINIR]`, `[A COTAR]` ou `[A DEFINIR]`. Cotação e escolha de fornecedor são do grupo.

## 1. Por condomínio (10 locais iguais)

| Equipamento | Qtd | Função | Modelo | Preço |
|---|---|---|---|---|
| Roteador/firewall com VPN IPsec | 1 | Gateway das VLANs, ACL e túnel para a nuvem | [MODELO A DEFINIR] | [A COTAR] |
| Switch gerenciável PoE de 16 portas | 1 | VLANs 802.1Q; PoE para câmeras e ponto de acesso | [MODELO A DEFINIR] | [A COTAR] |
| Ponto de acesso Wi-Fi | 1 | Rede de visitantes isolada (VLAN 30) | [MODELO A DEFINIR] | [A COTAR] |
| PC ou mini PC da portaria | 1 | Roda o nó de encomendas (`portaria`) | [MODELO A DEFINIR] | [A COTAR] |
| Impressora térmica | 1 | Imprime o código de retirada (aviso por interfone) | [MODELO A DEFINIR] | [A COTAR] |
| Nobreak | 1 | Mantém PC, switch e roteador em queda de energia | [MODELO A DEFINIR] | [A COTAR] |
| Câmeras e gravador de CFTV | já existentes | Segurança do condomínio (VLAN 20) | já existentes | não entram no orçamento |

## 2. Sede

| Equipamento | Qtd | Função | Modelo | Preço |
|---|---|---|---|---|
| Roteador/firewall com VPN IPsec | 1 | Gateway das VLANs, ACL e túnel para a nuvem | [MODELO A DEFINIR] | [A COTAR] |
| Switch gerenciável de 24 portas | 1 | VLANs 802.1Q | [MODELO A DEFINIR] | [A COTAR] |
| Pontos de acesso Wi-Fi | [A DEFINIR] | Wi-Fi de visitantes e uso interno | [MODELO A DEFINIR] | [A COTAR] |
| PCs | 8 | 1 gerente, 2 supervisores, 3 atendentes e 2 analistas (`01-organizacao/caracterizacao.md`) | [MODELO A DEFINIR] | [A COTAR] |
| Impressora | 1 | Uso administrativo | [MODELO A DEFINIR] | [A COTAR] |
| Nobreak | 1 | Mantém switch, roteador e PCs essenciais | [MODELO A DEFINIR] | [A COTAR] |

## 3. Nuvem

| Recurso | Qtd | Função | Observação |
|---|---|---|---|
| Servidor de aplicação (máquina virtual ou contêiner) | 1 | Roda a API central | Escala horizontalmente (ver `nuvem-e-sistemas-distribuidos.md`) |
| MySQL gerenciado | 1 | Banco relacional de todos os condomínios | Backup e atualização gerenciados pelo provedor |
| Armazenamento para backup | 1 | Cópias de segurança (regra 3-2-1) | Em outra região ou fora da nuvem principal |
| Provedor de nuvem | 1 | Hospeda tudo | [A DEFINIR] |

## 4. Totais

| Equipamento | Condomínios (10) | Sede | Total |
|---|---|---|---|
| Roteador/firewall com VPN | 10 | 1 | 11 |
| Switch gerenciável | 10 (PoE, 16 portas) | 1 (24 portas) | 11 |
| Ponto de acesso Wi-Fi | 10 | [A DEFINIR] | 10 + [A DEFINIR] |
| PC | 10 (portaria) | 8 | 18 |
| Impressora | 10 (térmica) | 1 | 11 |
| Nobreak | 10 | 1 | 11 |

Custo mensal e investimento inicial: [A COTAR]. Comparar com um servidor próprio na sede é assunto de `nuvem-e-sistemas-distribuidos.md`.

## 5. Observações

- Os 10 condomínios têm o mesmo kit, o que simplifica compra, configuração e reposição: a configuração do roteador e do switch muda só o número do local (X).
- A impressora térmica é o equipamento que atende o aviso por interfone com código impresso (RNF08).
- O nobreak é essencial para a portaria continuar operando (RNF01) em queda de energia; autonomia mínima: [A DEFINIR].
