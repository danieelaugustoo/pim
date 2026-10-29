# 8 Direitos humanos, inclusão e segurança (roteiro, cerca de 2 páginas, Etapa 7)

> **ROTEIRO, não é o texto.** O grupo escreve o capítulo e **substitui** este conteúdo na seção "Texto do grupo".

**Fonte principal:** `07-seguranca-privacidade-acessibilidade/analise.md` (já organizada nas oito exigências do manual). Complemento: `06-redes/seguranca-infraestrutura.md`.

## Tópicos (uma subseção curta para cada)

| # | Tópico | Origem em `analise.md` |
|---|---|---|
| 8.1 | Privacidade e proteção de dados (LGPD): dados tratados, finalidade, minimização, retenção, acesso por perfil | seção 1 |
| 8.2 | Segurança da informação: código de uso único, hash no banco, rastreabilidade, segurança da rede | seção 2 |
| 8.3 | Acessibilidade e inclusão digital: interfone com código impresso, WCAG, telas acessíveis | seção 3 |
| 8.4 | Impactos sociais, aspectos éticos e direitos humanos | seção 4 |
| 8.5 | Limitações desta análise | seção 5 |

## Figuras e tabelas

- Tabela: dados pessoais tratados × finalidade (`analise.md`, seção 1).
- Tabela: medidas de segurança × situação (protótipo ou sistema completo) (seção 2).
- Tabela: riscos éticos e como são tratados (seção 4).
- Nenhuma figura obrigatória; o espaço (cerca de 2 páginas) comporta no máximo uma tabela grande.

## O que depende do grupo

- [ ] **Conferir as leis nos textos oficiais** (LGPD, Lei nº 13.709/2018; Lei Brasileira de Inclusão, Lei nº 13.146/2015, art. 63) e as diretrizes WCAG, e só então citar `[FONTE A VERIFICAR]`.
- [x] Prazo de retenção: 90 dias após a retirada (decisão de 2026-10-29). Falta definir quem atende pedidos de titulares `[A DEFINIR]`.
- [x] Código de retirada na tela do porteiro: decisão do grupo (2026-10-29) de manter e declarar a limitação.
- [ ] Cortar para caber em cerca de 2 páginas: priorizar o que é específico do projeto.

## Cuidados

- Texto é análise acadêmica, não parecer jurídico; evitar afirmar que a solução "está em conformidade" com a LGPD.
- Impactos positivos são **hipóteses** até o piloto existir.

---

## Texto do grupo

> **Rascunho** redigido a partir do roteiro e de `07-seguranca-privacidade-acessibilidade/analise.md` (autorizado pela Prof.ª Eliana). O grupo revisa, ajusta e responde pelo conteúdo. Leis e diretrizes precisam ser conferidas nos textos oficiais antes de citadas.

# 8 DIREITOS HUMANOS, INCLUSÃO E SEGURANÇA

Este capítulo analisa a solução quanto à privacidade e proteção de dados, à segurança da informação, à acessibilidade e inclusão digital e aos aspectos éticos, sociais e de direitos humanos. A análise é acadêmica e não constitui parecer jurídico.

## 8.1 Privacidade e proteção de dados

O tratamento de dados pessoais no Brasil é regido pela Lei Geral de Proteção de Dados Pessoais (Lei nº 13.709/2018) (BRASIL, 2018). Entre seus princípios estão a finalidade, a adequação e a necessidade, esta entendida como a "limitação do tratamento ao mínimo necessário" para cumprir as finalidades (BRASIL, 2018, art. 6º, I a III). A solução trata dados do morador (nome, bloco e apartamento, canal de aviso e, quando o canal exige, o contato), o nome do destinatário da encomenda e o nome de quem a retirou, com data e hora (Quadro 14). A finalidade é única: entregar a encomenda certa à pessoa certa.

**Quadro 14 – Dados pessoais tratados e finalidade**

| Dado | Titular | Finalidade |
|---|---|---|
| Nome, bloco e apartamento | Morador | Saber a quem avisar |
| Canal de aviso e contato | Morador | Enviar o aviso de chegada |
| Nome do destinatário | Morador ou visitante | Identificar o volume |
| Nome de quem retirou, data e hora | Quem retira | Comprovar a entrega |

Fonte: elaborado pelos autores (2026).

Aplicou-se o princípio da minimização: o sistema não registra o conteúdo da encomenda nem o remetente, apenas a transportadora, e não guarda contato quando o canal de aviso é o interfone. O acesso, no sistema completo, seria por perfil: o porteiro vê apenas a sua portaria, o supervisor vê os relatórios dos condomínios que acompanha e o administrador gerencia usuários. Para a retenção, o grupo definiu que os dados pessoais seriam mantidos por 90 dias após a retirada da encomenda e, depois, anonimizados, preservando apenas números para os indicadores. Trata-se de uma decisão de projeto: a lei prevê que os dados sejam eliminados após o término do tratamento, com exceções como o cumprimento de obrigação legal (BRASIL, 2018, art. 16), e eventuais prazos legais específicos precisam ser verificados `[FONTE A VERIFICAR]`. A lei também assegura ao titular direitos como a confirmação do tratamento, o acesso e a correção dos dados (art. 18) e exige que o controlador indique um encarregado (art. 41); os caminhos práticos para exercer esses direitos e a indicação do encarregado dependem de decisão da administradora. Todos os dados usados no trabalho são fictícios.

## 8.2 Segurança da informação

A principal medida é o código de retirada de seis dígitos, de uso único, que só vale enquanto a encomenda está pendente, com limite de três tentativas por retirada. No sistema completo, o código seguiria apenas na mensagem ao morador, e o banco guardaria somente o seu resumo criptográfico (hash), nunca o número. Cada operação do sistema recebe um identificador único, data e hora, o que garante rastreabilidade, e a entrada de dados é validada para recusar caracteres que quebrariam os arquivos. A segurança da rede, tratada no capítulo 7, inclui segmentação por VLAN, listas de controle de acesso, rede privada virtual, criptografia das comunicações, autenticação em dois fatores no painel e cópias de segurança.

O protótipo tem limitações que devem ser declaradas: não possui login nem perfis, os arquivos de dados não são criptografados e, ao registrar uma encomenda, a tela do porteiro mostra o código de retirada para qualquer canal de aviso, o que contraria o requisito de que o código não seja exibido a terceiros. O grupo decidiu manter essa característica no protótipo e declará-la como limitação; no sistema completo, o porteiro digitaria o código informado pelo morador e o sistema o conferiria pelo hash.

## 8.3 Acessibilidade e inclusão digital

A solução considera moradores que não usam smartphone. O canal interfone permite que o porteiro avise por telefone interno e entregue o código impresso, e o canal de aviso é escolhido pelo morador no cadastro, sem exigir aplicativo. A retirada exige o mesmo código para todos, com ou sem smartphone, o que garante tratamento igual. Esse cuidado dialoga com a Lei Brasileira de Inclusão da Pessoa com Deficiência (Lei nº 13.146/2015), cujo art. 63 torna obrigatória a acessibilidade nos sítios da internet mantidos por empresas com sede ou representação comercial no País (BRASIL, 2015).

Para as telas do sistema completo, recomenda-se seguir as diretrizes de acessibilidade para conteúdo web (WCAG), do W3C, que definem os níveis de conformidade A, AA e AAA (WORLD WIDE WEB CONSORTIUM, 2024) `[definir o nível adotado]`: contraste adequado, fonte ampliável, navegação por teclado, compatibilidade com leitores de tela e avisos que não dependam apenas de cor ou som. O protótipo, por ser de console, não implementa esses recursos, mas já adota mensagens de erro que dizem ao usuário o que fazer. Como o aviso por aplicativo ou SMS depende da nuvem, ele não sai com a internet caída, e o interfone cobre essa falha.

## 8.4 Ética, impactos sociais e direitos humanos

São impactos positivos esperados, e portanto hipóteses a confirmar em um piloto: menos conflitos por encomendas extraviadas ou entregues à pessoa errada, carga de trabalho mais previsível para o porteiro e um comprovante de entrega que protege morador e funcionário. Os riscos e o tratamento previsto estão no Quadro 15.

**Quadro 15 – Riscos éticos e tratamento**

| Risco | Tratamento |
|---|---|
| Uso dos registros para vigiar o porteiro | Os registros servem para rastrear encomendas; os relatórios são por condomínio, sem ranking de funcionários |
| Vazamento de dados de moradores | Minimização, acesso por perfil, comunicação criptografada e cópias de segurança |
| Exclusão de quem não usa tecnologia | Canal interfone e código impresso |
| Dependência da tecnologia | Funcionamento offline e plano de contingência em papel |
| Câmeras do condomínio | Ficam em rede isolada e fora do tratamento de dados da solução |

Fonte: elaborado pelos autores (2026).

Do ponto de vista ético, a solução busca transparência (o morador sabe quais dados são guardados e para quê), proporcionalidade (só o necessário), igualdade de tratamento e respeito ao trabalhador, tratado como usuário da ferramenta e não como alvo de controle. Esses pontos se relacionam com direitos como a privacidade, a dignidade no trabalho e a não discriminação no acesso ao serviço `[FONTE A VERIFICAR: documentos a citar]`.

## 8.5 Limitações

Esta análise não substitui uma avaliação jurídica. Retenção, direitos do titular e encarregado dependem de decisão da administradora, e, sem levantamento de campo, não há dados reais sobre o uso de smartphone pelos moradores; o canal interfone é uma salvaguarda de projeto, e não uma resposta a dados coletados.
