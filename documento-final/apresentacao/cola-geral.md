# Cola geral da apresentação (para o grupo se ajudar)

**Projeto:** gestão de encomendas em condomínios. Um **nó em cada portaria que funciona sem internet** e uma **central** que consolida tudo **sem duplicar**. **Ordem:** Ysaac, Adilson, Lucas, Daniel, Pedro (cerca de 21 min). Quem terminou passa a palavra pelo nome do próximo.

## 1. Pesquisa, Tecnologia e Inovação (Ysaac)
- **Problema:** caderno da portaria gera extravios, entrega à pessoa errada e sobrecarga do porteiro.
- **Empresa:** Administradora Morada Central, **10 condomínios**, cerca de **960 unidades**, **40 porteiros**.
- **7 problemas:** extravio, rastreabilidade, tempo do porteiro, aviso falho, acúmulo de volumes, falta de dados, internet instável.
- **Pergunta:** como operação offline + sincronização central reduzem extravios e tempo do porteiro?
- **Diferencial:** offline com sincronização sem duplicar, aviso em vários canais com código impresso, consolidação dos condomínios.
- **Não dizer:** que os concorrentes *não* têm isso (as páginas só *não informam*); número do setor; "fictício" (dizer "dados de exemplo").

## 2. Engenharia de Software Ágil (Adilson)
- **Scrum simplificado:** Lucas é o PO, Daniel é o SM, os outros desenvolvem.
- **16 histórias** de usuário, **15 feitas** (a devolução ficou de fora). **12 requisitos funcionais** e **8 não funcionais**. **8 casos de uso**.
- **Decisão principal (ADR-003):** cada evento vira uma operação com **id único**; a central ignora os ids já aplicados. Reenviar não duplica.
- **Figuras:** 4 (casos de uso) e 5 (sequência).
- **Não dizer:** que os requisitos vieram de entrevistas (vieram do cenário); que as sprints 0 a 3 foram semanas separadas (foram num ciclo único em 29/10).

## 3. Banco de Dados (Lucas)
- **MySQL 8**, modelo relacional (regras: uma retirada por encomenda, uma aplicação por operação).
- **11 entidades, 11 tabelas, 44 restrições.** Normalizado até a **3ª forma normal**.
- **Código de retirada** guardado só como **hash SHA-256**; a chave da tabela de operações impede duplicar.
- **Testado** em MySQL 8.4 (Docker); resultados batem com o relatório do programa em C.
- **NoSQL:** só para o histórico de avisos, no futuro.
- **Não dizer:** que o programa em C usa o banco (usa arquivos CSV); que o hash existe no protótipo (é do sistema completo).

## 4. Programação em C e demonstração (Daniel)
- **C99**, só biblioteca padrão, **sem avisos**. Dois programas: `portaria` e `central`.
- **Matriz da estante 4x12**; até **500 encomendas** e **300 moradores** por portaria; dados em **CSV**.
- **A1** aloca a posição (circular); **A3** retirada **por código** com confirmação S/N (**3 tentativas**); **A5** central idempotente.
- **9 conjuntos de testes**, todos passando.
- **Demonstração:** central 2x, offline, 2 registros, sincronizar, retirada (código errado, N, S), relatório.
- **Não dizer:** que o código some da tela (aparece, é limitação); que o aviso é real (é simulado); que a coluna ANTIGAS é a do trabalho (muda com a data).

## 5. Redes, segurança e conclusão (Pedro)
- **Topologia:** sede, 10 condomínios e nuvem; estrela em cada local; nuvem no centro com **VPN** (11 túneis).
- **Endereços:** `10.X.Y.0/24`, **44 redes**, sem sobreposição. **VLANs:** 10 portaria, 20 CFTV, 30 visitantes, 99 gerência.
- **Packet Tracer 9.0.1:** **15 testes**, todos como esperado (portaria alcança a central; visitante não alcança a portaria; rede local segue sem a nuvem).
- **Privacidade:** LGPD, dados mínimos, retenção de 90 dias (decisão de projeto). **Inclusão:** interfone com código impresso. **WCAG:** nível AA nas telas futuras.
- **Conclusão:** viabilidade demonstrada; benefícios **ainda não medidos**; só um piloto mostra.
- **Não dizer:** que a VPN foi testada (só no desenho); que o HTTPS foi testado; que reduziu extravios.

## Números rápidos

| O quê | Valor | O quê | Valor |
|---|---|---|---|
| Condomínios | 10 | Tabelas / restrições | 11 / 44 |
| Unidades / porteiros | ~960 / 40 | Testes automatizados (C) | 9 conjuntos |
| Histórias feitas | 15 de 16 | Testes de rede | 15 de 15 |
| Requisitos | 12 RF + 8 RNF | Redes `/24` | 44 |
| Casos de uso | 8 | Código de retirada | 6 dígitos, 3 tentativas |

## Se alguém travar
1. Complete com **uma frase do bloco dele** (acima) e devolva a palavra.
2. Se não souber a resposta de uma pergunta, diga **"o trabalho declara isso como limite"** e aponte a seção (limitações: 6.7 e 9.4).
3. Se o programa falhar na demonstração, mostre os prints do trabalho (Figuras 7 e 10) e o relatório (Quadro 2).
