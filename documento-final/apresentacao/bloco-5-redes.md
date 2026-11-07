# Bloco 5: Redes, segurança e fechamento

Tempo: **cerca de 5 minutos**. Figuras: **9** (topologia) e **10** (testes T2 e T6). Só use números que estão no trabalho.

## Roteiro de fala

**1. Ideia da rede (45 s).** "A rede tem três tipos de local: a sede, os dez condomínios e a nuvem. Dentro de cada local, a topologia é em estrela: um roteador que também faz o papel de firewall, um switch com VLANs e um ponto de acesso Wi-Fi. Entre os locais, a nuvem é o centro e cada local liga nela por uma VPN, o que dá onze túneis. Um condomínio novo é só mais uma ponta." *(Figura 9)*

**2. Endereços e VLANs (1 min).** "O endereçamento é `10.X.Y.0/24`: X é o local (0 é a sede, 1 a 10 são os condomínios) e Y é a VLAN. Então `10.3.10.10` é o computador da portaria do condomínio 3. São 44 redes, e um script verificou que nenhuma se sobrepõe. As VLANs separam o tráfego por risco: **10** portaria, **20** CFTV, **30** visitantes e **99** gerência."

**3. Regras de acesso (45 s).** "A portaria só alcança a API na nuvem. O CFTV fala só com a própria VLAN. Os visitantes só chegam à internet. A gerência administra os equipamentos por SSH, a partir da sede."

**4. Testes (1 min 15 s).** "Montamos o laboratório no Packet Tracer 9.0.1, com a sede, dois condomínios e um servidor que representa a nuvem. Rodamos 15 testes e todos deram o resultado esperado. Na figura, à esquerda, a portaria do condomínio 1 alcança o servidor da central; à direita, o Wi-Fi de visitantes não alcança a portaria. Quando o tráfego deve ser barrado, a mensagem *Destination host unreachable* vem do próprio gateway, sinal de que as listas de acesso funcionaram. E sem o enlace com a nuvem, a rede local da portaria continua funcionando, que é o que o programa em C usa para guardar a fila." *(Figura 10)*

**5. Segurança e inclusão (45 s).** "Seguimos a LGPD: guardamos só os dados necessários e o sistema não registra o conteúdo da encomenda. Para quem não usa smartphone, o aviso é pelo interfone, com código impresso, e a retirada usa o mesmo código para todos. Para as telas futuras, propomos o nível AA do WCAG."

**6. Fechamento (30 s).** "O que está pronto e testado é o núcleo em C, os scripts do banco e a rede no simulador. O aviso e a rede entre portaria e central são simulados no programa, e a VPN existe só no desenho. Os benefícios, como menos extravios, ainda não foram medidos: só um piloto na administradora mostra. A conclusão é de viabilidade."

## O que NÃO dizer (o trabalho declara como limite)

- Não diga que a VPN foi testada: ela está **só no diagrama**.
- Não diga que testou o HTTPS da API nem o desempenho: **não foram testados**.
- Os testes usam `ping`: provam **conectividade e regras de acesso**, não aplicações.
- Os testes T5 a T8 foram feitos só no laptop de visitante do condomínio 1.
- Não diga que reduziu extravios: os benefícios são **esperados**.

## Perguntas de redes que podem cair

| Pergunta | Resposta |
|---|---|
| O que é VLAN e por que usar? | Rede virtual dentro do mesmo switch. Separa portaria, CFTV, visitantes e gerência, para que um visitante no Wi-Fi não alcance a portaria. |
| O que é o `/24`? | A máscara `255.255.255.0`. Cada VLAN tem uma rede de 254 endereços, fácil de ler, ao custo de gastar mais endereços do que sub-redes menores. |
| Quem faz o roteamento entre as VLANs? | O roteador, com uma subinterface por VLAN em um enlace tronco com o switch (router-on-a-stick). |
| O DHCP distribui quais endereços? | De `.100` a `.199` em cada rede. Os endereços fixos vão de `.10` a `.49`, e o gateway termina em `.1`. |
| Por que `203.0.113.0/24` na simulação? | É uma faixa reservada para documentação (RFC 5737), usada para simular a internet entre os roteadores. |
| Por que nuvem e não um servidor na sede? | A administradora não tem equipe de infraestrutura. O servidor próprio daria mais controle físico, mas exigiria investimento. Provedor e custo não foram definidos. |
| O que acontece se a internet cair? | A portaria continua: os dados ficam em arquivo local, as operações esperam na fila (teste T14 e T15), e o interfone cobre o aviso. |
| Como o aviso funciona para quem não tem smartphone? | Interfone: o porteiro avisa por telefone interno e entrega o código impresso. |
| Qual a retenção dos dados? | Decisão de projeto: 90 dias após a retirada, depois anonimizados. Prazos legais específicos não foram levantados. |
