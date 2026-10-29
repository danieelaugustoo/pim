# Plano do Projeto — PIM II (UNIP · ADS)

**Título:** Gestão de encomendas em condomínios residenciais: registro, aviso e retirada segura de pacotes na portaria
**Organização fictícia:** Administradora Morada Central (10 condomínios residenciais)
**Tema oficial do PIM II:** Projeto Integrado de Desenvolvimento de uma Solução Computacional para Transformação Digital de uma Organização
**Situação:** tema aprovado pelo professor

> Este arquivo é a fonte de verdade do projeto: diz **o que** fazer e **onde** guardar cada coisa.
> O `CLAUDE.md` traz as regras curtas que o Claude Code segue em toda sessão.
> Base: resumo do manual do PIM II enviado pelo grupo. Se algo divergir do manual oficial da UNIP, vale o manual.

---

## Sumário

0. Como usar este plano
1. Visão geral
2. Regras do PIM que valem para todo o projeto
3. Disciplinas e onde cada uma aparece
4. A organização fictícia (base da Etapa 1)
5. Escopo da solução
6. Decisões de arquitetura
7. Estrutura de pastas
8. Convenções e glossário
9. Etapas do manual: o que produzir e onde guardar
10. Plano de sprints (Scrum)
11. Documento final (ABNT)
12. Como começar no Claude Code (prompts prontos)
13. Pontos a confirmar com o grupo e o professor

---

## 0. Como usar este plano

1. Crie uma pasta vazia chamada `pim`, coloque `CLAUDE.md` e `PLANO.md` na raiz e inicialize o Git (`git init`).
2. Abra o Claude Code nessa pasta e use os prompts da seção 12, **um por vez**. Revise o resultado e faça commit antes de passar ao próximo.
3. Divisão de trabalho:
   - **Claude Code:** código C, scripts SQL, diagramas como código, documentação técnica (tabelas, dicionário de dados, planos de rede) e roteiros dos capítulos.
   - **Grupo:** texto dos capítulos do trabalho, pesquisa de campo, montagem no Packet Tracer (e no brModelo, se for exigido), revisão final e entrega.

---

## 1. Visão geral

**Problema.** Com o crescimento das compras online, as portarias recebem volumes o dia inteiro e controlam tudo em caderno. As encomendas se acumulam, são extraviadas ou entregues à pessoa errada, o porteiro gasta parte relevante do turno com isso e a administradora não tem dados para planejar equipe e espaço.

**Quem é afetado.** Moradores, porteiros, síndicos e a própria administradora, que recebe as reclamações.

**Solução.** Um sistema de gestão de encomendas com um nó em cada portaria, que funciona mesmo sem internet, e um servidor central da administradora que consolida os dados de todos os condomínios.

**Fluxo principal.** Encomenda chega → porteiro registra → sistema indica a posição na estante → gera o código de retirada → avisa o morador → morador retira com o código → operações sincronizam com a central → relatórios.

---

## 2. Regras do PIM que valem para todo o projeto

| Tema | Regra (resumo do manual) |
|---|---|
| Estrutura do documento | Capa, Resumo, Abstract, Sumário, Introdução, Desenvolvimento, Conclusão, Referências |
| Tamanho | Desenvolvimento entre 20 e 30 páginas, organizado em capítulos e subcapítulos |
| Formatação | Papel A4; margens de 3 cm (superior e esquerda) e 2 cm (inferior e direita); espaçamento 1,5; recuo de primeira linha de 1,5 cm; Arial ou Times New Roman tamanho 12; citações longas e notas em tamanho 10; texto justificado; numeração das páginas a partir da Introdução; ABNT |
| Resumo e Abstract | Resumo de até 500 palavras, seguido das palavras-chave; Abstract em inglês, espanhol ou francês, com as palavras-chave no mesmo idioma |
| Introdução | Objetivo da pesquisa, metodologia, breve apresentação da empresa e visão geral da proposta |
| Conclusão | Resultados apresentados com clareza, relação com os objetivos, retomada da proposta inicial e principais pontos encontrados |
| Autoria | Trabalho autoral e inédito; a pesquisa serve de fundamentação, mas o texto é escrito com as próprias palavras; toda citação tem fonte no texto e referência ABNT |
| Plágio | Proibidos o plágio integral, o parcial, o conceitual e o autoplágio; a UNIP usa software de similaridade |
| Entrega | Pelo sistema de trabalhos acadêmicos da UNIP, dentro do prazo, mais uma cópia impressa entregue ao coordenador do PIM; não vale e-mail, Dropbox ou envio atrasado (não enviar no prazo implica reprovação) |
| Grupo | Individual ou até 6 integrantes do mesmo curso e turma; só o líder faz a postagem e cadastra os demais |

**Uso de IA neste projeto (regra do grupo, derivada da regra de autoria).** O Claude gera código, scripts, diagramas e documentação técnica. Os capítulos do trabalho são redigidos pelo grupo; o Claude pode montar roteiros de tópicos e revisar os textos. Nunca inventar fontes, autores, dados ou estatísticas. Confirmar com o professor se a UNIP tem orientação específica sobre o uso de IA.

---

## 3. Disciplinas e onde cada uma aparece

| Disciplina | Onde aparece no projeto | Etapa |
|---|---|---|
| Pesquisa, Tecnologia e Inovação | Problema de pesquisa, pesquisa bibliográfica e de campo, trabalhos relacionados, diferenciais | 2 |
| Engenharia de Software Ágil | Requisitos, casos de uso, backlog, Scrum, arquitetura, diagramas UML | 3 |
| Modelagem de Banco de Dados | Modelo conceitual, DER, modelo lógico, normalização, modelo físico, SQL, discussão sobre NoSQL | 4 |
| Programação Estruturada em C | Protótipo do nó da portaria e do consolidador central | 5 |
| Redes de Computadores e Sistemas Distribuídos | Topologia, endereçamento, VLANs, nuvem, sincronização offline, escalabilidade | 6 |

**Direitos Humanos** é matéria complementar para o grupo. Mesmo assim, o manual lista a Etapa 7 (direitos humanos, inclusão e segurança) entre as etapas obrigatórias, então ela entra em versão curta, com cerca de 2 páginas (seção 9.7).

---

## 4. A organização fictícia (base da Etapa 1)

> Números fictícios e coerentes entre si. O grupo pode ajustar, desde que mantenha a coerência em todo o projeto (código, banco, rede e texto).

**Identificação.** Administradora Morada Central Ltda., com sede em São Paulo – SP (ajustável).

**Ramo de atuação.** Administração condominial e gestão de equipes de portaria para condomínios residenciais.

**Missão.** Administrar condomínios residenciais com organização, transparência e segurança, oferecendo a moradores e funcionários rotinas claras e confiáveis.

**Serviços.**
- Administração financeira e prestação de contas aos condôminos
- Gestão das equipes de portaria (contratação, escalas e treinamento)
- Gestão de manutenção e de fornecedores
- Atendimento ao morador e registro de ocorrências

**Porte.** 10 condomínios com 2 a 4 blocos cada, cerca de 960 unidades no total. São 40 porteiros (4 por condomínio, em escala 12x36). Na sede trabalham 1 gerente de operações, 2 supervisores (5 condomínios cada), 3 atendentes e 2 analistas administrativo-financeiros.

**Estrutura organizacional.** Diretoria → Gerência de Operações (Supervisores → Porteiros; Atendimento ao Morador) e Administrativo-Financeiro. O síndico de cada condomínio é eleito pelos condôminos e é o interlocutor da administradora (aparece como relação externa no organograma).

**Processo atual de encomendas.**
1. O entregador chega à portaria.
2. O porteiro anota no caderno a data, o nome, o bloco/apartamento e a transportadora.
3. O pacote vai para uma sala ou armário, sem posição definida.
4. O morador é avisado pelo interfone, quando o porteiro consegue.
5. O morador retira e, nem sempre, assina o caderno.
6. Extravios e reclamações chegam à sede por telefone ou WhatsApp.

**Processo proposto.** Registrar → alocar posição → gerar código → avisar → retirar com código → sincronizar → relatórios.

**Público-alvo.** Moradores (perfis variados, incluindo idosos e pessoas que não usam smartphone), síndicos, porteiros e a equipe da sede.

**Problemas encontrados.**
- **P1:** extravios e entregas à pessoa errada
- **P2:** falta de rastreabilidade (quem recebeu, onde está, quem retirou)
- **P3:** tempo do porteiro consumido por encomendas, com picos em novembro e dezembro
- **P4:** aviso ao morador falho ou inexistente
- **P5:** acúmulo de volumes e falta de espaço
- **P6:** nenhum dado para a sede planejar equipe e espaço
- **P7:** internet instável em parte das portarias, o que inviabiliza uma solução que só funcione online

**Justificativa da solução.** O problema se repete nos 10 condomínios e depende de registro, rastreabilidade e comunicação, coisas que uma solução computacional resolve bem: ela padroniza o processo, reduz erros e gera dados. A operação offline atende as portarias com internet instável (P7), e a consolidação central dá à administradora a visão de todos os condomínios (P6).

---

## 5. Escopo da solução

### 5.1 Sistema completo (projetado e documentado)
- Nó da portaria: aplicação local que registra, aloca, avisa e controla retiradas, funcionando sem internet
- Servidor central na nuvem: API e banco relacional (MySQL) com os dados de todos os condomínios
- Painel da administradora: indicadores e relatórios
- Canais de aviso: aplicativo, SMS ou interfone com código impresso

### 5.2 Protótipo em C (implementado)
- Executável `portaria`: nó local com menu em console, persistência em arquivos, fila de sincronização e modo online/offline simulado
- Executável `central`: consolida as operações de todas as portarias sem duplicar registros e gera relatórios consolidados
- A rede entre os dois é simulada por arquivos na pasta `dados/rede/`

### 5.3 Fora do escopo (vira "evolução futura" na Etapa 8)
App do morador e painel web reais; envio real de SMS ou WhatsApp; comunicação por sockets; interface gráfica; fotos das encomendas; armários inteligentes; ligação do programa em C com o MySQL (o banco é modelado e testado com scripts SQL à parte).

### 5.4 Por que esse recorte
O manual pede as principais funcionalidades em C estruturado. O recorte cabe no prazo, e cada parte do protótipo corresponde a uma parte do sistema completo:

| Protótipo em C | Sistema completo |
|---|---|
| Executável `portaria` | Nó da portaria |
| Arquivos em `dados/portarias/` | Armazenamento local que permite operar offline |
| Arquivos em `dados/rede/` | Envio pela rede (HTTPS para a API central) |
| Executável `central` | Servidor central e banco relacional |

---

## 6. Decisões de arquitetura

Cada decisão vira um arquivo em `03-engenharia-software/decisoes/` (contexto, decisão, alternativas consideradas, justificativa). O manual exige justificar academicamente as decisões; esses registros são a base disso.

| ID | Decisão | Justificativa resumida |
|---|---|---|
| ADR-001 | Banco **relacional** (MySQL 8) no servidor central; NoSQL apenas discutido | Entidades estáveis e muito relacionadas. O banco garante regras importantes: uma encomenda tem no máximo uma retirada (UNIQUE), cada operação sincronizada é aplicada uma única vez (chave primária) e há integridade entre unidade, encomenda e posição. Um banco de documentos faria sentido só para o histórico de avisos |
| ADR-002 | O protótipo em C guarda os dados em **arquivos de texto CSV separados por `;`** | Simula o armazenamento local de que a portaria precisa para funcionar offline, é legível para o professor e exercita manipulação de arquivos |
| ADR-003 | **Sincronização assíncrona** com fila de operações idempotentes | Cada operação tem um id único (`P01-000123`); reenviar não duplica; consistência eventual; a ordem é garantida dentro de cada portaria pela sequência |
| ADR-004 | **Scrum** com sprints de 1 semana | Grupo pequeno e prazo curto; cerimônias simplificadas; os registros das sprints viram evidência na Etapa 3 |
| ADR-005 | **Diagramas como código**: PlantUML para UML, Mermaid para fluxogramas, organograma e rascunhos; exportados em PNG | Versionáveis, revisáveis e fáceis de atualizar |
| ADR-006 | Endereçamento **10.X.Y.0/24** | X identifica o local (0 = sede, 1 a 10 = condomínios) e Y identifica a VLAN; legível e escalável até 254 locais sem redesenho |

---

## 7. Estrutura de pastas

```
pim/
├── CLAUDE.md                              # regras permanentes para o Claude Code
├── PLANO.md                               # este plano
├── README.md                              # visão geral, integrantes, como compilar e rodar
├── .gitignore
│
├── 00-projeto/                            # controle do PIM
│   ├── README.md
│   ├── regras-do-pim.md                   # seção 2 deste plano
│   ├── rastreabilidade.md                 # exigência do manual → arquivo → capítulo → status
│   ├── glossario.md                       # seção 8.7 deste plano
│   ├── cronograma.md                      # sprints com as datas reais
│   └── integrantes.md                     # nomes, RA e papéis no Scrum
│
├── 01-organizacao/                        # Etapa 1
│   ├── README.md
│   ├── caracterizacao.md
│   ├── processos.md                       # processo atual x proposto
│   └── diagramas/
│       ├── organograma.mmd
│       ├── processo-atual.mmd
│       └── processo-proposto.mmd
│
├── 02-pesquisa/                           # Etapa 2
│   ├── README.md
│   ├── problema-e-objetivos.md            # problema, objetivos e justificativa científica
│   ├── metodologia.md
│   ├── questionario-campo.md
│   ├── resultados-campo.md
│   ├── fundamentacao.md                   # fichamentos por tema
│   ├── trabalhos-relacionados.md
│   ├── diferenciais.md
│   └── fontes.md                          # lista mestre de fontes, com status de verificação
│
├── 03-engenharia-software/                # Etapa 3
│   ├── README.md
│   ├── requisitos.md
│   ├── casos-de-uso.md
│   ├── arquitetura.md
│   ├── ferramentas.md                     # materiais: ferramentas e tecnologias usadas
│   ├── decisoes/                          # ADR-001 a ADR-006
│   ├── scrum/
│   │   ├── papeis-e-cerimonias.md
│   │   ├── backlog.md
│   │   ├── definicao-de-pronto.md
│   │   └── sprints/                       # sprint-00.md a sprint-04.md
│   └── diagramas/
│       ├── casos-de-uso.puml
│       ├── classes-dominio.puml
│       ├── atividade-registrar-encomenda.puml
│       ├── atividade-retirar-encomenda.puml
│       ├── sequencia-sincronizacao.puml
│       └── estados-encomenda.puml
│
├── 04-banco-de-dados/                     # Etapa 4
│   ├── README.md
│   ├── modelo-conceitual.md
│   ├── modelo-logico.md
│   ├── normalizacao.md
│   ├── dicionario-de-dados.md
│   ├── diagramas/
│   │   └── der.mmd
│   ├── sql/
│   │   ├── 01-criacao-tabelas.sql
│   │   ├── 02-carga-exemplo.sql
│   │   ├── 03-consultas.sql
│   │   └── 04-views-indices.sql
│   └── nosql/
│       ├── comparativo.md
│       └── exemplo-aviso.json
│
├── 05-programa-c/                         # Etapa 5
│   ├── README.md                          # como compilar, testar e executar
│   ├── Makefile
│   ├── build.bat                          # compilação no Windows sem make
│   ├── include/                           # tipos.h + um .h por módulo
│   │   ├── tipos.h                        # structs, enums e constantes
│   │   ├── util.h
│   │   ├── morador.h
│   │   ├── estante.h
│   │   ├── codigo.h
│   │   ├── encomenda.h
│   │   ├── retirada.h
│   │   ├── aviso.h
│   │   ├── relatorio.h
│   │   ├── persistencia.h
│   │   ├── sincronizacao.h
│   │   └── consolidacao.h
│   ├── src/
│   │   ├── portaria.c                     # main do nó da portaria (só menu e chamadas)
│   │   ├── central.c                      # main do consolidador central
│   │   ├── util.c
│   │   ├── morador.c
│   │   ├── estante.c
│   │   ├── codigo.c
│   │   ├── encomenda.c
│   │   ├── retirada.c
│   │   ├── aviso.c
│   │   ├── relatorio.c
│   │   ├── persistencia.c
│   │   ├── sincronizacao.c
│   │   └── consolidacao.c
│   ├── tests/
│   │   ├── test_estante.c
│   │   ├── test_codigo.c
│   │   ├── test_util.c
│   │   └── test_consolidacao.c
│   ├── dados/
│   │   ├── exemplo/                       # dados fictícios versionados para demonstração
│   │   ├── portarias/                     # gerado na execução (fora do Git, com .gitkeep)
│   │   ├── rede/                          # "rede" simulada (fora do Git, com .gitkeep)
│   │   └── central/                       # dados consolidados (fora do Git, com .gitkeep)
│   ├── bin/                               # executáveis (fora do Git)
│   └── algoritmos/
│       ├── pseudocodigo.md                # A1 a A6
│       └── fluxogramas/                   # A1.mmd a A6.mmd + PNG exportado
│
├── 06-redes/                              # Etapa 6
│   ├── README.md
│   ├── arquitetura-e-topologia.md
│   ├── equipamentos.md
│   ├── enderecamento-ip.md
│   ├── vlans.md
│   ├── nuvem-e-sistemas-distribuidos.md
│   ├── seguranca-infraestrutura.md
│   ├── diagramas/
│   │   └── topologia.mmd
│   └── packet-tracer/                     # .pkt e prints montados pelo grupo
│
├── 07-seguranca-privacidade-acessibilidade/   # Etapa 7 (versão curta)
│   ├── README.md
│   └── analise.md
│
├── 08-integracao/                         # Etapa 8
│   ├── README.md
│   ├── integracao.md
│   ├── implantacao.md                     # piloto, treinamento e expansão
│   ├── beneficios-e-indicadores.md
│   ├── limitacoes-e-evolucao.md
│   └── diagramas/
│       └── fluxo-ponta-a-ponta.mmd
│
└── documento-final/                       # o trabalho em ABNT
    ├── README.md
    ├── estrutura-e-paginas.md             # sumário planejado e orçamento de páginas
    ├── checklist-abnt-e-entrega.md
    ├── capitulos/                         # rascunhos escritos pelo grupo
    │   ├── 00-resumo.md
    │   ├── 00-abstract.md
    │   ├── 01-introducao.md
    │   ├── 02-organizacao.md
    │   ├── 03-pesquisa.md
    │   ├── 04-engenharia-software.md
    │   ├── 05-banco-de-dados.md
    │   ├── 06-programacao-c.md
    │   ├── 07-redes.md
    │   ├── 08-seguranca-privacidade-acessibilidade.md
    │   ├── 09-integracao.md
    │   └── 10-conclusao.md
    ├── figuras/                           # figura-NN-descricao.png
    ├── referencias.md                     # lista final ABNT (só fontes usadas)
    └── versoes/                           # .docx e .pdf finais (fora do Git)
```

**Regras da estrutura.**
- Toda pasta tem um `README.md` curto: o que ela guarda e quais exigências do manual atende.
- O prefixo numérico das pastas segue a ordem das etapas do manual.
- Arquivos gerados na execução (executáveis e dados de teste) ficam fora do Git; as pastas vazias que o programa precisa têm um `.gitkeep`.
- Toda figura usada no trabalho é exportada para `documento-final/figuras/`.

---

## 8. Convenções e glossário

### 8.1 Idioma e codificação
- Pastas, arquivos e documentação em português.
- Identificadores em C e SQL sem acento.
- Textos do programa e dos arquivos de dados em ASCII, sem acento. Isso evita caracteres quebrados no console do Windows.

### 8.2 Pastas e arquivos
- Letras minúsculas, palavras separadas por hífen: `casos-de-uso.md`.
- Prefixo numérico quando a ordem importa: etapas, scripts SQL e capítulos.
- Figuras: `figura-NN-descricao.png`; tabelas exportadas como imagem: `tabela-NN-descricao.png`.

### 8.3 Linguagem C
- Um módulo = um par `.h` + `.c` com o mesmo nome (`estante.h`, `estante.c`).
- Funções com o prefixo do módulo, no formato `modulo_acao`: `estante_alocar_posicao`, `codigo_gerar_unico`.
- Tipos em PascalCase (`Encomenda`, `StatusEncomenda`); constantes e macros em MAIÚSCULAS (`MAX_ENCOMENDAS`); variáveis em minúsculas separadas por `_`.
- Valores de enum com prefixo do tipo: `STATUS_PENDENTE`, `CANAL_INTERFONE`, `OP_RETIRADA`.
- Header guard no formato `ESTANTE_H`.
- `main` enxuto: só menu e chamadas. Toda a lógica fica em módulos testáveis.
- Cada função tem um comentário em português com objetivo, parâmetros, retorno e a lógica em poucas linhas.

### 8.4 SQL
- Tabelas no singular, em minúsculas separadas por `_`: `encomenda`, `posicao_estante`.
- Chave primária `id_<tabela>`; chave estrangeira com o mesmo nome da chave referenciada.
- Restrições nomeadas: `pk_encomenda`, `fk_encomenda_unidade`, `uq_retirada_encomenda`, `ck_encomenda_status`.
- Palavras-chave SQL em MAIÚSCULAS.

### 8.5 Identificadores de artefatos
RF01 (requisito funcional), RNF01 (requisito não funcional), UC01 (caso de uso), US01 (história de usuário), ADR-001 (decisão de arquitetura), A1 (algoritmo), P1 (problema da organização).

### 8.6 Git
- A branch `main` sempre compila; o trabalho acontece em branches como `feature/US01-registrar-encomenda` ou `docs/redes-enderecamento`.
- Commits no formato `tipo(escopo): descricao (USxx)`, com os tipos `feat`, `fix`, `docs`, `test`, `refactor` e `chore`. Exemplo: `feat(estante): aloca posicao pela estante do bloco (US02)`.
- Tag de versão ao fim de cada sprint: `v0.1.0`, `v0.2.0`, `v0.3.0`; entrega final `v1.0.0`.

### 8.7 Glossário (mesmos nomes no texto, no código e no banco)

| Termo | Significado | No C | No banco |
|---|---|---|---|
| Encomenda | Volume recebido na portaria para uma unidade | `Encomenda` | `encomenda` |
| Unidade | Apartamento (bloco + número) | campos `bloco` e `apartamento` | `unidade` |
| Morador | Pessoa cadastrada em uma unidade | `Morador` | `morador` |
| Destinatário | Nome que consta na etiqueta | `destinatario` | `destinatario` |
| Portaria | Nó local de operação, identificado de P01 a P10 | `id_portaria` | `portaria` |
| Central | Servidor da administradora que consolida os dados | executável `central` | — |
| Estante, prateleira e posição | Matriz física de armazenamento; posição = estante + prateleira | `estante[][]` | `posicao_estante` |
| Código de retirada | 6 dígitos, uso único | `codigo` | `codigo_retirada_hash` |
| Retirada | Entrega ao morador mediante o código | módulo `retirada` | `retirada` |
| Aviso | Comunicação da chegada ao morador | módulo `aviso` | `aviso` |
| Canal de aviso | APP, SMS ou INTERFONE (com código impresso) | `CanalAviso` | `canal_aviso` |
| Operação | Evento da portaria a sincronizar: REGISTRO, RETIRADA ou DEVOLUCAO | `Operacao` | `operacao_sincronizacao` |
| Fila de sincronização | Operações ainda não enviadas à central | módulo `sincronizacao` | — |
| Consolidação | Aplicação das operações na central, sem duplicar | módulo `consolidacao` | — |
| Status | PENDENTE, RETIRADA ou DEVOLVIDA | `StatusEncomenda` | `status` |

---

## 9. Etapas do manual: o que produzir e onde guardar

Cada item com `[ ]` é uma exigência do manual. O arquivo `00-projeto/rastreabilidade.md` repete esses itens, junto com as exigências do documento (seção 11), em uma tabela com coluna de status.

### 9.1 Etapa 1 — Caracterização da organização → `01-organizacao/`

- [ ] Identificação da organização → `caracterizacao.md`
- [ ] Ramo de atuação → `caracterizacao.md`
- [ ] Missão → `caracterizacao.md`
- [ ] Produtos/serviços → `caracterizacao.md`
- [ ] Estrutura organizacional → `caracterizacao.md` + `diagramas/organograma.mmd`
- [ ] Processos de negócio → `processos.md` + `diagramas/processo-atual.mmd` e `diagramas/processo-proposto.mmd`
- [ ] Público-alvo → `caracterizacao.md`
- [ ] Problemas encontrados → `caracterizacao.md` (P1 a P7)
- [ ] Justificativa da solução proposta → `caracterizacao.md`

**Conteúdo:** seção 4 deste plano. **Formato:** tópicos e tabelas; o texto do capítulo 2 é escrito pelo grupo.

### 9.2 Etapa 2 — Pesquisa científica e inovação → `02-pesquisa/`

- [ ] Problema de pesquisa → `problema-e-objetivos.md`
- [ ] Objetivos → `problema-e-objetivos.md`
- [ ] Metodologia → `metodologia.md` (+ `questionario-campo.md` e `resultados-campo.md`)
- [ ] Fundamentação bibliográfica → `fundamentacao.md` + `fontes.md`
- [ ] Trabalhos relacionados → `trabalhos-relacionados.md`
- [ ] Justificativa científica → `problema-e-objetivos.md`
- [ ] Diferenciais inovadores → `diferenciais.md`

**Pergunta de pesquisa (sugestão).** Como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo dedicado pelos porteiros à gestão de encomendas em uma administradora de condomínios?

**Objetivo geral.** Desenvolver e documentar uma solução computacional para a gestão de encomendas nas portarias da Administradora Morada Central.

**Objetivos específicos.**
1. Caracterizar o processo atual de encomendas e seus problemas.
2. Levantar requisitos com pesquisa bibliográfica e de campo.
3. Modelar o banco de dados relacional e avaliar o uso de NoSQL.
4. Implementar em C o núcleo da portaria e a consolidação central.
5. Projetar a infraestrutura de rede e a arquitetura distribuída.
6. Analisar a segurança, a privacidade e a acessibilidade da solução.

**Metodologia.** Pesquisa aplicada e exploratória, com abordagem qualitativa e alguns dados quantitativos simples. Procedimentos:
- pesquisa bibliográfica;
- levantamento de campo com um questionário curto para porteiros e síndicos — anônimo, sem coletar dados pessoais e explicando a finalidade acadêmica (confirmar com o professor se a UNIP exige algum termo);
- desenvolvimento de protótipo com Scrum.

**Questionário de campo (8 a 10 perguntas).** Encomendas por dia; dias e épocas de pico; tempo gasto com encomendas por turno; como o registro é feito hoje; como o morador é avisado; extravios ou entregas erradas nos últimos 3 meses; espaço de armazenamento; qualidade da internet na portaria; o que mais ajudaria.

**Temas da fundamentação.** Crescimento do comércio eletrônico e entregas de última milha; gestão condominial e rotina de portaria; LGPD; sistemas distribuídos (operação offline, consistência eventual, idempotência); bancos relacionais e NoSQL; Scrum; programação estruturada.

**Trabalhos relacionados.** Comparar categorias de solução: caderno ou planilha (situação atual), aplicativos de gestão condominial com módulo de encomendas, armários inteligentes e portaria remota. Critérios: custo, dependência de internet, aviso ao morador, rastreabilidade, atendimento a quem não usa smartphone e visão de vários condomínios. Produtos reais só entram com fonte.

**Diferenciais.** Operação offline com sincronização sem duplicidade; endereçamento automático na estante; aviso multicanal com opção de código impresso; consolidação de vários condomínios; dados de pico para dimensionar a equipe.

**Fontes iniciais (verificar todas e dar preferência a fontes acadêmicas e oficiais).**
- Pitney Bowes Brasil, blog sobre gestão de encomendas em condomínios. É um fornecedor do setor; traz a estimativa de que porteiros chegam a dedicar de 15% a 40% do turno às encomendas. Usar como dado de mercado, citando a origem. https://www.pitneybowes.com/br/blog/gestao-encomendas-condominios-ecommerce-sindicos.html
- Condomínios SC, sobre atritos causados por encomendas nas portarias: https://condominiosc.com.br/secoes/condominio-e-cia/5482-encomendas-desencadeiam-atritos-nas-portarias-de-condominios-como-a-tecnologia-pode-ajudar-a-resolver-o-problema
- Condomínios SC, sobre o aumento de encomendas no fim do ano: https://condominiosc.com.br/jornal-dos-condominios/gestao/5686-recebimento-de-encomendas-no-natal-como-os-condominios-podem-garantir-logistica-e-seguranca
- Condomínios SC, sobre o crescimento das compras online e a adaptação dos condomínios: https://condominiosc.com.br/jornal-dos-condominios/comportamento/4400-compras-online-aumentam-e-exigem-adequacoes-nos-condominios
- Diário do Comércio, sobre a preparação dos condomínios para a Black Friday: https://diariodocomercio.com.br/opiniao/artigo/black-friday-como-os-condominios-devem-se-preparar/

**Bibliografia sugerida (conferir edição e ano na biblioteca da UNIP antes de referenciar).** Sommerville, *Engenharia de Software*; Pressman, *Engenharia de Software*; Schwaber e Sutherland, *O Guia do Scrum*; Heuser, *Projeto de Banco de Dados*; Elmasri e Navathe, *Sistemas de Banco de Dados*; Sadalage e Fowler, *NoSQL Essencial*; Tanenbaum, *Redes de Computadores*; Kurose e Ross, *Redes de Computadores e a Internet*; Tanenbaum e Van Steen, *Sistemas Distribuídos*; Deitel, *C: Como Programar*; Forbellone e Eberspächer, *Lógica de Programação*; Lei nº 13.709/2018 (LGPD); Lei nº 13.146/2015 (Lei Brasileira de Inclusão).

### 9.3 Etapa 3 — Engenharia de Software → `03-engenharia-software/`

- [ ] Requisitos funcionais → `requisitos.md`
- [ ] Requisitos não funcionais → `requisitos.md`
- [ ] Casos de uso → `casos-de-uso.md`
- [ ] Backlog do produto → `scrum/backlog.md`
- [ ] Arquitetura do sistema → `arquitetura.md` + `decisoes/`
- [ ] Diagrama de casos de uso → `diagramas/casos-de-uso.puml`
- [ ] Diagrama de classes (quando aplicável) → `diagramas/classes-dominio.puml` (modelo de domínio; em C, as "classes" viram structs e módulos)
- [ ] Diagrama de atividades ou de sequência → `diagramas/atividade-registrar-encomenda.puml`, `diagramas/atividade-retirar-encomenda.puml` e `diagramas/sequencia-sincronizacao.puml` (+ `diagramas/estados-encomenda.puml`)
- [ ] Planejamento com Scrum, XP ou Kanban → `scrum/` (papéis, cerimônias, sprints e definição de pronto)

**Atores.** Porteiro (principal), Morador, Supervisor da administradora, Central (sistema) e Serviço de avisos (sistema externo).

**Requisitos funcionais (base).**

| ID | Requisito |
|---|---|
| RF01 | Registrar encomenda com unidade, destinatário, transportadora e tamanho |
| RF02 | Indicar automaticamente uma posição livre na estante |
| RF03 | Gerar código de retirada único, de 6 dígitos |
| RF04 | Avisar o morador pelo canal cadastrado (app, SMS ou interfone com código impresso) |
| RF05 | Registrar a retirada conferindo o código, com data, hora e nome de quem retirou |
| RF06 | Listar as pendências e buscar encomendas por unidade |
| RF07 | Exibir o mapa de ocupação da estante |
| RF08 | Cadastrar moradores e o canal de aviso de cada um |
| RF09 | Continuar operando sem conexão, guardando as operações para envio posterior |
| RF10 | Sincronizar as operações com a central sem duplicar registros |
| RF11 | Alertar encomendas pendentes há mais de 7 dias |
| RF12 | Gerar relatórios de dia de pico, ocupação e pendências por condomínio |

**Requisitos não funcionais (base).**

| ID | Requisito |
|---|---|
| RNF01 | Disponibilidade: a operação da portaria não depende de internet |
| RNF02 | Usabilidade: registrar uma encomenda leva no máximo cerca de 30 segundos |
| RNF03 | Privacidade: só os dados pessoais necessários, com acesso por perfil (LGPD) |
| RNF04 | Segurança: código de uso único, não exibido a terceiros |
| RNF05 | Portabilidade: o protótipo compila no Windows e no Linux com gcc (C99) |
| RNF06 | Escalabilidade: incluir um condomínio sem alterar o código |
| RNF07 | Rastreabilidade: toda operação tem id único, data, hora e autor |
| RNF08 | Acessibilidade: aviso alternativo para quem não usa smartphone |

**Casos de uso.** UC01 Registrar encomenda (inclui UC02); UC02 Avisar morador; UC03 Retirar encomenda; UC04 Consultar pendências; UC05 Manter moradores; UC06 Sincronizar com a central; UC07 Consolidar operações; UC08 Emitir relatórios.

**Backlog (histórias de usuário).**

| ID | História | Sprint |
|---|---|---|
| US01 | Como porteiro, quero registrar uma encomenda com unidade, destinatário, transportadora e tamanho, para não depender do caderno | 1 |
| US02 | Como porteiro, quero que o sistema indique a posição na estante, para guardar e achar o volume rápido | 1 |
| US03 | Como morador, quero um código único de retirada, para que só eu ou quem eu autorizar retire o volume | 1 |
| US04 | Como porteiro, quero registrar a retirada conferindo o código, para saber quem retirou e quando | 1 |
| US05 | Como porteiro, quero listar as pendências e buscar por unidade, para atender o morador no balcão | 1 |
| US06 | Como administradora, quero os dados salvos em arquivo, para não perder registros ao fechar o programa | 1 |
| US07 | Como porteiro, quero cadastrar moradores com o canal de aviso preferido, para avisar cada um do jeito certo | 2 |
| US08 | Como morador, quero ser avisado pelo meu canal, para retirar logo | 2 |
| US09 | Como porteiro, quero continuar registrando sem internet, para a portaria não parar | 2 |
| US10 | Como porteiro, quero sincronizar as operações quando a conexão voltar, para a central ficar atualizada | 2 |
| US11 | Como supervisor, quero consolidar as operações de todas as portarias sem duplicidade, para ter uma visão única | 2 |
| US12 | Como porteiro, quero ver o mapa de ocupação da estante, para saber se há espaço | 3 |
| US13 | Como supervisor, quero alertas de volumes parados há mais de 7 dias, para cobrar a retirada | 3 |
| US14 | Como supervisor, quero relatórios de pico e ocupação por condomínio, para dimensionar a equipe | 3 |
| US15 | Como equipe, queremos testes automatizados das funções principais, para alterar o código com segurança | 3 |
| US16 | (Opcional) Como porteiro, quero marcar um volume como devolvido após o prazo, para liberar espaço | 3 |

Cada história ganha critérios de aceitação no `backlog.md`, no formato "Dado / Quando / Então".

**Arquitetura (`arquitetura.md`).**
- Camadas do nó da portaria: interface de console → regras de negócio (módulos) → persistência em arquivos → fila de sincronização.
- Sistema completo: portarias ↔ API central ↔ banco relacional; painel da administradora; serviço de avisos.
- Tabela de correspondência entre o protótipo e o sistema completo (seção 5.4).

**Ferramentas (`ferramentas.md`).** Lista das ferramentas e tecnologias usadas, com versão e finalidade: gcc (C99), Make, Git e GitHub, MySQL 8 e MySQL Workbench, PlantUML, Mermaid, Cisco Packet Tracer e brModelo, se for usado. É o item "materiais" que o manual pede no Desenvolvimento (seção 11).

**Scrum (`scrum/`).**
- Papéis: Product Owner, Scrum Master e time de desenvolvimento (nomes em `00-projeto/integrantes.md`).
- Cerimônias simplificadas: planejamento de 30 minutos no início da sprint; daily assíncrona no grupo de mensagens; revisão e retrospectiva registradas em `sprints/sprint-NN.md` (meta, histórias, o que foi entregue, o que não foi e o que melhorar).
- Quadro Kanban de apoio (GitHub Projects ou Trello) com as colunas A fazer → Fazendo → Em revisão → Pronto.
- Definição de pronto: seção 10.

### 9.4 Etapa 4 — Banco de dados → `04-banco-de-dados/`

- [ ] Modelo conceitual → `modelo-conceitual.md` (+ brModelo, se o professor pedir a notação de Chen)
- [ ] Diagrama Entidade-Relacionamento (DER) → `diagramas/der.mmd` + PNG
- [ ] Modelo lógico → `modelo-logico.md`
- [ ] Normalização → `normalizacao.md`
- [ ] Modelo físico → `sql/01-criacao-tabelas.sql`
- [ ] Principais comandos SQL → `sql/02-carga-exemplo.sql`, `sql/03-consultas.sql` e `sql/04-views-indices.sql`
- [ ] Discussão sobre o uso de bancos NoSQL → `nosql/comparativo.md` + `nosql/exemplo-aviso.json`

**SGBD.** MySQL 8 como padrão (trocar se a disciplina usar outro).

**Tabelas e atributos principais.**

| Tabela | Atributos principais | Regras |
|---|---|---|
| `condominio` | id_condominio, nome, cidade | — |
| `bloco` | id_bloco, id_condominio, nome | FK para condomínio |
| `unidade` | id_unidade, id_bloco, numero | UNIQUE (id_bloco, numero) |
| `morador` | id_morador, id_unidade, nome, canal_aviso, contato, ativo | canal em APP, SMS ou INTERFONE; contato pode ser nulo |
| `funcionario` | id_funcionario, id_condominio, nome, funcao | — |
| `portaria` | id_portaria (P01 a P10), id_condominio, descricao | — |
| `posicao_estante` | id_posicao, id_portaria, estante, prateleira, tipo_volume | UNIQUE (id_portaria, estante, prateleira) |
| `encomenda` | id_encomenda, id_portaria, id_local, id_unidade, id_posicao, id_funcionario_recebimento, destinatario, transportadora, tamanho, recebida_em, codigo_retirada_hash, status | UNIQUE (id_portaria, id_local); status em PENDENTE, RETIRADA ou DEVOLVIDA |
| `retirada` | id_retirada, id_encomenda, id_funcionario, retirado_por, retirada_em | UNIQUE (id_encomenda): no máximo uma retirada por encomenda |
| `aviso` | id_aviso, id_encomenda, id_morador, canal, enviado_em, situacao | — |
| `operacao_sincronizacao` | id_operacao (ex.: P01-000123), id_portaria, tipo, id_local, data_hora_origem, aplicada_em | a chave primária no id da operação garante a idempotência |

`id_local` é o id da encomenda no arquivo da portaria. Junto com `id_portaria`, ele liga o protótipo em C ao banco central.

**Normalização.** Partir de uma página do caderno da portaria (tabela não normalizada, com "Bloco A apto 12" num campo só e dados do morador repetidos) e mostrar a 1FN, a 2FN e a 3FN até chegar às tabelas acima.

**Consultas (`sql/03-consultas.sql`).** Pendências por condomínio; pendências há mais de 7 dias; tempo médio entre a chegada e a retirada por condomínio; encomendas por dia e dia de pico; ocupação da estante por portaria; histórico de uma unidade; auditoria (quem registrou e quem retirou).

**Views e índices (`sql/04-views-indices.sql`).** `vw_pendentes` e `vw_indicadores_condominio`; índices em `encomenda (status, recebida_em)` e `encomenda (id_unidade)`.

**NoSQL (`nosql/`).** Comparar, para este caso, o modelo relacional, o de documentos (ex.: MongoDB) e o de chave-valor (ex.: Redis). Conclusão: relacional no núcleo (ADR-001); um banco de documentos poderia guardar o histórico de avisos, cujos campos variam conforme o canal. Incluir um documento JSON de exemplo.

### 9.5 Etapa 5 — Programação estruturada em C → `05-programa-c/`

- [ ] Algoritmos → `algoritmos/pseudocodigo.md` (A1 a A6)
- [ ] Fluxogramas → `algoritmos/fluxogramas/` (A1 a A6, em `.mmd` + PNG)
- [ ] Pseudocódigo → `algoritmos/pseudocodigo.md`
- [ ] Implementação em C → `src/` e `include/`
- [ ] Estruturas condicionais → validações, regra de tamanho do volume, `switch` do menu
- [ ] Estruturas de repetição → varredura da matriz, leitura de arquivos linha a linha, laço do menu
- [ ] Funções → todos os módulos (prefixo `modulo_`)
- [ ] Vetores e matrizes → vetores de encomendas e de moradores e contagem por dia no relatório; matriz `estante[NUM_ESTANTES][NUM_PRATELEIRAS]`
- [ ] Manipulação de arquivos → `persistencia.c`, `sincronizacao.c` e `consolidacao.c`

**Executáveis.**
- `portaria <n>`: nó da portaria n (1 a 10). Exemplo: `bin/portaria 1` opera a P01.
- `central`: lê o que as portarias enviaram, consolida sem duplicar e gera o relatório consolidado.

**Menu da portaria.**

```
=== PORTARIA P01 - Morada Central ===   [ONLINE]
1 - Registrar encomenda
2 - Registrar retirada
3 - Listar pendentes
4 - Buscar por unidade
5 - Mapa da estante
6 - Moradores
7 - Relatorios
8 - Sincronizar com a central
9 - Alternar online/offline (simulacao)
0 - Sair
```

**Módulos.**

| Módulo | Responsabilidade | Funções principais (sugestão) |
|---|---|---|
| `tipos.h` | Structs, enums e constantes compartilhadas | — |
| `util` | Leitura segura do teclado, datas e validações | `util_ler_texto`, `util_ler_inteiro`, `util_data_hora_atual`, `util_dias_entre` |
| `morador` | Cadastro e busca de moradores e do canal de aviso | `morador_cadastrar`, `morador_buscar_por_unidade`, `morador_listar` |
| `estante` | Matriz de posições: alocar, liberar, reconstruir, mapa e ocupação | `estante_alocar_posicao`, `estante_liberar_posicao`, `estante_reconstruir`, `estante_imprimir_mapa`, `estante_ocupacao` |
| `codigo` | Código de retirada de 6 dígitos | `codigo_gerar_unico`, `codigo_conferir` |
| `encomenda` | Registro, listagem e busca | `encomenda_registrar`, `encomenda_listar_pendentes`, `encomenda_buscar_por_unidade` |
| `retirada` | Retirada com conferência do código | `retirada_registrar` |
| `aviso` | Aviso simulado conforme o canal do morador | `aviso_enviar` |
| `relatorio` | Contagem por dia, pico, pendências antigas e ocupação | `relatorio_contar_por_dia`, `relatorio_dia_pico`, `relatorio_pendentes_antigas` |
| `persistencia` | Leitura e gravação dos arquivos CSV | `persistencia_carregar_encomendas`, `persistencia_salvar_encomendas`, `persistencia_carregar_moradores`, `persistencia_salvar_moradores` |
| `sincronizacao` | Fila de operações e envio quando online | `sincronizacao_registrar_operacao`, `sincronizacao_enviar_pendentes`, `sincronizacao_contar_pendentes` |
| `consolidacao` | Aplicação idempotente das operações na central | `consolidacao_processar_portaria`, `consolidacao_operacao_ja_aplicada` |

**Estruturas e enums (`tipos.h`).**

| Estrutura | Campos |
|---|---|
| `Morador` | `id`, `nome`, `bloco`, `apartamento`, `canal` (`CanalAviso`), `contato` (vazio quando o canal é interfone), `ativo` |
| `Encomenda` | `id`, `bloco`, `apartamento`, `destinatario`, `transportadora`, `tamanho` (P, M ou G), `recebida_em`, `estante`, `prateleira`, `codigo`, `status` (`StatusEncomenda`), `retirada_em`, `retirado_por` |
| `Operacao` | `id_operacao` (ex.: `P01-000123`), `id_portaria`, `data_hora`, `tipo` (`TipoOperacao`), `id_encomenda`, `bloco`, `apartamento` |

| Enum | Valores |
|---|---|
| `StatusEncomenda` | `STATUS_PENDENTE`, `STATUS_RETIRADA`, `STATUS_DEVOLVIDA` |
| `CanalAviso` | `CANAL_APP`, `CANAL_SMS`, `CANAL_INTERFONE` |
| `TipoOperacao` | `OP_REGISTRO`, `OP_RETIRADA`, `OP_DEVOLUCAO` |

**Constantes (`tipos.h`).**

| Constante | Valor | Uso |
|---|---|---|
| `MAX_ENCOMENDAS` | 500 | Tamanho do vetor de encomendas |
| `MAX_MORADORES` | 300 | Tamanho do vetor de moradores |
| `NUM_ESTANTES` | 4 | Linhas da matriz (uma estante por bloco, de A a D) |
| `NUM_PRATELEIRAS` | 12 | Colunas da matriz |
| `PRATELEIRA_INICIAL_G` | 10 | As prateleiras 10 e 11 ficam reservadas a volumes grandes |
| `TAM_CODIGO` | 6 | Dígitos do código de retirada |
| `MAX_TENTATIVAS` | 3 | Tentativas de código numa retirada |
| `DIAS_ALERTA` | 7 | Dias a partir dos quais uma pendência é considerada antiga |
| `MAX_PORTARIAS` | 10 | Portarias lidas pela central |

**Arquivos de dados.**

| Arquivo | Conteúdo (colunas separadas por `;`) |
|---|---|
| `dados/portarias/P01-moradores.csv` | id;nome;bloco;apartamento;canal;contato;ativo |
| `dados/portarias/P01-encomendas.csv` | id;bloco;apartamento;destinatario;transportadora;tamanho;recebida_em;estante;prateleira;codigo;status;retirada_em;retirado_por |
| `dados/portarias/P01-fila.csv` | id_operacao;id_portaria;data_hora;tipo;id_encomenda;bloco;apartamento |
| `dados/portarias/P01-avisos.txt` | Registro legível dos avisos simulados |
| `dados/portarias/P01-sequencia.txt` | Último número de operação usado |
| `dados/rede/P01.log` | Operações "transmitidas" pela portaria (mesmo formato da fila) |
| `dados/central/operacoes-aplicadas.csv` | Ids das operações já aplicadas |
| `dados/central/encomendas-consolidadas.csv` | id_portaria;id_encomenda;bloco;apartamento;status;recebida_em;retirada_em |
| `dados/central/relatorio-consolidado.txt` | Relatório por portaria |

Regras dos arquivos: datas no formato `AAAA-MM-DD HH:MM`; a primeira linha é o cabeçalho; campos de texto não aceitam `;`. A matriz da estante não tem arquivo próprio: ela é reconstruída a partir das encomendas pendentes quando o programa abre, para existir uma única fonte de verdade.

**Algoritmos (documentar cada um em pseudocódigo e fluxograma).**
- **A1. Alocar posição na estante (matriz).** Estante preferida = posição do bloco no alfabeto (A = 0, B = 1…) módulo `NUM_ESTANTES`. Volumes G usam as prateleiras a partir de `PRATELEIRA_INICIAL_G`; volumes P e M usam as anteriores. O algoritmo procura a primeira posição livre dessa faixa na estante preferida; se não houver, procura nas outras estantes; se tudo estiver cheio, avisa o porteiro.
- **A2. Gerar código único.** Sorteia um número de 100000 a 999999 e repete enquanto ele já existir em alguma encomenda pendente.
- **A3. Registrar retirada.** Busca as pendências da unidade e pede o código (até `MAX_TENTATIVAS`). Se conferir, marca a encomenda como RETIRADA com data, hora e nome de quem retirou, libera a posição e registra a operação na fila.
- **A4. Sincronizar (portaria).** Se estiver offline, informa quantas operações aguardam. Se estiver online, copia cada operação da fila para `dados/rede/Pnn.log` e esvazia a fila.
- **A5. Consolidar (central, idempotente).** Para cada portaria de P01 a P10, lê `dados/rede/Pnn.log`, se existir. Para cada operação: se o id já está em `operacoes-aplicadas.csv`, ignora; senão, aplica no consolidado e registra o id como aplicado.
- **A6. Relatórios.** Vetor de 31 posições com a contagem por dia do mês; dia de pico = índice do maior valor; pendências com mais de `DIAS_ALERTA` dias; ocupação = posições ocupadas ÷ total de posições × 100.

**Testes (`tests/`, com `assert.h`).**
- `test_estante.c`: aloca na estante do bloco; volume G vai para a faixa reservada; estante cheia leva a outra estante; tudo cheio retorna erro; liberar uma posição funciona.
- `test_codigo.c`: o código tem 6 dígitos; não repete entre pendentes; conferência certa e errada.
- `test_util.c`: diferença em dias entre duas datas.
- `test_consolidacao.c`: processar o mesmo log duas vezes não duplica nada.

**Compilar, testar e executar** (sempre a partir de `05-programa-c/`).
- `make` gera `bin/portaria` e `bin/central` com `gcc -std=c99 -Wall -Wextra -pedantic`.
- `make test` compila e roda os testes; `make clean` limpa.
- No Windows sem make: `build.bat` (com MinGW-w64).
- Executar: `bin/portaria 1` e `bin/central` (no Windows, `bin\portaria.exe 1`).

**Regras do código.** C99 e apenas a biblioteca padrão (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `time.h`, `assert.h`); vetores e matrizes estáticos, com tamanhos em constantes; entrada com `fgets` e conversão validada (nunca `scanf("%s")`); sem `conio.h`, `windows.h` ou bibliotecas externas; comentário didático em cada função.

### 9.6 Etapa 6 — Redes de computadores e sistemas distribuídos → `06-redes/`

- [ ] Arquitetura da rede → `arquitetura-e-topologia.md`
- [ ] Topologia → `arquitetura-e-topologia.md` + `diagramas/topologia.mmd` + print do Packet Tracer
- [ ] Equipamentos → `equipamentos.md`
- [ ] Endereçamento IP → `enderecamento-ip.md`
- [ ] VLANs → `vlans.md`
- [ ] Comunicação entre serviços → `nuvem-e-sistemas-distribuidos.md`
- [ ] Computação em nuvem → `nuvem-e-sistemas-distribuidos.md`
- [ ] Arquitetura distribuída → `nuvem-e-sistemas-distribuidos.md`
- [ ] Escalabilidade → `nuvem-e-sistemas-distribuidos.md`
- [ ] Segurança da infraestrutura → `seguranca-infraestrutura.md`

**Locais.** Sede (local 0), condomínios 1 a 10 e a nuvem.

**Topologia.** Estrela em cada local: roteador/firewall, switch gerenciável com VLANs (802.1Q) e ponto de acesso Wi-Fi. Na WAN, hub-and-spoke: cada local fecha uma VPN IPsec com a nuvem. Se a VPN ou a internet cair, a portaria continua operando (RNF01).

**VLANs.**

| VLAN | Condomínios | Sede |
|---|---|---|
| 10 | PORTARIA: PC da portaria e impressora | ADMINISTRATIVO: PCs da gerência e do financeiro |
| 20 | CFTV: câmeras e gravador | ATENDIMENTO: PCs dos atendentes |
| 30 | VISITANTES: Wi-Fi isolado, só internet | VISITANTES: Wi-Fi isolado, só internet |
| 99 | GERENCIA: switch, ponto de acesso e roteador | GERENCIA: switch, ponto de acesso e roteador |

**Endereçamento.** Padrão `10.X.Y.0/24`, com X = local e Y = VLAN. Gateway no `.1`, equipamentos com IP fixo de `.10` a `.49`, DHCP de `.100` a `.199`. O `/24` por VLAN privilegia a clareza; o texto pode comentar que sub-redes menores (VLSM) economizariam endereços.

| Exemplo | Rede | Gateway | IPs fixos |
|---|---|---|---|
| Condomínio 3, VLAN 10 (portaria) | 10.3.10.0/24 | 10.3.10.1 | PC 10.3.10.10; impressora 10.3.10.20 |
| Sede, VLAN 10 (administrativo) | 10.0.10.0/24 | 10.0.10.1 | — |
| Nuvem, sub-rede pública (API) | 172.16.1.0/24 | — | — |
| Nuvem, sub-rede privada (banco) | 172.16.2.0/24 | — | — |

`enderecamento-ip.md` traz a tabela completa: sede e 10 condomínios, com as 4 VLANs de cada local.

**Equipamentos.**
- Por condomínio: roteador/firewall com VPN; switch gerenciável PoE de 16 portas; ponto de acesso; PC ou mini PC da portaria; impressora térmica para o código impresso; nobreak; câmeras e gravador já existentes.
- Sede: roteador/firewall; switch de 24 portas; pontos de acesso; PCs; impressora; nobreak.
- Nuvem: servidor de aplicação (máquina virtual ou contêiner) com a API; MySQL gerenciado; armazenamento para backup.

**Comunicação entre serviços.** No sistema completo, a portaria envia lotes da fila para a API central por HTTPS (REST com JSON); o painel da administradora consulta a mesma API; a API aciona o serviço de avisos (SMS ou app). No protótipo, os arquivos de `dados/rede/` fazem o papel dessa comunicação.

**Nuvem.** Explicar IaaS, PaaS e SaaS. Decisão: PaaS para o banco (backup e atualização gerenciados) e máquina virtual ou contêiner para a API. Comparar com um servidor próprio na sede (custo mensal versus investimento inicial, disponibilidade e manutenção).

**Sistema distribuído.** Nós autônomos que funcionam offline; sincronização assíncrona; consistência eventual; idempotência pelo id da operação; ordem garantida dentro de cada portaria pela sequência; tolerância a falhas (a queda da internet ou da nuvem não para a portaria); reenvio seguro.

**Escalabilidade.** Um novo condomínio exige um novo nó, uma nova faixa `10.X.0.0` e uma nova VPN, sem mudar o código. A API escala horizontalmente; o banco usa índices e, se crescer, réplicas de leitura para os relatórios.

**Segurança da infraestrutura.** Firewall com regras mínimas (a VLAN 30 só acessa a internet; a VLAN 10 só fala com a API pela VPN); VPN IPsec; HTTPS/TLS; acesso por perfil com senhas fortes e autenticação em dois fatores no painel; backups na regra 3-2-1; atualizações; logs de auditoria; CFTV isolado na VLAN 20.

**Packet Tracer (feito pelo grupo).** Montar a sede, 2 condomínios representativos e um servidor representando a central, com VLANs, roteamento entre VLANs e DHCP. Testes para print: a portaria alcança o servidor central; o Wi-Fi de visitantes não alcança a portaria (ACL). Se a VPN ficar complexa demais no simulador, ela pode aparecer só no diagrama.

### 9.7 Etapa 7 — Direitos humanos, inclusão e segurança (versão curta) → `07-seguranca-privacidade-acessibilidade/analise.md`

- [ ] Acessibilidade
- [ ] Inclusão digital
- [ ] Privacidade
- [ ] Proteção de dados
- [ ] Segurança da informação
- [ ] Impactos sociais
- [ ] Aspectos éticos
- [ ] Direitos humanos

Todos os itens ficam no mesmo arquivo, para um capítulo de cerca de 2 páginas:
- **Privacidade e proteção de dados (LGPD, Lei nº 13.709/2018).** Dados tratados: nome, unidade, canal e contato do morador, nome de quem retirou e datas. Finalidade: entregar a encomenda. Minimização: não registrar conteúdo nem remetente, só a transportadora; contato apenas quando o canal exige. Retenção com prazo definido (ex.: 12 meses) e depois anonimização. Acesso por perfil.
- **Segurança da informação.** Código de uso único, não exibido a terceiros; no banco central ele é guardado como hash (no protótipo fica em texto, o que entra como limitação); log de auditoria; backup; referência a `06-redes/seguranca-infraestrutura.md`.
- **Acessibilidade e inclusão digital.** Aviso por interfone e código impresso para quem não usa smartphone; telas do sistema completo seguindo as WCAG (contraste, fonte ampliável, compatibilidade com leitor de tela); Lei Brasileira de Inclusão (Lei nº 13.146/2015), cujo art. 63 exige acessibilidade nos sites de empresas.
- **Ética, impactos sociais e direitos humanos.** Menos conflito entre moradores e portaria; carga de trabalho do porteiro mais previsível; os registros servem para rastrear encomendas, não para vigiar funcionários; tratamento igual para todos os moradores, com ou sem smartphone.

### 9.8 Etapa 8 — Integração da solução → `08-integracao/`

- [ ] Como os componentes se integram → `integracao.md` + `diagramas/fluxo-ponta-a-ponta.mmd`
- [ ] Implantação (o manual inclui a implantação no percurso da solução, de "organização" até "implantação") → `implantacao.md`
- [ ] Benefícios esperados para a organização → `beneficios-e-indicadores.md`
- [ ] Limitações da solução → `limitacoes-e-evolucao.md`
- [ ] Possibilidades de evolução futura → `limitacoes-e-evolucao.md`
- [ ] Conclusão geral → `documento-final/capitulos/10-conclusao.md` (escrita pelo grupo)

**Integração.** Seguir uma encomenda do começo ao fim e mostrar cada disciplina no caminho: história de usuário (Scrum) → regra e algoritmo em C → registro em arquivo e, no sistema completo, no banco → operação atravessando a rede até a central → aviso ao morador com privacidade e acessibilidade → indicador que responde à pergunta de pesquisa.

**Implantação.** Piloto em um condomínio por 2 semanas; treinamento curto dos porteiros, com uma cartilha de uma página; no primeiro dia, as pendências do caderno são cadastradas no sistema; expansão para os demais condomínios em ondas, ajustada pelo que o piloto mostrar; comunicado aos moradores sobre o código de retirada e os canais de aviso; plano de contingência (se o PC da portaria falhar, usa-se um formulário em papel e os registros são lançados depois).

**Indicadores.** Extravios por mês; tempo médio entre chegada e retirada; percentual de moradores avisados em até 15 minutos; tempo de registro por encomenda; pendências com mais de 7 dias. O "antes" vem da pesquisa de campo; o "depois" é meta ou estimativa e precisa ser apresentado como tal.

**Limitações.** Rede simulada por arquivos; aviso simulado; sem interface gráfica; código de retirada em texto no protótipo; dados fictícios.

**Evolução futura.** App do morador; API real (HTTPS) no lugar dos arquivos; integração com armários inteligentes; foto da etiqueta com leitura automática; painel de indicadores; avisos por WhatsApp.

---

## 10. Plano de sprints (Scrum)

Sprints de 1 semana. Ajustar as datas ao prazo real em `00-projeto/cronograma.md` (ver seção 13).

| Sprint | Meta | Entregas |
|---|---|---|
| 0 | Base do projeto | Estrutura do repositório, regras, glossário e rastreabilidade; Etapa 1; problema, objetivos e metodologia (Etapa 2); requisitos, casos de uso, ADRs e backlog (Etapa 3) |
| 1 | Portaria funcionando | US01 a US06; modelo conceitual, modelo lógico e normalização; questionário de campo aplicado |
| 2 | Sistema distribuído | US07 a US11; scripts SQL; endereçamento e VLANs |
| 3 | Relatórios e qualidade | US12 a US15 (US16 se sobrar tempo); pseudocódigos e fluxogramas de A1 a A6; Packet Tracer; Etapas 7 e 8 |
| 4 | Documento e entrega | Capítulos, resumo e abstract, revisão ABNT, conferência da rastreabilidade, impressão e postagem pelo líder |

**Definição de pronto (DoD).**
- Compila sem warnings e todos os testes passam.
- Funções comentadas; algoritmos principais com pseudocódigo e fluxograma.
- Critérios de aceitação da história atendidos.
- `00-projeto/rastreabilidade.md` e a `sprint-NN.md` da sprint atualizadas.
- Revisado por outro integrante antes do merge na `main`.

---

## 11. Documento final (ABNT)

**Sumário planejado e orçamento de páginas.**

| Parte | Conteúdo | Etapa | Páginas |
|---|---|---|---|
| Pré-textuais | Capa, Resumo, Abstract e Sumário (seguir o modelo da UNIP) | — | — |
| 1 Introdução | Objetivo, metodologia, apresentação da empresa e visão geral da proposta | — | ~2 |
| 2 Caracterização da organização | Seção 9.1 | 1 | 3 |
| 3 Pesquisa científica e inovação | Seção 9.2 | 2 | 3 |
| 4 Engenharia de software | Seção 9.3 | 3 | 4 |
| 5 Banco de dados | Seção 9.4 | 4 | 4 |
| 6 Programação estruturada em C | Seção 9.5 | 5 | 4 |
| 7 Redes e sistemas distribuídos | Seção 9.6 | 6 | 4 |
| 8 Direitos humanos, inclusão e segurança | Seção 9.7 | 7 | 2 |
| 9 Integração da solução | Seção 9.8 | 8 | 2 |
| 10 Conclusão | Resultados × objetivos, retomada da proposta e principais pontos | — | ~1,5 |
| Referências | Lista em ABNT | — | — |

O Desenvolvimento (capítulos 2 a 9) soma cerca de 26 páginas, dentro da faixa de 20 a 30 com folga para ajustes.

**Exigências do documento (entram na rastreabilidade junto com as da seção 9).**
- [ ] Capa, Resumo, Abstract, Sumário, Introdução, Desenvolvimento, Conclusão e Referências → `documento-final/`
- [ ] Resumo conciso e objetivo, com conteúdo principal, pontos relevantes e conclusões, em até 500 palavras, seguido das palavras-chave → `capitulos/00-resumo.md`
- [ ] Abstract em inglês (ou espanhol ou francês), com as palavras-chave no mesmo idioma → `capitulos/00-abstract.md`
- [ ] Introdução com objetivo da pesquisa, metodologia, breve apresentação da empresa e visão geral da proposta → `capitulos/01-introducao.md`
- [ ] Desenvolvimento entre 20 e 30 páginas, em capítulos e subcapítulos, apresentando pesquisa, fundamentação, métodos, materiais, resultados e discussão → capítulos 2 a 9 (tabela abaixo)
- [ ] Conclusão que apresenta os resultados de forma clara, relaciona os resultados aos objetivos, retoma a proposta inicial e destaca os principais pontos encontrados → `capitulos/10-conclusao.md`
- [ ] Referências de todas as fontes usadas, em ABNT → `referencias.md`
- [ ] Citações conforme a ABNT; todo trecho reproduzido diretamente com a fonte citada no texto e a obra referenciada → todos os capítulos
- [ ] Formatação da seção 2 → `checklist-abnt-e-entrega.md`
- [ ] Entrega pelo sistema de trabalhos acadêmicos da UNIP dentro do prazo, cópia impressa ao coordenador do PIM e postagem feita pelo líder → `checklist-abnt-e-entrega.md`

**Onde ficam métodos, materiais, resultados e discussão.**

| O manual pede no Desenvolvimento | Onde aparece |
|---|---|
| Métodos | Metodologia da pesquisa (capítulo 3) e processo Scrum (capítulo 4) |
| Materiais | Ferramentas e tecnologias usadas (`03-engenharia-software/ferramentas.md`, subseção do capítulo 4) |
| Resultados | Resultados da pesquisa de campo (capítulo 3), consultas SQL executadas (capítulo 5), testes e telas do protótipo (capítulo 6) e testes no Packet Tracer (capítulo 7) |
| Discussão | Benefícios, limitações e comparação com os trabalhos relacionados (capítulo 9) |

**Figuras sugeridas.** Organograma; processo atual × proposto; diagrama de casos de uso; classes de domínio; atividade de registro; sequência da sincronização; DER; topologia (print do Packet Tracer); fluxograma do A1; print do mapa da estante; fluxo ponta a ponta.

**Código no documento.** Trechos principais no capítulo 6; código completo no repositório (link) ou em apêndice. Confirmar com o professor se o apêndice entra na contagem de páginas.

**Montagem.** O texto final vai para o Word ou o Google Docs com o modelo ABNT da UNIP. Os rascunhos de `documento-final/capitulos/` são escritos pelo grupo e depois colados no modelo. O `checklist-abnt-e-entrega.md` repete as regras de formatação e entrega da seção 2.

---

## 12. Como começar no Claude Code (prompts prontos)

**Antes de começar, tenham instalado:** Git; um compilador C (gcc: MinGW-w64 no Windows ou `build-essential` no Linux); MySQL 8 e MySQL Workbench (ou o SGBD da disciplina); extensões de PlantUML e Mermaid no VS Code (ou os sites oficiais das duas ferramentas para exportar os diagramas); Cisco Packet Tracer; brModelo, se o professor pedir.

Use um prompt por vez, revise o que foi feito e faça commit antes de seguir.

**Prompt 1 — Estrutura (Sprint 0)**
> Leia o CLAUDE.md e o PLANO.md inteiros. Crie a estrutura de pastas da seção 7, com um README.md curto em cada pasta dizendo o que ela guarda e quais exigências do manual atende. Crie também o .gitignore, o README.md da raiz e, em 00-projeto/, os arquivos regras-do-pim.md (seção 2), glossario.md (seção 8.7) e rastreabilidade.md (uma linha para cada item [ ] das seções 9 e 11, com as colunas Exigência, Arquivo, Capítulo e Status). Não escreva código C nem SQL ainda. No fim, mostre a árvore criada.

**Prompt 2 — Organização, requisitos e Scrum (Sprint 0)**
> Com base nas seções 4, 6, 9.1 e 9.3 do PLANO.md, crie os arquivos de 01-organizacao/ e de 03-engenharia-software/: requisitos, casos de uso, arquitetura, ferramentas, os seis ADRs, backlog com critérios de aceitação para cada US, papéis e cerimônias, definição de pronto e sprint-00.md. Use tópicos e tabelas, não texto corrido. Crie os diagramas listados, em PlantUML e Mermaid. Atualize a rastreabilidade.

**Prompt 3 — Pesquisa (Sprint 0)**
> Com base na seção 9.2, crie os arquivos de 02-pesquisa/ em formato de roteiro: problema e objetivos, metodologia, questionário de campo, estrutura dos trabalhos relacionados e lista de fontes com as fontes iniciais marcadas como "a verificar". Não invente referências, autores nem dados.

**Prompt 4 — Portaria funcionando (Sprint 1)**
> Implemente a Sprint 1 (US01 a US06) em 05-programa-c/, seguindo as seções 8.3 e 9.5. Antes de escrever código, mostre a lista de arquivos e funções que vai criar. Depois implemente, crie o Makefile e o build.bat, compile sem warnings, crie dados fictícios em dados/exemplo/ e os testes test_estante.c, test_codigo.c e test_util.c. No fim, explique em poucas linhas o que cada arquivo faz e atualize a sprint-01.md e a rastreabilidade.

**Prompt 5 — Banco de dados (Sprints 1 e 2)**
> Crie o conteúdo de 04-banco-de-dados/ conforme a seção 9.4: modelo conceitual, modelo lógico, normalização a partir do caderno da portaria, dicionário de dados, DER em Mermaid, scripts SQL para MySQL 8 (criação, carga fictícia, consultas, views e índices) e o comparativo NoSQL com o exemplo em JSON. Se houver MySQL disponível, rode os scripts; se não houver, revise a sintaxe com cuidado e me avise.

**Prompt 6 — Sistema distribuído (Sprint 2)**
> Implemente a Sprint 2 (US07 a US11): moradores com canal de aviso, aviso simulado, fila de sincronização, modo online/offline e o executável central com consolidação idempotente, conforme o ADR-003 e a seção 9.5. Crie o test_consolidacao.c provando que processar o mesmo log duas vezes não duplica nada. Documente os algoritmos A4 e A5 em pseudocódigo e fluxograma.

**Prompt 7 — Redes (Sprint 2)**
> Crie a documentação de 06-redes/ conforme a seção 9.6, com as tabelas completas de endereçamento e de VLANs da sede e dos 10 condomínios, e um roteiro passo a passo para o grupo montar a topologia no Packet Tracer.

**Prompt 8 — Relatórios e qualidade (Sprint 3)**
> Implemente a Sprint 3 (US12 a US15; a US16 só se sobrar tempo), complete os pseudocódigos e fluxogramas de A1 a A6, rode todos os testes e crie os arquivos de 07-seguranca-privacidade-acessibilidade/ e de 08-integracao/ (incluindo o plano de implantação) em tópicos, conforme as seções 9.7 e 9.8.

**Prompt 9 — Fechamento (Sprint 4)**
> Revise o repositório inteiro contra 00-projeto/rastreabilidade.md e me diga o que falta para cada exigência do manual. Depois crie em documento-final/ o roteiro de cada capítulo (tópicos, figuras e tabelas a usar, sem redigir o texto), o estrutura-e-paginas.md e o checklist-abnt-e-entrega.md.

---

## 13. Pontos a confirmar com o grupo e o professor

- Data de entrega do PIM (define a duração das sprints)
- Integrantes, RA e papéis no Scrum (Product Owner e Scrum Master)
- SGBD usado na disciplina (padrão: MySQL 8) e se o modelo conceitual precisa ser feito no brModelo
- O que o professor de redes espera do Packet Tracer
- Sistema operacional e IDE do grupo (o `build.bat` cobre o Windows com MinGW-w64)
- Se a UNIP tem orientação sobre o uso de IA no PIM
- Se o código completo vai em apêndice ou só como link para o repositório

