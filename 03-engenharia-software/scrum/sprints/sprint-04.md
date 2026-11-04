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
- **Tamanho:** em 2026-11-03 os capítulos 2 a 9 foram reescritos de forma mais curta, sem tirar fatos nem números (cerca de 11.350 para 8.690 palavras; quadros renumerados de 1 a 7). Detalhes e cortes ainda possíveis em `documento-final/estrutura-e-paginas.md`, seção 8. A paginação real depende do Word.
- **Revisão de coerência (2026-11-03):** introdução, resumo, abstract e conclusão conferidos contra os capítulos 2 a 9 e contra o repositório (11 tabelas, 44 restrições, 12 RF e 8 RNF, 8 UC, 16 US, 9 conjuntos de testes, 44 redes, 15 testes T1 a T15, capacidades do `tipos.h`, dados do cenário e equipamentos da sede). Nenhuma divergência; uma marca de atualização acrescentada na introdução sobre o Packet Tracer.
- **Packet Tracer (2026-11-04):** laboratório montado e os **15 testes (T1 a T15) executados, todos como esperado** (resultados no capítulo 7, Quadro 6). **Concluído em 2026-11-04:** HTTP/HTTPS no `SRV-API`, Wi-Fi dos três laptops, prints da topologia, do T2 e do T6 (figuras 13 a 15) e `morada-central.pkt` no repositório. O segundo ping do T9 (CFTV → API não responde) foi confirmado pelo grupo em 2026-11-04.
- **Passe de conferência dos capítulos 4 a 6 (2026-11-04):** afirmações conferidas contra o código (menu, estante, código de retirada, tentativas, sincronização, consolidação, alerta de 7 dias), o banco (11 tabelas, 44 restrições, coluna gerada, hash, consultas, views e índices) e os documentos (UC, enums, ADR); demonstração reexecutada (17 operações, 14 encomendas, segunda execução sem nada novo). Nenhuma divergência; só foram acrescentadas datas aos valores que dependem do dia.
- **Prints do programa (2026-11-04):** mapa da estante (Figura 12) e resultado dos 9 testes (Figura 11, após repetir o `build.bat test` por causa do bloqueio intermitente do Device Guard). As figuras foram **renumeradas pela ordem de aparição** (DER = 8, fluxograma A1 = 9, A5 = 10, testes = 11, mapa = 12; 13 a 16 inalteradas).
- **Mudança no algoritmo A3 (2026-11-04), pedida pelo grupo:** a retirada passou a **achar a encomenda pelo código** (o porteiro não digita mais o id) e a pedir a **confirmação S/N** do porteiro com o morador; 3 códigos sem encomenda pendente negam, N cancela. Plano feito com o Opus e confirmado pelo grupo (só o fluxo novo, no lugar do antigo; 3 tentativas por atendimento; Figura 11 não refeita). Código: `codigo_localizar_pendente` (`codigo.c`), `encomenda_contar_pendentes` e `encomenda_mostrar_uma` (`encomenda.c`), `retirada.c` reescrito; testes novos em `test_codigo.c` e `test_encomenda.c` (continuam 9 conjuntos); documentos atualizados: pseudocódigo e fluxograma do A3 (PNG re-exportado), diagrama de atividade (só o fonte `.puml`), UC03, US04, README e capítulos 6, 8 e 9. **A Figura 11 (print dos testes) foi tirada antes desta mudança**: a saída é a mesma (9 linhas `OK`), mas o print é de uma versão anterior do código.
- **Quadros** numerados na ordem de aparição (renumerados de 1 a 8 após os cortes de 2026-11-03 e a inclusão do quadro de testes de rede); as figuras seguem a numeração de `estrutura-e-paginas.md`.

## Decisões do grupo (2026-10-29)

| Tema | Decisão |
|---|---|
| Prazo | Sábado, 14/11/2026, até as 23h59 (sistema da UNIP) |
| Líder | Lucas Ribeiro Tomiossi Kribely |
| Product Owner e Scrum Master | Os dois papéis existem, de forma simplificada; PO: Lucas Ribeiro Tomiossi Kribely; SM: Daniel Augusto Amarante da Silva (indicados em 2026-11-03); cenários de atuação dos papéis em `scrum/cenarios-po-e-sm.md` |
| Cerimônias | Revisão e retrospectiva por mensagem escrita no grupo, às sextas, 19h (sem reunião) |
| Levantamento de campo | Dispensado (não é obrigatório) |
| Código de retirada na tela do porteiro | Manter no protótipo e declarar a limitação |
| US16 (devolução) | Não implementar; fica como evolução futura |
| VPN IPsec | Só no diagrama, sem configurar no Packet Tracer |
| Idioma do abstract | Inglês |
| Retenção dos dados | 90 dias após a retirada; depois, anonimização |
| Demonstração do programa | Será feita no computador de Daniel, levado à apresentação; não é preciso rodar `make test` nas demais máquinas (informado em 2026-11-03) |
| Cenários do PO e do SM | Podem ser construídos pelo grupo; a Prof.ª Eliana autorizou (informado pelo grupo em 2026-11-03) |
| Dados do protótipo e dos indicadores | Dados simulados (fictícios), **sempre rotulados como simulação** no texto; nunca apresentados como dado medido nem como pesquisa |
| Modelo conceitual | Sem brModelo; SGBD MySQL 8 |
| Código no documento | Apenas o link do GitHub, sem apêndice; trechos curtos no capítulo 6 |
| Cópia impressa | Mesmo prazo da postagem (14/11/2026) |
| Integrantes | 5 (nomes e RA em `00-projeto/integrantes.md`); e-mail não registrado |
| Packet Tracer | Será feito, sem a VPN |

## Impedimentos e riscos

- Prazo oficial de entrega ainda não confirmado.
- Sem levantamento de campo (dispensado): o problema vem do cenário e da bibliografia, e os indicadores "antes" ficam como linha de base a medir no piloto. A comparação com trabalhos relacionados depende de fontes verificadas.
- Packet Tracer não está instalado: nada foi executado nele. Em 2026-10-31 os diagramas Mermaid foram renderizados em PNG (mermaid-cli 11.4.2, em ambiente de nuvem). O PlantUML **ainda não foi renderizado** (cinco `.puml`); o grupo exporta pela extensão do VS Code ou pelo site oficial, ou roda `plantuml -tpng` com o `.jar` e Graphviz.
- Risco de passar de 30 páginas com 16 figuras (ver `documento-final/estrutura-e-paginas.md`).
- Uso de IA: confirmar com o professor se a UNIP tem orientação; os capítulos são do grupo (regra 9 do `CLAUDE.md`).

## Retrospectiva (a preencher pelo grupo)

- O que funcionou:
- O que melhorar:
- Ações finais antes da entrega:
