# Checklist de formatação ABNT e entrega

Baseado em `00-projeto/regras-do-pim.md` (resumo do manual do PIM II). **Se algo divergir do manual oficial da UNIP ou do modelo de trabalho da universidade, vale o manual e o modelo.** Marque cada item quando conferir no documento montado (não no rascunho em Markdown).

## 1. Estrutura obrigatória

- [ ] Capa (modelo da UNIP)
- [ ] Resumo (até 500 palavras) + palavras-chave
- [ ] Abstract (inglês, espanhol ou francês) + palavras-chave no mesmo idioma
- [ ] Sumário (gerado pelo editor, com os títulos de capítulo e subcapítulo)
- [ ] Introdução: objetivo da pesquisa, metodologia, breve apresentação da empresa, visão geral da proposta
- [ ] Desenvolvimento, em capítulos e subcapítulos, com pesquisa, fundamentação, métodos, materiais, resultados e discussão
- [ ] Conclusão: resultados claros, relação com os objetivos, retomada da proposta, principais pontos
- [ ] Referências (ABNT)

## 2. Tamanho

- [ ] Desenvolvimento entre **20 e 30 páginas** (conferir a contagem real; ver `estrutura-e-paginas.md`)
- [ ] Definido com o professor se Introdução, Conclusão e apêndices entram na contagem

## 3. Formatação

| Item | Regra | Conferido |
|---|---|---|
| Papel | A4 | [ ] |
| Margens | Superior e esquerda 3 cm; inferior e direita 2 cm | [ ] |
| Espaçamento entre linhas | 1,5 | [ ] |
| Recuo da primeira linha | 1,5 cm | [ ] |
| Fonte | Arial ou Times New Roman, tamanho 12 | [ ] |
| Citações longas e notas | Tamanho 10 | [ ] |
| Alinhamento | Justificado | [ ] |
| Numeração das páginas | A partir da Introdução | [ ] |
| Títulos e subtítulos | Numeração progressiva, padronizada em todo o trabalho | [ ] |

Itens que o manual deixa em aberto ou que o grupo deve confirmar no modelo da UNIP: posição do número da página, formato do sumário, estilo de legenda de figuras e tabelas, tratamento das citações curtas `[A CONFIRMAR no modelo]`.

## 4. Figuras, tabelas e código

- [ ] Toda figura numerada, com título acima e fonte abaixo (ABNT), e **citada no texto**
- [ ] Toda tabela numerada, com título e fonte
- [ ] Figuras legíveis no tamanho impresso (prints de terminal e de Packet Tracer com letra legível)
- [ ] Arquivos em `figuras/figura-NN-descricao.png`, na mesma ordem de `estrutura-e-paginas.md`
- [ ] Diagramas renderizados a partir do código-fonte (PlantUML e Mermaid ainda não foram renderizados)
- [ ] Trechos de código curtos, com fonte monoespaçada e explicação no texto

## 5. Autoria, citações e referências

- [ ] Texto **autoral e inédito**, escrito pelo grupo com as próprias palavras
- [ ] Nenhum trecho copiado de fonte, de colega ou de ferramenta de IA sem reescrita e sem citação (a UNIP usa software de similaridade: plágio integral, parcial, conceitual e autoplágio são proibidos)
- [ ] Todo trecho reproduzido diretamente entre aspas (ou recuado, se longo), com **autor, ano e página**
- [ ] Toda citação no texto tem a obra em `referencias.md` e toda obra listada foi citada
- [ ] Todas as marcações `[FONTE A VERIFICAR]` resolvidas: fonte conferida e citada, ou a afirmação removida
- [ ] Referências em ordem alfabética, no padrão ABNT, sem invenção de autor, ano, editora ou página
- [ ] Leis citadas (LGPD, LBI) conferidas no texto oficial
- [ ] Verificado com o professor se a UNIP tem orientação sobre o uso de IA no PIM

## 6. Pendências do projeto que precisam estar resolvidas antes do texto final

Todas as marcações abaixo estão no repositório (`grep -rn "A DEFINIR\|A PREENCHER\|FONTE A VERIFICAR\|A COTAR" --include=*.md .`).

- [ ] Prazo de entrega confirmado
- [ ] Integrantes, RA, líder, Product Owner e Scrum Master definidos
- [ ] Pesquisa de campo aplicada e `02-pesquisa/resultados-campo.md` preenchido
- [ ] Packet Tracer montado, testes T1 a T15 executados e prints salvos
- [ ] Fontes de `02-pesquisa/fontes.md` verificadas
- [ ] Fluxogramas e diagramas renderizados e exportados
- [ ] Revisão por outro integrante de cada história e de cada capítulo
- [ ] Decisão sobre o código de retirada exibido na tela do porteiro

## 7. Entrega

- [ ] Versão final em `.docx` e `.pdf` guardada em `versoes/` (pasta fora do Git)
- [ ] PDF conferido página por página (margens, quebras, figuras no lugar, numeração)
- [ ] **Só o líder** faz a postagem e cadastra os demais integrantes
- [ ] Envio pelo **sistema de trabalhos acadêmicos da UNIP**, dentro do prazo (não vale e-mail, Dropbox ou envio atrasado; não enviar no prazo implica reprovação)
- [ ] Comprovante de envio guardado (print ou protocolo)
- [ ] **Cópia impressa entregue ao coordenador do PIM**, no prazo
- [ ] Todos os integrantes do grupo (até 6, mesmo curso e turma) conferidos na postagem

## 8. Repositório e apresentação (apoio, não é exigência de formatação)

- [ ] Repositório no GitHub criado, com link no trabalho se o grupo decidir citá-lo
- [ ] `make test` roda sem erro na máquina de apresentação
- [ ] Todos os integrantes sabem explicar o código, o banco e a topologia (regra 7 do `CLAUDE.md`)
- [ ] Roteiro da demonstração: registrar, ficar offline, sincronizar, rodar a central duas vezes, ver o mapa e os relatórios
