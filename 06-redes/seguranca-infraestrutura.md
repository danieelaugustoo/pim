# Segurança da infraestrutura (Etapa 6)

> Roteiro para o capítulo 7. As regras da seção 2 são **proposta do grupo**, derivada do `PLANO.md` (seção 9.6); o grupo confirma e ajusta. Segurança da informação do software (código de retirada, privacidade) fica em `07-seguranca-privacidade-acessibilidade/`.

## 1. Princípios

| Princípio | Aplicação |
|---|---|
| Menor privilégio | Cada VLAN só alcança o que precisa |
| Defesa em camadas | VLAN, ACL, VPN, HTTPS, senhas fortes, 2FA, backup e log |
| Padrão negar | O que não está liberado é bloqueado |
| Separar o que pode ser invadido | CFTV e visitantes ficam isolados da portaria |
| Registrar | Tudo que importa deixa log |

## 2. Matriz de fluxos permitidos

Legenda: **P** permitido, **N** negado. Tráfego de resposta de conexões permitidas segue liberado.

### Condomínio (X = 1 a 10)

| De \ Para | Portaria (VLAN 10) | CFTV (VLAN 20) | Visitantes (VLAN 30) | Gerência (VLAN 99) | API na nuvem | Internet |
|---|---|---|---|---|---|---|
| **VLAN 10 Portaria** | P (dentro da VLAN) | N | N | N | **P** (HTTPS 443, pela VPN) | N |
| **VLAN 20 CFTV** | N | P (dentro da VLAN) | N | N | N | N |
| **VLAN 30 Visitantes** | **N** | N | P (dentro da VLAN) | N | N | **P** |
| **VLAN 99 Gerência** | N | N | N | P (dentro da VLAN) | N | N |
| **Sede, VLAN 99, via VPN** | N | N | N | **P** (SSH 22) | N | — |

### Sede (X = 0)

| De \ Para | VLAN 10 Administrativo | VLAN 20 Atendimento | VLAN 30 Visitantes | VLAN 99 Gerência | API na nuvem | Internet |
|---|---|---|---|---|---|---|
| **VLAN 10** | P (dentro da VLAN) | [A DEFINIR] | N | N | P (painel, HTTPS 443) | P |
| **VLAN 20** | [A DEFINIR] | P (dentro da VLAN) | N | N | P (consulta, HTTPS 443) [A confirmar] | P |
| **VLAN 30 Visitantes** | **N** | **N** | P (dentro da VLAN) | N | N | **P** |
| **VLAN 99 Gerência** | N | N | N | P (dentro da VLAN) | N | P (atualizações) |

### Nuvem

| Para \ De | Locais (via VPN) | API | Internet |
|---|---|---|---|
| **Sub-rede pública 172.16.1.0/24 (API)** | **P** (HTTPS 443) | P (dentro da sub-rede) | N |
| **Sub-rede privada 172.16.2.0/24 (banco)** | **N** | **P** (MySQL 3306) | N |

Em todos os casos, o que não aparece como permitido é negado.

## 3. Medidas por camada

| Camada | Medida | Observação |
|---|---|---|
| Rede interna | VLANs 802.1Q separando portaria, CFTV, visitantes e gerência | Ver `vlans.md` |
| Roteador/firewall | ACL e regras de firewall conforme a seção 2; VLAN 30 só acessa a internet; VLAN 10 só fala com a API pela VPN | Lab no Packet Tracer demonstra a regra de visitantes |
| WAN | VPN IPsec entre cada local e a nuvem | Algoritmos e chaves: [A DEFINIR] seguindo recomendações atuais; chaves protegidas |
| Aplicação | HTTPS/TLS na API | Certificado válido; versões antigas de TLS desativadas |
| Acesso | Perfis (porteiro, supervisor, administrador), senhas fortes, **autenticação em dois fatores no painel** | Acesso por perfil também atende RNF03 |
| Equipamentos | Gerência por SSH, só na VLAN 99; senhas padrão trocadas; portas sem uso desligadas | Nunca Telnet |
| Dados | Banco só acessível pela API; código de retirada guardado como hash | Detalhes em `04-banco-de-dados/` e na Etapa 7 |
| Disponibilidade | Nobreak em cada local; configuração dos equipamentos salva | Ver `equipamentos.md` |
| Backup | **Regra 3-2-1** | Seção 4 |
| Manutenção | Atualização periódica de roteadores, switches, pontos de acesso, PC da portaria e API | Janela de atualização combinada com a sede |
| Auditoria | Logs de auditoria: quem registrou, quem retirou, quem acessou o painel (RNF07) | Retenção dos dados pessoais: 90 dias após a retirada (decisão do grupo); prazo dos logs [A DEFINIR] |
| CFTV | Isolado na VLAN 20, sem saída para a internet | Acesso remoto às câmeras não está previsto [A DEFINIR] |

## 4. Backup (regra 3-2-1)

| Elemento | Significado | Aplicação |
|---|---|---|
| 3 cópias | O dado original e duas cópias | Banco em produção + backup automático do provedor + cópia exportada |
| 2 mídias diferentes | Tipos de armazenamento distintos | Armazenamento do banco gerenciado e armazenamento de objetos para backup |
| 1 fora do local | Cópia em outro lugar | Cópia em outra região ou fora do provedor principal |

Nas portarias, os arquivos locais (`dados/portarias/`) também precisam de cópia: backup periódico do PC da portaria para a sede quando houver conexão [A DEFINIR]. Testar a restauração faz parte da rotina, porque um backup não restaurado não é garantia.

## 5. Riscos que a infraestrutura não elimina

| Risco | Observação |
|---|---|
| PC da portaria comprometido | Roda o nó local com dados pessoais; exige bloqueio de tela, usuário comum e atualização |
| Pessoa com acesso físico | O gabinete do roteador e do switch deve ficar trancado |
| Falta de energia prolongada | O nobreak tem autonomia limitada |
| Fornecedor de nuvem indisponível | A portaria continua operando; a sede perde a visão consolidada até a volta |

## 6. Como o laboratório demonstra isso

O roteiro do Packet Tracer ([`packet-tracer/roteiro.md`](packet-tracer/roteiro.md)) implementa três regras desta página: o Wi-Fi de visitantes não alcança a portaria nem a nuvem, a portaria só alcança a API, e o banco só é alcançado pela rede da API. A VPN IPsec aparece apenas no diagrama.
