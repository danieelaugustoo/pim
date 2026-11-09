# Modelo de texto dos slides (para copiar no Canva)

Cada slide tem **título**, **no máximo 3 tópicos** curtos, a **figura** e a **legenda** (copiar na figura, em letra pequena). Os números são os do trabalho. Fonte: **Fonte: elaborado pelos autores (2026)**.

---

### Slide 1: Capa
**Título:** Gestão de encomendas em condomínios residenciais
**Subtítulo:** Registro, aviso e retirada segura de pacotes na portaria
**Linha:** PIM II • Análise e Desenvolvimento de Sistemas • UNIP Anchieta • 2026
**Autores:** Adilson Batista do Nascimento de Lima • Daniel Augusto Amarante da Silva • Lucas Ribeiro Tomiossi Kribely • Pedro Urquisa Rocha • Ysaac de Souza França
**Orientadora:** Prof.ª Eliana
**Imagem:** logo da UNIP

### Slide 2: O problema (Ysaac)
**Título:** O caderno da portaria
- Extravios e entregas à pessoa errada
- Porteiro sobrecarregado, sem rastreio
- Internet instável em parte das portarias

**Faixa de números:** 10 condomínios • ~960 unidades • 40 porteiros
**Figura 2** (processo atual). Legenda: *Processo atual de encomendas (caderno).*

### Slide 3: A solução (Ysaac)
**Título:** Portaria que funciona sem internet
- Nó na portaria: opera offline
- Central: consolida sem duplicar
- Aviso por app, SMS ou interfone

**Figura 3** (processo proposto). Legenda: *Processo proposto de encomendas.*

### Slide 4: Engenharia de software (Adilson)
**Título:** Engenharia de software ágil
- Scrum: PO Lucas, SM Daniel
- 16 histórias, 15 implementadas
- 12 RF • 8 RNF • 8 casos de uso

**Figura 4** (casos de uso). Legenda: *Diagrama de casos de uso.*

### Slide 5: Sincronização (Adilson)
**Título:** Sincronizar sem duplicar
- Cada operação tem identificador único
- Sem internet, a fila espera
- A central ignora ids já aplicados

**Figura 5** (sequência). Legenda: *Sincronização e consolidação (ADR-003).*

### Slide 6: Banco de dados (Lucas)
**Título:** Banco de dados relacional
- MySQL 8
- 11 tabelas, 44 restrições
- Normalizado até a 3ª forma normal

**Figura 6** (DER). Legenda: *Diagrama entidade-relacionamento.*

### Slide 7: Banco, o que garante (Lucas)
**Título:** O que o banco garante
- A chave da operação impede duplicar
- Código guardado só como hash (SHA-256)
- Resultados batem com o programa em C

**Rodapé pequeno:** hash: sistema completo; o protótipo usa arquivos CSV.
**Figura 7** (consulta SQL). Legenda: *Consulta no MySQL 8.4, com dados de exemplo.*

### Slide 8: Programação em C (Daniel)
**Título:** Programação estruturada em C
- C99, sem avisos de compilação
- Estante: matriz 4 x 12
- 9 conjuntos de testes passando

**Figura 8** (fluxograma do A1). Legenda: *Fluxograma da alocação na estante (A1).*

### Slide 9: Demonstração (Daniel)
**Título:** Demonstração ao vivo
1. Portaria offline
2. Registrar encomendas
3. Sincronizar com a central
4. Retirar com o código

*(Este slide é a exceção: 4 passos curtos, sem figura.)*

### Slide 10: Redes e conclusão (Pedro)
**Título:** Redes, inclusão e conclusão
- 44 redes, 4 VLANs, 15 de 15 testes
- Interfone com código para quem não usa smartphone
- Viável; benefícios a medir em piloto

**Rodapé pequeno:** aviso e rede simulados no programa; VPN só no desenho.
**Figuras 9 e 10** (topologia; testes T2 e T6), lado a lado. Legenda: *Topologia no Packet Tracer 9.0.1 e testes T2 e T6.*

### Slide 11 (opcional): Encerramento
**Título:** Obrigado!
**Linha:** Perguntas?
**Texto:** github.com/danieelaugustoo/pim
**Imagem:** QR code do repositório

---

## Ajustes finais no Canva

- **Letra:** título 40 pt ou mais, tópicos 28 pt, legendas 14 pt.
- **Cores:** fundo claro, uma cor de destaque. Usar a mesma em todos os slides.
- **Figuras:** colocar uma por slide, grande, centralizada. As 2, 3 e 8 têm SVG em `documento-final/figuras/fontes/`.
- **Conferir antes de apresentar:** nenhum slide com a palavra "fictício", e nenhum com percentual de melhoria.
