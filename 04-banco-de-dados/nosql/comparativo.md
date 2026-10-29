# Comparativo: relacional × documentos × chave-valor (Etapa 4)

> Roteiro para a discussão sobre NoSQL no capítulo 5. As afirmações abaixo são conceituais e gerais, não citam estudos nem números. Antes de citar no trabalho, o grupo deve confirmar nas fontes B04, B05 e B06 de `02-pesquisa/fontes.md` `[FONTE A VERIFICAR]`. Decisão resultante: [ADR-001](../../03-engenharia-software/decisoes/adr-001-banco-relacional.md).

## 1. Os três modelos neste caso

| Modelo | Exemplo de produto citado no plano | Como guardaria uma encomenda |
|---|---|---|
| Relacional | MySQL 8 | Linhas em tabelas ligadas por chaves (`encomenda`, `unidade`, `retirada`...) |
| Documentos | MongoDB | Um documento JSON por encomenda, com unidade, retirada e avisos aninhados |
| Chave-valor | Redis | Uma chave (por exemplo, o id da encomenda) apontando para um valor, sem consulta por outros campos |

## 2. Critérios aplicados ao sistema

| Critério | Relacional | Documentos | Chave-valor |
|---|---|---|---|
| Entidades muito relacionadas (unidade, morador, posição, encomenda, retirada) | Muito adequado: chaves estrangeiras e junções | Possível, mas as relações ficam por conta da aplicação ou duplicadas nos documentos | Fraco: não há relações |
| Regras de integridade (uma retirada por encomenda, uma operação aplicada uma vez, posição não repetida entre pendentes) | Garantidas pelo banco (`UNIQUE`, PK, FK, `CHECK`) | Dependem da aplicação, exceto índices únicos simples | Dependem da aplicação |
| Consultas de relatório (pendências por condomínio, pico, ocupação, tempo médio) | Naturais em SQL (agregações, junções, janelas) | Possíveis com agregação, porém mais trabalhosas entre coleções | Inadequado para consultas por vários campos |
| Esquema estável | Vantagem: o esquema é bem conhecido | Flexibilidade que o domínio não precisa na maior parte | Não se aplica |
| Dados com estrutura variável | Exige colunas opcionais ou tabelas extras | Vantagem: cada documento tem os campos que precisa | Valor opaco |
| Consistência entre várias tabelas (aplicar operação e atualizar encomenda juntos) | Transações com garantias ACID no InnoDB | Depende do produto e da configuração | Depende do produto |
| Leitura muito rápida por chave | Boa com índices | Boa com índices | Ponto forte |
| Conhecimento do grupo | Visto na disciplina de banco de dados | A estudar | A estudar |

## 3. Conclusão para este projeto

1. **Relacional no núcleo** (ADR-001). As entidades são estáveis e muito relacionadas, e o banco garante regras que o sistema precisa ter por construção: uma retirada por encomenda, idempotência por chave primária (ADR-003) e posição única entre as pendentes.
2. **Documentos para o histórico de avisos** (hipótese de evolução). Os avisos têm campos que mudam com o canal: um aviso de app guarda o identificador do dispositivo, um SMS guarda o provedor e o id da mensagem, o interfone guarda quem avisou e se o código foi impresso. No relacional isso vira muitas colunas quase sempre vazias ou várias tabelas; num documento, cada aviso traz só o que importa. Por isso o exemplo JSON é de aviso: [`exemplo-aviso.json`](exemplo-aviso.json).
3. **Chave-valor como apoio, não como base.** Faria sentido para dados temporários e de acesso rápido (por exemplo, controlar tentativas de código ou guardar sessões do painel). Não é necessário no escopo atual.

## 4. Riscos e cuidados de uma solução mista

| Risco | Cuidado |
|---|---|
| Dois bancos para operar e proteger | Só adotar o segundo se o volume e a variedade dos avisos justificarem |
| Ligação entre o aviso (documento) e a encomenda (linha) | Guardar `id_portaria` e `id_local` no documento, que são a chave natural do banco central |
| Dados pessoais nos avisos (contato do morador) | Aplicar as mesmas regras de privacidade e retenção do banco relacional (LGPD, `07-seguranca-privacidade-acessibilidade/`) |

## 5. Ligação com o restante do projeto

- O modelo relacional escolhido está em [`modelo-logico.md`](../modelo-logico.md) e nos scripts de [`sql/`](../sql/).
- O protótipo em C não usa banco nenhum: guarda CSV (ADR-002).
