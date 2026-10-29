# Resumo (roteiro)

> **ROTEIRO, não é o texto.** Os tópicos abaixo organizam o que o resumo precisa conter. O grupo escreve o resumo com as próprias palavras e **substitui** este conteúdo na seção "Texto do grupo". Escrever por último, depois de fechar os demais capítulos.

**Exigência do manual:** resumo conciso e objetivo, com o conteúdo principal, os pontos relevantes e as conclusões, em **até 500 palavras**, seguido das palavras-chave.

## Roteiro (uma ideia por frase ou bloco curto)

1. **Contexto e problema:** gestão de encomendas em condomínios por caderno; extravios, entregas erradas e sobrecarga dos porteiros (P1 a P7 em `01-organizacao/caracterizacao.md`).
2. **Objetivo:** objetivo geral de `02-pesquisa/problema-e-objetivos.md`.
3. **Método:** pesquisa bibliográfica e análise do cenário (sem levantamento de campo), Scrum em sprints, protótipo em C, modelagem relacional, projeto de rede.
4. **Solução:** nó de portaria que funciona sem internet + central que consolida sem duplicar; aviso ao morador por app, SMS ou interfone.
5. **O que foi feito:** o que existe de fato (protótipo em C testado, modelo e scripts SQL executados, projeto de rede, análise de segurança e acessibilidade).
6. **Resultados:** apenas o que foi **medido ou verificado**. Não incluir percentuais de melhoria sem dados reais.
7. **Conclusão:** principais pontos e limitações (aviso e rede simulados).

## Palavras-chave (sugestões a revisar)

Encomendas; condomínios; sistemas distribuídos; operação offline; banco de dados relacional.

## Checklist

- [ ] Até 500 palavras (conferir a contagem).
- [ ] Palavras-chave logo após o texto, no padrão do modelo da UNIP.
- [ ] Sem citações diretas e sem números que não estejam no corpo do trabalho.
- [ ] Coerente com a conclusão (capítulo 10).

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Conferir a contagem de palavras (máximo de 500) no editor final.

**RESUMO**

Este trabalho trata da gestão de encomendas nas portarias de condomínios residenciais, a partir de um cenário fictício: uma administradora de dez condomínios cujas portarias registram as encomendas em caderno, o que gera extravios, entregas a pessoas erradas, falta de rastreabilidade e sobrecarga dos porteiros, além de internet instável em parte das portarias. O objetivo foi desenvolver e documentar uma solução computacional que reduza esses problemas, com operação offline e sincronização central. A metodologia combinou pesquisa bibliográfica, análise do cenário, desenvolvimento com Scrum e verificação por testes, sem levantamento de campo com usuários. A solução proposta tem duas partes: um nó de portaria, que registra a encomenda, indica a posição na estante, gera um código único de retirada, avisa o morador pelo canal escolhido (aplicativo, SMS ou interfone com código impresso) e funciona sem internet; e uma central, que aplica cada operação enviada pelas portarias uma única vez e gera relatórios consolidados. Foram elaborados os requisitos e a modelagem, um banco de dados relacional em MySQL com onze tabelas, um protótipo em linguagem C com seis algoritmos documentados e nove conjuntos de testes automatizados, o projeto de uma rede com VLANs, regras de acesso e nuvem, e a análise de privacidade, segurança e acessibilidade. Os testes do protótipo passaram e a consolidação não duplica registros ao processar os mesmos dados duas vezes. A rede e o aviso ao morador são simulados, e os benefícios esperados, como a redução de extravios, dependem de um piloto para serem medidos. Conclui-se que a solução é viável tecnicamente e que seus efeitos reais ainda precisam ser avaliados.

**Palavras-chave:** encomendas; condomínios; sistemas distribuídos; operação offline; banco de dados relacional.
