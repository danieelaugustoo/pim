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

*(escrever aqui)*
