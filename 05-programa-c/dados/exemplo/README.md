# 05-programa-c/dados/exemplo

**O que guarda:** dados fictícios, versionados no Git, para demonstrar o programa e a central.

**Exigências do manual que atende (Etapa 5):** manipulação de arquivos. Também alimenta as telas do protótipo mostradas nos resultados.

| Arquivo | Copiar para | Conteúdo |
|---|---|---|
| `P01-encomendas.csv` | `dados/portarias/` | 8 encomendas da portaria P01 (pendentes, uma retirada e uma devolvida) |
| `P01-moradores.csv` | `dados/portarias/` | 8 moradores, com os três canais de aviso |
| `P01-sequencia.txt` | `dados/portarias/` | último número de operação já enviado (10) |
| `P01.log` | `dados/rede/` | as 10 operações de P01 que correspondem às encomendas acima |
| `P02.log` | `dados/rede/` | 7 operações de uma segunda portaria (para a central consolidar duas) |

Os dados são coerentes com `04-banco-de-dados/sql/02-carga-exemplo.sql`: depois de consolidar, o relatório mostra P01 com 6 pendentes, 1 retirada e 1 devolvida, e P02 com 5 pendentes e 1 retirada, os mesmos números das consultas do banco.

Copie o `P01-sequencia.txt` junto com o `P01.log`: sem ele a portaria repetiria ids de operações já aplicadas (ver o README de `05-programa-c/`).
