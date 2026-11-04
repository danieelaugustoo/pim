# Cenários do Product Owner e do Scrum Master

> Cenários de atuação do Product Owner e do Scrum Master neste projeto, escritos em 2026-11-03. Os episódios são exemplos construídos pelo grupo, conforme autorização da Prof.ª Eliana informada pelo grupo (registrada em `sprints/sprint-04.md`). Os integrantes citados devem conferir o que está escrito em seu nome.

## Quem faz cada papel nos cenários

| Papel | Quem | Perfil no cenário |
|---|---|---|
| Product Owner (PO) | **Lucas Ribeiro Tomiossi Kribely** | Representa a Administradora Morada Central, os 10 condomínios e os porteiros; decide a ordem do backlog |
| Scrum Master (SM) | **Daniel Augusto Amarante da Silva** | Facilita as cerimônias por mensagem, cuida do quadro Kanban e remove impedimentos |
| Time de desenvolvimento | Pedro Urquisa Rocha, Adilson Batista do Nascimento de Lima e Ysaac de Souza França, mais PO e SM, que também desenvolvem | Entregam as histórias e revisam o trabalho uns dos outros |

Nos cenários em que aparece um "Integrante" sem nome (A, B, C), é um papel genérico do time, **não** uma pessoa específica.

---

## Parte 1: cenários do Product Owner

O PO responde à pergunta "o que entra primeiro e por quê". Ele não programa e não decide *como* fazer.

### Cenário PO-1: priorizar o backlog com tempo curto

**Contexto.** Faltam poucos dias úteis para o prazo. O backlog (`backlog.md`) tem US16 (devolução), ainda sem prazo de devolução definido, e histórias de relatório já prontas. O time pergunta o que fazer com o tempo que sobra.

**Conversa**

> **Daniel (SM):** Lucas, sobrou capacidade. O time pergunta se faz a US16 ou melhora os relatórios.
> **Lucas (PO):** Pergunta de volta: quem sente a falta de cada uma? Hoje o que dói na portaria é encomenda parada e extravio. Devolução é rara e eu nem defini o prazo para devolver.
> **Lucas (PO):** Decisão: US16 não entra. Registrem como evolução futura. A sobra vai para teste e revisão do que já existe, porque uma entrega que funciona vale mais que uma a mais pela metade.

**Critério usado pelo PO:** valor para a portaria, risco de ficar incompleta e dependência de regra ainda indefinida.

**Resultado:** US16 permanece "Não iniciada" no backlog, com a nota "evolução futura" (consistente com a decisão do grupo em `sprint-04.md`).

### Cenário PO-2: aceitar ou devolver uma história na revisão

**Contexto.** Na revisão da sprint, o time demonstra o alerta de volumes parados há mais de 7 dias (US13).

**Conversa**

> **Lucas (PO):** Conferi pelos critérios Dado/Quando/Então da US13. Com 8 dias de espera o volume aparece, e com 5 não aparece. Aceito.
> **Lucas (PO):** Só uma observação que vira item novo, não bloqueia: o porteiro precisa ver quem é o destinatário na mesma linha, para cobrar a retirada sem abrir outra tela.

**Regra ilustrada:** o PO aceita pela **definição de pronto** e pelos critérios de aceitação; pedido novo vira item no backlog, não altera a história já aceita.

### Cenário PO-3: pedido de mudança no meio da sprint

**Contexto.** A diretoria da administradora pergunta se o aviso poderia sair por um aplicativo de mensagens específico.

**Conversa**

> **Lucas (PO):** Entendi o pedido, mas a sprint já tem meta. O sistema hoje avisa por APP, SMS ou INTERFONE, conforme o canal do morador. Incluir um canal novo muda a integração e os testes.
> **Lucas (PO):** Registro como evolução futura e levo para o planejamento da próxima sprint, se houver. Esta sprint não muda.

**Regra ilustrada:** a meta da sprint é protegida; mudança vira backlog.

### Cenário PO-4: conflito entre o que o porteiro quer e o que a administradora quer

**Contexto.** Os porteiros querem ver o código de retirada na tela para conferir mais rápido. A administradora teme que isso facilite uso indevido.

**Conversa**

> **Lucas (PO):** Os dois lados têm razão. Decisão para o protótipo: o código aparece na tela do porteiro, porque sem isso a demonstração não fecha. Na lista de limitações vai escrito que, em produção, ele deveria ser mostrado só ao morador.
> **Daniel (SM):** Anoto a decisão e a limitação no registro da sprint.

**Regra ilustrada:** o PO decide, registra o motivo e declara a limitação, em vez de esconder o problema (alinhado à decisão do grupo sobre o código na tela, em `sprint-04.md`).

---

## Parte 2: cenários do Scrum Master

O SM responde à pergunta "o processo está fluindo e o que está travando o time". Ele não prioriza o backlog e não manda no conteúdo técnico.

### Cenário SM-1: daily assíncrona

Formato do `papeis-e-cerimonias.md`: poucas linhas por pessoa, no grupo de mensagens, em dia útil.

**Exemplo**

> **Integrante A:** Ontem: rascunho do capítulo 6. Hoje: revisar os trechos de código. Impedimento: nenhum.
> **Integrante B:** Ontem: DER no capítulo 5. Hoje: conferir os nomes das tabelas com o script SQL. Impedimento: preciso de alguém para revisar.
> **Integrante C:** Ontem: tentei instalar o simulador de redes e deu erro de login. Hoje: tentar de novo. Impedimento: sim, preciso de ajuda.
> **Daniel (SM):** B, o A revisa seu capítulo hoje à noite. C, vejo isso agora (cenário SM-2).

### Cenário SM-2: remover um impedimento

**Contexto.** O Integrante C não consegue entrar no simulador de redes, e os testes T1 a T15 do roteiro dependem dele.

**Passos do SM**

1. Confirma na daily que o bloqueio é só do C e que os outros não têm o problema.
2. Pergunta se algum integrante já tem o simulador funcionando e pode montar a topologia.
3. Combina que quem tem o simulador monta e roda os testes, e o C acompanha por chamada de vídeo para aprender e revisar o capítulo 7.
4. Registra o impedimento e a solução em `sprint-NN.md`, na seção de impedimentos.

**Regra ilustrada:** o SM não instala o programa por ele; remove o bloqueio redistribuindo o trabalho e mantendo a aprendizagem (regra 11 do `CLAUDE.md`).

### Cenário SM-3: risco de estourar o limite de páginas

**Contexto.** O desenvolvimento passa do limite de 30 páginas (`estrutura-e-paginas.md`, seção 8).

**Conversa**

> **Daniel (SM):** Estamos acima do limite. Proponho olhar o plano de cortes e cada responsável cortar o seu capítulo, nesta ordem: repetição entre capítulos, tabelas que ficam melhor no repositório e fluxogramas que não são essenciais.
> **Daniel (SM):** Prazo de cortes: antes da revisão por pares, para o revisor ler o texto já enxuto.
> **Lucas (PO):** O que não pode sair: problema, solução, arquitetura e resultados. O resto, vocês decidem.

**Regra ilustrada:** o SM conduz a decisão e o prazo; o PO diz o que é essencial; o conteúdo continua com o time.

### Cenário SM-4: retrospectiva (formato Começar, Parar, Continuar)

Exemplo de como a retrospectiva por mensagem escrita fica. As retrospectivas de cada sprint ficam em `sprints/sprint-04.md` e `sprint-05.md`.

> **Mensagem do SM, sexta, 19h**
>
> **Continuar:** daily curta no grupo; revisão por pares antes de fechar cada capítulo; registrar decisões no `sprint-NN.md`.
> **Parar:** deixar a verificação das fontes para o fim; acumular rascunhos sem revisar.
> **Começar:** definir um responsável e um revisor por capítulo desde o início; rodar `make test` no computador da apresentação antes de gravar a demonstração; reservar um dia só para ABNT e similaridade.
> **Ação para a próxima sprint:** cada integrante confirma no grupo, até segunda, o seu capítulo e o seu revisor.

### Cenário SM-5: proteger a meta da sprint

**Contexto.** Um integrante propõe reescrever o módulo de relatórios "para ficar mais bonito" na semana da entrega.

**Resposta do SM**

> **Daniel (SM):** A meta desta sprint é revisar, fechar o documento e postar. Reescrever relatório não ajuda nisso e arrisca quebrar os testes que já passam. Anota como ideia para a evolução futura. Se alguém ainda quiser mexer, abre uma branch, roda `make test` e mostra que nada quebrou antes de qualquer merge.

---

## Como usar este material no trabalho

- No capítulo 4 (Engenharia de Software), usar um ou dois cenários para mostrar **o que cada papel faz**, mesmo com a estrutura simplificada.
- As falas não são fonte nem autoria; não entram nas referências.
