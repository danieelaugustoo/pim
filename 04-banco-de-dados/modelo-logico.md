# Modelo lógico (Etapa 4)

> Roteiro para o capítulo 5. Deriva do [modelo conceitual](modelo-conceitual.md) e é a base do script `sql/01-criacao-tabelas.sql`. SGBD: MySQL 8 (trocar se a disciplina usar outro).

## 1. Relações

Notação: **PK** chave primária, *FK* chave estrangeira, `UQ` único, `?` aceita nulo.

```
condominio (PK id_condominio, nome, cidade)

bloco (PK id_bloco, FK id_condominio -> condominio, nome)
    UQ (id_condominio, nome)

unidade (PK id_unidade, FK id_bloco -> bloco, numero)
    UQ (id_bloco, numero)

morador (PK id_morador, FK id_unidade -> unidade, nome, canal_aviso, contato?, ativo)

funcionario (PK id_funcionario, FK id_condominio -> condominio, nome, funcao)

portaria (PK id_portaria, FK id_condominio -> condominio, descricao)

posicao_estante (PK id_posicao, FK id_portaria -> portaria, estante, prateleira, tipo_volume)
    UQ (id_portaria, estante, prateleira)

encomenda (PK id_encomenda, FK id_portaria -> portaria, id_local,
           FK id_unidade -> unidade, FK id_posicao -> posicao_estante,
           FK id_funcionario_recebimento -> funcionario,
           destinatario, transportadora, tamanho, recebida_em,
           codigo_retirada_hash, status, id_posicao_pendente [derivada])
    UQ (id_portaria, id_local)
    UQ (id_posicao_pendente)

retirada (PK id_retirada, FK id_encomenda -> encomenda, FK id_funcionario -> funcionario,
          retirado_por, retirada_em)
    UQ (id_encomenda)

aviso (PK id_aviso, FK id_encomenda -> encomenda, FK id_morador? -> morador,
       canal, enviado_em?, situacao)

operacao_sincronizacao (PK id_operacao, FK id_portaria -> portaria, tipo, id_local,
                        data_hora_origem, aplicada_em)
```

## 2. Tipos e restrições principais

| Tabela | Coluna | Tipo | Restrição de valor |
|---|---|---|---|
| morador | canal_aviso | VARCHAR(9) | `ck_morador_canal`: APP, SMS ou INTERFONE |
| morador | contato | VARCHAR(40) | `ck_morador_contato`: obrigatório quando o canal é APP ou SMS |
| portaria | id_portaria | CHAR(3) | `ck_portaria_codigo`: P01 a P10 |
| posicao_estante | tipo_volume | VARCHAR(2) | `ck_posicao_estante_tipo`: PM ou G |
| encomenda | tamanho | CHAR(1) | `ck_encomenda_tamanho`: P, M ou G |
| encomenda | status | VARCHAR(9) | `ck_encomenda_status`: PENDENTE, RETIRADA ou DEVOLVIDA |
| encomenda | codigo_retirada_hash | CHAR(64) | `ck_encomenda_hash`: 64 caracteres (SHA-256 em hexadecimal) |
| aviso | canal | VARCHAR(9) | `ck_aviso_canal`: APP, SMS ou INTERFONE |
| aviso | situacao | VARCHAR(9) | `ck_aviso_situacao`: PENDENTE, ENVIADO ou FALHA |
| operacao_sincronizacao | tipo | VARCHAR(9) | `ck_operacao_tipo`: REGISTRO, RETIRADA ou DEVOLUCAO |
| operacao_sincronizacao | id_operacao | VARCHAR(12) | `ck_operacao_id`: começa pelo código da portaria |

Dicionário completo: [`dicionario-de-dados.md`](dicionario-de-dados.md).

## 3. Regras que o SGBD não verifica sozinho

Uma chave estrangeira simples não garante estas ligações entre três tabelas. Ficam a cargo da aplicação (a API central) e podem ser conferidas pela consulta de auditoria de consistência em `sql/03-consultas.sql`.

| # | Regra |
|---|---|
| C1 | A posição de uma encomenda pertence à mesma portaria da encomenda |
| C2 | A unidade da encomenda pertence ao condomínio da portaria |
| C3 | O funcionário que recebeu ou entregou trabalha no condomínio da portaria |
| C4 | O morador de um aviso pertence à unidade da encomenda |

## 4. Decisões de modelagem

| Decisão | Motivo |
|---|---|
| `id_portaria` como `CHAR(3)` ('P01' a 'P10') | O mesmo código aparece no arquivo do protótipo e no id da operação (`P01-000123`) |
| `id_local` separado do `id_encomenda` | O id local vem do arquivo da portaria; o `id_encomenda` é a chave interna do banco. O par (`id_portaria`, `id_local`) é único |
| `codigo_retirada_hash` em vez do código | O código de 6 dígitos nunca fica em texto no banco central (RNF04). Limitação: com só 10^6 possibilidades, um hash simples é fraco contra força bruta; mitigar com limite de tentativas e sal por encomenda (evolução futura) |
| `id_posicao_pendente` (coluna derivada) | Vale `id_posicao` enquanto o status é PENDENTE e fica nula nos demais casos. Um índice único sobre ela impede duas pendentes na mesma posição (RN04), sem impedir que a posição seja reaproveitada depois da retirada |
| `encomenda.id_posicao` mantido após a retirada | Preserva o histórico de onde o volume ficou |
| `aviso.id_morador` aceita nulo | A unidade pode não ter morador cadastrado; nesse caso o aviso é feito manualmente |
| Coluna `id_funcionario_recebimento` | Exceção ao padrão "FK com o mesmo nome da chave": a tabela `encomenda` e a `retirada` ligam-se ao mesmo funcionário em papéis diferentes, e o nome deixa o papel claro (`PLANO.md`, seção 9.4) |
| Sem FK de `operacao_sincronizacao` para `encomenda` | A operação REGISTRO é a que cria a encomenda na central; exigir a encomenda antes inverteria a ordem de aplicação |
