# PIM II: Gestão de encomendas em condomínios

Projeto Integrado Multidisciplinar II (UNIP, curso de Análise e Desenvolvimento de Sistemas).

**Título:** Gestão de encomendas em condomínios residenciais: registro, aviso e retirada segura de pacotes na portaria.

**Organização fictícia:** Administradora Morada Central, com 10 condomínios residenciais.

## O problema

As portarias controlam as encomendas em caderno. Isso gera extravios, entregas à pessoa errada, falta de rastreabilidade e sobrecarga dos porteiros, e a administradora não tem dados para planejar equipe e espaço. Parte das portarias tem internet instável.

## A solução

Um nó em cada portaria, que funciona sem internet, e um consolidador central da administradora.

Fluxo principal: encomenda chega → porteiro registra → sistema indica a posição na estante → gera o código de retirada → avisa o morador → morador retira com o código → operações sincronizam com a central → relatórios.

O protótipo em C implementa dois executáveis: `portaria` (nó local) e `central` (consolidador). A rede entre eles é simulada por arquivos. O que fica fora do protótipo está em `PLANO.md`, seção 5.3.

## Integrantes

A preencher em `00-projeto/integrantes.md` (nomes, RA e papéis no Scrum).

## Como compilar e rodar

Os comandos rodam dentro de `05-programa-c/`. O código ainda não foi escrito (Sprint 1 em diante), então estes comandos passam a funcionar quando o `Makefile` e o `build.bat` forem criados.

```
make                 # compila bin/portaria e bin/central
make test            # compila e roda os testes
make clean           # apaga executáveis e objetos
build.bat            # compila no Windows sem make (MinGW-w64)
bin/portaria 1       # abre a portaria P01
bin/central          # consolida e gera o relatório
```

Requisito: `gcc` com suporte a C99 (MinGW-w64 no Windows, `build-essential` no Linux).

## Estrutura do repositório

| Pasta | Conteúdo | Etapa do manual |
|---|---|---|
| `00-projeto/` | regras do PIM, glossário, rastreabilidade, cronograma e integrantes | controle |
| `01-organizacao/` | caracterização da organização e processos | 1 |
| `02-pesquisa/` | problema, objetivos, metodologia, fundamentação e fontes | 2 |
| `03-engenharia-software/` | requisitos, casos de uso, arquitetura, ADRs, Scrum e UML | 3 |
| `04-banco-de-dados/` | modelos, normalização, scripts SQL e NoSQL | 4 |
| `05-programa-c/` | protótipo em C, testes, dados e algoritmos | 5 |
| `06-redes/` | topologia, endereçamento, VLANs, nuvem e segurança da infraestrutura | 6 |
| `07-seguranca-privacidade-acessibilidade/` | análise curta de segurança, privacidade e acessibilidade | 7 |
| `08-integracao/` | integração, implantação, benefícios e evolução | 8 |
| `documento-final/` | o trabalho em ABNT | entrega |

Toda pasta tem um `README.md` com o que ela guarda e quais exigências do manual atende.

## Documentos de referência

- [`PLANO.md`](PLANO.md): fonte de verdade do projeto (escopo, arquitetura, estrutura, convenções, etapas e sprints).
- [`CLAUDE.md`](CLAUDE.md): regras que o Claude Code segue em toda sessão.
- [`00-projeto/rastreabilidade.md`](00-projeto/rastreabilidade.md): exigência do manual → arquivo → capítulo → status.

## Autoria

Os capítulos do trabalho (`documento-final/capitulos/`) são redigidos pelo grupo. O Claude Code gera código, scripts, diagramas e documentação técnica. Todos os dados de exemplo são fictícios.
