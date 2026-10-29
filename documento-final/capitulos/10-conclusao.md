# 10 Conclusão (roteiro, cerca de 1,5 página)

> **ROTEIRO, não é o texto.** A conclusão geral é escrita pelo grupo (`PLANO.md`, seção 9.8). Substituir este conteúdo na seção "Texto do grupo". Escrever depois dos capítulos 2 a 9 e antes do resumo.

**Exigência do manual:** apresentar os resultados de forma clara, relacionar os resultados aos objetivos, retomar a proposta inicial e destacar os principais pontos encontrados.

## Tópicos

1. **Retomada da proposta:** problema, pergunta de pesquisa e solução (nó de portaria offline + central).
2. **Resultados × objetivos:** um parágrafo ou linha por objetivo específico, dizendo o que foi feito e o que foi verificado.

| Objetivo específico (`02-pesquisa/problema-e-objetivos.md`) | Onde o resultado aparece | Resultado a relatar |
|---|---|---|
| 1. Caracterizar o processo atual | Capítulo 2 | `[o grupo descreve]` |
| 2. Levantar requisitos com pesquisa bibliográfica e análise do cenário | Capítulos 3 e 4 | requisitos, casos de uso e histórias (sem levantamento de campo) |
| 3. Modelar o banco relacional e avaliar NoSQL | Capítulo 5 | modelo, scripts executados e comparativo |
| 4. Implementar em C o núcleo da portaria e a consolidação | Capítulo 6 | protótipo testado (9 conjuntos de testes) |
| 5. Projetar a infraestrutura de rede e a arquitetura distribuída | Capítulo 7 | projeto; testes do Packet Tracer dependem do grupo |
| 6. Analisar segurança, privacidade e acessibilidade | Capítulo 8 | análise e limitações |

3. **Principais pontos encontrados:** o que funcionou, o que foi simulado, o que ficou como limitação.
4. **Contribuições e aprendizados** (do grupo, por disciplina, se couber).
5. **Trabalhos futuros:** de `08-integracao/limitacoes-e-evolucao.md`.
6. **Fechamento:** responder à pergunta de pesquisa **dentro do que foi verificado**.

## Cuidados

- Sem novas informações nem citações: a conclusão só retoma o que já foi apresentado.
- Não afirmar benefícios que o piloto ainda não mediu.
- Coerência com o resumo e o abstract.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Atualize os itens marcados quando o Packet Tracer e a revisão por pares forem concluídos.

# 10 CONCLUSÃO

Este trabalho propôs e documentou uma solução para a gestão de encomendas nas portarias de uma administradora de condomínios fictícia, motivada por um processo manual, em caderno, que gera extravios, entregas incorretas, falta de rastreabilidade e sobrecarga dos porteiros. A solução reúne um nó de portaria que funciona sem internet e uma central que consolida as operações sem duplicá-las, e foi desenvolvida em quatro frentes: engenharia de software, banco de dados, programação em C e redes.

Em relação aos objetivos específicos, o processo atual e seus sete problemas foram caracterizados (capítulo 2). Os requisitos foram levantados a partir de pesquisa bibliográfica e da análise do cenário, sem levantamento de campo, o que limita a base empírica (capítulos 3 e 4). O banco de dados foi modelado, normalizado até a terceira forma normal e implementado em MySQL, com onze tabelas e 44 restrições nomeadas, e os scripts foram executados em um servidor de teste sem erros; a discussão sobre NoSQL concluiu que o modelo relacional é o adequado para o núcleo (capítulo 5). O núcleo da portaria e a consolidação central foram implementados em C, com seis algoritmos documentados e nove conjuntos de testes automatizados que passaram, e a execução da central duas vezes sobre os mesmos dados confirmou que nada é duplicado (capítulo 6). A infraestrutura de rede foi projetada, com 44 redes sem sobreposição de endereços, VLANs, regras de acesso e nuvem como ponto comum; `[ATUALIZAR: os testes no Packet Tracer foram executados e o resultado foi ...]` (capítulo 7). A análise de segurança, privacidade e acessibilidade apontou medidas já presentes no protótipo e limitações a tratar no sistema completo (capítulo 8).

Os principais pontos encontrados foram: a decisão de sincronizar de forma assíncrona, com operações identificadas de modo único e aplicadas uma só vez, é o que permite a portaria funcionar sem internet; o canal de aviso alternativo, por interfone com código impresso, é uma salvaguarda de inclusão; e os relatórios de pendências antigas, dia de pico e ocupação dão à sede dados que hoje não existem. As limitações também são claras: a rede e o aviso são simulados, o protótipo não tem interface gráfica nem controle de acesso, o código de retirada é visível na tela do porteiro e os dados são fictícios. Os benefícios apresentados, como menos extravios e menos tempo de registro, são esperados e dependem de um piloto para serem medidos, pois não há linha de base.

Retomando a proposta inicial, a pergunta de pesquisa recebe, dentro do que foi verificado, uma resposta de viabilidade: é possível construir uma solução que opere sem internet e sincronize sem duplicar registros, com as regras de negócio testadas e a infraestrutura projetada. Se isso de fato reduz extravios e o tempo dos porteiros é uma hipótese que só um piloto na administradora pode confirmar.

Como trabalhos futuros, destacam-se a troca da rede simulada por uma API segura, a conexão do sistema ao banco, o aplicativo do morador, o painel de indicadores, a devolução de volumes após o prazo e o controle de acesso por perfil, conforme o capítulo 9. O desenvolvimento permitiu ao grupo integrar, em um problema concreto, conhecimentos de várias disciplinas `[o grupo pode acrescentar aprendizados próprios]`.
