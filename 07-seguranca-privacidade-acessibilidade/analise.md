# Direitos humanos, inclusão e segurança (Etapa 7, versão curta)

> **Roteiro de tópicos** para o capítulo 8, de cerca de 2 páginas, que o grupo redige com texto próprio. Este arquivo organiza o conteúdo, liga cada ponto ao que existe no projeto e marca o que falta decidir ou citar. As leis aparecem pelo nome e número que constam no `PLANO.md`; **os artigos e trechos exatos precisam ser conferidos no texto oficial antes de entrarem no trabalho** `[FONTE A VERIFICAR]`.

## Cobertura das exigências do manual

| Exigência | Seção deste arquivo |
|---|---|
| Acessibilidade | 3 |
| Inclusão digital | 3 |
| Privacidade | 1 |
| Proteção de dados | 1 |
| Segurança da informação | 2 |
| Impactos sociais | 4 |
| Aspectos éticos | 4 |
| Direitos humanos | 4 |

---

## 1. Privacidade e proteção de dados

**Referência legal:** Lei Geral de Proteção de Dados Pessoais, Lei nº 13.709/2018 `[FONTE A VERIFICAR: princípios e artigos que o grupo for citar]`.

**Quais dados a solução trata** (conforme `04-banco-de-dados/dicionario-de-dados.md` e o protótipo):

| Dado | Quem é o titular | Para que serve (finalidade) |
|---|---|---|
| Nome, bloco e apartamento do morador | Morador | Saber a quem avisar |
| Canal de aviso e contato (telefone ou e-mail, só quando o canal exige) | Morador | Enviar o aviso de chegada |
| Nome do destinatário da encomenda | Morador ou visitante | Identificar o volume |
| Nome de quem retirou, data e hora | Quem retira | Comprovar a entrega |
| Transportadora, tamanho e posição do volume | Não é dado pessoal | Operação da estante |

**Finalidade única:** entregar a encomenda certa à pessoa certa. Os dados não servem para outro fim.

**Minimização (o que a solução deliberadamente não registra):**
- conteúdo da encomenda e remetente: só a transportadora;
- contato do morador quando o canal é interfone (o campo fica vazio);
- o arquivo de registro de avisos do protótipo (`Pnn-avisos.txt`) não guarda o código de retirada (conferido na Sprint 2).

**Acesso por perfil (sistema completo):** porteiro vê só a própria portaria; supervisor vê os relatórios dos condomínios que acompanha; administrador gerencia usuários. O protótipo não tem login (limitação, seção 5).

**Retenção:** guardar os registros por prazo definido e, depois, anonimizar (apagar nome e contato, manter só números para os indicadores). Prazo: **[A DEFINIR pelo grupo; o plano sugere 12 meses como exemplo]**.

**Direitos do titular (pontos a tratar no texto):** confirmação de que há tratamento, acesso, correção e eliminação de dados quando cabível. Cada um precisa de um caminho concreto na administradora (por exemplo, pedido à gerência) `[A DEFINIR]`.

**Quem responde pelos dados:** a Administradora Morada Central é a organização que decide sobre o tratamento; definir um encarregado de contato é uma decisão da organização `[A DEFINIR; conferir a figura na LGPD]`.

**Dados de exemplo do projeto** são todos fictícios (regra 10 do `CLAUDE.md`); nenhum dado real de morador foi usado.

---

## 2. Segurança da informação

| Medida | Como aparece no projeto | Situação |
|---|---|---|
| Código de retirada de 6 dígitos, para uso único | A2 gera, A3 confere; vale só para a encomenda pendente; após a retirada o código não serve mais | No protótipo |
| Limite de tentativas | Três códigos errados negam a retirada (`MAX_TENTATIVAS`) | No protótipo |
| Código não exibido a terceiros | No sistema completo vai só na mensagem ao morador, e o banco guarda apenas o **hash** (`SHA2`) | Sistema completo; ver limitação abaixo |
| Rastreabilidade | Toda operação tem id único (`P01-000123`), data e hora; a central ignora repetições | No protótipo (RNF07) |
| Log de auditoria | Registros de operações e dos avisos | Parcial no protótipo; completo no sistema |
| Segurança da rede | VLANs, ACL, VPN IPsec, HTTPS/TLS, 2FA no painel, backup 3-2-1 | Projeto em `06-redes/seguranca-infraestrutura.md`; ACL a testar no Packet Tracer |
| Entrada de dados validada | `fgets` com conversão validada; recusa texto com `;` e acento | No protótipo |

**Limitação que o grupo deve discutir (ponto honesto):** no protótipo, ao registrar uma encomenda a tela do porteiro mostra o código de retirada **para todos os canais**, e o código fica em texto nos arquivos de dados. Isso contraria o RNF04 (código não exibido a terceiros) no caso de app e SMS, em que só o morador deveria conhecê-lo. No sistema completo o fluxo muda: o código vai apenas na mensagem ao morador, o porteiro digita o código que o morador informa e o sistema confere o hash. Decisão do grupo (2026-10-29): manter o protótipo assim e declarar a limitação.

---

## 3. Acessibilidade e inclusão digital

**Referências:** Lei Brasileira de Inclusão da Pessoa com Deficiência, Lei nº 13.146/2015, cujo art. 63 trata da acessibilidade em sites de empresas `[FONTE A VERIFICAR: conferir o artigo]`; diretrizes WCAG do W3C `[FONTE A VERIFICAR: versão e nível que o grupo adotar]`.

**Inclusão digital (quem não usa smartphone):**
- o canal **interfone** existe justamente para isso: o porteiro liga e entrega o código impresso (RNF08);
- o canal é escolhido pelo morador no cadastro (US07), sem exigir app;
- o tratamento é igual para todos: a retirada exige o mesmo código, com ou sem smartphone.

**Acessibilidade das telas (sistema completo):**
- contraste adequado e fonte ampliável;
- navegação por teclado e compatibilidade com leitor de tela;
- mensagens de erro claras, que digam o que fazer (o protótipo já segue o padrão "Valor invalido. Digite um numero entre X e Y");
- avisos que não dependam só de cor ou som.

**Limitação do protótipo:** é um programa de console, sem acentos e sem recursos de acessibilidade; as diretrizes valem para o sistema completo `[A DEFINIR: o grupo pode listar as telas previstas]`.

**Ponto de atenção:** o aviso por app ou SMS depende da nuvem e não sai com a internet caída (ver `06-redes/nuvem-e-sistemas-distribuidos.md`). Nesse caso, o interfone cobre a lacuna.

---

## 4. Ética, impactos sociais e direitos humanos

**Impactos positivos esperados (hipóteses a confirmar com o piloto, não resultados):**
- menos conflito entre moradores e portaria por encomenda extraviada ou entregue à pessoa errada;
- carga de trabalho do porteiro mais previsível, com busca rápida em vez de folhear o caderno;
- comprovante de entrega com data, hora e nome, que protege morador e porteiro.

**Riscos e como o projeto os trata:**

| Risco | Tratamento |
|---|---|
| Uso dos registros para vigiar o porteiro | O registro serve para **rastrear encomendas**, não para medir pessoas; relatórios são por condomínio, sem ranking de funcionários; regra a constar no comunicado de implantação |
| Vazamento de dados de moradores | Minimização, acesso por perfil, VPN, HTTPS e backup (seções 1 e 2) |
| Exclusão de quem não usa tecnologia | Canal interfone e código impresso (seção 3) |
| Dependência da tecnologia | O funcionamento offline e o plano de contingência em papel (`08-integracao/implantacao.md`) |
| Câmeras (CFTV) | Ficam em VLAN isolada e **não fazem parte do tratamento de dados da solução**; o uso das imagens segue regra própria do condomínio `[A DEFINIR]` |

**Aspectos éticos (pontos para o texto):**
- transparência: o morador sabe quais dados são guardados e para quê;
- proporcionalidade: só o necessário para entregar a encomenda;
- tratamento igual a todos os moradores;
- respeito ao trabalhador: ferramenta de apoio ao porteiro, com treinamento, sem punição por uso.

**Direitos humanos:** o grupo pode relacionar o projeto à privacidade, à dignidade no trabalho e à não discriminação no acesso ao serviço. Citar documentos específicos (declarações, Constituição) só depois de verificar o texto `[FONTE A VERIFICAR]`.

---

## 5. Limitações desta etapa

- Sem login nem perfis no protótipo; sem criptografia dos arquivos de dados.
- Código de retirada em texto nos arquivos e visível na tela do porteiro (seção 2).
- Retenção, direitos do titular e encarregado dependem de decisão da administradora.
- Nenhuma auditoria jurídica foi feita; o texto é uma análise acadêmica, não parecer legal.
- Sem levantamento de campo (dispensado pelo grupo), não há dado real sobre o uso de smartphone pelos moradores; o canal interfone é uma salvaguarda de projeto, não uma resposta a dados coletados.

## 6. O que o grupo precisa fazer

- [ ] Conferir as leis citadas nos textos oficiais e preencher `fontes.md`.
- [ ] Decidir o prazo de retenção e quem atende pedidos de titulares.
- [ ] Decidir o ajuste (ou a declaração de limitação) do código na tela do porteiro.
- [ ] Redigir o capítulo com texto próprio (cerca de 2 páginas).
