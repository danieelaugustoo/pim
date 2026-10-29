# Plano de implantação (Etapa 8)

> **Roteiro de tópicos** para o capítulo 9. É uma **proposta de plano**: nada foi implantado. Prazos, responsáveis e condomínio-piloto são decisões da Administradora Morada Central e do grupo; o que depende dessa decisão está marcado `[A DEFINIR]`.

## 1. Visão geral

Implantação **em ondas**, começando por um piloto, para aprender com poucos usuários antes de levar a solução aos 10 condomínios.

| Fase | O quê | Duração sugerida |
|---|---|---|
| 0. Preparação | Infraestrutura mínima, cadastro de moradores, comunicado, treinamento | `[A DEFINIR]` |
| 1. Piloto | Um condomínio usa a solução; o caderno fica de reserva | 2 semanas (proposta do `PLANO.md`) |
| 2. Avaliação | Comparar com os indicadores; corrigir problemas | `[A DEFINIR]` |
| 3. Expansão | Demais condomínios em ondas, ajustadas pelo que o piloto mostrar | `[A DEFINIR]` |
| 4. Operação | Suporte, manutenção e acompanhamento dos indicadores | contínuo |

## 2. Preparação

**Infraestrutura** (detalhes em `06-redes/equipamentos.md` e `enderecamento-ip.md`):
- [ ] PC da portaria com o programa instalado e nobreak;
- [ ] rede local conforme as VLANs; acesso à central pela VPN quando houver internet;
- [ ] impressora para o código de retirada (canal interfone), se for usada;
- [ ] backup configurado (regra 3-2-1, `06-redes/seguranca-infraestrutura.md`).

**Escolha do condomínio-piloto** `[A DEFINIR pela administradora]`. Critérios sugeridos: volume de encomendas suficiente para testar, porteiros abertos à mudança, internet disponível (e, se possível, um segundo condomínio com internet instável para testar o modo offline na prática).

**Dados iniciais:**
- [ ] cadastrar os moradores e o canal de aviso de cada um (US07), com o consentimento e o aviso de privacidade da seção 5;
- [ ] **no primeiro dia, cadastrar as pendências que ainda estão no caderno**, para a estante e o sistema começarem iguais;
- [ ] conferir a estante física com o mapa do sistema;
- [ ] **medir a linha de base** nos primeiros dias, ainda com o caderno (extravios, tempo de registro, pendências antigas), para comparar com os indicadores de `beneficios-e-indicadores.md`.

## 3. Treinamento dos porteiros

- Sessão curta e prática, com a encomenda de exemplo (registrar, avisar, retirar, ver o mapa da estante).
- **Cartilha de uma página** com os cinco passos do dia a dia e o que fazer quando algo falha. Conteúdo sugerido:
  1. registrar a encomenda (opção 1) e guardar na posição indicada;
  2. conferir o aviso ao morador;
  3. na retirada, pedir o código (três tentativas) e o nome de quem retira (opção 2);
  4. ver o mapa da estante e as pendências antigas (opções 5 e 7);
  5. se a internet cair: continuar normalmente; as operações seguem na fila e são enviadas ao voltar (opção 8).
- Mensagem importante: a ferramenta apoia o porteiro; os registros servem para rastrear encomendas, não para vigiar pessoas (`07-.../analise.md`, seção 4).

## 4. Comunicação aos moradores

- Comunicado do condomínio explicando: o que muda, como escolher o canal de aviso (app, SMS ou interfone), para que serve o **código de retirada** e que ele não deve ser compartilhado.
- Alternativa para quem não usa smartphone: aviso por interfone com código impresso.
- Canal para dúvidas e para pedidos sobre os dados pessoais `[A DEFINIR]`.

## 5. Privacidade na implantação

- Informar quais dados são tratados, para quê e por quanto tempo (`07-.../analise.md`, seção 1).
- Acesso por perfil e senhas individuais no sistema completo.
- Retenção e descarte dos registros do caderno antigo `[A DEFINIR]`.

## 6. Plano de contingência

| Falha | O que fazer |
|---|---|
| Sem internet | Seguir normalmente: o nó da portaria funciona offline; sincronizar ao voltar |
| PC da portaria quebrou | Usar um **formulário em papel** (data, unidade, destinatário, transportadora, tamanho, posição); lançar os registros no sistema depois, na ordem |
| Queda de energia | Nobreak mantém o PC pelo tempo necessário para salvar; dados já gravados em arquivo |
| Arquivo de dados corrompido | Restaurar o backup mais recente e relançar o que veio depois a partir do papel e do log da rede |
| Aviso não chegou ao morador | O porteiro avisa pelo interfone; o registro do aviso mostra o que foi tentado |

## 7. Critérios para expandir

Avançar da fase do piloto para a expansão quando, ao fim das duas semanas:
- [ ] os porteiros registram e retiram sem recorrer ao caderno;
- [ ] não há divergência entre estante física e mapa do sistema;
- [ ] os indicadores de `beneficios-e-indicadores.md` foram medidos e não pioraram em relação ao "antes";
- [ ] os problemas encontrados foram corrigidos ou registrados com plano.

## 8. Riscos da implantação

| Risco | Mitigação |
|---|---|
| Resistência à mudança | Treinamento prático, cartilha, caderno de reserva durante o piloto |
| Cadastro incompleto de moradores | Aviso manual por interfone enquanto o cadastro cresce |
| Registro "esquecido" na hora da correria | Revisão diária do mapa da estante contra a estante física |
| Internet ruim em alguns locais | Modo offline e sincronização assíncrona (ADR-003) |
| Custos não previstos | Cotação dos equipamentos (`06-redes/equipamentos.md`, itens `[A COTAR]`) antes da decisão |

## 9. O que depende da administradora

Orçamento, escolha do piloto, datas, responsáveis pelo treinamento e pelo suporte, política de retenção de dados e aprovação do comunicado aos moradores.
