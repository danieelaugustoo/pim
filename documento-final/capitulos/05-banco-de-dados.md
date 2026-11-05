# 5 Banco de dados (roteiro, cerca de 4 páginas, Etapa 4)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo".

**Fontes no repositório:** `04-banco-de-dados/` (modelos, normalização, dicionário, DER, scripts SQL, NoSQL).

## Tópicos

| # | Tópico | Origem |
|---|---|---|
| 5.1 | Por que um banco relacional (ADR-001) e o papel do banco na solução (central/nuvem; o protótipo usa CSV) | `03-engenharia-software/decisoes/adr-001-banco-relacional.md`, `adr-002-armazenamento-csv.md` |
| 5.2 | Modelo conceitual: entidades, atributos e relacionamentos | `modelo-conceitual.md` |
| 5.3 | DER | `diagramas/der.mmd` |
| 5.4 | Normalização a partir do caderno da portaria (1FN, 2FN, 3FN) | `normalizacao.md` |
| 5.5 | Modelo lógico (tabelas, chaves, restrições) | `modelo-logico.md` |
| 5.6 | Dicionário de dados | `dicionario-de-dados.md` |
| 5.7 | Modelo físico em MySQL 8: criação, restrições nomeadas, coluna gerada e índice único | `sql/01-criacao-tabelas.sql` |
| 5.8 | Comandos SQL principais: carga, consultas, views e índices | `sql/02-carga-exemplo.sql`, `03-consultas.sql`, `04-views-indices.sql` |
| 5.9 | Resultados: consultas executadas e conferidas (inclusive a consolidação idempotente) | `sql/README.md`, `03-engenharia-software/scrum/sprints/sprint-01.md` (verificação em MySQL 8.4.13) |
| 5.10 | Discussão sobre NoSQL: quando serviria e por que não foi escolhido | `nosql/comparativo.md`, `nosql/exemplo-aviso.json` |

## Figuras e tabelas

| Item | Origem |
|---|---|
| Figura 09: DER | `diagramas/der.mmd` |
| Tabela: entidades e finalidade (11 tabelas) | `modelo-logico.md` |
| Tabela: passos da normalização | `normalizacao.md` |
| Tabela ou trecho de código: 2 ou 3 consultas SQL com o resultado obtido | `sql/03-consultas.sql` |
| Tabela: SQL × NoSQL | `nosql/comparativo.md` |

## Fatos verificados que podem ser citados

- Os 4 scripts foram executados em MySQL 8.4.13 (Docker) sem erro; o modelo físico tem 11 tabelas e 44 restrições nomeadas.
- Os resultados das consultas de relatório conferem com os da central em C.

## O que depende do grupo

- [ ] Confirmar o SGBD da disciplina e se o professor exige o modelo conceitual no **brModelo** (`PLANO.md`, seção 13).
- [ ] Renderizar o DER e exportar o PNG.
- [ ] Rodar os scripts na máquina de apresentação (`sql/README.md` explica) e tirar o print de uma consulta.
- [ ] Citar teoria de normalização e de bancos só com fonte verificada.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro e dos arquivos de `04-banco-de-dados/` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Marcas `[ ... ]` indicam o que ainda precisa de fonte, print ou decisão.

# 5 BANCO DE DADOS

Este capítulo apresenta a modelagem do banco de dados, da análise do caderno da portaria ao modelo físico em MySQL, e discute o uso de bancos NoSQL. O banco pertence ao servidor central do sistema completo. O protótipo em C (capítulo 6) guarda seus dados em arquivos de texto e não se conecta a ele, que foi modelado e testado à parte.

## 5.1 Escolha do modelo relacional

O banco central guarda entidades estáveis e muito relacionadas (condomínio, bloco, unidade, morador, encomenda e retirada) e precisa garantir regras que o sistema não pode violar, como uma única retirada por encomenda e uma única aplicação de cada operação de sincronização. O modelo relacional faz isso com chaves primárias e estrangeiras e com restrições de unicidade e de valor (ELMASRI; NAVATHE, 2011), e por isso foi adotado o MySQL 8 (ADR-001). Os arquivos CSV do protótipo (ADR-002) são uma simplificação que vale só para a demonstração.

## 5.2 Modelo conceitual

O modelo tem onze entidades: condomínio, bloco, unidade, morador, funcionário, portaria, posição de estante, encomenda, retirada, aviso e operação de sincronização. Um condomínio tem blocos, que têm unidades, que abrigam moradores. Cada condomínio tem uma portaria, que recebe as encomendas, controla as posições de estante e origina as operações de sincronização. Uma encomenda tem destino em uma unidade, ocupa uma posição enquanto está pendente, tem no máximo uma retirada e pode gerar vários avisos (Figura 8).

**[Figura 8 – Diagrama entidade-relacionamento (DER). Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-08-der.png`]**

As regras do modelo são: o canal de aviso é aplicativo, SMS ou interfone, e os dois primeiros exigem contato; o status é pendente, retirada ou devolvida; uma encomenda tem no máximo uma retirada, e uma posição guarda no máximo uma encomenda pendente; o identificador da encomenda é único dentro da portaria; e cada operação de sincronização é aplicada uma única vez.

## 5.3 Normalização

A normalização partiu de uma página do caderno da portaria, com um volume por linha e dados misturados: "Bloco A apto 12" em um só campo, transportadora e tamanho juntos, telefone repetido a cada volume e retirada misturada ao registro de chegada. Foram seguidas as formas normais (HEUSER, 2009; ELMASRI; NAVATHE, 2011).

Na primeira forma normal, bloco e apartamento e também transportadora e tamanho foram separados, e cada linha passou a ser identificada pela portaria e pelo número local da encomenda. Na segunda, nome e cidade do condomínio, que dependiam só da portaria, foram para as tabelas de condomínio e de portaria. Na terceira, os dados do morador, repetidos a cada volume, ganharam uma tabela própria, assim como bloco, unidade, funcionário e posição na estante. A retirada ficou em tabela separada, com unicidade por encomenda, e surgiram as tabelas de aviso e de operação de sincronização (RF04 e RF10), somando onze tabelas.

## 5.4 Modelo lógico e modelo físico

Cada tabela tem uma chave primária e chaves estrangeiras para as tabelas de que depende. A chave é numérica na maioria dos casos. Na portaria é o código de P01 a P10 e, na operação, o próprio código, como "P01-000123". A encomenda guarda o código de retirada apenas como resumo criptográfico (SHA-256, 64 caracteres hexadecimais), e não o número, o que o protege se o banco for acessado indevidamente (NATIONAL INSTITUTE OF STANDARDS AND TECHNOLOGY, 2015).

O modelo físico, em MySQL 8, tem onze tabelas e 44 restrições nomeadas com os prefixos `pk_`, `fk_`, `uq_` e `ck_`. Três soluções merecem destaque. A chave primária da tabela de operações impede registrar a mesma operação duas vezes, o que sustenta a sincronização sem duplicidade (ADR-003). Uma coluna gerada, preenchida só enquanto a encomenda está pendente, recebe restrição de unicidade: duas pendentes não ocupam a mesma posição, mas posições liberadas voltam a ser usadas. E restrições de valor garantem o canal, o tamanho (P, M ou G), o status e o formato do código da portaria e do resumo.

## 5.5 Comandos SQL e resultados

Os scripts, executados em ordem, criam as tabelas, carregam dados de exemplo (dois condomínios e duas portarias), reúnem as consultas e criam visões e índices. Rodaram sem erro em um servidor MySQL 8.4.13, em contêiner Docker. As consultas tratam de pendências, tempo médio de retirada, dia de pico, ocupação da estante, histórico de uma unidade, auditoria, consistência dos dados e aplicação idempotente de uma operação de sincronização. Com a data de referência fixada em 29/10/2026, os resultados do Quadro 3 coincidem com os do relatório do programa em C.

**Quadro 3 – Resultados de consultas com dados de exemplo**

| Consulta | Resultado |
|---|---|
| Pendências por condomínio | Residencial Aurora: 6; Condomínio Bela Vista: 5 |
| Pendências com mais de 7 dias | Encomenda 4 (14 dias) e encomenda 1 (9 dias); a de 7 dias não entra |
| Dia de pico no Bela Vista | 27/10/2026, com 3 encomendas |
| Ocupação da estante | P01: 6 de 48 posições (12,5%); P02: 5 de 48 (10,4%) |

Fonte: elaborado pelos autores (2026), a partir de `03-consultas.sql`.

**[Figura 9 – Resultado da consulta de pendências por condomínio (consulta 1 de `03-consultas.sql`) no MySQL 8.4 em contêiner Docker, com dados de exemplo. Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-09-consulta-sql.png`]**

## 5.6 Discussão sobre bancos NoSQL

Foram comparados o modelo relacional (MySQL), o de documentos (por exemplo, MongoDB) e o de chave-valor (por exemplo, Redis) (SADALAGE; FOWLER, 2013). As entidades do sistema são muito relacionadas e as regras de integridade são essenciais, o que favorece o modelo relacional, com transações e restrições garantidas pelo próprio banco. As consultas de relatório, com agregações, junções e janelas de tempo, também são naturais em SQL.

Um banco de documentos poderia servir, numa evolução futura, ao histórico de avisos, porque os campos variam conforme o canal (o aplicativo guarda o identificador do dispositivo, e o SMS, o provedor e o identificador da mensagem). Um banco chave-valor apoiaria dados temporários, mas o escopo atual não o exige. Um segundo banco teria de ser operado e protegido, e só se justificaria com mais volume e variedade de avisos, sob as mesmas regras de privacidade e retenção (capítulo 8).
