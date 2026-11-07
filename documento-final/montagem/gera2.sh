#!/bin/bash
# Gera o documento no modelo da UNIP em duas passagens (a 2a preenche as paginas do sumario).
cd /tmp/claude-0/-home-user-pim/1eb6241f-b33c-5a31-a9e2-e4e8ae5fb8f3/scratchpad/doc
python3 build_doc.py >/dev/null && pandoc trabalho.md -o trabalho.docx --reference-doc=ref_abnt.docx --from markdown+pipe_tables+fenced_divs+implicit_figures && python3 pos.py trabalho.docx base.docx
python3 monta_unip.py base.docx passo1.docx modelo/logo-unip.png - >/dev/null && soffice --headless --convert-to pdf passo1.docx >/dev/null 2>&1
python3 paginas.py passo1.pdf passo1.docx.entradas.json paginas.json
python3 monta_unip.py base.docx PIM_Morada_Central.docx modelo/logo-unip.png paginas.json && soffice --headless --convert-to pdf PIM_Morada_Central.docx >/dev/null 2>&1
n=$(pdfinfo PIM_Morada_Central.pdf | awk '/Pages/{print $2}'); echo "total $n paginas"
python3 - <<'PYEOF'
import subprocess,re
pdf='PIM_Morada_Central.pdf'
def y(page,word):
    out=subprocess.run(['pdftotext','-f',str(page),'-l',str(page),'-bbox',pdf,'-'],capture_output=True,text=True).stdout
    for m in re.finditer(r'<word xMin="[\d.]+" yMin="([\d.]+)" xMax="[\d.]+" yMax="([\d.]+)">([^<]*)</word>',out):
        if word in m.group(3): return float(m.group(1))
n=int(re.search(r'Pages:\s+(\d+)',subprocess.run(['pdfinfo',pdf],capture_output=True,text=True).stdout).group(1))
ini=fim=None
for p in range(1,n+1):
    a=y(p,'MARCADOR_INICIO_DESENVOLVIMENTO'); b=y(p,'MARCADOR_FIM_DESENVOLVIMENTO')
    if a is not None: ini=(p,a)
    if b is not None: fim=(p,b)
H=841.9; top=85; bot=H-57; util=bot-top
print('introducao na pag',ini[0],'| conclusao termina na pag',fim[0],'| comprimento real: %.2f paginas'%((fim[0]-ini[0]-1)+(bot-ini[1])/util+(fim[1]-top)/util))
PYEOF
