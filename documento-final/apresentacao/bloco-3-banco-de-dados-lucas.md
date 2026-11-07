# Bloco 3: Banco de dados (Lucas)

Tempo: **cerca de 3 minutos**. Figuras: **6** (DER) e **7** (consulta SQL no MySQL). Só use números que estão no trabalho.

## Roteiro de fala

**1. Por que relacional (40 s).** "O banco fica no servidor central. Ele guarda entidades estáveis e muito ligadas entre si, como condomínio, bloco, unidade, morador, encomenda e retirada, e precisa garantir regras que não podem ser violadas: uma única retirada por encomenda e uma única aplicação de cada operação de sincronização. O modelo relacional faz isso com chaves e restrições, por isso escolhemos o MySQL 8." *(ADR-001)*

**2. O modelo (45 s).** "O modelo tem **11 entidades**. Cada condomínio tem blocos, que têm unidades, que abrigam moradores. Cada condomínio tem uma portaria, que recebe as encomendas, controla as posições da estante e origina as operações de sincronização. Uma encomenda ocupa uma posição enquanto está pendente, tem no máximo uma retirada e pode gerar vários avisos." *(Figura 6, o DER)*

**3. Normalização (45 s).** "Partimos de uma página do caderno da portaria: 'Bloco A apto 12' num campo só, transportadora e tamanho juntos, telefone repetido a cada volume. Na **primeira forma normal** separamos esses campos. Na **segunda**, o nome e a cidade do condomínio foram para as tabelas de condomínio e de portaria. Na **terceira**, os dados do morador, que se repetiam a cada volume, ganharam tabela própria. O resultado foi 11 tabelas."

**4. O que merece destaque no modelo físico (45 s).** "São **44 restrições nomeadas**. Três soluções: a chave primária da tabela de operações impede registrar a mesma operação duas vezes, o que sustenta a sincronização sem duplicidade. Uma coluna gerada, preenchida só enquanto a encomenda está pendente, tem restrição de unicidade, então duas pendentes não ocupam a mesma posição, mas posições liberadas voltam a ser usadas. E o código de retirada é guardado só como **resumo criptográfico (SHA-256)**, não o número, para proteger se o banco for acessado indevidamente."

**5. Resultados e NoSQL (30 s).** "Rodamos os scripts em um MySQL 8.4 em contêiner Docker, sem erro, e os resultados batem com o relatório do programa em C: 6 pendências em um condomínio e 5 no outro, ocupação de 6 de 48 posições no P01 e 5 de 48 no P02." *(Figura 7)* "Sobre NoSQL, só faria sentido no histórico de avisos, numa evolução futura, porque os campos variam por canal."

## O que NÃO dizer (o trabalho declara como limite)

- O **programa em C não usa o banco**: ele usa arquivos CSV (ADR-002). O banco foi modelado e testado à parte.
- O hash do código é do **sistema completo**; no protótipo o código fica em texto e aparece na tela do porteiro.
- Os dados são **dados de exemplo** (dois condomínios e duas portarias).

## Perguntas de banco que podem cair

| Pergunta | Resposta |
|---|---|
| O que é a 1ª, a 2ª e a 3ª forma normal? | 1ª: cada campo guarda um valor só e a linha tem identificação. 2ª: o que depende só de parte da chave vai para outra tabela. 3ª: o que depende de outro campo não-chave (como os dados do morador) vai para a sua própria tabela. |
| Por que MySQL e não NoSQL? | As entidades são muito relacionadas, as regras de integridade são essenciais e os relatórios usam agregações e junções. Um segundo banco só se justificaria com mais volume e variedade de avisos. |
| O que é chave primária e chave estrangeira? | A primária identifica a linha. A estrangeira aponta para a primária de outra tabela e garante que a ligação existe. |
| Como o banco impede duplicar uma operação? | A chave primária da tabela de operações é o identificador da operação (como `P01-000123`). Registrar o mesmo duas vezes dá erro. |
| Por que guardar o resumo (hash) e não o código? | Se alguém acessar o banco, não vê os códigos de retirada. O resumo é SHA-256, com 64 caracteres hexadecimais. |
| O programa em C conversa com o banco? | Não. Usa arquivos CSV. O banco é do sistema completo e foi testado com scripts SQL. |
| Quantas tabelas e restrições? | 11 tabelas e 44 restrições, nomeadas com os prefixos `pk_`, `fk_`, `uq_` e `ck_`. |
| Os números do banco batem com o programa? | Sim, com a data de referência de 29/10/2026: 6 e 5 pendências por condomínio, encomendas 4 (14 dias) e 1 (9 dias) com mais de 7 dias, ocupação 6 de 48 (12,5%) e 5 de 48 (10,4%). |
