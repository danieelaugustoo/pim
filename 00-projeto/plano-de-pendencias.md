# Plano de pendências até a entrega

**Criado em:** terça, 03/11/2026. **Prazo final:** sábado, 14/11/2026, até as 23h59 (recomendado postar até sex 13/11 à noite).
**Como usar:** marque `[x]` ao concluir cada item e, ao terminar, atualize `00-projeto/rastreabilidade.md` e a `sprint-NN.md` da sprint atual (regra 12 do `CLAUDE.md`). Responsáveis sem nome estão `[A DEFINIR]` pelo grupo.

**Já está pronto (não precisa refazer):** protótipo em C com `make test` passando e sem warnings; scripts SQL executados em MySQL 8.4.13; rascunhos de todos os capítulos, já enxutos (desenvolvimento com cerca de 8.690 palavras); PNG dos diagramas Mermaid (figuras 01 a 03, 09, 10, 12 e 16, mais fluxogramas A1 a A6 e topologia); `referencias.md` conferido contra as citações; titulares do Scrum (Lucas, PO e líder; Daniel, Scrum Master).

---

## 1. Para o Daniel fazer em casa (máquina da apresentação)

### 1.1 Rodar o programa e tirar os prints (prazo: qui 05/11)

> **Atenção na demonstração:** a coluna **Antigas** do relatório (e a lista de pendências antigas) depende da **data do computador**. Em 29/10 os dados de exemplo davam 2 antigas (P01) e 0 (P02); rodando em 04/11 deu 4 e 4 (total 8). O capítulo 6 já informa isso, mas na apresentação os números vão diferir do Quadro 4. Os demais valores (registradas, pendentes, retiradas, devolvidas, dia de pico, 17 operações e 14 encomendas) não mudam. Conferido em 04/11 por execução do `bin/central`.

- [ ] Atualizar o repositório na branch `claude/jolly-johnson-cue2j0` (`git pull`).
- [x] **Print do `make test` feito em 2026-11-04** (Figura 11, `figura-11-testes-automatizados.png`): no notebook do Daniel o Device Guard bloqueou o `test_codigo.exe` em algumas tentativas, e repetir o `.\build.bat test` em laço (até 10 vezes) fez os 9 testes passarem. O bloqueio é intermitente (já registrado no `sprint-01.md`). Se acontecer ao vivo na apresentação, não rodar os testes: mostrar o print.
- [ ] (original, se o Device Guard não bloquear) Dentro de `05-programa-c/`, rodar `make test` (no Windows, `build.bat`). Tirar o **print do resultado** ("Todos os testes passaram") → entra no capítulo 6, seção 6.5. Se algum teste falhar na sua máquina, copiar a mensagem e mandar para o Claude.
- [x] *(Figura 12 — mapa da estante — feita em 2026-11-04: `figura-12-mapa-estante.png`, 6 de 48 ocupadas, 12,5%.)*
- [ ] ~~Copiar os dados de exemplo~~ (já feito para a Figura 12; refazer só se for ensaiar de novo)
- [ ] (original) Copiar os dados de exemplo (comandos em `05-programa-c/README.md`, seção "Demonstração com os dados de exemplo"), rodar `bin/portaria 1`, escolher a opção **5 (mapa da estante)** e tirar o print → **Figura 12**, salvar como `documento-final/figuras/figura-12-mapa-estante.png`.
- [ ] Rodar `bin/central` duas vezes e conferir se a segunda aplica 0 operações (é o que o texto do capítulo 6 afirma). Se o resultado for diferente, avisar para corrigirmos o texto.
- [ ] Ensaiar a demonstração do início ao fim (registrar, retirar, offline, sincronizar, central, relatório) para a apresentação.

### 1.2 Banco de dados (prazo: qui 05/11)

**Concluído em 2026-11-04:** scripts 01, 02 e 04 executados em MySQL 8.4 (Docker) e print da consulta de pendências por condomínio (Aurora 6, Bela Vista 5) como **Figura 9** (`figura-09-consulta-sql.png`).

- [ ] Rodar os scripts de `04-banco-de-dados/sql/` em ordem (01, 02, 03, 04) no MySQL Workbench ou no terminal.
- [ ] Tirar o print de **uma consulta com resultado** (por exemplo, pendências por condomínio) → capítulo 5, seção 5.5, como figura.

### 1.3 Packet Tracer (prazo: qua 04/11 montar; qui 05/11 prints)

**Packet Tracer concluído em 2026-11-04:** topologia montada, T1 a T15 executados (todos como esperado), HTTP/HTTPS no `SRV-API`, Wi-Fi dos três laptops, figuras 13 a 15 e `morada-central.pkt` no repositório; capítulo 7, conclusão, introdução, resumo e abstract atualizados. T9 confirmado pelo grupo em 04/11 (CFTV → API não responde). Nada mais pendente no Packet Tracer.

Seguir `06-redes/packet-tracer/roteiro.md` (VPN fica só no diagrama, decisão do grupo).

- [ ] Montar a topologia (sede, condomínios 1 e 3, servidor da central e switch que simula a internet).
- [ ] Executar os testes **T1 a T15** e anotar **esperado × obtido** de cada um. Se algum não funcionar, anotar o erro (o Claude ajuda a corrigir o roteiro).
- [ ] Prints obrigatórios: **topologia (Figura 13)**, **T2** portaria alcança a central e **T6** visitantes não alcançam a portaria (juntos na **Figura 14**). Salvar o `.pkt` como `06-redes/packet-tracer/morada-central.pkt` e os prints em `documento-final/figuras/`.
- [ ] Anotar a **versão do Packet Tracer** (capítulo 4, seção 4.7 tem `[VERSÃO A CONFIRMAR]`).
- [ ] Mandar para o Claude o resultado dos testes: ele preenche a seção 7.7, a conclusão e a introdução.

**Se o Packet Tracer atrasar:** o capítulo 7 fica só com o projeto, a declaração de que os testes não foram executados e a retirada de "simulação de rede" da introdução (marca `[ATUALIZAR]` já colocada).

---

> **Mudança de responsável (2026-11-04):** o Daniel assumiu **todas** as tarefas que estavam com o "grupo" (seções 2 e 4 abaixo, e o item "para a apresentação"). Continuam com outras pessoas apenas a **postagem e a cópia impressa** (Lucas, o líder) e a **revisão por pares**, que precisa ser de **outro integrante** (basta uma pessoa para ler os capítulos e o código na terça e quarta). Onde o texto abaixo diz "grupo", leia "Daniel".

> **Atualização de 2026-11-05:** cortes aplicados (ver `documento-final/estrutura-e-paginas.md`); o teste do LibreOffice dá cerca de 29 páginas da introdução à conclusão com as figuras em tamanho legível. A menção ao Claude Code no capítulo 4 foi retirada por decisão do Daniel. As Figuras 2, 3, 10 e 15 foram redesenhadas em grade, porque as versões verticais não davam para ler.

> **Atualização de 2026-11-04 (noite):** os capítulos 1 a 10, o resumo e o abstract foram reescritos (sem a palavra "fictícia", com voz mais natural) e o texto está em cerca de 30 páginas no teste do LibreOffice. **Falta de verdade:** (1) montar no **Word com o modelo da UNIP** (capa, sumário, numeração de página a partir da introdução, legendas) e conferir as páginas; (2) as **figuras 4 a 7 (UML)**; (3) resolver as **marcas `[ ... ]`** que sobraram no texto (fontes, WCAG, metas, link do GitHub); (4) **revisão por outra pessoa**; (5) similaridade, PDF e postagem pelo Lucas; (6) preparar a **apresentação** (demonstração, Canva e banner).

## 2. Para o Daniel decidir ou conferir (antes: "o grupo") (prazo: qua 04/11 a sex 06/11)

### 2.1 Fontes e leitura

Revisado em 2026-11-04: **ninguém precisa ler livro inteiro**, e o grupo decidiu também não conferir o sumário dos livros.

- [x] ~~F02, F03 e F04 (Condomínios SC)~~: **dispensadas**, nenhum capítulo as cita. Só voltam à lista se o grupo decidir usá-las.
- [x] **MACK (2024)**, citada nos capítulos 1, 2 e 3: já verificada (artigo de opinião do Diário do Comércio, 28/11/2024). Falta só conferir a data de acesso em `referencias.md`.
- [x] **Livros citados** (Elmasri e Navathe, Heuser, Sadalage e Fowler, Deitel e Deitel, Forbellone e Eberspächer, Tanenbaum e Wetherall, Kurose e Ross, Tanenbaum e Van Steen): **sem conferência de sumário, por decisão do grupo (2026-11-04)**. O texto os usa só para afirmações gerais de manual, e os dados bibliográficos foram verificados em catálogo. O Claude não abriu as obras. Se a professora pedir a página de alguma afirmação, o grupo precisa conseguir mostrá-la; se preferir não correr esse risco, a alternativa é tirar a citação e manter a frase sem fonte (o Claude faz a limpeza).
- [x] Documentos abertos na internet (Guia do Scrum 2020, RFC 5737, NIST SP 800-145 e FIPS 180-4, WCAG 2.2, **LGPD e LBI**): já verificados em fonte oficial em 29/10 (`02-pesquisa/fontes.md`, seção 4) e conferidos de novo por fontes secundárias em 04/11. Com isso, dois pontos do capítulo 8 foram ajustados (o encarregado pode ser dispensado pela ANPD; o art. 63 também vale para órgãos de governo). Nada a ler pelo grupo. **Opcional:** ao montar as referências, abrir o Planalto uma vez só para anotar a data de acesso.
- [x] **Data do FIPS 180-4** em `documento-final/referencias.md`: conferida pelo grupo na capa do PDF em 04/11 (agosto de 2015); nada a corrigir.
- [ ] Capítulo 3, seção 3.5: escrever, **com as próprias palavras**, 1 ou 2 frases de síntese para cada um dos 5 ou 6 temas (Scrum, bancos de dados, C e algoritmos, redes e nuvem, proteção de dados e acessibilidade). É a parte mais autoral do trabalho.
- [ ] Capítulo 3, seção 3.6: pesquisar **produtos reais** de cada categoria (aplicativos de gestão condominial, armários inteligentes, portaria remota), preencher `02-pesquisa/trabalhos-relacionados.md` com a fonte de cada célula e só então afirmar o que a proposta tem de diferente (capítulos 3 e 9). Sem fonte, nenhum produto deve ser citado. **Se o tempo apertar**, manter a seção como descrição da comparação e não afirmar diferencial frente a produtos reais.
- [ ] Marcas `[FONTE A VERIFICAR]`: referência de UML (cap. 4), referência metodológica se o professor exigir (cap. 3), dados do setor (cap. 2), VLSM (cap. 7), documentos de direitos humanos (cap. 8), prazos legais de retenção (cap. 8). **Alternativa para cada uma:** buscar a fonte ou tirar a afirmação.

### 2.2 Decisões

- [ ] **Nível WCAG** adotado (A, AA ou AAA) no capítulo 8, seção 8.3.
- [ ] **Metas dos indicadores** do capítulo 9 (Quadro 7) ficam `[A DEFINIR]`: definir como metas ou deixar assim e declarar.
- [ ] Mencionar ou não o **Claude Code** na seção de ferramentas (cap. 4, 4.7). A Prof.ª Eliana autorizou o uso de IA e o grupo disse que não é preciso declarar; a decisão de citar é do grupo.
- [ ] Escrever os **aprendizados próprios** do grupo na conclusão (marca `[o grupo pode acrescentar aprendizados próprios]`).
- [ ] Decidir se o repositório fica **público ou privado** (nomes e RA dos integrantes ficam visíveis se for público; ver `00-projeto/integrantes.md`).
- [ ] Preencher a **retrospectiva** da Sprint 4 (mensagem escrita) e `Responsável` das etapas em `00-projeto/integrantes.md`.

### 2.3 Dúvidas para a Prof.ª Eliana (uma mensagem só)

- [ ] Introdução e conclusão entram na contagem das 20 a 30 páginas do desenvolvimento?
- [ ] Apêndices (código, scripts, comandos) contam nas páginas? (Decisão do grupo é só colocar o link do GitHub.)
- [ ] Guardar a resposta por escrito, inclusive a que autoriza os cenários de PO e SM (`sprint-04.md`).

---

## 3. Para o Claude fazer (quando o grupo liberar ou mandar o resultado)

- [ ] **Renderizar o PlantUML** (figuras 04 a 08): liberar a permissão de Bash para `java -jar` do PlantUML (Graphviz já está instalado) ou exportar pela extensão do VS Code para `documento-final/figuras/` com os nomes `figura-04-casos-de-uso.png`, `figura-05-classes-dominio.png`, `figura-06-atividade-registrar-encomenda.png`, `figura-07-sequencia-sincronizacao.png` e `estados-encomenda` (opcional, sem número: não é citado no capítulo 4).
- [ ] Preencher **7.7 (resultados dos testes)**, a conclusão (objetivo 5) e a introdução com o resultado do Packet Tracer, quando o Daniel mandar.
- [ ] Atualizar capítulos 5 e 6 se os prints mostrarem diferença do texto.
- [ ] Aplicar os **cortes de figuras** se o Word passar de 30 páginas (lista em `documento-final/estrutura-e-paginas.md`, seção 8).
- [ ] Repetir a conferência de citações × referências depois da revisão do grupo.
- [ ] Abrir o **pull request para a `main`** quando o grupo pedir, depois da revisão final.

---

## 4. Revisão por pares (ter 10/11 a qua 11/11)

Cada capítulo é lido por **outro** integrante, que confere contra a definição de pronto (`03-engenharia-software/scrum/definicao-de-pronto.md`) e marca `Revisado` na rastreabilidade. O autor não revisa o próprio capítulo.

| Capítulo | Quem escreve/ajusta | Quem revisa |
|---|---|---|
| 1 Introdução, resumo, abstract e 10 Conclusão | [A DEFINIR] | [A DEFINIR] |
| 2 Organização | [A DEFINIR] | [A DEFINIR] |
| 3 Pesquisa | [A DEFINIR] | [A DEFINIR] |
| 4 Engenharia de software | [A DEFINIR] | [A DEFINIR] |
| 5 Banco de dados | [A DEFINIR] | [A DEFINIR] |
| 6 Programação em C | [A DEFINIR] | [A DEFINIR] |
| 7 Redes | [A DEFINIR] | [A DEFINIR] |
| 8 Segurança e acessibilidade | [A DEFINIR] | [A DEFINIR] |
| 9 Integração | [A DEFINIR] | [A DEFINIR] |

- [ ] **Abstract em inglês**: alguém com bom inglês revisa.
- [ ] Revisão por pares do **código C** (comentários, nomes, regras do `CLAUDE.md`). O grupo precisa saber explicar o código na apresentação.

---

## 5. Montagem, ABNT e postagem

| Quando | O que | Quem |
|---|---|---|
| seg 09/11 | Fechar introdução, conclusão, resumo e abstract com os resultados finais; resolver as marcas `[ATUALIZAR]` | [A DEFINIR] |
| qua 11/11 | Montar no **modelo da UNIP** (Word): capa, sumário, figuras e quadros numerados, legendas e fontes; ver a **paginação real** (20 a 30 páginas) e aplicar cortes | [A DEFINIR] |
| qui 12/11 | Revisão **ABNT** (`documento-final/checklist-abnt-e-entrega.md`), **similaridade** e gerar **PDF e .docx** em `documento-final/versoes/`; resolver todas as marcas `[FONTE A VERIFICAR]`, `[A DEFINIR]` e `[A PREENCHER]` | [A DEFINIR] |
| sex 13/11, 19h | Retrospectiva da Sprint 5 por mensagem e conferência final | Daniel (Scrum Master) |
| sex 13/11 | **Postagem** no sistema da UNIP (cadastrando os demais integrantes), guardar o comprovante, e **entregar a cópia impressa** ao coordenador | Lucas (líder) |
| sáb 14/11 | Reserva, só para imprevistos (prazo 23h59) | todos |

- [ ] Rodar `make test` de novo antes de congelar a versão final e anotar o resultado.
- [ ] **Criar as tags do repositório** (convenção: uma por sprint, `v0.1.0` em diante, e `v1.0.0` na entrega). Nenhuma tag está no GitHub: o acesso da sessão do Claude não permite enviar tags. Rodar na máquina do Daniel, dentro do repositório atualizado, os comandos abaixo (os hashes são os commits em que cada sprint foi registrada) e depois `git push origin --tags`:

```bash
git tag -a v0.1.0 36376ca -m "Sprint 0: base do projeto, Etapas 1 a 3"
git tag -a v0.2.0 2a9b371 -m "Sprint 1: portaria funcionando (US01-US06) e banco de dados"
git tag -a v0.3.0 0f0452d -m "Sprint 2: sistema distribuido (US07-US11) e redes"
git tag -a v0.4.0 7d01558 -m "Sprint 3: relatorios e qualidade (US12-US15)"
git push origin --tags
```

  Faltam ainda a tag da Sprint 4 (`v0.5.0`, sex 06/11), a da Sprint 5 e a `v1.0.0` da entrega.
- [ ] **Conferir o link do GitHub no capítulo 6** (inserido em 2026-11-04, na seção 6.1, com marca `[CONFERIR]`): ele só funciona para quem corrige se o repositório for público ou se o acesso for concedido.

---

## 6. Riscos e plano B

| Risco | Plano B |
|---|---|
| Packet Tracer não fica pronto | Capítulo 7 só com o projeto; declarar que os testes não foram executados; tirar "simulação de rede" da introdução |
| Passar de 30 páginas no Word | Cortar figuras e juntar prints (`estrutura-e-paginas.md`, seção 8) |
| Professora perguntar onde está a afirmação de um livro | Mostrar a página ou, se não der, tirar a citação e manter a frase sem fonte (o Claude faz a limpeza) |
| Trabalhos relacionados sem pesquisa | Manter a seção 3.6 como metodologia da comparação e não afirmar diferencial frente a produtos reais |
| Pouco tempo para a revisão por pares | Priorizar capítulos 3, 4 e 6, os mais densos |
| Alto índice de similaridade | Reescrever com palavras próprias os trechos que o software marcar; nunca copiar de fonte, de colega ou de IA sem reescrita |
