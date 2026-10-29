# Normalização (Etapa 4)

> Roteiro para o capítulo 5. Parte de uma página do caderno da portaria e chega às tabelas do modelo lógico. Todos os dados abaixo são fictícios.

## 0. Ponto de partida: a página do caderno (não normalizada)

Uma folha do caderno de uma portaria registra, em texto livre, um volume por linha:

| Data | Destinatário | Local | Telefone do morador | Transportadora | Recebeu | Retirou / assinatura | Data da retirada |
|---|---|---|---|---|---|---|---|
| 20/10 09:15 | Maria Souza | Bloco A apto 12 | 11 90000-0001 | Transp Alfa, 1 caixa pequena | Antonio | (em branco) | |
| 27/10 14:40 | Joao Souza | Bloco A apto 12 | 11 90000-0002 | Transp Beta, 1 caixa média | Antonio | (em branco) | |
| 10/10 08:45 | Rafael Costa | Bloco D apto 7 | (não consta) | Transp Gama, 1 envelope | Bruna | Rafael Costa, 11/10 18:20 | 11/10 18:20 |

Problemas visíveis:
- "Bloco A apto 12" junta bloco e apartamento em um campo só.
- "Transp Alfa, 1 caixa pequena" junta transportadora e tamanho.
- O telefone se repete a cada volume da mesma unidade.
- Retirada e assinatura ficam misturadas com o registro de chegada, e muitas vezes ficam em branco.
- Nada diz em que condomínio o caderno está nem onde o volume foi guardado.

**Relação não normalizada (UNF)**, com o condomínio/portaria incluído para o cenário de 10 portarias:

```
caderno (portaria, nome_condominio, cidade, data_chegada, destinatario, local_texto,
         telefone_morador, transportadora_e_tamanho, quem_recebeu, retirado_por, data_retirada)
```

## 1. Primeira forma normal (1FN): valores atômicos, sem grupos repetidos

Ações:
1. Separar `local_texto` em `bloco` e `apartamento`.
2. Separar `transportadora_e_tamanho` em `transportadora` e `tamanho`.
3. Transformar o telefone/canal em campos próprios (`canal_aviso`, `contato`).
4. Dar a cada linha um identificador: o número da linha do caderno naquela portaria (`id_local`). Chave: (`portaria`, `id_local`).

```
encomenda_1fn (PK portaria, id_local,
               nome_condominio, cidade, data_chegada, destinatario, bloco, apartamento,
               canal_aviso, contato, transportadora, tamanho, quem_recebeu,
               retirado_por, data_retirada)
```

Resultado: todo campo tem um único valor e cada linha é identificada pela chave composta.

## 2. Segunda forma normal (2FN): sem dependência parcial da chave

Chave composta: (`portaria`, `id_local`). Verificação de cada atributo:

| Atributo | Depende de | Parcial? |
|---|---|---|
| `nome_condominio`, `cidade` | só de `portaria` | **Sim** |
| `destinatario`, `bloco`, `apartamento`, `transportadora`, `tamanho`, `data_chegada`, `quem_recebeu`, `retirado_por`, `data_retirada` | da chave inteira (`portaria` + `id_local`) | Não |
| `canal_aviso`, `contato` | da unidade (`bloco`, `apartamento`) | Não é parcial, mas é transitiva (ver 3FN) |

Ação: tirar `nome_condominio` e `cidade` para a tabela do condomínio.

```
condominio (PK id_condominio, nome, cidade)
portaria   (PK id_portaria, FK id_condominio, descricao)
encomenda_2fn (PK id_portaria, id_local,
               data_chegada, destinatario, bloco, apartamento, canal_aviso, contato,
               transportadora, tamanho, quem_recebeu, retirado_por, data_retirada)
```

## 3. Terceira forma normal (3FN): sem dependência transitiva

Dependências transitivas em `encomenda_2fn`:

| Dependência | Problema | Ação |
|---|---|---|
| (`id_portaria`, `id_local`) → (`bloco`, `apartamento`) → `canal_aviso`, `contato` | Os dados do morador se repetem a cada volume e uma mudança de telefone obriga a corrigir várias linhas | Criar `morador` ligado à `unidade` |
| (`bloco`, `apartamento`) pertencem a um condomínio | `bloco` e `apartamento` só fazem sentido dentro de um condomínio | Criar `bloco` (ligado a `condominio`) e `unidade` (ligada a `bloco`) |
| `quem_recebeu` → função e condomínio do funcionário | O nome do porteiro se repete e pode ser escrito de formas diferentes | Criar `funcionario` e guardar só o `id_funcionario_recebimento` |
| posição na estante (estante, prateleira) → `tipo_volume` | O caderno não registra onde o volume fica; no sistema novo a posição é uma informação da portaria (uma prateleira existe com ou sem volume), não da encomenda | Criar `posicao_estante` e guardar só o `id_posicao` na encomenda |

Decomposição adicional por semântica, para evitar colunas quase sempre vazias e garantir a regra "uma retirada por encomenda":
- `retirado_por`, `data_retirada` (e o funcionário que entregou) só existem depois da retirada → tabela `retirada`, com `UNIQUE (id_encomenda)`.
- O aviso ao morador passa a ser registrado (o caderno não registra) → tabela `aviso`.
- O envio ao servidor central passa a ser registrado → `operacao_sincronizacao`.

## 4. Resultado

| Tabela final | Origem na normalização |
|---|---|
| `condominio` | 2FN: dependência parcial de `portaria` |
| `portaria` | 2FN |
| `bloco`, `unidade` | 3FN: endereço da unidade |
| `morador` | 3FN: dados do morador repetidos |
| `funcionario` | 3FN: quem recebeu e quem entregou |
| `posicao_estante` | 3FN: posição física |
| `encomenda` | O que sobra de `encomenda_2fn`, com chaves estrangeiras no lugar de textos |
| `retirada` | Decomposição por semântica |
| `aviso` | Novo requisito (RF04) |
| `operacao_sincronizacao` | Novo requisito (RF10) |

```
encomenda (PK id_encomenda, FK id_portaria, id_local, FK id_unidade, FK id_posicao,
           FK id_funcionario_recebimento, destinatario, transportadora, tamanho,
           recebida_em, codigo_retirada_hash, status)
```

Justificativa de manter `destinatario` e `transportadora` como texto na `encomenda`: o destinatário é o nome na etiqueta, que pode diferir do morador cadastrado (glossário); a transportadora é um dado informativo, sem atributos próprios neste escopo. Se o escopo crescer, `transportadora` pode virar tabela.

A conferência da 3FN em cada tabela final está nas colunas "Chave" do [dicionário de dados](dicionario-de-dados.md): nenhum atributo não chave depende de outro atributo não chave.
