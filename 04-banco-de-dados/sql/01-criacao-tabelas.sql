-- =====================================================================
-- 01-criacao-tabelas.sql
-- Modelo fisico do banco central da Administradora Morada Central.
-- SGBD: MySQL 8 (CHECK exige 8.0.16 ou superior).
-- Executar primeiro; depois 02, 03 e 04, nessa ordem.
-- Textos em ASCII, sem acento.
-- =====================================================================

CREATE DATABASE IF NOT EXISTS morada_central
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_0900_ai_ci;

USE morada_central;

-- Para recriar do zero (apaga TODOS os dados), execute manualmente:
-- DROP DATABASE morada_central;

-- ---------------------------------------------------------------------
-- condominio
-- ---------------------------------------------------------------------
CREATE TABLE condominio (
    id_condominio INT UNSIGNED NOT NULL AUTO_INCREMENT,
    nome          VARCHAR(80)  NOT NULL,
    cidade        VARCHAR(60)  NOT NULL,
    CONSTRAINT pk_condominio PRIMARY KEY (id_condominio)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- bloco
-- ---------------------------------------------------------------------
CREATE TABLE bloco (
    id_bloco      INT UNSIGNED NOT NULL AUTO_INCREMENT,
    id_condominio INT UNSIGNED NOT NULL,
    nome          VARCHAR(10)  NOT NULL,
    CONSTRAINT pk_bloco PRIMARY KEY (id_bloco),
    CONSTRAINT uq_bloco_condominio_nome UNIQUE (id_condominio, nome),
    CONSTRAINT fk_bloco_condominio FOREIGN KEY (id_condominio)
        REFERENCES condominio (id_condominio)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- unidade (apartamento)
-- ---------------------------------------------------------------------
CREATE TABLE unidade (
    id_unidade INT UNSIGNED      NOT NULL AUTO_INCREMENT,
    id_bloco   INT UNSIGNED      NOT NULL,
    numero     SMALLINT UNSIGNED NOT NULL,
    CONSTRAINT pk_unidade PRIMARY KEY (id_unidade),
    CONSTRAINT uq_unidade_bloco_numero UNIQUE (id_bloco, numero),
    CONSTRAINT ck_unidade_numero CHECK (numero BETWEEN 1 AND 9999),
    CONSTRAINT fk_unidade_bloco FOREIGN KEY (id_bloco)
        REFERENCES bloco (id_bloco)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- morador
-- ---------------------------------------------------------------------
CREATE TABLE morador (
    id_morador  INT UNSIGNED NOT NULL AUTO_INCREMENT,
    id_unidade  INT UNSIGNED NOT NULL,
    nome        VARCHAR(40)  NOT NULL,
    canal_aviso VARCHAR(9)   NOT NULL,
    contato     VARCHAR(40)  NULL,
    ativo       BOOLEAN      NOT NULL DEFAULT TRUE,
    CONSTRAINT pk_morador PRIMARY KEY (id_morador),
    CONSTRAINT ck_morador_canal CHECK (canal_aviso IN ('APP', 'SMS', 'INTERFONE')),
    -- APP e SMS exigem contato; INTERFONE pode ficar sem contato
    CONSTRAINT ck_morador_contato CHECK (canal_aviso = 'INTERFONE' OR contato IS NOT NULL),
    CONSTRAINT fk_morador_unidade FOREIGN KEY (id_unidade)
        REFERENCES unidade (id_unidade)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- funcionario
-- ---------------------------------------------------------------------
CREATE TABLE funcionario (
    id_funcionario INT UNSIGNED NOT NULL AUTO_INCREMENT,
    id_condominio  INT UNSIGNED NOT NULL,
    nome           VARCHAR(40)  NOT NULL,
    funcao         VARCHAR(30)  NOT NULL,
    CONSTRAINT pk_funcionario PRIMARY KEY (id_funcionario),
    CONSTRAINT fk_funcionario_condominio FOREIGN KEY (id_condominio)
        REFERENCES condominio (id_condominio)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- portaria (P01 a P10)
-- ---------------------------------------------------------------------
CREATE TABLE portaria (
    id_portaria   CHAR(3)      NOT NULL,
    id_condominio INT UNSIGNED NOT NULL,
    descricao     VARCHAR(80)  NOT NULL,
    CONSTRAINT pk_portaria PRIMARY KEY (id_portaria),
    CONSTRAINT ck_portaria_codigo CHECK (REGEXP_LIKE(id_portaria, '^P(0[1-9]|10)$', 'c')),
    CONSTRAINT fk_portaria_condominio FOREIGN KEY (id_condominio)
        REFERENCES condominio (id_condominio)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- posicao_estante
-- estante e prateleira usam os mesmos indices do arquivo do prototipo
-- (estante 0 = A, 1 = B...; prateleira de 0 a 11).
-- ---------------------------------------------------------------------
CREATE TABLE posicao_estante (
    id_posicao  INT UNSIGNED     NOT NULL AUTO_INCREMENT,
    id_portaria CHAR(3)          NOT NULL,
    estante     TINYINT UNSIGNED NOT NULL,
    prateleira  TINYINT UNSIGNED NOT NULL,
    tipo_volume VARCHAR(2)       NOT NULL,
    CONSTRAINT pk_posicao_estante PRIMARY KEY (id_posicao),
    CONSTRAINT uq_posicao_estante_local UNIQUE (id_portaria, estante, prateleira),
    CONSTRAINT ck_posicao_estante_tipo CHECK (tipo_volume IN ('PM', 'G')),
    CONSTRAINT fk_posicao_estante_portaria FOREIGN KEY (id_portaria)
        REFERENCES portaria (id_portaria)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- encomenda
-- id_local = id da encomenda no arquivo da portaria.
-- codigo_retirada_hash = SHA-256 (hexadecimal) do codigo de 6 digitos.
-- id_posicao_pendente = coluna gerada: vale id_posicao enquanto o status
--   e PENDENTE e fica NULL nos demais casos. O UNIQUE sobre ela impede
--   duas encomendas pendentes na mesma posicao, mas permite reaproveitar
--   a posicao depois da retirada (NULL nao conta como repetido).
-- ---------------------------------------------------------------------
CREATE TABLE encomenda (
    id_encomenda               INT UNSIGNED NOT NULL AUTO_INCREMENT,
    id_portaria                CHAR(3)      NOT NULL,
    id_local                   INT UNSIGNED NOT NULL,
    id_unidade                 INT UNSIGNED NOT NULL,
    id_posicao                 INT UNSIGNED NOT NULL,
    id_funcionario_recebimento INT UNSIGNED NOT NULL,
    destinatario               VARCHAR(40)  NOT NULL,
    transportadora             VARCHAR(30)  NOT NULL,
    tamanho                    CHAR(1)      NOT NULL,
    recebida_em                DATETIME     NOT NULL,
    codigo_retirada_hash       CHAR(64)     NOT NULL,
    status                     VARCHAR(9)   NOT NULL DEFAULT 'PENDENTE',
    id_posicao_pendente        INT UNSIGNED
        GENERATED ALWAYS AS (CASE WHEN status = 'PENDENTE' THEN id_posicao ELSE NULL END) STORED,
    CONSTRAINT pk_encomenda PRIMARY KEY (id_encomenda),
    CONSTRAINT uq_encomenda_portaria_local UNIQUE (id_portaria, id_local),
    CONSTRAINT uq_encomenda_posicao_pendente UNIQUE (id_posicao_pendente),
    CONSTRAINT ck_encomenda_tamanho CHECK (tamanho IN ('P', 'M', 'G')),
    CONSTRAINT ck_encomenda_status CHECK (status IN ('PENDENTE', 'RETIRADA', 'DEVOLVIDA')),
    CONSTRAINT ck_encomenda_hash CHECK (REGEXP_LIKE(codigo_retirada_hash, '^[0-9a-f]{64}$', 'c')),
    CONSTRAINT fk_encomenda_portaria FOREIGN KEY (id_portaria)
        REFERENCES portaria (id_portaria),
    CONSTRAINT fk_encomenda_unidade FOREIGN KEY (id_unidade)
        REFERENCES unidade (id_unidade),
    CONSTRAINT fk_encomenda_posicao FOREIGN KEY (id_posicao)
        REFERENCES posicao_estante (id_posicao),
    CONSTRAINT fk_encomenda_funcionario FOREIGN KEY (id_funcionario_recebimento)
        REFERENCES funcionario (id_funcionario)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- retirada (no maximo uma por encomenda)
-- ---------------------------------------------------------------------
CREATE TABLE retirada (
    id_retirada    INT UNSIGNED NOT NULL AUTO_INCREMENT,
    id_encomenda   INT UNSIGNED NOT NULL,
    id_funcionario INT UNSIGNED NOT NULL,
    retirado_por   VARCHAR(40)  NOT NULL,
    retirada_em    DATETIME     NOT NULL,
    CONSTRAINT pk_retirada PRIMARY KEY (id_retirada),
    CONSTRAINT uq_retirada_encomenda UNIQUE (id_encomenda),
    CONSTRAINT fk_retirada_encomenda FOREIGN KEY (id_encomenda)
        REFERENCES encomenda (id_encomenda),
    CONSTRAINT fk_retirada_funcionario FOREIGN KEY (id_funcionario)
        REFERENCES funcionario (id_funcionario)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- aviso
-- id_morador pode ser NULL (unidade sem morador cadastrado).
-- ---------------------------------------------------------------------
CREATE TABLE aviso (
    id_aviso     INT UNSIGNED NOT NULL AUTO_INCREMENT,
    id_encomenda INT UNSIGNED NOT NULL,
    id_morador   INT UNSIGNED NULL,
    canal        VARCHAR(9)   NOT NULL,
    enviado_em   DATETIME     NULL,
    situacao     VARCHAR(9)   NOT NULL DEFAULT 'PENDENTE',
    CONSTRAINT pk_aviso PRIMARY KEY (id_aviso),
    CONSTRAINT ck_aviso_canal CHECK (canal IN ('APP', 'SMS', 'INTERFONE')),
    CONSTRAINT ck_aviso_situacao CHECK (situacao IN ('PENDENTE', 'ENVIADO', 'FALHA')),
    CONSTRAINT fk_aviso_encomenda FOREIGN KEY (id_encomenda)
        REFERENCES encomenda (id_encomenda),
    CONSTRAINT fk_aviso_morador FOREIGN KEY (id_morador)
        REFERENCES morador (id_morador)
) ENGINE = InnoDB;

-- ---------------------------------------------------------------------
-- operacao_sincronizacao
-- A chave primaria no id da operacao (ex.: P01-000123) garante que cada
-- operacao seja aplicada uma unica vez (idempotencia, ADR-003).
-- ---------------------------------------------------------------------
CREATE TABLE operacao_sincronizacao (
    id_operacao      VARCHAR(12) NOT NULL,
    id_portaria      CHAR(3)     NOT NULL,
    tipo             VARCHAR(9)  NOT NULL,
    id_local         INT UNSIGNED NOT NULL,
    data_hora_origem DATETIME    NOT NULL,
    aplicada_em      DATETIME    NOT NULL DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_operacao_sincronizacao PRIMARY KEY (id_operacao),
    CONSTRAINT ck_operacao_tipo CHECK (tipo IN ('REGISTRO', 'RETIRADA', 'DEVOLUCAO')),
    -- formato Pnn-NNNNNN e prefixo igual ao codigo da portaria
    CONSTRAINT ck_operacao_id CHECK (
        REGEXP_LIKE(id_operacao, '^P(0[1-9]|10)-[0-9]{6}$', 'c')
        AND LEFT(id_operacao, 3) = id_portaria
    ),
    CONSTRAINT fk_operacao_sincronizacao_portaria FOREIGN KEY (id_portaria)
        REFERENCES portaria (id_portaria)
) ENGINE = InnoDB;
