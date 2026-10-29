# ADR-002: Dados do protótipo em CSV separado por `;`

**Status:** aceita

## Contexto

Cada portaria precisa guardar localmente seus dados para funcionar sem internet (RNF01). O protótipo é em C99, só com biblioteca padrão, e precisa ser compreendido e explicado pelo grupo e pelo professor.

## Decisão

O protótipo guarda os dados em **arquivos de texto CSV separados por `;`**, em ASCII, com cabeçalho na primeira linha e datas no formato `AAAA-MM-DD HH:MM`. Campos de texto não aceitam `;`.

## Alternativas consideradas

| Alternativa | Avaliação |
|---|---|
| Arquivos binários (`fwrite` de structs) | Compactos, mas ilegíveis para o professor e frágeis a mudanças nas structs |
| Banco embutido (ex.: SQLite) | Exige biblioteca externa, proibida pelas regras do projeto |
| Ligação direta com o MySQL | Fora do escopo do protótipo (`PLANO.md`, seção 5.3) |

## Justificativa

- Simula o armazenamento local de que a portaria precisa para operar offline.
- É legível a olho nu, o que facilita depuração e demonstração.
- Exercita leitura linha a linha e manipulação de arquivos, exigidos na Etapa 5.

## Consequências

- Leitura e gravação concentradas no módulo `persistencia`.
- A matriz da estante não tem arquivo próprio: é reconstruída a partir das encomendas pendentes ao abrir o programa, mantendo uma única fonte de verdade.
- O código de retirada fica em texto no protótipo (no banco central, seria hash). Isso entra como limitação na Etapa 8.
