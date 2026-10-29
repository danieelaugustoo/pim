-- =====================================================================
-- 02-carga-exemplo.sql
-- Carga de dados FICTICIOS para demonstracao e para as consultas de 03.
-- Pre-requisito: 01-criacao-tabelas.sql executado em banco vazio.
-- Dois condominios, duas portarias (P01 e P02). As encomendas de P01
-- seguem o arquivo 05-programa-c/dados/exemplo/P01-encomendas.csv.
-- Textos em ASCII, sem acento.
-- =====================================================================

USE morada_central;

START TRANSACTION;

-- ---------------------------------------------------------------------
-- Condominios, blocos e unidades
-- ---------------------------------------------------------------------
INSERT INTO condominio (id_condominio, nome, cidade) VALUES
    (1, 'Residencial Aurora',    'Sao Paulo'),
    (2, 'Condominio Bela Vista', 'Sao Paulo');

INSERT INTO bloco (id_bloco, id_condominio, nome) VALUES
    (1, 1, 'A'), (2, 1, 'B'), (3, 1, 'C'), (4, 1, 'D'),
    (5, 2, 'A'), (6, 2, 'B');

INSERT INTO unidade (id_unidade, id_bloco, numero) VALUES
    (1, 1, 12),   -- A-12  (Aurora)
    (2, 1, 45),   -- A-45
    (3, 2, 101),  -- B-101
    (4, 2, 203),  -- B-203
    (5, 3, 34),   -- C-34
    (6, 4, 7),    -- D-7
    (7, 4, 15),   -- D-15
    (8, 5, 21),   -- A-21  (Bela Vista)
    (9, 6, 305);  -- B-305

-- ---------------------------------------------------------------------
-- Moradores (contatos ficticios; INTERFONE nao tem contato)
-- ---------------------------------------------------------------------
INSERT INTO morador (id_morador, id_unidade, nome, canal_aviso, contato, ativo) VALUES
    (1,  1, 'Maria Souza',    'APP',       'app-0001',    TRUE),
    (2,  1, 'Joao Souza',     'SMS',       '11900000002', TRUE),
    (3,  3, 'Carla Mendes',   'INTERFONE', NULL,          TRUE),
    (4,  4, 'Paulo Lima',     'SMS',       '11900000004', TRUE),
    (5,  5, 'Ana Ribeiro',    'APP',       'app-0005',    TRUE),
    (6,  6, 'Rafael Costa',   'INTERFONE', NULL,          TRUE),
    (7,  7, 'Beatriz Alves',  'SMS',       '11900000007', TRUE),
    (8,  2, 'Lucas Pereira',  'APP',       'app-0008',    TRUE),
    (9,  8, 'Fernanda Dias',  'SMS',       '11900000009', TRUE),
    (10, 9, 'Marcos Rocha',   'INTERFONE', NULL,          TRUE);

-- ---------------------------------------------------------------------
-- Funcionarios e portarias
-- ---------------------------------------------------------------------
INSERT INTO funcionario (id_funcionario, id_condominio, nome, funcao) VALUES
    (1, 1, 'Antonio Silva', 'PORTEIRO'),
    (2, 1, 'Bruna Santos',  'PORTEIRO'),
    (3, 2, 'Carlos Nunes',  'PORTEIRO'),
    (4, 2, 'Debora Lima',   'PORTEIRO');

INSERT INTO portaria (id_portaria, id_condominio, descricao) VALUES
    ('P01', 1, 'Portaria principal - Residencial Aurora'),
    ('P02', 2, 'Portaria principal - Condominio Bela Vista');

-- ---------------------------------------------------------------------
-- Posicoes da estante: 4 estantes x 12 prateleiras por portaria.
-- id_posicao = base + estante * 12 + prateleira + 1   (P01: base 0; P02: base 48)
-- Prateleiras 10 e 11 sao reservadas a volumes grandes (tipo G).
-- ---------------------------------------------------------------------
INSERT INTO posicao_estante (id_posicao, id_portaria, estante, prateleira, tipo_volume)
SELECT p.base + e.n * 12 + s.n + 1,
       p.id_portaria,
       e.n,
       s.n,
       CASE WHEN s.n >= 10 THEN 'G' ELSE 'PM' END
FROM (SELECT 'P01' AS id_portaria, 0 AS base
      UNION ALL SELECT 'P02', 48) AS p
CROSS JOIN (SELECT 0 AS n UNION ALL SELECT 1 UNION ALL SELECT 2 UNION ALL SELECT 3) AS e
CROSS JOIN (SELECT 0 AS n UNION ALL SELECT 1 UNION ALL SELECT 2 UNION ALL SELECT 3
            UNION ALL SELECT 4 UNION ALL SELECT 5 UNION ALL SELECT 6 UNION ALL SELECT 7
            UNION ALL SELECT 8 UNION ALL SELECT 9 UNION ALL SELECT 10 UNION ALL SELECT 11) AS s;

-- ---------------------------------------------------------------------
-- Encomendas (o codigo de retirada e guardado como hash SHA-256)
-- id_encomenda 1 a 8: portaria P01 (iguais ao CSV de exemplo)
-- id_encomenda 9 a 14: portaria P02
-- ---------------------------------------------------------------------
INSERT INTO encomenda
    (id_encomenda, id_portaria, id_local, id_unidade, id_posicao, id_funcionario_recebimento,
     destinatario, transportadora, tamanho, recebida_em, codigo_retirada_hash, status)
VALUES
    (1,  'P01', 1, 1, 1,  1, 'Maria Souza',   'Transp Alfa', 'P', '2026-10-20 09:15:00', SHA2('482913', 256), 'PENDENTE'),
    (2,  'P01', 2, 1, 2,  1, 'Joao Souza',    'Transp Beta', 'M', '2026-10-27 14:40:00', SHA2('731256', 256), 'PENDENTE'),
    (3,  'P01', 3, 3, 23, 2, 'Carla Mendes',  'Transp Gama', 'G', '2026-10-28 10:05:00', SHA2('150847', 256), 'PENDENTE'),
    (4,  'P01', 4, 4, 13, 1, 'Paulo Lima',    'Transp Alfa', 'M', '2026-10-15 16:30:00', SHA2('906124', 256), 'PENDENTE'),
    (5,  'P01', 5, 5, 25, 2, 'Ana Ribeiro',   'Transp Beta', 'P', '2026-10-26 11:20:00', SHA2('264781', 256), 'PENDENTE'),
    (6,  'P01', 6, 6, 37, 2, 'Rafael Costa',  'Transp Gama', 'P', '2026-10-10 08:45:00', SHA2('377415', 256), 'RETIRADA'),
    (7,  'P01', 7, 7, 47, 1, 'Beatriz Alves', 'Transp Alfa', 'G', '2026-10-05 13:10:00', SHA2('845209', 256), 'DEVOLVIDA'),
    (8,  'P01', 8, 2, 3,  2, 'Lucas Pereira', 'Transp Beta', 'M', '2026-10-29 08:50:00', SHA2('619734', 256), 'PENDENTE'),
    (9,  'P02', 2, 8, 49, 3, 'Fernanda Dias', 'Transp Alfa', 'M', '2026-10-22 10:00:00', SHA2('111222', 256), 'PENDENTE'),
    (10, 'P02', 6, 9, 61, 4, 'Marcos Rocha',  'Transp Beta', 'P', '2026-10-28 15:30:00', SHA2('333444', 256), 'PENDENTE'),
    (11, 'P02', 1, 8, 59, 3, 'Fernanda Dias', 'Transp Gama', 'G', '2026-10-09 09:00:00', SHA2('555666', 256), 'RETIRADA'),
    (12, 'P02', 3, 9, 62, 4, 'Marcos Rocha',  'Transp Alfa', 'M', '2026-10-27 11:00:00', SHA2('777888', 256), 'PENDENTE'),
    (13, 'P02', 4, 8, 50, 3, 'Fernanda Dias', 'Transp Gama', 'M', '2026-10-27 11:40:00', SHA2('246810', 256), 'PENDENTE'),
    (14, 'P02', 5, 9, 51, 4, 'Marcos Rocha',  'Transp Beta', 'P', '2026-10-27 16:20:00', SHA2('135790', 256), 'PENDENTE');

-- ---------------------------------------------------------------------
-- Retiradas (encomendas 6 e 11)
-- ---------------------------------------------------------------------
INSERT INTO retirada (id_retirada, id_encomenda, id_funcionario, retirado_por, retirada_em) VALUES
    (1, 6,  2, 'Rafael Costa',  '2026-10-11 18:20:00'),
    (2, 11, 3, 'Fernanda Dias', '2026-10-12 17:45:00');

-- ---------------------------------------------------------------------
-- Avisos (um falhou e dois ainda estao pendentes de envio)
-- ---------------------------------------------------------------------
INSERT INTO aviso (id_aviso, id_encomenda, id_morador, canal, enviado_em, situacao) VALUES
    (1,  1,  1,  'APP',       '2026-10-20 09:16:00', 'ENVIADO'),
    (2,  2,  2,  'SMS',       '2026-10-27 14:41:00', 'ENVIADO'),
    (3,  3,  3,  'INTERFONE', '2026-10-28 10:06:00', 'ENVIADO'),
    (4,  4,  4,  'SMS',       NULL,                  'FALHA'),
    (5,  5,  5,  'APP',       '2026-10-26 11:21:00', 'ENVIADO'),
    (6,  6,  6,  'INTERFONE', '2026-10-10 08:46:00', 'ENVIADO'),
    (7,  7,  7,  'SMS',       '2026-10-05 13:11:00', 'ENVIADO'),
    (8,  8,  8,  'APP',       '2026-10-29 08:51:00', 'ENVIADO'),
    (9,  9,  9,  'SMS',       '2026-10-22 10:01:00', 'ENVIADO'),
    (10, 10, 10, 'INTERFONE', '2026-10-28 15:31:00', 'ENVIADO'),
    (11, 11, 9,  'SMS',       '2026-10-09 09:01:00', 'ENVIADO'),
    (12, 12, 10, 'INTERFONE', NULL,                  'PENDENTE'),
    (13, 13, 9,  'SMS',       '2026-10-27 11:41:00', 'ENVIADO'),
    (14, 14, 10, 'INTERFONE', NULL,                  'PENDENTE');

-- ---------------------------------------------------------------------
-- Operacoes de sincronizacao ja aplicadas pela central
-- (numeradas na ordem em que cada portaria gerou as operacoes)
-- ---------------------------------------------------------------------
INSERT INTO operacao_sincronizacao
    (id_operacao, id_portaria, tipo, id_local, data_hora_origem, aplicada_em) VALUES
    ('P01-000001', 'P01', 'REGISTRO',  7, '2026-10-05 13:10:00', '2026-10-05 13:30:00'),
    ('P01-000002', 'P01', 'REGISTRO',  6, '2026-10-10 08:45:00', '2026-10-10 09:00:00'),
    ('P01-000003', 'P01', 'RETIRADA',  6, '2026-10-11 18:20:00', '2026-10-11 18:40:00'),
    ('P01-000004', 'P01', 'REGISTRO',  4, '2026-10-15 16:30:00', '2026-10-15 17:00:00'),
    ('P01-000005', 'P01', 'DEVOLUCAO', 7, '2026-10-19 10:00:00', '2026-10-19 10:20:00'),
    ('P01-000006', 'P01', 'REGISTRO',  1, '2026-10-20 09:15:00', '2026-10-20 09:40:00'),
    ('P01-000007', 'P01', 'REGISTRO',  5, '2026-10-26 11:20:00', '2026-10-26 12:00:00'),
    ('P01-000008', 'P01', 'REGISTRO',  2, '2026-10-27 14:40:00', '2026-10-27 15:00:00'),
    ('P01-000009', 'P01', 'REGISTRO',  3, '2026-10-28 10:05:00', '2026-10-28 10:30:00'),
    ('P01-000010', 'P01', 'REGISTRO',  8, '2026-10-29 08:50:00', '2026-10-29 09:10:00'),
    ('P02-000001', 'P02', 'REGISTRO',  1, '2026-10-09 09:00:00', '2026-10-09 09:20:00'),
    ('P02-000002', 'P02', 'RETIRADA',  1, '2026-10-12 17:45:00', '2026-10-12 18:00:00'),
    ('P02-000003', 'P02', 'REGISTRO',  2, '2026-10-22 10:00:00', '2026-10-22 10:30:00'),
    ('P02-000004', 'P02', 'REGISTRO',  3, '2026-10-27 11:00:00', '2026-10-27 11:30:00'),
    ('P02-000005', 'P02', 'REGISTRO',  4, '2026-10-27 11:40:00', '2026-10-27 12:00:00'),
    ('P02-000006', 'P02', 'REGISTRO',  5, '2026-10-27 16:20:00', '2026-10-27 16:40:00'),
    ('P02-000007', 'P02', 'REGISTRO',  6, '2026-10-28 15:30:00', '2026-10-28 16:00:00');

COMMIT;
