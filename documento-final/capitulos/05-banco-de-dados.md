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

Este capítulo apresenta a modelagem do banco de dados da solução, da análise do caderno da portaria ao modelo físico em MySQL, e discute o uso de bancos NoSQL. O banco pertence ao servidor central do sistema completo. O protótipo em C, descrito no capítulo 6, guarda seus dados em arquivos de texto e não se conecta ao banco, que foi modelado e testado de forma independente.

## 5.1 Escolha do modelo relacional

O banco central precisa guardar entidades estáveis e muito relacionadas (condomínio, bloco, unidade, morador, encomenda, retirada) e garantir regras que o sistema não pode violar, como uma única retirada por encomenda e uma única aplicação de cada operação de sincronização. O modelo relacional atende a esses requisitos por meio de chaves primárias, chaves estrangeiras, restrições de unicidade e de valor `[FONTE A VERIFICAR: referência sobre bancos de dados relacionais]`. Por isso foi adotado o MySQL 8 (decisão ADR-001). O armazenamento em arquivos CSV do protótipo (ADR-002) é uma simplificação deliberada, restrita à demonstração.

## 5.2 Modelo conceitual

O modelo conceitual identifica onze entidades: condomínio, bloco, unidade, morador, funcionário, portaria, posição de estante, encomenda, retirada, aviso e operação de sincronização. Um condomínio possui blocos, que possuem unidades, que abrigam moradores. Cada condomínio tem uma portaria, que recebe as encomendas, possui posições de estante e origina as operações de sincronização. Uma encomenda tem destino em uma unidade, ocupa uma posição enquanto está pendente, pode ter no máximo uma retirada e pode gerar vários avisos. A Figura 9 apresenta o diagrama entidade-relacionamento.

**[Figura 9 – Diagrama entidade-relacionamento (DER). Fonte: elaborado pelos autores (2026). Arquivo: `figuras/figura-09-der.png`]**

Seis regras de negócio orientam o modelo: o canal de aviso é aplicativo, SMS ou interfone, e os dois primeiros exigem contato; o status da encomenda é pendente, retirada ou devolvida; uma encomenda tem no máximo uma retirada; uma posição guarda no máximo uma encomenda pendente; o identificador da encomenda é único dentro da portaria; e cada operação de sincronização é aplicada uma única vez.

## 5.3 Normalização

A normalização partiu de uma página do caderno da portaria, que registra em texto livre um volume por linha, com dados misturados: "Bloco A apto 12" em um só campo, transportadora e tamanho juntos, telefone repetido a cada volume da mesma unidade e retirada misturada ao registro de chegada. Os dados usados são fictícios. O processo seguiu as formas normais `[FONTE A VERIFICAR: referência sobre normalização]`:

- **Primeira forma normal (1FN):** separação de bloco e apartamento, de transportadora e tamanho, e criação de campos próprios para canal de aviso e contato. Cada linha passou a ser identificada pela chave composta formada pela portaria e pelo número local da encomenda.
- **Segunda forma normal (2FN):** o nome e a cidade do condomínio dependiam apenas da portaria, e foram movidos para as tabelas de condomínio e portaria.
- **Terceira forma normal (3FN):** os dados do morador, que se repetiam a cada volume, foram para a tabela de moradores; bloco e unidade passaram a ter tabelas próprias; o funcionário que recebeu o volume foi separado; e a posição na estante virou uma tabela própria.

Por decisão semântica, os dados da retirada ficaram em uma tabela separada, com restrição de unicidade por encomenda, e foram criadas as tabelas de aviso e de operação de sincronização, que respondem aos requisitos RF04 e RF10. O resultado são onze tabelas.

## 5.4 Modelo lógico e modelo físico

No modelo lógico, cada tabela tem uma chave primária (numérica na maioria; na portaria, o código de P01 a P10; e, na tabela de operações, o próprio código da operação, como "P01-000123") e chaves estrangeiras para as tabelas de que depende. A tabela de encomenda guarda o código de retirada apenas como resumo criptográfico (hash SHA-256 em hexadecimal, 64 caracteres), e não o número em si, o que protege o código caso o banco seja acessado indevidamente `[FONTE A VERIFICAR: referência sobre SHA-256]`. O dicionário de dados descreve cada coluna, seu tipo e suas restrições.

O modelo físico foi escrito em MySQL 8 e contém, no total, onze tabelas e 44 restrições nomeadas, com prefixos que indicam o tipo (`pk_`, `fk_`, `uq_` e `ck_`). Três soluções merecem destaque:

- **Operações idempotentes:** a chave primária da tabela de operações impede que a mesma operação seja registrada duas vezes, o que sustenta a sincronização sem duplicidade (capítulo 4, decisão ADR-003).
- **Uma encomenda pendente por posição:** uma coluna gerada, preenchida apenas quando a encomenda está pendente, recebe uma restrição de unicidade. Assim, duas encomendas pendentes não ocupam a mesma posição, mas posições de encomendas já retiradas podem ser reutilizadas.
- **Validação de valores:** restrições de valor garantem o canal de aviso, o tamanho do volume (P, M ou G), o status, o formato do código da portaria (P01 a P10) e o formato do resumo do código.

## 5.5 Comandos SQL e resultados

Os scripts estão organizados em quatro arquivos, executados em ordem: criação das tabelas, carga de dados fictícios (dois condomínios e duas portarias), consultas, e visões com índices. Foram executados em um servidor MySQL 8.4.13, em contêiner Docker, sem erros. As consultas cobrem as necessidades de relatório do sistema: pendências por condomínio, pendências com mais de 7 dias, tempo médio entre chegada e retirada, dia de pico, ocupação da estante, histórico de uma unidade, auditoria de quem registrou e de quem entregou, verificação de consistência dos dados, e a aplicação idempotente de uma operação de sincronização.

Com os dados de exemplo e a data de referência fixada em 29/10/2026, as consultas devolveram os resultados do Quadro 5, que coincidem com os do relatório gerado pelo programa em C a partir dos mesmos dados.

**Quadro 5 – Resultados de consultas com dados de exemplo (fictícios)**

| Consulta | Resultado |
|---|---|
| Pendências por condomínio | Residencial Aurora: 6; Condomínio Bela Vista: 5 |
| Pendências com mais de 7 dias | Encomenda 4 (14 dias) e encomenda 1 (9 dias); a de 7 dias não entra, pois a regra é "mais de 7" |
| Dia de pico no Bela Vista | 27/10/2026, com 3 encomendas |
| Ocupação da estante | P01: 6 de 48 posições (12,5%); P02: 5 de 48 (10,4%) |

Fonte: elaborado pelos autores (2026), a partir de `03-consultas.sql`.

Também foram criadas duas visões, uma de pendências e outra de indicadores por condomínio, e dois índices para acelerar as consultas por status e data e por unidade. **[Inserir um print de uma consulta no MySQL Workbench, como Figura/Quadro, quando o grupo executar os scripts. Não está feito.]**

## 5.6 Discussão sobre bancos NoSQL

Para comparar, foram considerados o modelo relacional (MySQL), o de documentos (por exemplo, MongoDB) e o de chave-valor (por exemplo, Redis) `[FONTE A VERIFICAR: referências sobre NoSQL]`. As entidades do sistema são muito relacionadas e as regras de integridade são essenciais, o que favorece o modelo relacional, com transações e restrições garantidas pelo próprio banco. As consultas de relatório (agregações, junções e janelas de tempo) também são naturais em SQL.

Um banco de documentos poderia ser útil, em uma evolução futura, para o histórico de avisos, porque os campos variam conforme o canal (um aviso de aplicativo guarda um identificador do dispositivo, enquanto um SMS guarda o provedor e o identificador da mensagem). Para esse caso foi elaborado um exemplo de documento JSON. Um banco chave-valor serviria como apoio a dados temporários, como o controle de tentativas de código, mas não é necessário no escopo atual. A adoção de um segundo banco exigiria operá-lo e protegê-lo, e só se justificaria se o volume e a variedade dos avisos aumentassem. Os dados pessoais nos avisos seguiriam as mesmas regras de privacidade e retenção do banco relacional (capítulo 8).

## 5.7 Considerações do capítulo

O banco foi modelado a partir de um problema real do caderno, normalizado até a terceira forma normal e implementado em MySQL com restrições que traduzem as regras de negócio. Os scripts foram executados em MySQL 8.4.13 e os resultados conferem com os do programa em C. Ficam como pendências a execução dos scripts nas máquinas do grupo, o print de uma consulta e a verificação das referências teóricas.
