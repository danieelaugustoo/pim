from docx import Document
from docx.shared import Pt, Cm
from docx.enum.text import WD_ALIGN_PARAGRAPH
from docx.oxml.ns import qn
from docx.oxml import OxmlElement
import sys
d=Document(sys.argv[1])
def bordas(tbl):
    tblPr=tbl._tbl.tblPr
    b=OxmlElement('w:tblBorders')
    for lado in ('top','left','bottom','right','insideH','insideV'):
        e=OxmlElement(f'w:{lado}'); e.set(qn('w:val'),'single'); e.set(qn('w:sz'),'4'); e.set(qn('w:color'),'000000'); b.append(e)
    tblPr.append(b)
for t in d.tables:
    bordas(t)
    for row in t.rows:
        for c in row.cells:
            for p in c.paragraphs:
                pf=p.paragraph_format; pf.line_spacing=1.0; pf.first_line_indent=Cm(0); pf.alignment=WD_ALIGN_PARAGRAPH.LEFT
                for r in p.runs: r.font.size=Pt(10); r.font.name='Times New Roman'
d.save(sys.argv[2])
