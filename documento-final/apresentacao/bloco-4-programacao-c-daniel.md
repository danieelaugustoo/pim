# Bloco 4: Programação em C e demonstração (Daniel)

Tempo: **cerca de 7 minutos**: uns 3 de fala e 4 de demonstração. Figura: **8** (fluxograma do A1). Passo a passo da tela em `roteiro-demonstracao.md`. Só use números que estão no trabalho.

## Roteiro de fala (3 min)

**1. O que é o protótipo (40 s).** "São dois programas em C. O `portaria` é o nó de uma portaria: tem um menu para registrar encomenda e retirada, listar pendências, ver o mapa da estante, cadastrar moradores, gerar relatórios e sincronizar. O `central` lê o que as portarias enviaram, aplica cada operação uma vez e gera o relatório consolidado. O código completo está no GitHub."

**2. Padrões (40 s).** "Seguimos o C99, só com a biblioteca padrão, e compila sem nenhum aviso com `-Wall -Wextra -pedantic`. A programação é estruturada: funções pequenas, com o nome do módulo no prefixo, como `estante_alocar_posicao`; vetores e matrizes estáticos, com os tamanhos em constantes; e o `main` só tem o menu e as chamadas. A entrada do teclado usa `fgets` com validação, e todas as funções têm comentário com objetivo, parâmetros, retorno e lógica."

**3. Estruturas de dados (40 s).** "Os dados ficam em vetores: até 500 encomendas e 300 moradores por portaria. A estante é uma **matriz 4 por 12**: cada linha é a estante de um bloco, de A a D, cada coluna é uma prateleira, e a célula guarda o id da encomenda ou zero. As prateleiras 10 e 11 são para volumes grandes. A matriz não é gravada: ao abrir o programa ela é reconstruída a partir das encomendas pendentes. Os dados persistem em arquivos CSV." 

**4. Três algoritmos (1 min).** "O **A1** aloca a posição: começa pela estante do bloco da unidade, procura a primeira prateleira livre da faixa do tamanho do volume e, se a estante estiver cheia, tenta as outras em ordem circular. *(Figura 8)* O **A3**, a retirada, é pelo código: o porteiro digita o código, o programa acha a encomenda pendente, mostra unidade e destinatário e o porteiro confirma com o morador; são até 3 tentativas. O **A5**, na central, é a consolidação idempotente: para cada operação, confere se o id já foi aplicado; se foi, ignora."

**5. Testes (20 s).** "São 9 conjuntos de testes automatizados, todos passando. Um deles processa o mesmo arquivo duas vezes e confirma que nada é duplicado. Agora vou mostrar funcionando." → seguir o `roteiro-demonstracao.md`.

## Funções que você precisa saber explicar

| Função | O que faz |
|---|---|
| `estante_alocar_posicao` (A1) | Calcula a estante preferida pelo bloco, escolhe a faixa de prateleiras pelo tamanho (G usa 10 e 11) e varre as estantes em ordem circular até achar uma célula com zero. Se não achar, informa que não há vaga. |
| `retirada_registrar` (A3) | Se não há pendentes, avisa. Senão, busca o código (3 tentativas), mostra a encomenda, pede S/N e, se for S, pede o nome de quem retira e registra. |
| `codigo_localizar_pendente` | Conta as pendentes com aquele código. Zero devolve "não encontrado" (-1) e mais de uma devolve "duplicado" (-2). |
| `consolidacao_processar_portaria` (A5) | Para cada operação do log, se o id já está nos aplicados, ignora; senão, aplica e anota o id. Operação impossível, como retirar uma encomenda desconhecida, é rejeitada sem ser anotada. |

## O que NÃO dizer (o trabalho declara como limite)

- O código de retirada **fica em texto** nos arquivos e **aparece na tela** ao registrar: é limitação declarada.
- O aviso ao morador e a rede são **simulados** (tela e arquivos).
- **Não há** interface gráfica, login nem perfis; a **devolução** de volumes não foi implementada.
- A capacidade é fixa (500 e 300) e os arquivos são reescritos por inteiro.
- Compilado no Windows e também testado em Linux com `gcc`.

## Perguntas de C que podem cair

| Pergunta | Resposta |
|---|---|
| Por que `fgets` e não `scanf`? | `fgets` lê a linha inteira com limite de tamanho, evitando estouro de buffer, e depois convertemos e validamos. |
| Por que vetores estáticos? | O manual pede vetores e matrizes; os tamanhos ficam em constantes em `tipos.h`, então mudar a capacidade é mudar uma constante. |
| Como a estante sabe o que está ocupado? | Ao abrir, o programa percorre as encomendas pendentes e preenche a matriz. Assim há uma única fonte de verdade. |
| O que acontece se a estante estiver cheia? | O A1 tenta as outras estantes em ordem circular. Se todas estiverem cheias, a encomenda não é registrada e o porteiro é avisado. |
| E se dois códigos forem iguais? | O sorteio se repete até o número não existir em outra pendente (limite de 1000 tentativas). Um código errado digitado pode coincidir com outra encomenda (cerca de 1 em 9.000 com 100 pendentes), por isso há confirmação. |
| O que significa idempotente? | Aplicar a mesma operação várias vezes dá o mesmo resultado que aplicar uma. A central anota os ids aplicados. |
| Como testaram? | Com `assert.h`: 9 conjuntos (`make test` ou `build.bat test`), incluindo consolidar o mesmo arquivo duas vezes. A parte interativa da retirada foi conferida na execução manual. |
| Por que os textos do programa não têm acento? | Regra do projeto: ASCII nos textos do programa e dos arquivos, para evitar problema de codificação no console. |
| Quais bibliotecas usaram? | Só a padrão: `stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `time.h` e `assert.h`. |
| Como compilar? | `make` (ou `.\build.bat` no Windows) dentro de `05-programa-c`. |
