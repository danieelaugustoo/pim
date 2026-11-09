# Plano do Canva (slides) e do banner

Atualizado em 09/11/2026. A apresentação é: **demonstração do programa + Canva + banner**. Regra do conteúdo: **pouco texto, muito número e figura**. Quem fala conta o resto; o slide só lembra.

## Regras de ouro

1. **No máximo 3 tópicos por slide**, de até 8 palavras cada. Letra com **24 pt ou mais**.
2. **Um número grande vale mais que um parágrafo.** Ex.: "15 de 15 testes".
3. **Só use números do trabalho** (lista no fim). Nada de resultado medido: os benefícios são *esperados*.
4. **Não escrever "fictício".** Para dados, "dados de exemplo".
5. **Não afirmar** que a VPN ou o HTTPS foram testados, nem que os concorrentes "não têm" operação offline.
6. Figuras do trabalho estão em `documento-final/figuras/`. As gradeadas (2, 3, 8) também têm SVG em `figuras/fontes/`, que ampliam sem perder nitidez.

## Slides: 10 no total, para cerca de 21 minutos

| # | Slide | Quem fala | O que entra (máximo) | Figura |
|---|---|---|---|---|
| 1 | **Capa** | todos | Título do trabalho, curso, UNIP Anchieta 2026, os 5 nomes | logo da UNIP |
| 2 | **O problema** | Ysaac | "Caderno na portaria" • extravios e entregas erradas • 10 condomínios, ~960 unidades, 40 porteiros | Figura 2 (processo atual) |
| 3 | **A solução e o diferencial** | Ysaac | Nó na portaria **sem internet** • Central que **não duplica** • Aviso em vários canais | Figura 3 (processo proposto) |
| 4 | **Engenharia de software** | Adilson | Scrum: PO Lucas, SM Daniel • 16 histórias (15 feitas) • 12 RF, 8 RNF, 8 casos de uso | Figura 4 (casos de uso) |
| 5 | **Como a sincronização funciona** | Adilson | Cada operação tem **id único** • Central ignora ids já aplicados • Reenviar não duplica | Figura 5 (sequência) |
| 6 | **Banco de dados** | Lucas | MySQL 8 • 11 tabelas, 44 restrições • 3ª forma normal | Figura 6 (DER) |
| 7 | **Banco: provas** | Lucas | Código só como **hash SHA-256** • Resultados batem com o programa em C | Figura 7 (consulta SQL) |
| 8 | **Programação em C** | Daniel | C99, sem avisos • Matriz da estante 4x12 • 9 conjuntos de testes | Figura 8 (fluxograma A1) |
| 9 | **Demonstração ao vivo** | Daniel | Slide só com os 4 passos: *offline → registrar → sincronizar → retirar* | nenhuma (programa rodando) |
| 10 | **Redes e fechamento** | Pedro | 44 redes, 4 VLANs • **15 de 15** testes • Conclusão: viável; benefícios a medir em piloto | Figuras 9 (topologia) e 10 (testes T2 e T6) |

Se couber, um **slide 11 de encerramento** com "Obrigado", o link do GitHub (`github.com/danieelaugustoo/pim`) e o QR code.

## Banner: o que entra e em que ordem

**Formato:** o grupo faz no Canva. **O tamanho (A1, A0, etc.) precisa ser confirmado com a professora ou com a UNIP**: eu não tenho essa informação. Organizar em **3 colunas**, lendo da esquerda para a direita.

| Posição | Bloco | Conteúdo enxuto | Figura |
|---|---|---|---|
| Topo, largo | **Título e autores** | Título do trabalho • "PIM II • ADS • UNIP Anchieta 2026" • 5 nomes • logo da UNIP | logo |
| Coluna 1 | **Problema** | Caderno na portaria: extravios, entregas erradas, sobrecarga • 10 condomínios, ~960 unidades, 40 porteiros | Figura 2 |
| Coluna 1 | **Solução** | Nó offline na portaria + central que consolida sem duplicar | Figura 3 |
| Coluna 2 | **Como funciona** | Sincronização com id único • Código de retirada de 6 dígitos, 3 tentativas • Aviso por app, SMS ou interfone | Figura 5 |
| Coluna 2 | **Banco de dados** | 11 tabelas • 44 restrições • 3ª forma normal | Figura 6 |
| Coluna 3 | **Rede** | 44 redes • 4 VLANs • 15 de 15 testes | Figura 9 |
| Coluna 3 | **Programa em C** | C99 sem avisos • 9 conjuntos de testes • estante 4x12 | Figura 8 |
| Faixa de números | **5 números grandes** | **10** condomínios • **15 de 16** histórias • **11** tabelas • **9** testes em C • **15 de 15** testes de rede | só números |
| Rodapé | **Limites e próximos passos** | Aviso e rede simulados • benefícios ainda a medir em piloto • evolução: API real, banco ligado, app do morador | nenhuma |
| Canto | **QR code** | Link do GitHub para o código completo | QR |

**Qualidade de impressão:** a imagem dos casos de uso (Figura 4) e a da sequência (Figura 5) são de **baixa resolução** (cerca de 700 a 900 pixels de largura) e podem ficar borradas se ampliadas. Para o banner, o ideal é exportar de novo com `skinparam dpi 300` na primeira linha do `.puml`. As figuras 2, 3, 8 têm SVG, que não perde nitidez.

## O que NÃO colocar (no slide nem no banner)

- Trechos de código longos (se quiser mostrar código, só **3 a 5 linhas** do A1 ou do A5).
- Qualquer **percentual de melhoria** ou "redução de extravios": não foi medido.
- A palavra **"fictício"** e a afirmação de que **a VPN foi testada**.
- Mais de **uma figura por slide**, exceto no slide 10.

## Números que podem aparecer (todos estão no trabalho)

10 condomínios • cerca de 960 unidades • 40 porteiros • 7 problemas • 16 histórias (15 feitas) • 12 requisitos funcionais e 8 não funcionais • 8 casos de uso • 11 tabelas e 44 restrições • 9 conjuntos de testes em C • matriz 4x12 • 500 encomendas e 300 moradores por portaria • código de 6 dígitos com 3 tentativas • 44 redes `10.X.Y.0/24` • VLANs 10, 20, 30 e 99 • 15 testes de rede, todos como esperado • Packet Tracer 9.0.1 • MySQL 8.4.

## Ordem de trabalho sugerida para o grupo

1. **Cada um monta o próprio slide** (ou dois) no Canva, seguindo a tabela acima.
2. **Alguém junta** tudo em um arquivo único e padroniza fonte e cores (sugestão: fundo claro, uma cor de destaque).
3. **Um responsável pelo banner**, usando os blocos da tabela, e outro revisa os números contra a lista acima.
4. **Ensaio completo** com os slides, cronometrando 21 minutos.
