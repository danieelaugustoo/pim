# Diferenciais inovadores (Etapa 2)

> Roteiro para o capítulo 3. São diferenciais **da proposta deste projeto**; afirmar que as soluções existentes não os têm depende da pesquisa de `trabalhos-relacionados.md`.

| # | Diferencial | O que significa | Onde está no projeto |
|---|---|---|---|
| D1 | Operação offline com sincronização sem duplicidade | A portaria não para sem internet; as operações vão para uma fila e a central aplica cada uma uma única vez | RF09, RF10, RNF01, ADR-003, algoritmos A4 e A5 |
| D2 | Endereçamento automático na estante | O sistema indica a posição livre conforme bloco e tamanho do volume | RF02, algoritmo A1 |
| D3 | Aviso multicanal com opção de código impresso | App, SMS ou interfone; quem não usa smartphone recebe o código impresso | RF04, RNF08 |
| D4 | Consolidação de vários condomínios | A administradora vê os 10 condomínios em um relatório único | RF10, RF12, módulo `consolidacao` |
| D5 | Dados de pico para dimensionar a equipe | Contagem por dia e dia de pico por condomínio | RF12, algoritmo A6 |

## Para o grupo desenvolver

- Para cada diferencial: qual problema (P1 a P7) ele resolve e como isso seria medido.
- Em que o diferencial é inovador no contexto do estudo e em que é apenas boa prática (evitar exagero).
- Quais limitações o protótipo tem em cada um (aviso e rede simulados, sem interface gráfica).

Nenhum diferencial deve ser apresentado como "único no mercado" sem fonte que sustente.
