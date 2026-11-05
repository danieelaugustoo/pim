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
| 5. Projetar a infraestrutura de rede e a arquitetura distribuída | Capítulo 7 | projeto; 15 testes no Packet Tracer 9.0.1, todos como esperado |
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

> **Rascunho** redigido a partir do roteiro (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Atualize os itens marcados quando a revisão por pares for concluída.

# 10 CONCLUSÃO

O trabalho propôs e documentou uma solução para a gestão de encomendas nas portarias de uma administradora de condomínios. O ponto de partida foi o caderno, que gera extravios, entregas incorretas, falta de rastreabilidade e sobrecarga dos porteiros. A solução tem um nó de portaria que funciona sem internet e uma central que consolida as operações sem duplicá-las, e foi desenvolvida em quatro frentes: engenharia de software, banco de dados, programação em C e redes.

O processo atual e seus sete problemas foram caracterizados no capítulo 2. Os requisitos vieram da pesquisa bibliográfica e da análise do cenário, sem levantamento de campo, o que limita a base empírica (capítulos 3 e 4). O banco foi modelado até a terceira forma normal e implementado em MySQL, com onze tabelas e 44 restrições nomeadas, e a discussão sobre NoSQL concluiu que o modelo relacional é o adequado para o núcleo (capítulo 5). O núcleo da portaria e a consolidação central foram implementados em C, com seis algoritmos documentados e nove conjuntos de testes aprovados, e executar a central duas vezes sobre os mesmos dados confirmou que nada é duplicado (capítulo 6). A rede foi projetada com VLANs, regras de acesso e uma nuvem como ponto comum, e os quinze testes no Packet Tracer 9.0.1 deram o resultado esperado, ainda sem a VPN (capítulo 7). O capítulo 8 apontou as medidas de segurança presentes no protótipo e as limitações que ficam para o sistema completo.

Três resultados merecem destaque. A sincronização assíncrona, com operações de identificador único aplicadas uma só vez, é o que permite à portaria funcionar sem internet. O aviso por interfone com código impresso atende quem não usa smartphone. E os relatórios de pendências antigas, dia de pico e ocupação dão à sede dados que hoje não existem. Há limitações: a rede e o aviso são simulados, o protótipo não tem interface gráfica nem controle de acesso, o código de retirada aparece na tela do porteiro e os testes usaram dados de exemplo. Os benefícios esperados, como menos extravios e menos tempo de registro, ainda não foram medidos, porque não há linha de base.

A pergunta de pesquisa recebe, dentro do que foi verificado, uma resposta de viabilidade: é possível construir uma solução que opere sem internet e sincronize sem duplicar registros, com as regras de negócio testadas e a infraestrutura projetada. Se isso reduz de fato os extravios e o tempo dos porteiros, só um piloto na administradora poderá mostrar.

Como trabalhos futuros, ficam a troca da rede simulada por uma API segura, a ligação do sistema ao banco, o aplicativo do morador, o painel de indicadores, a devolução de volumes e o controle de acesso por perfil (capítulo 9). O desenvolvimento reuniu, em um problema concreto, conhecimentos de várias disciplinas `[o grupo pode acrescentar aprendizados próprios]`.
