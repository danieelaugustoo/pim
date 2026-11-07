# Bloco 2: Engenharia de Software Ágil (Adilson)

Tempo: **cerca de 3 minutos**. Figuras: **4** (casos de uso) e **5** (sequência da sincronização). Só use números que estão no trabalho. Capítulo de apoio: 4.

## Roteiro de fala

**1. Processo ágil (45 s).** "Usamos o Scrum simplificado. O **Lucas** é o Product Owner, o **Daniel** é o Scrum Master e os demais formam o time de desenvolvimento. A revisão e a retrospectiva de cada sprint saem por mensagem escrita no grupo, às sextas, às 19h, e ficam registradas em arquivos no repositório. O backlog tem **16 histórias de usuário**, escritas no formato Dado, Quando, Então. **15** foram implementadas. A 16ª, a devolução de volumes, ficou como evolução futura, porque depende de um prazo que a administradora precisa definir."

**2. Requisitos (30 s).** "Definimos **12 requisitos funcionais**, como registrar a encomenda, indicar a posição na estante, gerar o código de retirada, avisar o morador, registrar a retirada, sincronizar sem duplicar e gerar relatórios, e **8 não funcionais**, como a portaria não depender de internet, rastreabilidade e acessibilidade."

**3. Casos de uso (40 s).** "Os requisitos se agrupam em **oito casos de uso**: registrar encomenda, avisar morador, retirar encomenda, consultar pendências, manter moradores, sincronizar com a central, consolidar operações e emitir relatórios. Os atores são o porteiro, o morador, o supervisor e dois sistemas, a central e o serviço de avisos." *(Figura 4)*

**4. Arquitetura e a decisão principal (50 s).** "O sistema completo tem duas partes: um **nó de portaria** em cada condomínio, que opera sem internet, e um **servidor central**, com API e banco relacional. A decisão mais importante, a ADR-003, é a sincronização assíncrona: cada evento vira uma operação com **identificador único**, guardada em uma fila, e a central ignora os identificadores já aplicados. Então reenviar um lote não duplica registros." *(Figura 5: a portaria só envia a fila quando está online, e a central aplica cada operação uma única vez.)*

**5. Qualidade e ferramentas (15 s).** "A definição de pronto exige compilação sem avisos, testes passando, funções comentadas e revisão por outro integrante. São 9 conjuntos de testes automatizados. Usamos C, Git, MySQL em Docker, PlantUML, Mermaid e o Packet Tracer."

## O que NÃO dizer (o trabalho declara como limite)

- No trabalho aparecem **só dois diagramas UML**: casos de uso e sequência. O de classes e o de atividade estão no repositório, não no documento.
- Os requisitos vêm do cenário e da análise do processo, **não de entrevistas** com usuários.
- As **sprints 0 a 3 rodaram em um ciclo único em 29/10/2026** (datas do histórico do Git). Se perguntarem, não finja que foram quatro semanas separadas.
- Os benefícios ainda **não foram medidos**.

## Perguntas de engenharia de software que podem cair

| Pergunta | Resposta |
|---|---|
| O que é o Scrum? | Um modelo de trabalho em ciclos curtos, as sprints, com inspeção e adaptação ao fim de cada uma, e papéis de Product Owner, Scrum Master e Developers. |
| Qual o papel de cada um no grupo? | Lucas é o Product Owner (decide a ordem do backlog) e o líder da postagem. Daniel é o Scrum Master (facilita e remove impedimentos). Os demais desenvolvem. |
| O que é uma história de usuário? | Uma funcionalidade escrita do ponto de vista de quem usa, com critérios de aceitação em Dado, Quando, Então. Temos 16. |
| Qual a diferença entre requisito funcional e não funcional? | Funcional é o que o sistema faz (registrar encomenda). Não funcional é como ele se comporta (funcionar sem internet, ser rastreável). |
| O que é um caso de uso? | Uma interação entre um ator e o sistema para atingir um objetivo, como "retirar encomenda". Temos 8. |
| O que é idempotente? | Aplicar a mesma operação várias vezes dá o mesmo resultado que aplicar uma. A central anota os ids aplicados e ignora repetidos. |
| O que é uma ADR? | Um registro de decisão de arquitetura no repositório. As principais: MySQL 8 (ADR-001), CSV no protótipo (ADR-002), sincronização assíncrona idempotente (ADR-003). |
| O que é a definição de pronto? | Compila sem avisos, testes passando, funções comentadas, critérios de aceitação atendidos, rastreabilidade atualizada e revisão por outro integrante. |
| Por que a devolução não foi feita? | Depende de um prazo de devolução que a administradora precisa definir. Ficou como evolução futura. |
| Por que não há interface gráfica? | O protótipo é de console, com foco no núcleo (registro, fila, sincronização, consolidação e relatórios). Interface é evolução futura. |
