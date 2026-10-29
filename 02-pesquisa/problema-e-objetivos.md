# Problema, objetivos e justificativa científica (Etapa 2)

> Roteiro para o capítulo 3, que o grupo redige. Aqui ficam tópicos e perguntas-guia, não o texto final.

## 1. Problema de pesquisa

**Sugestão de pergunta (a grupo valida ou reformula):**
Como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo dedicado pelos porteiros à gestão de encomendas em uma administradora de condomínios?

Pontos para o grupo desenvolver:
- Contexto: portarias que controlam encomendas em caderno (`01-organizacao/caracterizacao.md`, P1 a P7).
- Quem é afetado: moradores, porteiros, síndicos e administradora.
- Por que a pergunta é relevante e por que é pesquisável.
- Termos da pergunta que precisam de definição no texto: extravio, entrega incorreta, tempo dedicado, operação offline, sincronização.

## 2. Objetivos

**Objetivo geral.** Desenvolver e documentar uma solução computacional para a gestão de encomendas nas portarias da Administradora Morada Central.

**Objetivos específicos.**

| # | Objetivo | Onde é atendido |
|---|---|---|
| 1 | Caracterizar o processo atual de encomendas e seus problemas | `01-organizacao/` |
| 2 | Levantar requisitos com pesquisa bibliográfica e de campo | `02-pesquisa/`, `03-engenharia-software/requisitos.md` |
| 3 | Modelar o banco de dados relacional e avaliar o uso de NoSQL | `04-banco-de-dados/` |
| 4 | Implementar em C o núcleo da portaria e a consolidação central | `05-programa-c/` |
| 5 | Projetar a infraestrutura de rede e a arquitetura distribuída | `06-redes/` |
| 6 | Analisar a segurança, a privacidade e a acessibilidade da solução | `07-seguranca-privacidade-acessibilidade/` |

Esta tabela serve de base para a conclusão: cada objetivo precisa ser retomado no capítulo 10 com o resultado obtido.

## 3. Justificativa científica

Perguntas-guia para o grupo escrever com as próprias palavras:
- **Relevância social:** o que muda para moradores, porteiros e síndicos se o problema for reduzido?
- **Relevância acadêmica e técnica:** que conceitos das disciplinas o projeto integra (engenharia de software ágil, banco de dados, programação estruturada, redes e sistemas distribuídos)?
- **Lacuna:** o que as soluções existentes deixam de atender (ver `trabalhos-relacionados.md` e `diferenciais.md`)?
- **Viabilidade:** por que o recorte (protótipo em C com rede simulada) cabe no prazo e ainda assim representa o sistema completo?

Dados de apoio (volume de encomendas, crescimento do e-commerce, tempo do porteiro): só entram com fonte verificada. Hoje todos estão como `[FONTE A VERIFICAR]` em [`fontes.md`](fontes.md). Não usar número algum no texto antes de conferir a fonte.
