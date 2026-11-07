from docx import Document
from docx.shared import Pt, Cm, RGBColor
from docx.enum.text import WD_ALIGN_PARAGRAPH
from docx.oxml.ns import qn
from docx.oxml import OxmlElement
d=Document('ref.docx')
for s in d.sections:
    s.page_width=Cm(21.0); s.page_height=Cm(29.7)
    s.top_margin=Cm(3); s.left_margin=Cm(3); s.bottom_margin=Cm(2); s.right_margin=Cm(2)
S={st.name:st for st in d.styles}
def fonte(st,nome='Times New Roman',tam=12,neg=None):
    st.font.name=nome; st.font.size=Pt(tam)
    rpr=st.element.get_or_add_rPr()
    rf=rpr.find(qn('w:rFonts'))
    if rf is None:
        rf=OxmlElement('w:rFonts'); rpr.append(rf)
    for a in ('w:ascii','w:hAnsi','w:cs','w:eastAsia'): rf.set(qn(a),nome)
    for a in ('w:asciiTheme','w:hAnsiTheme','w:cstheme','w:eastAsiaTheme'):
        if rf.get(qn(a)) is not None: del rf.attrib[qn(a)]
    if neg is not None: st.font.bold=neg
    st.font.color.rgb=RGBColor(0,0,0)
for n,st in S.items():
    if st.type==1 and n!='Source Code': fonte(st)
for n in ('Normal','Body Text','First Paragraph','Compact'):
    st=S[n]; pf=st.paragraph_format
    pf.line_spacing=1.5; pf.space_after=Pt(0); pf.space_before=Pt(0); pf.alignment=WD_ALIGN_PARAGRAPH.JUSTIFY
    if n in ('Body Text','First Paragraph'): pf.first_line_indent=Cm(1.5)
    if n=='Compact': pf.line_spacing=1.0; pf.first_line_indent=Cm(0)
for i in (1,2,3):
    st=S[f'Heading {i}']; fonte(st,neg=True)
    pf=st.paragraph_format; pf.line_spacing=1.5; pf.space_before=Pt(12 if i>1 else 0); pf.space_after=Pt(6); pf.keep_with_next=True
    pf.alignment=WD_ALIGN_PARAGRAPH.LEFT; pf.first_line_indent=Cm(0)
S['Heading 1'].font.all_caps=True
for n in ('Image Caption','Table Caption','Captioned Figure','Figure'):
    if n in S:
        st=S[n]; fonte(st,tam=10); st.paragraph_format.alignment=WD_ALIGN_PARAGRAPH.CENTER; st.paragraph_format.first_line_indent=Cm(0); st.paragraph_format.line_spacing=1.0
if 'Source Code' in S:
    st=S['Source Code']; st.font.name='Courier New'; st.font.size=Pt(9); st.paragraph_format.line_spacing=1.0; st.paragraph_format.first_line_indent=Cm(0)
d.save('ref_abnt.docx'); print('ref ok')
