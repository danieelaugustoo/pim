# Roteiro da demonstração do programa

Tempo previsto: **6 a 7 minutos**. Quem digita fica com o computador do Daniel (o grupo levará o notebook). As saídas abaixo foram **executadas em 07/11/2026** com os dados de exemplo; só mudam o **código de retirada** (sorteado) e as **datas** (ver "Atenção").

## Antes de entrar na sala (fazer em casa e de novo 10 minutos antes)

1. `git pull origin main` e, dentro de `05-programa-c`, `.\build.bat` e `.\build.bat test`. Os **9 conjuntos de testes** precisam passar sem aviso.
2. Se o Windows bloquear o `.exe` recém-compilado (Device Guard), repita o comando. Não mexa em configuração de segurança.
3. Apague o conteúdo de `dados\portarias`, `dados\rede` e `dados\central` (para começar do zero) e copie os dados de exemplo:

```
copy dados\exemplo\P01-encomendas.csv dados\portarias\
copy dados\exemplo\P01-moradores.csv dados\portarias\
copy dados\exemplo\P01-sequencia.txt dados\portarias\
copy dados\exemplo\P01.log dados\rede\
copy dados\exemplo\P02.log dados\rede\
```

4. Abra **dois terminais** na pasta `05-programa-c`: um para `bin\central.exe` e outro para `bin\portaria.exe 1`. Deixe o PDF do trabalho aberto e as figuras 5, 6 e 9 à mão, caso o programa falhe.

## Passo a passo

| # | O que fazer | O que aparece | O que dizer (1 frase) |
|---|---|---|---|
| 1 | Terminal 2: `bin\central.exe` | `P01: 10 lida(s), 10 aplicada(s)`, `P02: 7 lida(s), 7 aplicada(s)`, `Total consolidado: 17 operacao(oes), 14 encomenda(s).` | "A central lê o que as portarias enviaram e aplica cada operação." |
| 2 | Rodar `bin\central.exe` **de novo** | `0 aplicada(s), 10 ja aplicada(s)` e `0 aplicada(s), 7 ja aplicada(s)` | "Reenviar o mesmo arquivo não duplica nada: é a consolidação idempotente (A5)." |
| 3 | Terminal 1: `bin\portaria.exe 1`, opção `3` | 6 pendentes (A-12 duas, B-101, B-203, C-34, A-45) | "Essa é a portaria 1 com as pendências do caderno já digitalizadas." |
| 4 | Opção `5` | Mapa com `Ocupadas: 6 de 48 (12.5%)` | "A estante é uma matriz 4 por 12; as prateleiras 10 e 11 são para volumes grandes." |
| 5 | Opção `9` | `Portaria agora OFFLINE.` | "Agora a internet caiu. A portaria continua trabalhando." |
| 6 | Opção `1`: bloco `D`, apto `7`, `Rafael Costa`, `Transp Alfa`, `M` | `Encomenda 9 registrada para D-7.` `Guardar na estante D, prateleira 0.` `Codigo de retirada: NNNNNN` e `Aviso: ligar pelo interfone para D-7` | "O sistema escolhe a posição, gera o código e avisa pelo canal do morador. Esse mora com interfone." **Anote o código.** |
| 7 | Opção `1`: `D`, `15`, `Beatriz Alves`, `Transp Gama`, `P` | `Encomenda 10 registrada para D-15.` e `Aviso simulado por SMS para 11900000007` | "Outro morador, outro canal: SMS." |
| 8 | Opção `8` | `Portaria OFFLINE: 2 operacao(oes) aguardando envio.` | "As operações esperam na fila, sem perder nada." |
| 9 | Opção `9` (volta a ONLINE) e opção `8` | `2 operacao(oes) enviada(s) para dados/rede/P01.log.` | "Voltou a conexão: a fila foi enviada e esvaziada." |
| 10 | Terminal 2: `bin\central.exe` | `P01: 12 lida(s), 2 aplicada(s), 10 ja aplicada(s)` e `Total consolidado: 19 operacao(oes), 16 encomenda(s).` | "Só as 2 novas foram aplicadas; as outras 10 foram reconhecidas." |
| 11 | Opção `2` (retirada), digitar um código **errado** (ex.: `123456`) | `Nenhuma encomenda pendente com esse codigo (tentativa 1 de 3).` | "Até 3 tentativas; com 3 erros a retirada é negada e nada muda." |
| 12 | Digitar o código **certo** | Tabela com `9 D-7 Rafael Costa ...` e `Confirme com o morador a unidade e o destinatario. Entregar esta encomenda? (S/N):` | "O morador não precisa saber o id: o código acha a encomenda e o porteiro confirma com ele." |
| 13 | Responder `N` | `Retirada cancelada. A encomenda continua pendente.` | "Se a confirmação falhar, nada é alterado." |
| 14 | Opção `2` de novo, código certo, `S`, nome `Rafael Costa` | `Retirada registrada: encomenda 9, em <data e hora>, por Rafael Costa.` | "Registra quem retirou, a data e a hora, e libera a posição na estante." |
| 15 | Opção `8` e, no terminal 2, `bin\central.exe` | `1 aplicada(s), 12 ja aplicada(s)` e `Total consolidado: 20 operacao(oes), 16 encomenda(s).` | "A retirada também sobe para a central." |
| 16 | Abrir `dados\central\relatorio-consolidado.txt` | Tabela por portaria (REGISTRADAS, PENDENTES, RETIRADAS, DEVOLVIDAS, ANTIGAS, PICO) | "É o relatório que a administradora usa para ver os dez condomínios." |

Os arquivos ficam em texto simples: se perguntarem, abra `dados\rede\P01.log` ou `dados\central\operacoes-aplicadas.csv` para mostrar que cada operação tem um identificador único (como `P01-000011`).

## Atenção (coisas que mudam ou dão errado)

- **A coluna ANTIGAS muda com a data.** No trabalho (Quadro 2) os valores são de 29/10/2026 (P01 com 2 antigas). No dia da apresentação o programa vai mostrar números maiores (em 07/11 mostrou 6 em P01 e 5 em P02), porque conta pendências com mais de 7 dias. Avise antes: "o relatório depende da data de hoje".
- **O código de retirada é sorteado**: leia o que aparece na tela, não use o do roteiro.
- **Retirada com o código de outra encomenda:** o programa mostra a unidade e o destinatário justamente para o porteiro conferir. É a limitação declarada na seção 6.7.
- **Se o programa travar ou o `.exe` for bloqueado:** repita o comando uma vez. Se continuar, mostre os prints das Figuras 7 (consulta SQL) e 10 (testes de rede) e o relatório do Quadro 2 do PDF, e explique o fluxo pela Figura 5 (diagrama de sequência).
- **Não é possível mostrar** a VPN, o HTTPS da API nem o banco ligado ao programa: isso é projeto, não protótipo (seção 9.1 do trabalho).
- **Reiniciar a demonstração do zero:** repita o item 3 da preparação.
