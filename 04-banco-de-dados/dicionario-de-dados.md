# Dicionário de dados (Etapa 4)

> Base: `sql/01-criacao-tabelas.sql`. Convenção: tabelas no singular, PK `id_<tabela>`, restrições nomeadas (`pk_`, `fk_`, `uq_`, `ck_`). Tipos de MySQL 8.

Legenda de chave: **PK** primária, **FK** estrangeira, **UQ** única (sozinha ou em grupo).

## condominio

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_condominio | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_condominio`) | Identificador |
| nome | VARCHAR(80) | Não | | Nome do condomínio |
| cidade | VARCHAR(60) | Não | | Cidade |

## bloco

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_bloco | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_bloco`) | Identificador |
| id_condominio | INT UNSIGNED | Não | FK (`fk_bloco_condominio`) | Condomínio do bloco |
| nome | VARCHAR(10) | Não | UQ com id_condominio (`uq_bloco_condominio_nome`) | Nome do bloco (A, B...) |

## unidade

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_unidade | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_unidade`) | Identificador |
| id_bloco | INT UNSIGNED | Não | FK (`fk_unidade_bloco`) | Bloco da unidade |
| numero | SMALLINT UNSIGNED | Não | UQ com id_bloco (`uq_unidade_bloco_numero`) | Número do apartamento (1 a 9999) |

Restrição: `ck_unidade_numero` (numero entre 1 e 9999, igual ao limite do protótipo).

## morador

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_morador | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_morador`) | Identificador |
| id_unidade | INT UNSIGNED | Não | FK (`fk_morador_unidade`) | Unidade onde mora |
| nome | VARCHAR(40) | Não | | Nome do morador |
| canal_aviso | VARCHAR(9) | Não | | APP, SMS ou INTERFONE (`ck_morador_canal`) |
| contato | VARCHAR(40) | Sim | | Telefone ou identificador do app. Obrigatório para APP e SMS (`ck_morador_contato`); vazio para INTERFONE |
| ativo | BOOLEAN | Não | | 1 = ativo, 0 = inativo. Padrão 1 |

## funcionario

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_funcionario | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_funcionario`) | Identificador |
| id_condominio | INT UNSIGNED | Não | FK (`fk_funcionario_condominio`) | Condomínio onde trabalha |
| nome | VARCHAR(40) | Não | | Nome |
| funcao | VARCHAR(30) | Não | | Função (por exemplo, PORTEIRO) |

## portaria

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_portaria | CHAR(3) | Não | PK (`pk_portaria`) | Código P01 a P10 (`ck_portaria_codigo`) |
| id_condominio | INT UNSIGNED | Não | FK (`fk_portaria_condominio`) | Condomínio da portaria |
| descricao | VARCHAR(80) | Não | | Descrição |

## posicao_estante

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_posicao | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_posicao_estante`) | Identificador |
| id_portaria | CHAR(3) | Não | FK (`fk_posicao_estante_portaria`); UQ (`uq_posicao_estante_local`) com estante e prateleira | Portaria dona da estante |
| estante | TINYINT UNSIGNED | Não | | Índice da estante (0 = A, 1 = B...) |
| prateleira | TINYINT UNSIGNED | Não | | Índice da prateleira (0 a 11 no protótipo) |
| tipo_volume | VARCHAR(2) | Não | | PM (volumes pequenos e médios) ou G (grandes) (`ck_posicao_estante_tipo`) |

## encomenda

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_encomenda | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_encomenda`) | Identificador interno do banco |
| id_portaria | CHAR(3) | Não | FK (`fk_encomenda_portaria`); UQ (`uq_encomenda_portaria_local`) com id_local | Portaria que recebeu |
| id_local | INT UNSIGNED | Não | | Id da encomenda no arquivo da portaria |
| id_unidade | INT UNSIGNED | Não | FK (`fk_encomenda_unidade`) | Unidade de destino |
| id_posicao | INT UNSIGNED | Não | FK (`fk_encomenda_posicao`) | Posição na estante (mantida após a retirada, como histórico) |
| id_funcionario_recebimento | INT UNSIGNED | Não | FK (`fk_encomenda_funcionario`) | Funcionário que registrou a chegada |
| destinatario | VARCHAR(40) | Não | | Nome na etiqueta |
| transportadora | VARCHAR(30) | Não | | Transportadora |
| tamanho | CHAR(1) | Não | | P, M ou G (`ck_encomenda_tamanho`) |
| recebida_em | DATETIME | Não | | Data e hora da chegada |
| codigo_retirada_hash | CHAR(64) | Não | | SHA-256 do código de 6 dígitos, em hexadecimal (`ck_encomenda_hash`) |
| status | VARCHAR(9) | Não | | PENDENTE, RETIRADA ou DEVOLVIDA (`ck_encomenda_status`). Padrão PENDENTE |
| id_posicao_pendente | INT UNSIGNED | Sim | UQ (`uq_encomenda_posicao_pendente`) | **Coluna derivada** (gerada): igual a `id_posicao` quando o status é PENDENTE, nula nos outros casos. Não se grava diretamente |

## retirada

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_retirada | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_retirada`) | Identificador |
| id_encomenda | INT UNSIGNED | Não | FK (`fk_retirada_encomenda`); UQ (`uq_retirada_encomenda`) | Encomenda retirada (no máximo uma retirada por encomenda) |
| id_funcionario | INT UNSIGNED | Não | FK (`fk_retirada_funcionario`) | Funcionário que entregou |
| retirado_por | VARCHAR(40) | Não | | Nome de quem retirou |
| retirada_em | DATETIME | Não | | Data e hora da retirada |

## aviso

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_aviso | INT UNSIGNED AUTO_INCREMENT | Não | PK (`pk_aviso`) | Identificador |
| id_encomenda | INT UNSIGNED | Não | FK (`fk_aviso_encomenda`) | Encomenda avisada |
| id_morador | INT UNSIGNED | Sim | FK (`fk_aviso_morador`) | Morador avisado (nulo se a unidade não tem morador cadastrado) |
| canal | VARCHAR(9) | Não | | APP, SMS ou INTERFONE (`ck_aviso_canal`) |
| enviado_em | DATETIME | Sim | | Quando foi enviado (nulo se ainda pendente ou se falhou) |
| situacao | VARCHAR(9) | Não | | PENDENTE, ENVIADO ou FALHA (`ck_aviso_situacao`). Padrão PENDENTE |

Os valores de `situacao` são uma proposta deste modelo; o `PLANO.md` não os define.

## operacao_sincronizacao

| Coluna | Tipo | Nulo | Chave | Descrição |
|---|---|---|---|---|
| id_operacao | VARCHAR(12) | Não | PK (`pk_operacao_sincronizacao`) | Id da operação, no formato `P01-000123`; começa pelo código da portaria (`ck_operacao_id`). A chave primária garante a idempotência |
| id_portaria | CHAR(3) | Não | FK (`fk_operacao_sincronizacao_portaria`) | Portaria de origem |
| tipo | VARCHAR(9) | Não | | REGISTRO, RETIRADA ou DEVOLUCAO (`ck_operacao_tipo`) |
| id_local | INT UNSIGNED | Não | | Id da encomenda na portaria |
| data_hora_origem | DATETIME | Não | | Quando a portaria gerou a operação |
| aplicada_em | DATETIME | Não | | Quando a central aplicou a operação. Padrão: instante da inserção |

## Observações

- Datas: `DATETIME` sem fuso, no horário local da portaria (formato do protótipo `AAAA-MM-DD HH:MM`).
- Textos em ASCII, sem acento, para combinar com os arquivos do protótipo.
- Tamanhos de texto acompanham o protótipo (nome 40 caracteres, transportadora 30).
