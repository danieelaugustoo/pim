# Sprint 2: sistema distribuído

**Datas:** [DATA A DEFINIR]
**Meta:** a portaria cadastra moradores, avisa pelo canal de cada um, continua trabalhando sem internet e envia as operações à central, que as consolida sem duplicar (US07 a US11).

## Histórias

| ID | História | Situação |
|---|---|---|
| US07 | Cadastrar moradores com canal de aviso | Feito (falta revisão do grupo) |
| US08 | Aviso pelo canal do morador | Feito (falta revisão do grupo) |
| US09 | Registrar sem internet | Feito (falta revisão do grupo) |
| US10 | Sincronizar quando a conexão voltar | Feito (falta revisão do grupo) |
| US11 | Consolidar sem duplicidade | Feito (falta revisão do grupo) |

Critérios de aceitação em `scrum/backlog.md`. "Feito" significa implementado, compilando sem warnings e testado; a revisão por outro integrante (definição de pronto) ainda não aconteceu.

## Verificações realizadas (2026-10-29)

- `gcc -std=c99 -Wall -Wextra -pedantic` sem warnings, também com `-O2`, para `portaria` e `central`.
- `make`, `make test`, `make clean` (com e sem `sh` no PATH) e `build.bat`/`build.bat test` funcionando.
- 8 conjuntos de testes passando: os 5 da Sprint 1 e `test_morador`, `test_sincronizacao` e `test_consolidacao`.
- Execução real com os dados de exemplo:
  - **Central rodada duas vezes** com os mesmos logs: 17 operações e 14 encomendas aplicadas na 1ª; na 2ª, 0 aplicadas e 17 já aplicadas, e os arquivos ficaram idênticos byte a byte.
  - **Portaria offline:** 3 registros (A-12 com SMS, D-7 com interfone, Z-1 sem morador) entraram na fila; sincronizar offline informou "3 operações aguardando" e preservou a fila; ao voltar online, as 3 foram enviadas e a fila ficou só com o cabeçalho.
  - **Numeração:** `P01-000011` a `P01-000013`, continuando da sequência do arquivo.
  - **Central depois do envio:** 3 aplicadas e 10 já aplicadas; depois da retirada da encomenda 9, 1 aplicada e 13 já aplicadas.
  - **Moradores:** nome repetido na mesma unidade e contato inválido para SMS foram recusados.
  - **Privacidade:** o arquivo `Pnn-avisos.txt` não contém o código de retirada.
- O relatório da central bate com as consultas do banco de exemplo.

## Redes (Etapa 6, Prompt 7)

Entregue junto com a sprint (o plano reparte a Etapa 6 entre as Sprints 2 e 3):

| Entrega | Situação |
|---|---|
| `06-redes/`: arquitetura e topologia, equipamentos, endereçamento, VLANs, nuvem e sistemas distribuídos, segurança da infraestrutura e diagrama de topologia | Feito (falta revisão do grupo; diagrama não renderizado) |
| Tabelas completas de endereçamento (sede e 10 condomínios, 4 VLANs cada, mais a nuvem) | Feito, geradas por script |
| Roteiro passo a passo do Packet Tracer (`packet-tracer/roteiro.md`) | Feito, **comandos não executados no simulador** |
| Montagem no Packet Tracer, testes e prints | **Do grupo**, ainda não feitos |

Verificação feita no lugar da execução: um script gerou as 44 redes e conferiu que nenhuma se sobrepõe, que todo gateway pertence à sua rede e que todas as faixas (fixos `.10` a `.49`, DHCP `.100` a `.199`) cabem no `/24`; outro script leu os 8 blocos de comandos do roteiro e conferiu endereços, subinterfaces, ACL, DHCP e rotas contra a tabela. A lógica das ACL foi relida contra os 15 testes esperados. Isso **não substitui** montar no Packet Tracer.

Modelos de equipamento, preços, quantidade de câmeras, provedor de nuvem e algoritmos de VPN ficaram como `[A DEFINIR]`/`[A COTAR]`. As regras de firewall e o endereçamento do laboratório (`203.0.113.0/24`) são propostas a validar com o grupo.

## O que foi entregue

- Módulos novos `morador`, `aviso`, `sincronizacao` e `consolidacao`, e o executável `central` (`src/central.c`).
- `portaria.c` com os menus 6 (moradores), 8 (sincronizar) e 9 (online/offline) e o indicador `[ONLINE]`/`[OFFLINE]`; registro e retirada passam a enfileirar a operação.
- Persistência de moradores; `retirada_registrar` devolve o índice da encomenda; `Makefile` e `build.bat` compilam a central e os 8 testes.
- Dados de exemplo (moradores, sequência e logs `P01.log` e `P02.log`).
- Pseudocódigo e fluxogramas de A4 e A5 em `05-programa-c/algoritmos/`.

## O que não foi entregue / fica para depois

- Pseudocódigo e fluxogramas de A1, A2, A3 e A6: previstos para a Sprint 3 pelo `PLANO.md`; foram feitos na Sprint 3 (ver `sprint-03.md`).
- Operação DEVOLUCAO gerada pela portaria (US16, opcional, Sprint 3): a central já a entende.
- Aviso e rede reais: seguem simulados.
- Tag `v0.2.0` ao fim da sprint: depende da revisão e do commit.

## Impedimentos e riscos

- Apagar `Pnn-sequencia.txt` sem apagar o log da rede faz a portaria repetir ids de operações já aplicadas, e a central as ignora. Está nas limitações do README; no sistema completo, a chave primária e a API tratam isso.
- O Cisco Packet Tracer não está instalado na máquina de desenvolvimento: os comandos do roteiro precisam ser testados pelo grupo, que também decide se faz a VPN IPsec (opcional).
- Prazo oficial de entrega ainda não confirmado.

## Retrospectiva (a preencher pelo grupo)

- O que funcionou:
- O que melhorar:
- Ações para a próxima sprint:
