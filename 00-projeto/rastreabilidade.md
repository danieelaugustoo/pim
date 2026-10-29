# Rastreabilidade

Liga cada exigência do manual do PIM ao arquivo do repositório que a atende, ao capítulo do trabalho em que ela aparece e ao andamento. Há uma linha para cada item `[ ]` das seções 9 e 11 do `PLANO.md`.

**Como ler**
- **Arquivo:** caminho a partir da raiz do repositório.
- **Capítulo:** arquivo em `documento-final/capitulos/` em que o conteúdo é redigido pelo grupo.
- **Status:** `Pendente` (nada feito), `Em andamento`, `Feito` (arquivo pronto, falta revisão) ou `Revisado` (conferido por outro integrante). Atualizar ao concluir cada tarefa, junto com a `sprint-NN.md` da sprint atual.

## Etapa 1: Caracterização da organização

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Identificação da organização | `01-organizacao/caracterizacao.md` | `02-organizacao.md` | Feito |
| Ramo de atuação | `01-organizacao/caracterizacao.md` | `02-organizacao.md` | Feito |
| Missão | `01-organizacao/caracterizacao.md` | `02-organizacao.md` | Feito |
| Produtos/serviços | `01-organizacao/caracterizacao.md` | `02-organizacao.md` | Feito |
| Estrutura organizacional | `01-organizacao/caracterizacao.md` + `01-organizacao/diagramas/organograma.mmd` | `02-organizacao.md` | Feito |
| Processos de negócio | `01-organizacao/processos.md` + `01-organizacao/diagramas/processo-atual.mmd` e `processo-proposto.mmd` | `02-organizacao.md` | Feito |
| Público-alvo | `01-organizacao/caracterizacao.md` | `02-organizacao.md` | Feito |
| Problemas encontrados (P1 a P7) | `01-organizacao/caracterizacao.md` | `02-organizacao.md` | Feito |
| Justificativa da solução proposta | `01-organizacao/caracterizacao.md` | `02-organizacao.md` | Feito |

## Etapa 2: Pesquisa científica e inovação

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Problema de pesquisa | `02-pesquisa/problema-e-objetivos.md` | `03-pesquisa.md` | Feito |
| Objetivos | `02-pesquisa/problema-e-objetivos.md` | `03-pesquisa.md` | Feito |
| Metodologia | `02-pesquisa/metodologia.md` + `02-pesquisa/questionario-campo.md` + `02-pesquisa/resultados-campo.md` | `03-pesquisa.md` | Em andamento |
| Fundamentação bibliográfica | `02-pesquisa/fundamentacao.md` + `02-pesquisa/fontes.md` | `03-pesquisa.md` | Em andamento |
| Trabalhos relacionados | `02-pesquisa/trabalhos-relacionados.md` | `03-pesquisa.md` | Em andamento |
| Justificativa científica | `02-pesquisa/problema-e-objetivos.md` | `03-pesquisa.md` | Em andamento |
| Diferenciais inovadores | `02-pesquisa/diferenciais.md` | `03-pesquisa.md` | Feito |

## Etapa 3: Engenharia de Software

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Requisitos funcionais | `03-engenharia-software/requisitos.md` | `04-engenharia-software.md` | Feito |
| Requisitos não funcionais | `03-engenharia-software/requisitos.md` | `04-engenharia-software.md` | Feito |
| Casos de uso | `03-engenharia-software/casos-de-uso.md` | `04-engenharia-software.md` | Feito |
| Backlog do produto | `03-engenharia-software/scrum/backlog.md` | `04-engenharia-software.md` | Feito |
| Arquitetura do sistema | `03-engenharia-software/arquitetura.md` + `03-engenharia-software/decisoes/` | `04-engenharia-software.md` | Feito |
| Diagrama de casos de uso | `03-engenharia-software/diagramas/casos-de-uso.puml` | `04-engenharia-software.md` | Feito |
| Diagrama de classes (quando aplicável) | `03-engenharia-software/diagramas/classes-dominio.puml` | `04-engenharia-software.md` | Feito |
| Diagrama de atividades ou de sequência | `03-engenharia-software/diagramas/atividade-registrar-encomenda.puml` + `atividade-retirar-encomenda.puml` + `sequencia-sincronizacao.puml` (+ `estados-encomenda.puml`) | `04-engenharia-software.md` | Feito |
| Planejamento com Scrum, XP ou Kanban | `03-engenharia-software/scrum/` (papéis, cerimônias, sprints e definição de pronto) | `04-engenharia-software.md` | Feito |

## Etapa 4: Banco de dados

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Modelo conceitual | `04-banco-de-dados/modelo-conceitual.md` (+ brModelo, se o professor pedir a notação de Chen) | `05-banco-de-dados.md` | Pendente |
| Diagrama Entidade-Relacionamento (DER) | `04-banco-de-dados/diagramas/der.mmd` + PNG | `05-banco-de-dados.md` | Pendente |
| Modelo lógico | `04-banco-de-dados/modelo-logico.md` | `05-banco-de-dados.md` | Pendente |
| Normalização | `04-banco-de-dados/normalizacao.md` | `05-banco-de-dados.md` | Pendente |
| Modelo físico | `04-banco-de-dados/sql/01-criacao-tabelas.sql` | `05-banco-de-dados.md` | Pendente |
| Principais comandos SQL | `04-banco-de-dados/sql/02-carga-exemplo.sql` + `03-consultas.sql` + `04-views-indices.sql` | `05-banco-de-dados.md` | Pendente |
| Discussão sobre o uso de bancos NoSQL | `04-banco-de-dados/nosql/comparativo.md` + `04-banco-de-dados/nosql/exemplo-aviso.json` | `05-banco-de-dados.md` | Pendente |

## Etapa 5: Programação estruturada em C

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Algoritmos | `05-programa-c/algoritmos/pseudocodigo.md` (A1 a A6) | `06-programacao-c.md` | Pendente |
| Fluxogramas | `05-programa-c/algoritmos/fluxogramas/` (A1 a A6, `.mmd` + PNG) | `06-programacao-c.md` | Pendente |
| Pseudocódigo | `05-programa-c/algoritmos/pseudocodigo.md` | `06-programacao-c.md` | Pendente |
| Implementação em C | `05-programa-c/src/` + `05-programa-c/include/` | `06-programacao-c.md` | Em andamento |
| Estruturas condicionais | `05-programa-c/src/` (validações, regra de tamanho do volume, `switch` do menu) | `06-programacao-c.md` | Em andamento |
| Estruturas de repetição | `05-programa-c/src/` (varredura da matriz, leitura de arquivos linha a linha, laço do menu) | `06-programacao-c.md` | Em andamento |
| Funções | `05-programa-c/src/` (todos os módulos, prefixo `modulo_`) | `06-programacao-c.md` | Em andamento |
| Vetores e matrizes | `05-programa-c/src/` (vetores de encomendas e moradores, contagem por dia, matriz `estante[NUM_ESTANTES][NUM_PRATELEIRAS]`) | `06-programacao-c.md` | Em andamento |
| Manipulação de arquivos | `05-programa-c/src/persistencia.c` + `sincronizacao.c` + `consolidacao.c` | `06-programacao-c.md` | Em andamento |

## Etapa 6: Redes de computadores e sistemas distribuídos

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Arquitetura da rede | `06-redes/arquitetura-e-topologia.md` | `07-redes.md` | Pendente |
| Topologia | `06-redes/arquitetura-e-topologia.md` + `06-redes/diagramas/topologia.mmd` + print do Packet Tracer em `06-redes/packet-tracer/` | `07-redes.md` | Pendente |
| Equipamentos | `06-redes/equipamentos.md` | `07-redes.md` | Pendente |
| Endereçamento IP | `06-redes/enderecamento-ip.md` | `07-redes.md` | Pendente |
| VLANs | `06-redes/vlans.md` | `07-redes.md` | Pendente |
| Comunicação entre serviços | `06-redes/nuvem-e-sistemas-distribuidos.md` | `07-redes.md` | Pendente |
| Computação em nuvem | `06-redes/nuvem-e-sistemas-distribuidos.md` | `07-redes.md` | Pendente |
| Arquitetura distribuída | `06-redes/nuvem-e-sistemas-distribuidos.md` | `07-redes.md` | Pendente |
| Escalabilidade | `06-redes/nuvem-e-sistemas-distribuidos.md` | `07-redes.md` | Pendente |
| Segurança da infraestrutura | `06-redes/seguranca-infraestrutura.md` | `07-redes.md` | Pendente |

## Etapa 7: Direitos humanos, inclusão e segurança (versão curta)

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Acessibilidade | `07-seguranca-privacidade-acessibilidade/analise.md` | `08-seguranca-privacidade-acessibilidade.md` | Pendente |
| Inclusão digital | `07-seguranca-privacidade-acessibilidade/analise.md` | `08-seguranca-privacidade-acessibilidade.md` | Pendente |
| Privacidade | `07-seguranca-privacidade-acessibilidade/analise.md` | `08-seguranca-privacidade-acessibilidade.md` | Pendente |
| Proteção de dados | `07-seguranca-privacidade-acessibilidade/analise.md` | `08-seguranca-privacidade-acessibilidade.md` | Pendente |
| Segurança da informação | `07-seguranca-privacidade-acessibilidade/analise.md` | `08-seguranca-privacidade-acessibilidade.md` | Pendente |
| Impactos sociais | `07-seguranca-privacidade-acessibilidade/analise.md` | `08-seguranca-privacidade-acessibilidade.md` | Pendente |
| Aspectos éticos | `07-seguranca-privacidade-acessibilidade/analise.md` | `08-seguranca-privacidade-acessibilidade.md` | Pendente |
| Direitos humanos | `07-seguranca-privacidade-acessibilidade/analise.md` | `08-seguranca-privacidade-acessibilidade.md` | Pendente |

## Etapa 8: Integração da solução

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Como os componentes se integram | `08-integracao/integracao.md` + `08-integracao/diagramas/fluxo-ponta-a-ponta.mmd` | `09-integracao.md` | Pendente |
| Implantação | `08-integracao/implantacao.md` | `09-integracao.md` | Pendente |
| Benefícios esperados para a organização | `08-integracao/beneficios-e-indicadores.md` | `09-integracao.md` | Pendente |
| Limitações da solução | `08-integracao/limitacoes-e-evolucao.md` | `09-integracao.md` | Pendente |
| Possibilidades de evolução futura | `08-integracao/limitacoes-e-evolucao.md` | `09-integracao.md` | Pendente |
| Conclusão geral | `documento-final/capitulos/10-conclusao.md` (escrita pelo grupo) | `10-conclusao.md` | Pendente |

## Documento final (seção 11)

| Exigência | Arquivo | Capítulo | Status |
|---|---|---|---|
| Capa, Resumo, Abstract, Sumário, Introdução, Desenvolvimento, Conclusão e Referências | `documento-final/` | Todos | Pendente |
| Resumo conciso e objetivo, com conteúdo principal, pontos relevantes e conclusões, em até 500 palavras, seguido das palavras-chave | `documento-final/capitulos/00-resumo.md` | `00-resumo.md` | Pendente |
| Abstract em inglês (ou espanhol ou francês), com as palavras-chave no mesmo idioma | `documento-final/capitulos/00-abstract.md` | `00-abstract.md` | Pendente |
| Introdução com objetivo da pesquisa, metodologia, breve apresentação da empresa e visão geral da proposta | `documento-final/capitulos/01-introducao.md` | `01-introducao.md` | Pendente |
| Desenvolvimento entre 20 e 30 páginas, em capítulos e subcapítulos, apresentando pesquisa, fundamentação, métodos, materiais, resultados e discussão | `documento-final/capitulos/` (capítulos 2 a 9) + `documento-final/estrutura-e-paginas.md` | `02` a `09` | Pendente |
| Conclusão que apresenta os resultados de forma clara, relaciona os resultados aos objetivos, retoma a proposta inicial e destaca os principais pontos encontrados | `documento-final/capitulos/10-conclusao.md` | `10-conclusao.md` | Pendente |
| Referências de todas as fontes usadas, em ABNT | `documento-final/referencias.md` | Referências | Pendente |
| Citações conforme a ABNT; todo trecho reproduzido diretamente com a fonte citada no texto e a obra referenciada | `documento-final/capitulos/` (todos) + `documento-final/referencias.md` | Todos | Pendente |
| Formatação da seção 2 (A4, margens, espaçamento, fonte, recuo, numeração) | `documento-final/checklist-abnt-e-entrega.md` | — | Pendente |
| Entrega pelo sistema de trabalhos acadêmicos da UNIP dentro do prazo, cópia impressa ao coordenador do PIM e postagem feita pelo líder | `documento-final/checklist-abnt-e-entrega.md` | — | Pendente |
