# 04-banco-de-dados/sql

**O que guarda:** os scripts SQL para MySQL 8, numerados na ordem de execução: criação das tabelas, carga de exemplo (dados fictícios), consultas, views e índices.

**Exigências do manual que atende (Etapa 4):** modelo físico (`01-criacao-tabelas.sql`) e principais comandos SQL (`02` a `04`). As consultas executadas alimentam os resultados do capítulo de banco de dados.

## Como executar

Requer MySQL 8.0.16 ou superior (as restrições `CHECK` só são aplicadas a partir daí). Rode os arquivos nesta ordem, em banco novo: `01`, `02`, `03` e `04`. O `01` cria o banco `morada_central`.

No MySQL Workbench: abra cada arquivo e clique no botão do raio (executar tudo).

Pela linha de comando, com o `mysql` instalado:

```
mysql -u root -p < 01-criacao-tabelas.sql
```

Sem instalar o MySQL, com Docker (contêiner descartável, sem porta aberta e sem senha, só para teste local):

```
docker run -d --name pim-mysql-teste -e MYSQL_ALLOW_EMPTY_PASSWORD=yes mysql:8.4
docker exec -i pim-mysql-teste mysql -uroot -t < 01-criacao-tabelas.sql
docker rm -f pim-mysql-teste
```

Aguarde alguns segundos entre o primeiro e o segundo comando, até o servidor aceitar conexões. Repita o segundo comando para `02`, `03` e `04`.

Os scripts foram executados com sucesso em MySQL 8.4.13 (ver `03-engenharia-software/scrum/sprints/sprint-01.md`).
