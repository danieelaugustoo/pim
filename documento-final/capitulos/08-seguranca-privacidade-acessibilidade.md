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

Este capítulo analisa a solução quanto à privacidade e proteção de dados, à segurança da informação, à acessibilidade e inclusão digital e aos aspectos éticos e sociais. A análise é acadêmica e não constitui parecer jurídico.

## 8.1 Privacidade e proteção de dados

O tratamento de dados pessoais no Brasil é regido pela Lei Geral de Proteção de Dados Pessoais (Lei nº 13.709/2018) (BRASIL, 2018). Entre seus princípios estão a finalidade, a adequação e a necessidade, entendida como a "limitação do tratamento ao mínimo necessário" (BRASIL, 2018, art. 6º, I a III). A solução trata o nome, o bloco, o apartamento e o canal de aviso do morador (com o contato, quando o canal exige), o nome do destinatário e o de quem retirou a encomenda, com data e hora. A finalidade é única: entregar a encomenda certa à pessoa certa.

Pela minimização, o sistema não registra o conteúdo da encomenda nem o remetente, só a transportadora, e não guarda contato quando o canal é o interfone. No sistema completo, o acesso seria por perfil: o porteiro vê apenas a sua portaria, o supervisor vê os relatórios dos condomínios que acompanha e o administrador gerencia usuários. O grupo definiu que os dados pessoais seriam mantidos por 90 dias após a retirada e depois anonimizados, preservando só números para os indicadores. É uma decisão de projeto: a lei prevê a eliminação dos dados após o término do tratamento, com exceções como o cumprimento de obrigação legal (BRASIL, 2018, art. 16), e prazos legais específicos precisam ser verificados `[FONTE A VERIFICAR]`. A lei também assegura ao titular a confirmação do tratamento, o acesso e a correção (art. 18) e prevê a indicação de um encarregado pelo controlador, que a Autoridade Nacional de Proteção de Dados pode dispensar em algumas hipóteses (art. 41); os caminhos práticos dependem de decisão da administradora. Todos os dados usados no trabalho são fictícios.

## 8.2 Segurança da informação

A principal medida é o código de retirada de seis dígitos, de uso único, válido só enquanto a encomenda está pendente, com limite de três tentativas por atendimento. A retirada acha a encomenda pelo código, e o porteiro confirma a unidade e o destinatário com o morador antes de entregar, porque um código errado pode coincidir com o de outra encomenda pendente (chance de cerca de 1 em 9.000 com 100 pendentes). No sistema completo, o código seguiria apenas na mensagem ao morador e o banco guardaria somente o seu resumo criptográfico (hash). Cada operação recebe identificador único, data e hora, o que garante rastreabilidade, e a entrada é validada. A segurança da rede (capítulo 7) inclui segmentação por VLAN, listas de controle de acesso, VPN, criptografia, autenticação em dois fatores no painel e cópias de segurança.

O protótipo tem limitações declaradas: não possui login nem perfis, os arquivos não são criptografados e a tela do porteiro mostra o código de retirada ao registrar a encomenda, o que contraria o requisito de que ele não seja exibido a terceiros. O grupo manteve essa característica e a declara como limitação.

## 8.3 Acessibilidade e inclusão digital

A solução considera moradores sem smartphone: o canal interfone permite que o porteiro avise por telefone interno e entregue o código impresso, e o canal é escolhido pelo morador no cadastro. A retirada exige o mesmo código de todos, o que garante tratamento igual. Isso dialoga com a Lei Brasileira de Inclusão (Lei nº 13.146/2015), cujo art. 63 torna obrigatória a acessibilidade nos sítios da internet mantidos por empresas com sede ou representação comercial no País ou por órgãos de governo (BRASIL, 2015).

Para as telas do sistema completo, recomenda-se seguir as diretrizes WCAG, do W3C, que definem os níveis A, AA e AAA (WORLD WIDE WEB CONSORTIUM, 2024) `[definir o nível adotado]`: contraste adequado, fonte ampliável, navegação por teclado, compatibilidade com leitores de tela e avisos que não dependam só de cor ou som. O protótipo, de console, não implementa esses recursos. Como o aviso por aplicativo ou SMS depende da nuvem, o interfone cobre a falha de internet.

## 8.4 Ética, impactos sociais e direitos humanos

São impactos esperados, e portanto hipóteses a confirmar em um piloto: menos conflitos por encomendas extraviadas ou entregues à pessoa errada, carga de trabalho mais previsível para o porteiro e um comprovante que protege morador e funcionário. Os principais riscos e o tratamento previsto são:

- **vigilância do porteiro:** os registros servem para rastrear encomendas e os relatórios são por condomínio, sem ranking de funcionários;
- **vazamento de dados:** minimização, acesso por perfil, comunicação criptografada e cópias de segurança;
- **exclusão de quem não usa tecnologia:** canal interfone e código impresso;
- **dependência da tecnologia:** funcionamento offline e plano de contingência em papel;
- **câmeras do condomínio:** ficam em rede isolada, fora do tratamento de dados da solução.

A solução busca transparência (o morador sabe quais dados são guardados e para quê), proporcionalidade, igualdade de tratamento e respeito ao trabalhador, tratado como usuário da ferramenta e não como alvo de controle, o que se relaciona com a privacidade, a dignidade no trabalho e a não discriminação `[FONTE A VERIFICAR: documentos a citar]`.

## 8.5 Limitações

A análise não substitui avaliação jurídica. Retenção, direitos do titular e encarregado dependem da administradora e, sem levantamento de campo, não há dados reais sobre o uso de smartphone pelos moradores: o canal interfone é uma salvaguarda de projeto, não uma resposta a dados coletados.
