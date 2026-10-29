# Sprint 4: documento e entrega

**Datas:** 29/10/2026 a 06/11/2026 (retrospectiva por mensagem escrita na sexta, 06/11, 19h)
**Meta:** conferir o repositório contra a rastreabilidade, deixar os roteiros dos capítulos prontos e entregar o trabalho no prazo (capítulos redigidos pelo grupo, revisão ABNT, postagem pelo líder e cópia impressa).

## Entregas desta sprint (parte do repositório)

| Entrega | Situação |
|---|---|
| Revisão do repositório contra `00-projeto/rastreabilidade.md` | Feita (resultado abaixo) |
| Roteiro de cada capítulo em `documento-final/capitulos/` (`00-resumo.md` a `10-conclusao.md`) | Feito; **sem texto final**, que é do grupo |
| `documento-final/estrutura-e-paginas.md` (sumário, orçamento de páginas, lista de figuras e tabelas) | Feito |
| `documento-final/checklist-abnt-e-entrega.md` | Feito |
| `00-projeto/integrantes.md` e `00-projeto/cronograma.md` | Modelos criados; preenchimento é do grupo |
| `documento-final/referencias.md` | **Não criado** de propósito: só pode listar fontes verificadas e usadas |

## Resultado da revisão (2026-10-29)

**Conferência automática:** 87 caminhos citados na rastreabilidade conferidos; todos existem, exceto os arquivos do documento final que ainda estavam por criar (`referencias.md` continua sem existir e é do grupo). Status atual: 60 Feito, 13 Em andamento, 2 Pendente, 0 Revisado (75 linhas).

**O que falta por etapa**

| Etapa | Situação | O que falta (e quem faz) |
|---|---|---|
| 1 Organização | Arquivos prontos | Revisão por outro integrante; renderizar organograma e processos; redigir cap. 2 (grupo) |
| 2 Pesquisa | Em andamento (levantamento de campo dispensado em 2026-10-29) | Verificar fontes F01 a F05 e B01 a B13; fichas de fundamentação; trabalhos relacionados com fonte; redigir cap. 3 (grupo) |
| 3 Engenharia de software | Arquivos prontos | Integrantes e papéis do Scrum; datas e retrospectivas das sprints; revisão por pares; renderizar PlantUML; redigir cap. 4 (grupo) |
| 4 Banco de dados | Arquivos prontos e scripts executados em MySQL 8.4.13 | Confirmar SGBD e brModelo com o professor; renderizar o DER; print de consulta; redigir cap. 5 (grupo) |
| 5 Programação em C | Código, testes e A1 a A6 prontos | Revisão por pares do código; renderizar os fluxogramas; prints; decidir o código na tela do porteiro; US16 opcional; redigir cap. 6 (grupo) |
| 6 Redes | Documentação pronta; comandos **não executados** | **Montar o Packet Tracer, rodar T1 a T15, prints, `.pkt`**; cotar equipamentos; redigir cap. 7 (grupo) |
| 7 Segurança e acessibilidade | Roteiro pronto | Conferir leis nos textos oficiais; definir retenção; redigir cap. 8 (grupo) |
| 8 Integração | Roteiro pronto | "Antes" dos indicadores (depende da pesquisa); redigir cap. 9 e a conclusão (grupo) |
| Documento final | Roteiros e checklist prontos | Redigir tudo; referências ABNT; resumo e abstract; montar no modelo da UNIP; revisão de similaridade; postagem e cópia impressa |

## Pendências que bloqueiam outras (ordem sugerida)

1. Confirmar o **prazo** e preencher `integrantes.md` e `cronograma.md`.
2. **Verificar as fontes** e pesquisar os trabalhos relacionados (alimentam os capítulos 2, 3, 4 e 9).
3. **Montar o Packet Tracer** (alimenta o capítulo 7).
4. **Renderizar os diagramas** e tirar os prints do protótipo.
5. Revisão por pares do código e dos documentos técnicos.
6. Redigir os capítulos; depois introdução, conclusão, resumo e abstract.
7. Referências, revisão ABNT e de similaridade, postagem e impressão.

## Rascunhos e fontes (2026-10-29)

- **Rascunhos de todos os capítulos** (resumo, abstract, 1 a 10) escritos na seção "Texto do grupo" de `documento-final/capitulos/`, a partir dos roteiros e do repositório, com base na autorização de uso de IA informada pelo grupo. Marcas de pendência: figuras a inserir, prints, resultados do Packet Tracer, fontes ainda sem verificação, titulares do Scrum.
- **Fontes verificadas** por ferramenta de web (registro em `02-pesquisa/fontes.md`, seção 4): LGPD e LBI (textos oficiais), RFC 5737, Guia do Scrum 2020, WCAG 2.2, NIST SP 800-145 e FIPS 180-4 (existência), artigo F05, e dados bibliográficos dos livros B01 a B11 em catálogos. **Nenhum livro foi aberto**: o grupo precisa conferir os trechos. F02, F03 e F04 não puderam ser lidos.
- **`documento-final/referencias.md`** criado só com as fontes verificadas e citadas.
- **Tamanho:** o desenvolvimento está acima do limite (cerca de 11.350 palavras); plano de cortes em `documento-final/estrutura-e-paginas.md`, seção 8.
- **Quadros** numerados de 1 a 18 na ordem de aparição; as figuras seguem a numeração de `estrutura-e-paginas.md`.

## Decisões do grupo (2026-10-29)

| Tema | Decisão |
|---|---|
| Prazo | Sábado, 14/11/2026, até as 23h59 (sistema da UNIP) |
| Líder | Lucas Ribeiro Tomiossi Kribely |
| Product Owner e Scrum Master | Os dois papéis existem, de forma simplificada; titulares `[A DEFINIR]` (um deles fica com o solicitante) |
| Cerimônias | Revisão e retrospectiva por mensagem escrita no grupo, às sextas, 19h (sem reunião) |
| Levantamento de campo | Dispensado (não é obrigatório) |
| Código de retirada na tela do porteiro | Manter no protótipo e declarar a limitação |
| US16 (devolução) | Não implementar; fica como evolução futura |
| VPN IPsec | Só no diagrama, sem configurar no Packet Tracer |
| Idioma do abstract | Inglês |
| Retenção dos dados | 90 dias após a retirada; depois, anonimização |
| Dados do protótipo e dos indicadores | Dados simulados (fictícios), **sempre rotulados como simulação** no texto; nunca apresentados como dado medido nem como pesquisa |
| Modelo conceitual | Sem brModelo; SGBD MySQL 8 |
| Código no documento | Apenas o link do GitHub, sem apêndice; trechos curtos no capítulo 6 |
| Cópia impressa | Mesmo prazo da postagem (14/11/2026) |
| Integrantes | 5 (nomes e RA em `00-projeto/integrantes.md`); e-mail não registrado |
| Packet Tracer | Será feito, sem a VPN |

## Impedimentos e riscos

- Prazo oficial de entrega ainda não confirmado.
- Sem levantamento de campo (dispensado): o problema vem do cenário e da bibliografia, e os indicadores "antes" ficam como linha de base a medir no piloto. A comparação com trabalhos relacionados depende de fontes verificadas.
- Packet Tracer, Mermaid e PlantUML não estão instalados na máquina de desenvolvimento: nada disso foi renderizado ou executado lá.
- Risco de passar de 30 páginas com 16 figuras (ver `documento-final/estrutura-e-paginas.md`).
- Uso de IA: confirmar com o professor se a UNIP tem orientação; os capítulos são do grupo (regra 9 do `CLAUDE.md`).

## Retrospectiva (a preencher pelo grupo)

- O que funcionou:
- O que melhorar:
- Ações finais antes da entrega:
