# Montagem do documento no modelo da UNIP

Scripts que geram o rascunho do trabalho (`versoes/PIM_Morada_Central_rascunho_*.docx`) a partir dos
capítulos em `capitulos/` (seção "Texto do grupo"), das figuras em `figuras/` e de `referencias.md`.

- `build_doc.py`: junta os capítulos em Markdown e insere as figuras com tamanhos legíveis.
- `pos.py`: bordas e fonte das tabelas. `mkref.py`: gera `ref_abnt.docx` (estilos ABNT).
- `monta_unip.py`: acrescenta capa, folha de rosto, frase de ênfase, sumário, rodapé da UNIP nas
  páginas iniciais e numeração a partir da introdução, seguindo o modelo da UNIP.
- `paginas.py` e `gera2.sh`: montam em duas passagens (a segunda preenche as páginas do sumário) e medem
  o comprimento da introdução à conclusão.

Os caminhos dentro dos scripts apontam para a pasta temporária da sessão em que foram criados e precisam
ser ajustados para rodar em outra máquina (precisa de Python com `python-docx` e `Pillow`, `pandoc` e
LibreOffice). O sumário é um campo do Word: depois de editar, clique com o botão direito nele e escolha
**Atualizar campo**.
