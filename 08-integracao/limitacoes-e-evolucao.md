# Limitações e evolução futura (Etapa 8)

> **Roteiro de tópicos** para o capítulo 9 (e para a conclusão, `documento-final/capitulos/10-conclusao.md`, que o grupo escreve). Limitações honestas aumentam a credibilidade do trabalho: o grupo deve apresentá-las com clareza.

## 1. Limitações da solução

### Do protótipo em C

| Limitação | Efeito | Onde está registrada |
|---|---|---|
| Rede simulada por arquivos | Não há comunicação real entre portaria e central; atrasos, quedas parciais e segurança do canal não são testados | `05-programa-c/README.md` |
| Aviso ao morador simulado | Mensagem na tela e registro em arquivo; nenhum SMS ou app real | `src/aviso.c` |
| Sem interface gráfica | Menu de console, sem acentos | `CLAUDE.md`, regra 5 |
| Sem login nem perfis | Qualquer pessoa com acesso ao PC usa todas as opções | `07-.../analise.md` |
| Código de retirada em texto e visível na tela do porteiro | Não atende por completo o RNF04 para app e SMS | `07-.../analise.md`, seção 2 |
| Capacidade fixa (vetores estáticos) | 500 encomendas por portaria, 300 moradores, 4 estantes × 12 prateleiras | `include/tipos.h` |
| Busca sequencial e arquivos CSV | Basta para o protótipo, não para grande volume | ADR-002 |
| Reconstrução da estante só pelas pendentes | Se o arquivo de encomendas for perdido, a posição é perdida | `src/estante.c` |
| Dados fictícios | Nenhum dado real foi usado ou protegido | `CLAUDE.md`, regra 10 |
| Sem relatório de tempo médio de retirada | O indicador depende de cálculo manual | `beneficios-e-indicadores.md` |
| Apagar a sequência sem apagar o log da rede faz a portaria repetir ids | A central ignora as operações repetidas | `05-programa-c/README.md` |
| Devolução de volume (US16) não implementada | O status DEVOLVIDA existe e a central entende a operação, mas a portaria não a gera | `scrum/backlog.md` |

### Do projeto como um todo

- **Rede não testada em simulador:** o roteiro do Packet Tracer foi conferido por script quanto a endereços e regras, mas os comandos **não foram executados**; o grupo precisa montar, testar e tirar os prints (`06-redes/packet-tracer/`).
- **Equipamentos, preços e provedor de nuvem** estão como `[A DEFINIR]` e `[A COTAR]`.
- **Sem levantamento de campo** (dispensado pelo grupo): não há dados reais sobre a frequência do problema nem sobre o uso de smartphone pelos moradores; o problema vem do cenário fictício e da bibliografia.
- **Banco de dados:** os scripts foram executados em um MySQL de teste, mas o protótipo em C não se conecta a ele.
- **Revisão por pares:** as histórias estão "feitas, falta revisão do grupo"; a definição de pronto exige revisão por outro integrante.
- **Diagramas** (UML, DER, topologia, fluxogramas) estão como código e **ainda não foram renderizados**.

## 2. Evolução futura

| Evolução | O que traz | Pré-requisito |
|---|---|---|
| **API real (HTTPS) no lugar dos arquivos** | Sincronização de verdade, com autenticação e TLS | Servidor na nuvem e contrato da API (`06-redes/nuvem-e-sistemas-distribuidos.md`) |
| **Conexão com o banco MySQL** | Consolidado e histórico no banco, com hash do código | API; scripts de `04-banco-de-dados/` |
| **App do morador** | Aviso, código e histórico no celular | API e autenticação |
| **Avisos por WhatsApp** | Canal que o morador já usa | Contrato com provedor e consentimento |
| **Painel de indicadores** | Gráficos de pico, ocupação, pendências e tempo médio | Banco e relatórios |
| **Armários inteligentes** | Retirada autônoma, 24 horas | Integração com fabricante |
| **Foto da etiqueta com leitura automática** | Registro mais rápido, menos digitação | Visão computacional e revisão de privacidade |
| **Perfis, login e 2FA** | Acesso por perfil e auditoria | Módulo de usuários |
| **Devolução automática após o prazo (US16)** | Libera espaço na estante | Decisão do prazo pela administradora |
| **Telas acessíveis (WCAG)** | Inclusão no sistema completo | Interface gráfica ou web |
| **Segundo link de internet por condomínio** | Menos dependência de uma operadora | Orçamento |

## 3. Como o grupo pode apresentar

- Separar "o que foi entregue e funciona", "o que foi simulado" e "o que fica como evolução".
- Ligar cada limitação a uma evolução da tabela acima: assim ela vira um caminho, e não só uma falha.
- Evitar prometer o que o protótipo não faz (aviso real, rede real, banco conectado).
