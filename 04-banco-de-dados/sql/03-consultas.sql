-- =====================================================================
-- 03-consultas.sql
-- Principais consultas do sistema. Executar depois de 01 e 02.
-- Para que o resultado seja reproduzivel com os dados de exemplo, a data
-- de referencia e fixa (@agora). Em uso real, trocar por NOW().
-- Textos em ASCII, sem acento.
-- =====================================================================

USE morada_central;

SET @agora = '2026-10-29 12:00:00';

-- ---------------------------------------------------------------------
-- 1. Pendencias por condominio
-- Esperado com a carga de exemplo: Aurora = 6, Bela Vista = 5
-- ---------------------------------------------------------------------
SELECT c.nome AS condominio,
       COUNT(*) AS pendentes
FROM encomenda e
JOIN portaria p   ON p.id_portaria = e.id_portaria
JOIN condominio c ON c.id_condominio = p.id_condominio
WHERE e.status = 'PENDENTE'
GROUP BY c.id_condominio, c.nome
ORDER BY pendentes DESC, c.nome;

-- ---------------------------------------------------------------------
-- 2. Pendencias ha mais de 7 dias (RF11)
-- DATEDIFF conta dias do calendario, como o prototipo em C.
-- Esperado: encomenda 4 (14 dias) e encomenda 1 (9 dias).
-- A encomenda 9 (7 dias) nao entra, pois a regra e "mais de 7".
-- ---------------------------------------------------------------------
SELECT c.nome AS condominio,
       e.id_portaria,
       e.id_local,
       b.nome AS bloco,
       u.numero AS apartamento,
       e.destinatario,
       e.recebida_em,
       DATEDIFF(@agora, e.recebida_em) AS dias_parada
FROM encomenda e
JOIN portaria p   ON p.id_portaria = e.id_portaria
JOIN condominio c ON c.id_condominio = p.id_condominio
JOIN unidade u    ON u.id_unidade = e.id_unidade
JOIN bloco b      ON b.id_bloco = u.id_bloco
WHERE e.status = 'PENDENTE'
  AND DATEDIFF(@agora, e.recebida_em) > 7
ORDER BY dias_parada DESC;

-- ---------------------------------------------------------------------
-- 3. Tempo medio entre a chegada e a retirada, por condominio (em horas)
-- ---------------------------------------------------------------------
SELECT c.nome AS condominio,
       COUNT(*) AS retiradas,
       ROUND(AVG(TIMESTAMPDIFF(MINUTE, e.recebida_em, r.retirada_em)) / 60, 1) AS horas_medias
FROM retirada r
JOIN encomenda e  ON e.id_encomenda = r.id_encomenda
JOIN portaria p   ON p.id_portaria = e.id_portaria
JOIN condominio c ON c.id_condominio = p.id_condominio
GROUP BY c.id_condominio, c.nome
ORDER BY c.nome;

-- ---------------------------------------------------------------------
-- 4a. Encomendas recebidas por dia, por condominio
-- ---------------------------------------------------------------------
SELECT c.nome AS condominio,
       DATE(e.recebida_em) AS dia,
       COUNT(*) AS recebidas
FROM encomenda e
JOIN portaria p   ON p.id_portaria = e.id_portaria
JOIN condominio c ON c.id_condominio = p.id_condominio
GROUP BY c.id_condominio, c.nome, DATE(e.recebida_em)
ORDER BY c.nome, dia;

-- ---------------------------------------------------------------------
-- 4b. Dia de pico por condominio (RANK mantem empates)
-- Esperado: Bela Vista = 2026-10-27, com 3 encomendas.
-- Aurora tem um volume por dia, entao todos os dias empatam.
-- ---------------------------------------------------------------------
WITH por_dia AS (
    SELECT c.id_condominio,
           c.nome AS condominio,
           DATE(e.recebida_em) AS dia,
           COUNT(*) AS recebidas
    FROM encomenda e
    JOIN portaria p   ON p.id_portaria = e.id_portaria
    JOIN condominio c ON c.id_condominio = p.id_condominio
    GROUP BY c.id_condominio, c.nome, DATE(e.recebida_em)
)
SELECT condominio, dia AS dia_de_pico, recebidas
FROM (
    SELECT condominio, dia, recebidas,
           RANK() OVER (PARTITION BY id_condominio ORDER BY recebidas DESC) AS classificacao
    FROM por_dia
) AS ranqueado
WHERE classificacao = 1
ORDER BY condominio, dia_de_pico;

-- ---------------------------------------------------------------------
-- 5. Ocupacao da estante por portaria
-- Esperado: P01 = 6 de 48 (12.5%), P02 = 5 de 48 (10.4%).
-- Uma posicao esta ocupada quando alguma encomenda PENDENTE a usa
-- (coluna gerada id_posicao_pendente).
-- ---------------------------------------------------------------------
SELECT p.id_portaria,
       COUNT(*) AS total_posicoes,
       SUM(CASE WHEN o.id_encomenda IS NOT NULL THEN 1 ELSE 0 END) AS ocupadas,
       ROUND(100 * SUM(CASE WHEN o.id_encomenda IS NOT NULL THEN 1 ELSE 0 END) / COUNT(*), 1)
           AS ocupacao_percentual
FROM portaria p
JOIN posicao_estante pe ON pe.id_portaria = p.id_portaria
LEFT JOIN encomenda o   ON o.id_posicao_pendente = pe.id_posicao
GROUP BY p.id_portaria
ORDER BY p.id_portaria;

-- ---------------------------------------------------------------------
-- 6. Historico de uma unidade (troque as variaveis para consultar outra)
-- ---------------------------------------------------------------------
SET @id_condominio = 1;
SET @bloco = 'A';
SET @apartamento = 12;

SELECT e.recebida_em,
       e.id_portaria,
       e.id_local,
       e.destinatario,
       e.transportadora,
       e.tamanho,
       e.status,
       r.retirada_em,
       r.retirado_por
FROM encomenda e
JOIN unidade u        ON u.id_unidade = e.id_unidade
JOIN bloco b          ON b.id_bloco = u.id_bloco
LEFT JOIN retirada r  ON r.id_encomenda = e.id_encomenda
WHERE b.id_condominio = @id_condominio
  AND b.nome = @bloco
  AND u.numero = @apartamento
ORDER BY e.recebida_em;

-- ---------------------------------------------------------------------
-- 7. Auditoria: quem registrou a chegada e quem entregou (RNF07)
-- ---------------------------------------------------------------------
SELECT e.id_portaria,
       e.id_local,
       e.recebida_em,
       fr.nome AS registrado_por,
       e.status,
       r.retirada_em,
       fe.nome AS entregue_por,
       r.retirado_por
FROM encomenda e
JOIN funcionario fr      ON fr.id_funcionario = e.id_funcionario_recebimento
LEFT JOIN retirada r     ON r.id_encomenda = e.id_encomenda
LEFT JOIN funcionario fe ON fe.id_funcionario = r.id_funcionario
ORDER BY e.id_portaria, e.recebida_em;

-- ---------------------------------------------------------------------
-- 8. Auditoria de consistencia (regras C1 a C4 de modelo-logico.md)
-- Cada linha devolvida e uma violacao. Esperado com a carga de exemplo:
-- nenhuma linha.
-- ---------------------------------------------------------------------
SELECT 'C1 posicao de outra portaria' AS regra, e.id_encomenda AS id
FROM encomenda e
JOIN posicao_estante pe ON pe.id_posicao = e.id_posicao
WHERE pe.id_portaria <> e.id_portaria
UNION ALL
SELECT 'C2 unidade de outro condominio', e.id_encomenda
FROM encomenda e
JOIN portaria p ON p.id_portaria = e.id_portaria
JOIN unidade u  ON u.id_unidade = e.id_unidade
JOIN bloco b    ON b.id_bloco = u.id_bloco
WHERE b.id_condominio <> p.id_condominio
UNION ALL
SELECT 'C3 funcionario de recebimento de outro condominio', e.id_encomenda
FROM encomenda e
JOIN portaria p     ON p.id_portaria = e.id_portaria
JOIN funcionario f  ON f.id_funcionario = e.id_funcionario_recebimento
WHERE f.id_condominio <> p.id_condominio
UNION ALL
SELECT 'C3 funcionario de entrega de outro condominio', r.id_retirada
FROM retirada r
JOIN encomenda e    ON e.id_encomenda = r.id_encomenda
JOIN portaria p     ON p.id_portaria = e.id_portaria
JOIN funcionario f  ON f.id_funcionario = r.id_funcionario
WHERE f.id_condominio <> p.id_condominio
UNION ALL
SELECT 'C4 morador de outra unidade', a.id_aviso
FROM aviso a
JOIN encomenda e ON e.id_encomenda = a.id_encomenda
JOIN morador m   ON m.id_morador = a.id_morador
WHERE m.id_unidade <> e.id_unidade;

-- ---------------------------------------------------------------------
-- 9. Demonstracao das restricoes (NAO executar em bloco: cada comando
--    abaixo DEVE falhar. Descomente um de cada vez para o teste.)
-- ---------------------------------------------------------------------
-- 9a. Segunda retirada da mesma encomenda -> viola uq_retirada_encomenda
-- INSERT INTO retirada (id_encomenda, id_funcionario, retirado_por, retirada_em)
-- VALUES (6, 1, 'Outra Pessoa', '2026-10-30 10:00:00');
--
-- 9b. Operacao repetida -> viola pk_operacao_sincronizacao
-- INSERT INTO operacao_sincronizacao
--     (id_operacao, id_portaria, tipo, id_local, data_hora_origem)
-- VALUES ('P01-000001', 'P01', 'REGISTRO', 7, '2026-10-05 13:10:00');
--
-- 9c. Duas pendentes na mesma posicao -> viola uq_encomenda_posicao_pendente
-- INSERT INTO encomenda
--     (id_portaria, id_local, id_unidade, id_posicao, id_funcionario_recebimento,
--      destinatario, transportadora, tamanho, recebida_em, codigo_retirada_hash, status)
-- VALUES ('P01', 99, 1, 1, 1, 'Teste', 'Transp Alfa', 'P', '2026-10-30 09:00:00',
--         SHA2('000001', 256), 'PENDENTE');
--
-- 9d. APP sem contato -> viola ck_morador_contato
-- INSERT INTO morador (id_unidade, nome, canal_aviso, contato)
-- VALUES (1, 'Teste Sem Contato', 'APP', NULL);

-- ---------------------------------------------------------------------
-- 10. Aplicacao idempotente de uma operacao (algoritmo A5 em SQL)
-- INSERT IGNORE descarta a linha repetida sem gerar erro. ROW_COUNT()
-- devolve 1 quando a operacao era nova e 0 quando ja tinha sido aplicada;
-- so no primeiro caso a central aplica o efeito da operacao.
-- Exemplo (descomentar para testar; a operacao P01-000001 ja existe):
-- ---------------------------------------------------------------------
-- INSERT IGNORE INTO operacao_sincronizacao
--     (id_operacao, id_portaria, tipo, id_local, data_hora_origem)
-- VALUES ('P01-000001', 'P01', 'REGISTRO', 7, '2026-10-05 13:10:00');
-- SELECT ROW_COUNT() AS linhas_inseridas;   -- 0 = ja aplicada, ignorar
