# Caracterização da organização (Etapa 1)

> Roteiro de tópicos para o capítulo 2, que o grupo redige. Números fictícios e coerentes entre si (`PLANO.md`, seção 4); o grupo pode ajustá-los, desde que mantenha a coerência em código, banco, rede e texto.

## 1. Identificação

| Item | Dado |
|---|---|
| Razão social | Administradora Morada Central Ltda. (fictícia) |
| Sede | São Paulo – SP (ajustável) |
| Ramo de atuação | Administração condominial e gestão de equipes de portaria para condomínios residenciais |

## 2. Missão

Administrar condomínios residenciais com organização, transparência e segurança, oferecendo a moradores e funcionários rotinas claras e confiáveis.

## 3. Produtos e serviços

- Administração financeira e prestação de contas aos condôminos
- Gestão das equipes de portaria (contratação, escalas e treinamento)
- Gestão de manutenção e de fornecedores
- Atendimento ao morador e registro de ocorrências

## 4. Porte

| Item | Quantidade |
|---|---|
| Condomínios administrados | 10 (de 2 a 4 blocos cada) |
| Unidades (total) | cerca de 960 |
| Porteiros | 40 (4 por condomínio, escala 12x36) |
| Sede: gerente de operações | 1 |
| Sede: supervisores | 2 (5 condomínios cada) |
| Sede: atendentes | 3 |
| Sede: analistas administrativo-financeiros | 2 |

## 5. Estrutura organizacional

- Diretoria
  - Gerência de Operações
    - Supervisores → Porteiros
    - Atendimento ao Morador
  - Administrativo-Financeiro
- O síndico de cada condomínio é eleito pelos condôminos e é o interlocutor da administradora. Aparece como relação externa no organograma.

Diagrama: [`diagramas/organograma.mmd`](diagramas/organograma.mmd).

## 6. Processos de negócio

O processo de encomendas (atual e proposto) está em [`processos.md`](processos.md).

## 7. Público-alvo

- Moradores, com perfis variados, incluindo idosos e pessoas que não usam smartphone
- Síndicos
- Porteiros
- Equipe da sede

## 8. Problemas encontrados

| ID | Problema |
|---|---|
| P1 | Extravios e entregas à pessoa errada |
| P2 | Falta de rastreabilidade (quem recebeu, onde está, quem retirou) |
| P3 | Tempo do porteiro consumido por encomendas, com picos em novembro e dezembro |
| P4 | Aviso ao morador falho ou inexistente |
| P5 | Acúmulo de volumes e falta de espaço |
| P6 | Nenhum dado para a sede planejar equipe e espaço |
| P7 | Internet instável em parte das portarias, o que inviabiliza uma solução que só funcione online |

> Nota: a ocorrência desses problemas nos 10 condomínios é o cenário fictício do trabalho. Qualquer número real sobre o setor (por exemplo, percentual do turno gasto com encomendas) precisa de fonte: `[FONTE A VERIFICAR]`, ver `02-pesquisa/fontes.md`.

## 9. Justificativa da solução proposta

- O problema se repete nos 10 condomínios e depende de registro, rastreabilidade e comunicação, coisas que uma solução computacional resolve bem: padroniza o processo, reduz erros e gera dados.
- A operação offline atende as portarias com internet instável (P7).
- A consolidação central dá à administradora a visão de todos os condomínios (P6).
