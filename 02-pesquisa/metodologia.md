# Metodologia (Etapa 2)

> Roteiro para o capítulo 3 (métodos). O grupo redige o texto.

## 1. Classificação da pesquisa

| Aspecto | Proposta |
|---|---|
| Natureza | Aplicada |
| Objetivo | Exploratória |
| Abordagem | Qualitativa; os dados quantitativos vêm dos testes e das verificações do protótipo |

> **Decisão do grupo (2026-10-29): o levantamento de campo foi dispensado**, porque não é obrigatório no PIM. O problema vem do cenário descrito em `01-organizacao/` (P1 a P7) e da pesquisa bibliográfica. Consequências: os requisitos não têm dados de respondentes, e os indicadores "antes" são medidos no piloto (ver `08-integracao/beneficios-e-indicadores.md`). O questionário permanece em `questionario-campo.md` como material opcional.

Confirmar com o professor se a classificação precisa de referência metodológica; se precisar, a fonte entra em `fontes.md` como `[FONTE A VERIFICAR]`.

## 2. Procedimentos

| Procedimento | O que é | Onde fica |
|---|---|---|
| Pesquisa bibliográfica | Leitura e fichamento das fontes sobre os temas da fundamentação | `fundamentacao.md`, `fontes.md` |
| Análise do cenário | Descrição do processo atual e dos problemas P1 a P7 da organização (fictícia) | `01-organizacao/` |
| Desenvolvimento de protótipo com Scrum | Sprints de 1 semana, com registro em `sprint-NN.md` | `03-engenharia-software/scrum/` |
| Verificação do protótipo | Testes automatizados, execução com dados fictícios, scripts SQL executados e testes de rede | `05-programa-c/tests/`, `04-banco-de-dados/sql/`, `06-redes/packet-tracer/` |
| Levantamento de campo (**dispensado**) | Questionário curto para porteiros e síndicos, opcional | `questionario-campo.md`, `resultados-campo.md` |

## 3. Levantamento de campo (dispensado, material opcional)

> **Não será aplicado.** Esta seção fica registrada para o caso de o grupo mudar de ideia. Se aplicar, preencher a tabela abaixo e `resultados-campo.md`, e voltar os indicadores "antes" para a pesquisa.

| Item | Definição |
|---|---|
| Público | Porteiros e síndicos |
| Instrumento | Questionário de 8 a 10 perguntas |
| Anonimato | Anônimo; não coleta nome, contato nem outro dado pessoal |
| Finalidade | Acadêmica, explicada no início do questionário |
| Termo de consentimento | **A confirmar com o professor** se a UNIP exige algum |
| Tamanho da amostra | [A DEFINIR] |
| Local e período | [A DEFINIR] |
| Responsável pela aplicação | [A DEFINIR] |

Cuidados:
- Não registrar nome do condomínio, do respondente nem dado que identifique pessoas.
- Os resultados reais só entram em `resultados-campo.md` depois da aplicação. Nenhum número do campo pode ser criado antes.

## 4. Análise dos dados

- Fundamentação: fichamento das fontes verificadas, com as ideias escritas pelo grupo.
- Protótipo: resultados dos testes, das consultas SQL e dos testes de rede, apresentados nos capítulos 5, 6 e 7.
- Indicadores: definidos em `08-integracao/beneficios-e-indicadores.md`, com a linha de base a medir no piloto.
- Se o levantamento de campo for aplicado: respostas fechadas por contagem e percentual; respostas abertas agrupadas por tema, sem identificar o respondente.

## 5. Limitações a declarar

- **Sem levantamento de campo:** o problema vem do cenário fictício e da bibliografia, não de dados de usuários reais. O trabalho deve dizer isso com clareza e não afirmar frequência de extravios nem preferências dos moradores.
- Organização do estudo é fictícia.
- Protótipo com rede e aviso simulados.
- Os benefícios são esperados e só seriam medidos em um piloto.
