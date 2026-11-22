# Guia de estudo do Daniel: Programação em C e demonstração

Apresentação do PIM II na quarta-feira, 25/11. A ordem é Ysaac, Adilson, Lucas, **você** e Pedro. O seu bloco tem cerca de **7 minutos**, e o centro dele é **mostrar o programa funcionando** para quem estiver assistindo. As bibliotecas e as boas práticas entram como comentários curtos durante a demonstração. Você não abre o código; se pedirem para ver, todas as 116 funções têm um comentário no topo dizendo o que fazem.

Todas as cenas da parte 3 foram executadas em 22/11, na ordem do guia, e as saídas batem com o que está escrito aqui.

## Plano de estudo até quarta

| Quando | O que fazer | Tempo |
|---|---|---|
| Domingo | Ler as partes 1 a 4: o seu bloco, a preparação e a demonstração cena por cena. | 40 min |
| Segunda | Preparar o notebook (parte 2) e fazer a demonstração inteira **3 vezes**, falando em voz alta e cronometrando. Ler as partes 5 a 7. | 2 h |
| Terça | Mais 2 demonstrações completas, uma delas para alguém assistir. Ensaiar com o grupo, se der. Ler as partes 10 e 11. | 2 h |
| Quarta | Preparar a demonstração 10 minutos antes (parte 2) e reler a cola (parte 13). | 30 min |

Treinar a demonstração com as mãos no teclado vale mais do que qualquer leitura.

---

## 1. O seu bloco em 7 minutos

| Momento | Tempo | Na tela |
|---|---|---|
| Abertura | 45 s | Slide 8 (Programação estruturada em C) |
| Programa funcionando (parte 3) | 5 min | Os terminais, um por vez, em tela cheia |
| Fechamento e passagem para o Pedro | 20 s | O relatório aberto ou o slide 9 |

**Abertura (slide 8).** "Eu fiquei com a programação em C, e em vez de mostrar código, vou mostrar o programa funcionando. São dois programas: a **portaria**, que o porteiro usa no lugar do caderno, e a **central**, que fica na administradora e junta tudo. Foram feitos em C99, só com a biblioteca padrão da linguagem, então rodam no Windows e no Linux sem instalar nada. O código tem 11 módulos, todas as funções são comentadas, toda entrada do teclado é validada, e há 9 conjuntos de testes automáticos, todos passando. Vamos ver na prática."

**Fechamento.** "Então é isso: o programa registra a encomenda, indica a prateleira, avisa o morador, continua funcionando sem internet, sincroniza sem duplicar e só entrega com o código certo. Agora o Pedro vai falar da rede e da conclusão."

---

## 2. Preparação do notebook

### Segunda (uma vez só)

Baixe o projeto numa pasta nova, para ter a versão atual do GitHub sem misturar com cópias antigas, e compile:

```
git clone https://github.com/danieelaugustoo/pim.git pim-apresentacao
cd pim-apresentacao\05-programa-c
.\build.bat
.\build.bat test
```

Os testes precisam terminar com "Todos os testes passaram." Se o Windows bloquear o `.exe` recém-compilado, repita o comando; não mexa em configuração de segurança. Use essa mesma pasta em todos os ensaios e no dia.

### Antes de cada ensaio e 10 minutos antes da apresentação

Dentro de `05-programa-c`, no PowerShell, limpe os dados e copie os de exemplo. Isso faz o programa voltar sempre ao mesmo ponto de partida:

```
Remove-Item dados\portarias\*.csv, dados\portarias\*.txt -ea SilentlyContinue
Remove-Item dados\rede\*.log, dados\central\*.csv, dados\central\*.txt -ea SilentlyContinue
Copy-Item dados\exemplo\P01-*.* dados\portarias\
Copy-Item dados\exemplo\P0?.log dados\rede\
```

### Na hora de começar

- Abra **dois terminais** na pasta `05-programa-c`: o **terminal 1** é a portaria e o **terminal 2** é a central.
- Deixe cada terminal em **tela cheia** e troque entre eles com **Alt + Tab**. Lado a lado, as tabelas quebram de linha e ficam difíceis de ler.
- Aumente a fonte (Ctrl + roda do mouse) até dar para ler do fundo da sala.
- Desligue as notificações, deixe o notebook na tomada e tenha papel e caneta para anotar o código de retirada.
- Deixe o deck aberto no slide 12 (reserva), escondido atrás dos terminais.

---

## 3. A demonstração, cena por cena

A demonstração conta uma história: o porteiro trabalha, a internet cai, chegam encomendas, a internet volta, a administradora recebe tudo sem duplicar, o morador busca a encomenda e a administradora vê o relatório. Em cada cena: **Faça** é o que você digita, **Aparece** é o que a turma vê, **Diga** é a frase para o público, e **Para citar** é o comentário técnico, se der tempo.

### Cena 1. A tela do porteiro (30 s)

- **Faça:** terminal 1, `.\bin\portaria.exe 1`. Opção `3` e depois opção `5`.
- **Aparece:** a lista com 6 encomendas pendentes e o mapa da estante, com `Ocupadas: 6 de 48 (12.5%)`.
- **Diga:** "Esta é a tela do porteiro do condomínio 1. Já há 6 encomendas guardadas. O mapa mostra a estante: cada linha é a estante de um bloco, e cada coluna, uma prateleira. X é ocupado, ponto é livre."
- **Para citar:** a estante é uma matriz de 4 por 12. A lista não mostra o código de retirada, para proteger o morador.

### Cena 2. A internet cai (10 s)

- **Faça:** opção `9`.
- **Aparece:** `Portaria agora OFFLINE.`, e o menu passa a mostrar `[OFFLINE]`.
- **Diga:** "Vou simular que a internet do condomínio caiu. O porteiro continua trabalhando normalmente."

### Cena 3. Chega uma encomenda (50 s)

- **Faça:** opção `1`. Bloco `D`. No apartamento, digite **`abc` de propósito**, e depois `7`. Destinatário `Rafael Costa`, transportadora `Transp Alfa`, tamanho `M`.
- **Aparece:** primeiro `Valor invalido. Digite um numero entre 1 e 9999.` Depois `Encomenda 9 registrada para D-7.`, `Guardar na estante D, prateleira 0.`, `Codigo de retirada:` com 6 dígitos e `Aviso: ligar pelo interfone para D-7 (Rafael Costa).`, com o código para impressão.
- **Diga:** "Se o porteiro digitar errado, o programa não aceita e pergunta de novo. Com os dados certos, ele diz em que prateleira guardar, gera um código de 6 dígitos e avisa o morador. Esse morador escolheu o interfone, então o porteiro liga e entrega o código impresso."
- **Para citar:** a leitura usa `fgets` com validação (`stdio.h` e `ctype.h`). A prateleira é escolhida pelo bloco (algoritmo A1), o código é sorteado com `rand` (`stdlib.h`, algoritmo A2), e a data e a hora vêm do `time.h`.
- **Anote o código** no papel.

### Cena 4. Outra encomenda, outro canal (25 s)

- **Faça:** opção `1`. `D`, `15`, `Beatriz Alves`, `Transp Gama`, `P`.
- **Aparece:** `Encomenda 10 registrada para D-15.`, `Guardar na estante D, prateleira 1.` e `Aviso simulado por SMS para 11900000007`.
- **Diga:** "Essa moradora escolheu SMS. O volume foi para a prateleira seguinte, porque a primeira já está ocupada."
- **Para citar:** o aviso é simulado na tela e fica registrado em arquivo.

### Cena 5. Nada se perde sem internet (15 s)

- **Faça:** opção `8`.
- **Aparece:** `Portaria OFFLINE: 2 operacao(oes) aguardando envio.`
- **Diga:** "Sem internet, os dois registros ficam numa fila, esperando a conexão voltar."
- **Para citar:** a fila é um arquivo, então não se perde nem se o computador desligar.

### Cena 6. A internet volta (15 s)

- **Faça:** opção `9` e depois opção `8`.
- **Aparece:** `Portaria agora ONLINE.` e `2 operacao(oes) enviada(s) para dados/rede/P01.log.`
- **Diga:** "A internet voltou, e a fila foi enviada para a administradora."
- **Para citar:** algoritmo A4. A fila só é apagada depois de copiada.

### Cena 7. A administradora recebe (25 s)

- **Faça:** Alt + Tab para o terminal 2, `.\bin\central.exe`.
- **Aparece:** `P01: 12 lida(s), 12 aplicada(s)`, `P02: 7 lida(s), 7 aplicada(s)` e `Total consolidado: 19 operacao(oes), 16 encomenda(s).`
- **Diga:** "Esta é a central da administradora. Ela juntou o condomínio 1, com as duas encomendas que acabamos de registrar, e o condomínio 2: 16 encomendas no total."
- **Para citar:** cada operação tem um número único, como `P01-000011`.

### Cena 8. Não duplica (20 s)

- **Faça:** `.\bin\central.exe` de novo.
- **Aparece:** `0 aplicada(s), 12 ja aplicada(s)` e `0 aplicada(s), 7 ja aplicada(s)`. O total continua `19 operacao(oes), 16 encomenda(s).`
- **Diga:** "Se a mesma informação chegar duas vezes, por exemplo depois de uma falha de conexão, a central reconhece e não duplica nada."
- **Para citar:** consolidação idempotente (algoritmo A5): a central anota os números já aplicados e ignora os repetidos.

### Cena 9. O morador vem buscar (60 s)

- **Faça:** Alt + Tab para o terminal 1, opção `2`. Digite um código errado, `123456`. Depois digite o código certo, responda `S` e informe `Rafael Costa`. Em seguida, opção `5`.
- **Aparece:** `Nenhuma encomenda pendente com esse codigo (tentativa 1 de 3).` Depois a ficha `9 D-7 Rafael Costa` com a pergunta S/N, e então `Retirada registrada: encomenda 9, em <data e hora>, por Rafael Costa.` No mapa, a prateleira 0 da estante D volta a ficar livre.
- **Diga:** "O morador informa o código. Se errar, tem até 3 tentativas. Com o código certo, o programa mostra de quem é a encomenda, o porteiro confere com o morador e confirma. Fica registrado quem retirou e quando, e a prateleira volta a ficar livre."
- **Para citar:** algoritmo A3. A confirmação evita entregar o volume de outra pessoa; se o porteiro responder `N`, nada muda.

### Cena 10. A retirada chega à administradora (20 s)

- **Faça:** opção `8`. Alt + Tab para o terminal 2, `.\bin\central.exe`.
- **Aparece:** `1 operacao(oes) enviada(s)` e, na central, `P01: 13 lida(s), 1 aplicada(s), 12 ja aplicada(s)` e `Total consolidado: 20 operacao(oes), 16 encomenda(s).`
- **Diga:** "A retirada também chegou à administradora, e só ela foi aplicada."

### Cena 11. O relatório da administradora (30 s)

- **Faça:** `notepad dados\central\relatorio-consolidado.txt`.
- **Aparece:** a tabela por portaria, com REGISTRADAS, PENDENTES, RETIRADAS, DEVOLVIDAS, ANTIGAS e PICO.
- **Diga:** "Este é o relatório que a administradora vê de todos os condomínios: quantas encomendas chegaram, quantas ainda estão na portaria, quantas foram retiradas e quantas estão paradas há mais de 7 dias."
- **Para citar:** algoritmo A6. A coluna ANTIGAS é calculada com a data de hoje.

Depois da cena 11, vá para o fechamento (parte 1).

---

## 4. Versão curta e imprevistos

**Versão curta (cerca de 3 minutos), se o tempo apertar:** faça as cenas 2, 3, 5, 6, 7, 8, 9 (sem o mapa no fim) e 11. Sem a cena 4, a central mostra números um pouco menores (uma encomenda a menos), e está tudo certo.

**O que muda no dia:**

- O código de retirada é sorteado: leia o que aparecer na tela e anote.
- A coluna ANTIGAS depende da data. Em 22/11 deu 6 na P01 e 5 na P02. No trabalho (Quadro 2) aparecem 2 e 0 porque o relatório foi gerado em 29/10. Se perguntarem, diga: "o relatório depende da data de hoje".
- O PICO da P01 vai ser o próprio dia da apresentação, com 2 registros.

**Se algo der errado:**

- `.exe` bloqueado pelo Windows: repita o comando uma vez.
- "ERRO: nao foi possivel abrir os arquivos": o terminal não está na pasta `05-programa-c`.
- Digitou algo inválido sem querer: o programa pergunta de novo. Siga em frente e aproveite para dizer que a entrada é validada.
- Esqueceu o código: na opção `3` ele não aparece, mas o aviso da cena 3 mostrou o código para impressão; role o terminal para cima.
- Travou de vez: vá para o slide 12 (reserva), que mostra a saída do programa, e explique o fluxo pela Figura 5 (diagrama de sequência).
- Para recomeçar do zero, repita os comandos de "Antes de cada ensaio".

---

## 5. O que o programa faz

### Portaria (`portaria.exe 1` abre a portaria P01)

| Opção | O que faz |
|---|---|
| 1. Registrar encomenda | Pergunta bloco, apartamento, destinatário, transportadora e tamanho (P, M ou G). Diz em que estante e prateleira guardar, gera o código de retirada de 6 dígitos e avisa o morador pelo canal dele. |
| 2. Registrar retirada | Pede o código (até 3 tentativas), mostra a encomenda e pergunta se o porteiro confirmou com o morador (S/N). Com S, registra o nome de quem retirou, a data e a hora e libera a prateleira. |
| 3. Listar pendentes | Mostra as encomendas que ainda estão na portaria, sem mostrar o código. |
| 4. Buscar por unidade | Mostra as pendentes de um apartamento. |
| 5. Mapa da estante | Desenha a estante (X ocupado, ponto livre) e mostra a ocupação, como "6 de 48 (12.5%)". |
| 6. Moradores | Cadastra o morador com o canal de aviso (app, SMS ou interfone) e lista os cadastrados. |
| 7. Relatórios | Pendências com mais de 7 dias, dia com mais registros num mês e ocupação por estante. |
| 8. Sincronizar | Offline, mostra quantas operações estão esperando. Online, envia a fila para a central. |
| 9. Online/offline | Simula a internet caindo ou voltando. |
| 0. Sair | Fecha a portaria. Os dados já estão gravados nos arquivos. |

### Central (`central.exe`)

Não tem menu. Lê os arquivos que as portarias enviaram, aplica cada operação uma única vez e mostra, para cada portaria, quantas operações leu, aplicou e já tinha aplicado. No fim, grava o relatório consolidado: por portaria, quantas encomendas foram registradas, estão pendentes, foram retiradas ou devolvidas, quantas estão há mais de 7 dias e qual foi o dia de pico.

### Regras que o programa segue

- O código de retirada tem 6 dígitos, é sorteado e não se repete entre as encomendas pendentes.
- Na retirada, são até 3 tentativas de código, e o porteiro confirma unidade e nome antes de entregar.
- A estante é escolhida pelo bloco (A a D) e, se estiver cheia, o programa tenta as outras. Volume G vai para as prateleiras 10 e 11.
- Pendência antiga é a que está há mais de 7 dias.
- O SMS exige um celular com 10 ou 11 dígitos; o interfone não precisa de contato e mostra o código para imprimir.
- Sem internet, o programa continua funcionando, e as operações esperam na fila até a conexão voltar.
- Os textos não aceitam acento nem ponto e vírgula, que é o separador dos arquivos.

---

## 6. As bibliotecas que o programa usa

Em C, uma biblioteca é um conjunto de funções prontas, incluído com `#include <nome.h>`. O programa usa **só a biblioteca padrão**, que vem com qualquer compilador C. Por isso nada foi instalado, e o mesmo código compila no Windows e no Linux. Bibliotecas como `conio.h` e `windows.h` ficaram de fora porque só existem no Windows.

| Biblioteca | Para que serve | O que usamos dela |
|---|---|---|
| `stdio.h` | Entrada e saída: tela, teclado e arquivos | `printf` (escrever na tela), `fgets` (ler uma linha do teclado ou de um arquivo), `fopen`, `fclose` e `fprintf` (abrir, fechar e gravar os arquivos), `snprintf` (montar texto com limite de tamanho) |
| `stdlib.h` | Utilidades gerais | `rand` e `srand` (sortear o código de retirada) |
| `string.h` | Texto | `strlen` (tamanho), `strcmp` (comparar), `strchr` (procurar uma letra), `memset` (zerar uma ficha) |
| `ctype.h` | Classificar caracteres | `isdigit` (é número?), `isalpha` (é letra?), `isspace` (é espaço?), `toupper` (passar para maiúscula) |
| `time.h` | Data e hora | `time` (hora atual), `localtime` e `strftime` (formatar como `2026-11-25 14:30`) |
| `assert.h` | Testes | `assert(condição)`: se a condição for falsa, o teste para e mostra onde falhou |

---

## 7. Boas práticas que você pode citar

| Prática | Por que |
|---|---|
| C99 e só a biblioteca padrão | Compila em qualquer sistema com `gcc`, sem instalar nada |
| Zero avisos com `-Wall -Wextra -pedantic` | Com os avisos ligados, o compilador aponta erros cedo |
| 11 módulos, um por assunto | Cada arquivo tem uma responsabilidade, o que facilita achar e testar |
| Nome do módulo no início da função | Pelo nome se sabe onde a função está (`estante_alocar_posicao` fica em `estante.c`) |
| Comentário em toda função | Objetivo, parâmetros, retorno e lógica: dá para entender a função sem ler o código |
| Constantes no lugar de números soltos | A capacidade (500, 300, 4 x 12) fica em `tipos.h`; para mudar, muda-se uma linha |
| Vetores e matriz de tamanho fixo, sem `malloc` | Pedido da disciplina; a memória fica previsível e não há vazamento |
| Leitura com `fgets` e validação | Lê com limite de tamanho e, se o valor for inválido, pergunta de novo |
| Nunca `scanf("%s")` | Ele não sabe o tamanho do destino e pode estourar a memória |
| Cópia de texto com `snprintf` | Respeita o tamanho do destino |
| Conferir erro ao abrir e gravar arquivos | Se der erro, o programa avisa e não perde a fila |
| Uma única fonte de verdade | A estante não é gravada; é remontada a partir das encomendas pendentes ao abrir |
| Textos em ASCII, sem acento | Evita letras quebradas no console do Windows |
| Testes automatizados | 9 conjuntos com `assert`, rodados com um comando (`build.bat test`) |

---

## 8. O que cada função faz (as principais)

O código tem 116 funções, todas com um comentário no topo. Estas são as que explicam o funcionamento. O começo do nome mostra o módulo: `estante_` fica em `estante.c`, `codigo_` em `codigo.c`, e assim por diante.

### Os dois programas

| Função | O que faz |
|---|---|
| `main` (portaria) | Abre a portaria escolhida, carrega os arquivos, remonta a estante e repete o menu até o porteiro sair |
| `portaria_executar` | Executa a opção escolhida no menu |
| `portaria_apos_registro` | Depois de um registro, grava o arquivo, põe a operação na fila e avisa o morador |
| `portaria_sincronizar` | Opção 8: envia a fila ou mostra quantas operações esperam |
| `portaria_alternar_modo` | Opção 9: simula a internet caindo ou voltando |
| `main` (central) | Carrega o que já foi aplicado, processa os arquivos das portarias e grava o resultado e o relatório |
| `central_processar_logs` | Lê o arquivo de cada portaria, de P01 a P10, e mostra quantas operações aplicou |

### Encomenda, estante e código

| Função | O que faz |
|---|---|
| `encomenda_registrar` | Pergunta os dados da encomenda e mostra a posição e o código |
| `encomenda_criar` | Aplica as regras do registro: número da encomenda, prateleira, código, data e status pendente |
| `encomenda_listar_pendentes` | Lista as encomendas pendentes (opção 3) |
| `encomenda_buscar_por_unidade` | Lista as pendentes de um apartamento (opção 4) |
| `estante_alocar_posicao` (A1) | Escolhe a prateleira onde guardar o volume |
| `estante_liberar_posicao` | Libera a prateleira depois da retirada |
| `estante_reconstruir` | Remonta a estante ao abrir o programa, a partir das encomendas pendentes |
| `codigo_gerar_unico` (A2) | Sorteia um código de 6 dígitos que nenhuma pendente usa |
| `codigo_localizar_pendente` | Acha a encomenda pendente pelo código digitado |

### Retirada, moradores e aviso

| Função | O que faz |
|---|---|
| `retirada_registrar` (A3) | Faz a retirada: pede o código, mostra a encomenda, pede a confirmação e o nome de quem retira |
| `retirada_efetuar` | Marca a encomenda como retirada, grava data, hora e nome e libera a prateleira |
| `morador_cadastrar` | Cadastra o morador com o canal de aviso preferido |
| `morador_contato_valido` | Confere se o contato serve para o canal (SMS exige celular com 10 ou 11 dígitos) |
| `morador_localizar_para_aviso` | Escolhe quem avisar: o morador com o nome da etiqueta ou, se não houver, o primeiro da unidade |
| `aviso_enviar` | Simula o aviso: mensagem por app ou SMS, ou orientação para ligar pelo interfone com o código impresso |

### Arquivos e sincronização

| Função | O que faz |
|---|---|
| `persistencia_carregar_encomendas` e `persistencia_salvar_encomendas` | Leem e gravam as encomendas no arquivo CSV |
| `persistencia_carregar_moradores` e `persistencia_salvar_moradores` | O mesmo para os moradores |
| `sincronizacao_registrar_operacao` | Guarda na fila a operação (registro ou retirada), com número único, como `P01-000011` |
| `sincronizacao_proximo_numero` | Gera o número da próxima operação, que nunca se repete, nem depois de fechar o programa |
| `sincronizacao_enviar_pendentes` (A4) | Copia a fila para a rede simulada e só depois esvazia a fila |

### Central

| Função | O que faz |
|---|---|
| `consolidacao_carregar_estado` | Recupera o que a central já aplicou nas execuções anteriores |
| `consolidacao_processar_portaria` (A5) | Lê o arquivo de uma portaria e aplica só as operações novas |
| `consolidacao_aplicar_operacao` | Aplica uma operação uma única vez; se o número já foi aplicado, ignora |
| `consolidacao_salvar_estado` | Grava o estado da central nos arquivos |
| `consolidacao_gerar_relatorio` | Grava o relatório por portaria |

### Relatórios (A6) e leitura do teclado

| Função | O que faz |
|---|---|
| `relatorio_mapa_estante` | Mostra o mapa da estante e a ocupação (opção 5) |
| `relatorio_menu` | Submenu de relatórios (opção 7) |
| `relatorio_pendencias_antigas` | Lista as pendentes há mais de 7 dias |
| `relatorio_pico_mensal` | Mostra os registros por dia de um mês e o dia de pico |
| `util_ler_linha` | Lê uma linha do teclado com `fgets`, sem estourar a memória |
| `util_ler_inteiro`, `util_ler_texto` e `util_ler_letra` | Leem número, texto e letra; se estiver errado, perguntam de novo |
| `util_data_hora_atual` | Pega a data e a hora do relógio |
| `util_dias_entre` | Calcula quantos dias separam duas datas (usado nas pendências antigas) |

---

## 9. Palavras técnicas em linguagem simples

Use a explicação da direita na primeira vez que disser a palavra.

| Termo | Como explicar |
|---|---|
| Compilar | Traduzir o código para um programa que o computador executa (o `.exe`). Quem faz isso é o compilador, o `gcc`. |
| C99 | A versão da linguagem C padronizada em 1999. |
| Aviso do compilador | O compilador dizendo "isso parece errado", mesmo quando o programa compila. |
| Biblioteca padrão | A caixa de ferramentas que já vem com a linguagem. |
| Módulo | Um arquivo de código que cuida de um assunto, como a estante. |
| Função | Um pedaço de código com nome que faz uma tarefa. |
| Vetor | Uma fileira de fichas do mesmo tipo, como as 500 encomendas. |
| Matriz | Um vetor com linhas e colunas, como uma planilha: a estante 4 x 12. |
| Programação estruturada | Programar com sequência, decisão e repetição, dividindo o problema em funções pequenas. |
| CSV | Uma planilha em texto: cada linha é um registro, e os campos são separados por ponto e vírgula. |
| Fila de sincronização | Como a caixa de saída do e-mail: as operações esperam até a internet voltar. |
| Idempotente | Fazer a mesma coisa duas vezes dá o mesmo resultado que fazer uma vez, como apertar duas vezes o botão do elevador. |
| Teste automatizado | Um programa que confere o nosso programa sozinho e avisa onde falhou. |
| Estouro de buffer | Escrever mais texto do que cabe na variável. O `fgets` com tamanho evita isso. |

---

## 10. O resto do trabalho: o mínimo que você precisa saber

### 10.1 Organização e pesquisa (Ysaac)

**Em uma frase:** as portarias da Administradora Morada Central controlam as encomendas num caderno, o que gera extravios, entregas à pessoa errada e sobrecarga dos porteiros, e a proposta é um nó em cada portaria que funciona sem internet e uma central que consolida sem duplicar.

- **Números:** 10 condomínios (de 2 a 4 blocos cada), cerca de 960 unidades e 40 porteiros (4 por condomínio, em escala 12x36). Sete problemas: extravio e entrega errada, falta de rastreabilidade, tempo do porteiro, aviso falho, acúmulo de volumes, falta de dados para a sede e internet instável.
- **Pergunta de pesquisa:** como uma solução computacional com operação offline e sincronização central pode reduzir extravios, entregas incorretas e o tempo que os porteiros gastam com encomendas?
- **Termos:** pesquisa **aplicada** (resolve um problema prático), **exploratória** (organiza um problema pouco estudado) e **qualitativa** (analisa sem medir em números).
- **O que já existe:** aplicativos de condomínio (como o ALL Condo, com fotos e QR code), armários inteligentes e portaria remota. As páginas consultadas não informam operação sem internet nem consolidação de vários condomínios.
- **Cuidado:** não houve levantamento de campo. Não diga que os concorrentes não têm algo; diga que as páginas não informam. Fale em "dados de exemplo".

### 10.2 Engenharia de software (Adilson) e o seu papel

**Em uma frase:** os requisitos viraram casos de uso, histórias e diagramas UML, e a decisão principal foi a sincronização assíncrona com operações de número único (ADR-003), que é o que a fila da portaria e a central fazem.

- **Números:** 12 requisitos funcionais, 8 não funcionais, 8 casos de uso, 16 histórias de usuário (15 feitas; a US16, devolução de volumes, ficou para o futuro) e 6 decisões de arquitetura (ADR).

| Termo | Como explicar |
|---|---|
| Requisito funcional | O que o sistema faz, como registrar a encomenda (RF01) |
| Requisito não funcional | Como o sistema deve ser: funcionar sem internet, proteger os dados, ser acessível |
| Caso de uso | Uma interação de um ator com o sistema. Atores: porteiro, morador, supervisor, a central e o serviço de avisos |
| História de usuário | "Como porteiro, quero..., para...", com critérios de aceitação no formato Dado, Quando, Então |
| UML | Linguagem padrão de diagramas. Usamos casos de uso, sequência, classes, atividade e estados |
| ADR | Registro de uma decisão com o motivo: 001 banco relacional, 002 CSV no protótipo, 003 sincronização assíncrona, 004 Scrum, 005 diagramas como código, 006 endereçamento IP |
| Scrum | Trabalho em ciclos curtos (sprints), com backlog priorizado, revisão e retrospectiva no fim de cada ciclo |
| Definição de pronto | Compila sem avisos, testes passam, funções comentadas, critérios atendidos e revisão por outro integrante |

**Você é o Scrum Master** (o Lucas é o Product Owner). O Scrum Master facilita as cerimônias e remove impedimentos. Quem decide a prioridade é o Product Owner, e o conteúdo técnico é do time. No projeto, a revisão e a retrospectiva saíram por mensagem escrita no grupo, às sextas, às 19h. Na sprint 5, você fechou introdução, conclusão e resumo e conferiu o limite de páginas, coordenando os cortes.

**Cuidado:** as sprints 0 a 3 rodaram num ciclo único em 29/10 (datas do histórico do Git). Os requisitos vieram do cenário, e não de entrevistas.

### 10.3 Banco de dados (Lucas)

**Em uma frase:** o banco fica no servidor central, em MySQL 8, com 11 tabelas e 44 restrições, normalizado até a 3ª forma normal, e o programa em C usa arquivos CSV e não se conecta a ele (ADR-002).

| Termo | Como explicar |
|---|---|
| Banco relacional | Dados em tabelas ligadas por chaves |
| Chave primária (PK) | Identifica cada linha e não se repete, como o CPF da linha |
| Chave estrangeira (FK) | Aponta para uma linha de outra tabela: a encomenda aponta para a unidade |
| Restrição | Regra que o próprio banco garante. Prefixos `pk_`, `fk_`, `uq_` (valor único) e `ck_` (valor permitido, como P, M ou G) |
| Normalização | Não repetir a mesma informação em vários lugares. **1FN:** cada campo guarda um valor só ("Bloco A apto 12" vira dois campos). **2FN:** cada informação depende da chave inteira. **3FN:** nenhuma informação depende de outra que não seja a chave (os dados do morador ganharam tabela própria) |
| DER | O desenho das entidades e das ligações entre elas (Figura 6) |
| SQL | A linguagem para criar tabelas e consultar o banco |
| Hash SHA-256 | Uma impressão digital do código: dá para conferir se o código digitado bate, mas não dá para descobrir o código a partir dela. Existe só no sistema completo |
| NoSQL | Bancos sem tabelas fixas, como documentos (MongoDB) e chave-valor (Redis). Só faria sentido para o histórico de avisos, no futuro |
| Docker | Um contêiner, ambiente isolado onde o MySQL 8.4 rodou os scripts |

- **Três soluções do modelo:** a chave primária da tabela de operações impede aplicar a mesma operação duas vezes; uma coluna gerada com valor único impede duas pendentes na mesma posição; o código fica guardado só como hash.
- **Resultados:** os scripts rodaram sem erro e batem com o relatório do programa em C: 6 e 5 pendências, 6 de 48 e 5 de 48 posições ocupadas.

### 10.4 Redes (Pedro)

**Em uma frase:** sede, 10 condomínios e a nuvem, cada local em estrela e todos ligados à nuvem por VPN, com endereços `10.X.Y.0/24`, 4 VLANs e listas de acesso, e 15 testes no Packet Tracer, todos com o resultado esperado.

| Termo | Como explicar |
|---|---|
| LAN e WAN | Rede local e rede entre locais |
| Topologia estrela | Todos os aparelhos ligados a um equipamento central. Entre os locais é *hub-and-spoke*: a nuvem no centro |
| Roteador, switch e ponto de acesso | Liga redes diferentes; liga os aparelhos da mesma rede; dá o Wi-Fi |
| Endereço IP e `/24` | O endereço de cada aparelho. `/24` é uma rede de 256 endereços. Em `10.X.Y.0`, X é o local (0 é a sede) e Y é a VLAN: `10.3.10.10` é o computador da portaria do condomínio 3 |
| VLAN | Dividir um switch em redes separadas, como corredores diferentes no mesmo prédio: 10 portaria, 20 CFTV, 30 visitantes e 99 gerência |
| Gateway e DHCP | A porta de saída da rede (termina em `.1`) e o serviço que entrega endereços automaticamente (de `.100` a `.199`) |
| ACL e firewall | Regras de quem pode falar com quem. A portaria só alcança a API, o CFTV só a própria VLAN, os visitantes só a internet, e a gerência entra por SSH a partir da sede |
| VPN (IPsec) | Um túnel criptografado pela internet. São 11 túneis, mas a VPN ficou só no desenho |
| HTTPS e SSH | Comunicação criptografada com a API e acesso remoto seguro aos equipamentos |
| `ping` | O teste "você me ouve?" entre dois aparelhos |
| IaaS, PaaS e SaaS | Alugar a máquina, alugar a plataforma pronta (MySQL gerenciado) ou usar um serviço pronto (SMS) |

- **Números:** 44 redes, 4 VLANs, 15 de 15 testes no Packet Tracer 9.0.1. No T2, a portaria alcança a central; no T6, o Wi-Fi de visitantes não alcança a portaria; no T14 e no T15, sem a nuvem, a rede local continua funcionando.
- **Ligação com o seu programa:** como a rede local continua sem a nuvem, a portaria segue trabalhando e a fila guarda as operações até a conexão voltar.
- **Cuidado:** VPN, HTTPS e desempenho não foram testados.

### 10.5 Segurança, privacidade e acessibilidade (Pedro)

- **LGPD (Lei 13.709/2018):** finalidade, adequação e necessidade, ou seja, usar só o mínimo. O sistema guarda nome, unidade, canal e contato; não guarda o conteúdo da encomenda nem o remetente, e não guarda contato quando o canal é o interfone.
- **Retenção:** 90 dias depois da retirada, com anonimização em seguida. É decisão de projeto do grupo, e não prazo legal.
- **Segurança:** código de 6 dígitos de uso único, 3 tentativas e confirmação do porteiro; número único em cada operação (rastreabilidade); entrada validada.
- **Acessibilidade:** interfone com código impresso para quem não usa smartphone. Para as telas futuras, o nível AA do WCAG (os níveis são A, AA e AAA). A Lei Brasileira de Inclusão (13.146/2015) também é citada.
- **Ética:** os relatórios são por condomínio, sem ranking de funcionários.
- **Cuidado:** o protótipo não tem login nem criptografia, e o código aparece na tela. São limitações declaradas.

### 10.6 Limitações e conclusão (Pedro)

- **Pronto e testado:** o programa em C, os scripts do banco e a rede no simulador.
- **Simulado:** o aviso ao morador e a rede entre portaria e central.
- **Só no projeto:** VPN, HTTPS, API, banco ligado ao programa, aplicativo do morador e painel.
- **Benefícios** (menos extravios, menos tempo do porteiro): esperados, ainda não medidos. Só um piloto pode mostrar.
- **Conclusão:** a solução é tecnicamente viável.

---

## 11. Perguntas que podem fazer para você

| Pergunta | Resposta curta |
|---|---|
| Por que C? | A disciplina é de programação estruturada em C. E o C gera um executável pequeno que roda sem instalar nada. |
| Quais bibliotecas usaram? | Só a padrão: `stdio`, `stdlib`, `string`, `ctype`, `time` e `assert`. Assim o código compila no Windows e no Linux sem instalar nada. |
| Para que servem `-Wall -Wextra -pedantic`? | Ligam um conjunto amplo de avisos do compilador e cobram o padrão C à risca. Compilamos com zero avisos. |
| Por que `fgets` e não `scanf`? | O `fgets` recebe o tamanho da variável e não escreve além dele. O `scanf("%s")` não sabe o tamanho e pode estourar a memória. Depois do `fgets`, convertemos e validamos. |
| E se digitar uma letra onde pede número? | Aparece "Valor invalido. Digite um numero entre X e Y." e a pergunta se repete. |
| Por que não aceita acento nem ponto e vírgula? | O ponto e vírgula é o separador do CSV e quebraria o arquivo. Acento dá problema no console do Windows, então o programa usa só ASCII. |
| Por que tamanho fixo (500 e 300)? | A disciplina pede vetores e matrizes, e o tamanho fixo deixa a memória previsível. Para mudar, muda-se uma constante. Na encomenda 501, o programa avisa e não registra. |
| Por que a estante não é salva em arquivo? | Para ter uma única fonte de verdade. A posição já está gravada em cada encomenda, e ao abrir o programa a estante é remontada a partir das pendentes. |
| Como o programa escolhe a prateleira? | Pela letra do bloco: A vai para a estante A, B para a B, e assim por diante. Se estiver cheia, tenta as próximas, dando a volta. Volume G vai para as prateleiras 10 e 11. |
| O código pode repetir? | Entre pendentes, não: o sorteio se repete até achar um livre. O código de uma encomenda já retirada pode voltar a ser usado. |
| E se digitarem o código de outra pessoa? | Um código errado pode, por azar, ser de outra pendente (cerca de 1 em 9.000 com 100 pendentes). Por isso o programa mostra unidade e nome e o porteiro confirma antes de entregar. |
| O que é idempotente? | Aplicar a mesma operação duas vezes dá o mesmo resultado que aplicar uma. A central anota os números já aplicados e ignora os repetidos. Na demonstração: 17 e depois 0. |
| E se a internet cair no meio do envio? | A fila só é esvaziada depois de copiada. Se cair no meio, as operações vão de novo, e a central ignora as que já aplicou. |
| Como os dados são salvos? | Em arquivos CSV, e a cada alteração o arquivo é reescrito inteiro. Fechar à força durante a gravação pode deixar o arquivo incompleto; é limitação declarada. |
| Como testaram? | Com 9 conjuntos de testes automáticos, que rodam com `build.bat test`. A parte em que o porteiro digita, na retirada, foi conferida à mão. |
| Funciona no Linux? | Sim. Foi compilado no Windows e testado também no Linux com `gcc`. |
| O aviso por SMS é real? | É simulado: aparece na tela e fica registrado em arquivo. O envio real dependeria de um serviço de SMS na nuvem. |
| O código aparece na tela. É seguro? | Não é o ideal, e o trabalho declara isso como limitação. No sistema completo, só o morador receberia o código, e o banco guardaria apenas o hash. |
| Por que a devolução não foi feita? | Depende de um prazo que a administradora precisa definir (US16). Ficou como evolução futura. |
| Posso ver o código? | Está no GitHub, `github.com/danieelaugustoo/pim`, pasta `05-programa-c`. Toda função tem um comentário no topo dizendo o que faz. |

**Se não souber a resposta**, não invente. Diga "isso não foi implementado, e o trabalho declara como limitação" (seções 6.7 e 9.4) ou "não sei com certeza; o que fizemos foi...".

---

## 12. Como se apresentar bem

- Diga o que vai fazer antes de apertar Enter ("agora vou derrubar a internet") e leia em voz alta a linha que importa na tela.
- Aponte para a tela quando a linha importante aparecer, e olhe para a turma quando disser o que ela significa.
- Digite com calma. Se errar, o programa pergunta de novo, e isso ainda mostra a validação funcionando.
- Explique o termo técnico na primeira vez que usar: "idempotente, ou seja, ...".
- Controle o tempo: se a abertura passar de 1 minuto, vá direto para o programa; se a demonstração atrasar, use a versão curta.
- Se pedirem para ver o código, abra o GitHub e mostre o comentário no topo de uma função.
- Se um colega travar, ajude com uma frase da parte 10 e devolva a palavra.
- No fim, passe a palavra pelo nome: "Agora o Pedro vai falar da rede e da conclusão."

---

## 13. Cola final (para ler na quarta de manhã)

**As 11 cenas:** porteiro (lista e mapa) → internet cai → registro com erro de digitação e interfone → registro por SMS → fila com 2 → internet volta e envia → central aplica 19 → central de novo, aplica 0 → retirada (código errado, certo, S) e mapa → retirada chega à central (aplica 1) → relatório.

| O quê | Valor |
|---|---|
| Programas | 2 (`portaria` e `central`), 11 módulos, 116 funções comentadas |
| Padrão | C99, só biblioteca padrão, zero avisos |
| Bibliotecas | `stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `time.h`, `assert.h` |
| Capacidade | 500 encomendas e 300 moradores por portaria |
| Estante | Matriz 4 x 12 = 48 posições; prateleiras 10 e 11 para volume G |
| Código | 6 dígitos, único entre pendentes, 3 tentativas na retirada |
| Algoritmos | A1 estante, A2 código, A3 retirada, A4 sincronizar, A5 consolidar, A6 relatórios |
| Testes | 9 conjuntos, todos passando |
| Grupo | 10 condomínios, ~960 unidades, 40 porteiros; 12 RF, 8 RNF, 8 casos de uso, 15 de 16 histórias; 11 tabelas e 44 restrições; 44 redes, 4 VLANs, 15 de 15 testes |

**Frase de abertura:** "Eu fiquei com a programação em C, e em vez de mostrar código, vou mostrar o programa funcionando."

**Frase de fechamento:** "Agora o Pedro vai falar da rede e da conclusão."
