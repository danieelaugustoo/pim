-- =====================================================================
-- 04-views-indices.sql
-- Views de apoio aos relatorios e indices de consulta.
-- Executar depois de 01 e 02. Textos em ASCII, sem acento.
-- =====================================================================

USE morada_central;

-- ---------------------------------------------------------------------
-- vw_pendentes: encomendas pendentes com condominio, unidade e posicao.
-- Nao expoe o hash do codigo de retirada (RNF04).
-- A posicao aparece como "letra da estante/prateleira" (ex.: A/0), como
-- no menu do prototipo em C. dias_parada usa a data corrente.
-- ---------------------------------------------------------------------
CREATE OR REPLACE VIEW vw_pendentes AS
SELECT c.id_condominio,
       c.nome AS condominio,
       e.id_portaria,
       e.id_local,
       b.nome AS bloco,
       u.numero AS apartamento,
       e.destinatario,
       e.transportadora,
       e.tamanho,
       CONCAT(CHAR(65 + pe.estante USING ascii), '/', pe.prateleira) AS posicao,
       e.recebida_em,
       DATEDIFF(CURDATE(), e.recebida_em) AS dias_parada
FROM encomenda e
JOIN portaria p         ON p.id_portaria = e.id_portaria
JOIN condominio c       ON c.id_condominio = p.id_condominio
JOIN unidade u          ON u.id_unidade = e.id_unidade
JOIN bloco b            ON b.id_bloco = u.id_bloco
JOIN posicao_estante pe ON pe.id_posicao = e.id_posicao
WHERE e.status = 'PENDENTE';

-- ---------------------------------------------------------------------
-- vw_indicadores_condominio: indicadores por condominio para a sede
-- (pendencias, pendencias antigas, retiradas e tempo medio de retirada).
-- ---------------------------------------------------------------------
CREATE OR REPLACE VIEW vw_indicadores_condominio AS
SELECT c.id_condominio,
       c.nome AS condominio,
       COUNT(e.id_encomenda) AS total_encomendas,
       SUM(CASE WHEN e.status = 'PENDENTE' THEN 1 ELSE 0 END) AS pendentes,
       SUM(CASE WHEN e.status = 'PENDENTE'
                 AND DATEDIFF(CURDATE(), e.recebida_em) > 7 THEN 1 ELSE 0 END) AS pendentes_antigas,
       SUM(CASE WHEN e.status = 'RETIRADA' THEN 1 ELSE 0 END) AS retiradas,
       SUM(CASE WHEN e.status = 'DEVOLVIDA' THEN 1 ELSE 0 END) AS devolvidas,
       ROUND(AVG(TIMESTAMPDIFF(MINUTE, e.recebida_em, r.retirada_em)) / 60, 1)
           AS horas_medias_ate_retirada
FROM condominio c
LEFT JOIN portaria p  ON p.id_condominio = c.id_condominio
LEFT JOIN encomenda e ON e.id_portaria = p.id_portaria
LEFT JOIN retirada r  ON r.id_encomenda = e.id_encomenda
GROUP BY c.id_condominio, c.nome;

-- ---------------------------------------------------------------------
-- Indices
-- idx_encomenda_status_recebida: acelera pendencias e pendencias antigas
--   (filtro por status e ordenacao/filtro por data).
-- idx_encomenda_unidade: acelera o historico e a busca por unidade.
-- Observacao: o InnoDB ja cria um indice automatico para a chave
-- estrangeira fk_encomenda_unidade; ao criar o indice abaixo, o MySQL pode
-- descartar o automatico, pois o novo indice atende a mesma chave.
-- ---------------------------------------------------------------------
CREATE INDEX idx_encomenda_status_recebida ON encomenda (status, recebida_em);
CREATE INDEX idx_encomenda_unidade ON encomenda (id_unidade);

-- Conferir o uso dos indices (exemplo):
-- EXPLAIN SELECT * FROM encomenda
--  WHERE status = 'PENDENTE' AND recebida_em < '2026-10-22 00:00:00';

-- ---------------------------------------------------------------------
-- Uso das views
-- ---------------------------------------------------------------------
-- SELECT * FROM vw_pendentes ORDER BY dias_parada DESC;
-- SELECT * FROM vw_indicadores_condominio;
