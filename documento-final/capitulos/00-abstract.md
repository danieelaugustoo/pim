# Abstract (roteiro)

> **ROTEIRO, não é o texto.** O grupo escreve o abstract e **substitui** este conteúdo na seção "Texto do grupo".

**Exigência do manual:** abstract em inglês (ou espanhol ou francês), com as palavras-chave no mesmo idioma.

## Roteiro

- Mesma estrutura do resumo (`00-resumo.md`): contexto, objetivo, método, solução, resultados verificados e conclusão.
- Escrever a partir do resumo já aprovado, sem ferramenta de tradução automática como único recurso e sem copiar frases da internet (risco de similaridade).
- Termos técnicos a padronizar em inglês antes de escrever (sugestões a confirmar): *parcel management*, *condominium*, *concierge desk* (portaria), *offline-first*, *synchronization*, *idempotent*.
- Palavras-chave (*keywords*): tradução das do resumo, na mesma ordem.

## Checklist

- [x] Idioma escolhido pelo grupo: inglês (decisão de 2026-10-29).
- [ ] Mesmo conteúdo e mesmo tamanho aproximado do resumo.
- [ ] Palavras-chave no mesmo idioma.
- [ ] Revisão de um integrante com bom domínio do idioma.

---

## Texto do grupo

> **Draft** written from the Portuguese summary (authorized by Prof. Eliana). The group reviews and adjusts it, and a member with good English should proofread it.

**ABSTRACT**

This work addresses parcel management at the front desks of residential condominiums, based on a fictional scenario: an administrator of ten condominiums whose front desks record parcels in a paper notebook, which leads to lost parcels, deliveries to the wrong person, lack of traceability and an overloaded staff, in addition to unstable internet access at some desks. The goal was to develop and document a computational solution that reduces these problems through offline operation and central synchronization. The methodology combined a literature review, an analysis of the scenario, Scrum-based development and verification by tests, without a field survey with users. The proposed solution has two parts: a front desk node, which records the parcel, suggests a shelf position, generates a unique pickup code, notifies the resident through the chosen channel (app, SMS or intercom with a printed code) and works without internet; and a central server, which applies each operation sent by the desks exactly once and produces consolidated reports. The work produced the requirements and models, a relational MySQL database with eleven tables, a C language prototype with six documented algorithms and nine automated test suites, a network design with VLANs, access rules and a cloud, and an analysis of privacy, security and accessibility. The prototype tests passed, and consolidation does not duplicate records when the same data is processed twice. The network and the resident notification are simulated, and the expected benefits, such as fewer lost parcels, depend on a pilot to be measured. It is concluded that the solution is technically feasible and that its real effects remain to be evaluated.

**Keywords:** parcels; condominiums; distributed systems; offline operation; relational database.
