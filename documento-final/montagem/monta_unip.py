# -*- coding: utf-8 -*-
"""Acrescenta ao docx gerado pelo pandoc as paginas pre-textuais do modelo da UNIP
(capa, folha de rosto, frase de enfase, sumario, rodape) e a numeracao de paginas."""
import sys, re, copy, json
from docx import Document
from docx.shared import Pt, Cm
from docx.enum.text import WD_ALIGN_PARAGRAPH as AL
from docx.oxml import OxmlElement, parse_xml
from docx.oxml.ns import qn, nsdecls

ENTRADA, SAIDA, LOGO, PAGS = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]
paginas = json.load(open(PAGS, encoding='utf-8')) if len(sys.argv) > 4 and PAGS != '-' else {}

TITULO = 'GESTÃO DE ENCOMENDAS EM CONDOMÍNIOS RESIDENCIAIS: REGISTRO, AVISO E RETIRADA SEGURA DE PACOTES NA PORTARIA'
NOMES = ['ADILSON BATISTA DO NASCIMENTO DE LIMA – R129IB1', 'DANIEL AUGUSTO AMARANTE DA SILVA – H900BA8',
         'LUCAS RIBEIRO TOMIOSSI KRIBELY – R990648', 'PEDRO URQUISA ROCHA – R310337', 'YSAAC DE SOUZA FRANÇA – R3000I4']
RODAPE = ('Elaborado pelos alunos da UNIP – Universidade Paulista Anchieta. Todos os direitos reservados. '
          'É permitida a reprodução parcial ou total desta obra, desde que citada a fonte e que não seja para venda ou qualquer fim comercial.')
FRASE = '"Quando não podemos mais mudar uma situação, somos desafiados a mudar a nós mesmos". (Viktor Frankl)'
RECUO = Cm(6.3)

d = Document(ENTRADA)
corpo = d.element.body
novos = []

def fonte(run, nome='Arial', tam=12, negrito=False, italico=False, cor=None):
    run.font.name = nome; run.font.size = Pt(tam); run.font.bold = negrito; run.font.italic = italico
    rpr = run._r.get_or_add_rPr(); rf = rpr.find(qn('w:rFonts'))
    if rf is None: rf = OxmlElement('w:rFonts'); rpr.insert(0, rf)
    for a in ('w:ascii', 'w:hAnsi', 'w:cs', 'w:eastAsia'): rf.set(qn(a), nome)

def par(texto='', negrito=False, tam=12, alinh=AL.CENTER, antes=0, depois=0, linha=1.5, recuo=None, quebra=False, italico=False, nome='Arial', sem_recuo_1a=True):
    p = d.add_paragraph(); p.style = d.styles['Normal']
    pf = p.paragraph_format
    pf.alignment = alinh; pf.space_before = Pt(antes); pf.space_after = Pt(depois); pf.line_spacing = linha
    pf.first_line_indent = Cm(0)
    if recuo is not None: pf.left_indent = recuo
    if quebra: pf.page_break_before = True
    if texto:
        r = p.add_run(texto); fonte(r, nome, tam, negrito, italico)
    novos.append(p._p); return p

def borda(p, lado, sz, espaco=1):
    ppr = p._p.get_or_add_pPr(); b = ppr.find(qn('w:pBdr'))
    if b is None: b = OxmlElement('w:pBdr'); ppr.append(b)
    e = OxmlElement('w:' + lado); e.set(qn('w:val'), 'single'); e.set(qn('w:sz'), str(sz)); e.set(qn('w:space'), str(espaco)); e.set(qn('w:color'), '000000'); b.append(e)

# ---------- capa
p = par(antes=14, depois=0)
p.add_run().add_picture(LOGO, width=Cm(4.9))
par('PROJETO INTEGRADO MULTIDISCIPLINAR', True, antes=20, depois=6)
par('CURSO SUPERIOR DE TECNOLOGIA EM ANÁLISE E DESENVOLVIMENTO DE SISTEMAS', True, depois=6)
for i, n in enumerate(NOMES): par(n, True, antes=(34 if i == 0 else 0), depois=6)
par(TITULO, True, antes=40, depois=6)
par('SÃO PAULO - SP', True, antes=60, depois=6)
par('UNIP ANCHIETA 2026', True, depois=0)

# ---------- folha de rosto
for i, n in enumerate(NOMES): par(n, True, antes=0, depois=6, quebra=(i == 0))
par(TITULO.split(':')[0], False, antes=110, depois=0, recuo=RECUO, linha=1.15)
par('Registro, aviso e retirada segura de pacotes na portaria', False, antes=4, depois=0, recuo=RECUO, linha=1.15)
par('Projeto Integrado Multidisciplinar em Análise e Desenvolvimento de Sistemas', False, antes=10, depois=0, recuo=RECUO, linha=1.15)
par('Projeto Integrado Multidisciplinar para obtenção do título de tecnólogo em Análise e Desenvolvimento de Sistemas, apresentado à Universidade Paulista – UNIP', False, antes=34, depois=0, recuo=RECUO, linha=1.15, alinh=AL.JUSTIFY)
q = par('Prof.ª Eliana', False, antes=40, depois=0, recuo=RECUO, linha=1.15); borda(q, 'top', 12, 4)
par('SÃO PAULO - SP', True, antes=110, depois=6)
par('UNIP ANCHIETA 2026', True)

# mover as paginas novas para o inicio do corpo
for i, el in enumerate(novos): corpo.insert(i, el)

# ---------- ajustar resumo / abstract / sumario do pandoc
def texto(p): return ''.join(t.text or '' for t in p.iter(qn('w:t')))
pars = list(corpo.iter(qn('w:p')))
def achar(txt, ini=0):
    for i in range(ini, len(pars)):
        if texto(pars[i]).strip() == txt: return i
    return None
def prelim(el, quebra=True):
    """Titulo pre-textual: negrito, sem estilo de titulo (nao entra no sumario)."""
    from docx.text.paragraph import Paragraph
    p = Paragraph(el, d._body)
    p.style = d.styles['Normal']
    t = ''.join(r.text for r in p.runs)
    for r in list(p.runs): r._r.getparent().remove(r._r)
    r = p.add_run(t); fonte(r, 'Arial', 12, True)
    p.paragraph_format.alignment = AL.LEFT; p.paragraph_format.first_line_indent = Cm(0)
    p.paragraph_format.space_after = Pt(6); p.paragraph_format.line_spacing = 1.5
    p.paragraph_format.page_break_before = quebra
for t in ('RESUMO', 'ABSTRACT'): prelim(pars[achar(t)])
i_sum = achar('SUMÁRIO'); i_ini = achar('MARCADOR_INICIO_DESENVOLVIMENTO'); i_fim = achar('MARCADOR_FIM_DESENVOLVIMENTO')
prelim(pars[i_sum])
for el in pars[i_sum + 1:i_ini]: el.getparent().remove(el)       # "(gerado pelo editor)"

# entradas do sumario: titulos 1 e 2 entre os marcadores + REFERENCIAS
from docx.text.paragraph import Paragraph
entradas = []
for el in pars[i_ini + 1:]:
    p = Paragraph(el, d._body); s = p.style.name if p.style is not None else ''
    t = texto(el).strip()
    if s in ('Heading 1', 'Heading 2') and t: entradas.append((1 if s == 'Heading 1' else 2, t))

def run_xml(tag_xml): return parse_xml(f'<w:r {nsdecls("w")}>{tag_xml}</w:r>')
toc = []
for k, (nivel, t) in enumerate(entradas):
    p = d.add_paragraph(); p.style = d.styles['Normal']; pf = p.paragraph_format
    pf.alignment = AL.LEFT; pf.first_line_indent = Cm(0); pf.left_indent = Cm(0.0 if nivel == 1 else 0.7)
    pf.space_before = Pt(3 if nivel == 1 else 0); pf.space_after = Pt(0); pf.line_spacing = 0.92
    pf.tab_stops.add_tab_stop(Cm(16.0), alignment=2, leader=1)   # direita, pontilhado
    if k == 0:
        p._p.append(run_xml('<w:fldChar w:fldCharType="begin"/>'))
        p._p.append(run_xml('<w:instrText xml:space="preserve"> TOC \\o "1-2" \\h \\z \\u </w:instrText>'))
        p._p.append(run_xml('<w:fldChar w:fldCharType="separate"/>'))
    r = p.add_run(t); fonte(r, 'Arial', 10 if nivel == 1 else 9, nivel == 1)
    r = p.add_run('\t' + str(paginas.get(t, 0))); fonte(r, 'Arial', 10 if nivel == 1 else 9, nivel == 1)
    if k == len(entradas) - 1: p._p.append(run_xml('<w:fldChar w:fldCharType="end"/>'))
    toc.append(p._p)
ref_sum = pars[i_sum]
for el in reversed(toc): ref_sum.addnext(el)

# quebra de secao depois do sumario (secao 1 = pre-textual, com o rodape da UNIP)
sect_final = corpo.find(qn('w:sectPr'))
sp = copy.deepcopy(sect_final)
for ref in sp.findall(qn('w:footerReference')) + sp.findall(qn('w:headerReference')): sp.remove(ref)
tipo = sp.find(qn('w:type'))
if tipo is None: tipo = OxmlElement('w:type'); sp.insert(0, tipo)
tipo.set(qn('w:val'), 'nextPage')
pbreak = OxmlElement('w:p'); ppr = OxmlElement('w:pPr'); ppr.append(sp); pbreak.append(ppr)
toc[-1].addnext(pbreak)

# marcadores de medicao: texto minusculo e branco
for el in (pars[i_ini], pars[i_fim]):
    for r in el.iter(qn('w:r')):
        rpr = r.find(qn('w:rPr'))
        if rpr is None: rpr = OxmlElement('w:rPr'); r.insert(0, rpr)
        for tag, val in (('w:sz', '2'), ('w:szCs', '2')):
            e = OxmlElement(tag); e.set(qn('w:val'), val); rpr.append(e)
        c = OxmlElement('w:color'); c.set(qn('w:val'), 'FFFFFF'); rpr.append(c)
    for pf in el.findall(qn('w:pPr')): pass
# REFERENCIAS em pagina nova
j = achar('REFERÊNCIAS')
if j is not None:
    ppr = pars[j].get_or_add_pPr() if hasattr(pars[j], 'get_or_add_pPr') else None
p_ref = Paragraph(pars[j], d._body); p_ref.paragraph_format.page_break_before = True
for el in pars[j + 1:]:
    q = Paragraph(el, d._body)
    if q.text.strip().startswith('MARCADOR') or not q.text.strip(): continue
    pf = q.paragraph_format; pf.line_spacing = 1.0; pf.first_line_indent = Cm(0); pf.left_indent = Cm(0)
    pf.alignment = AL.LEFT; pf.space_after = Pt(2); pf.space_before = Pt(0)
    for r in q.runs: r.font.size = Pt(9.5)

# ---------- rodapes
sec = d.sections
sec_pre, sec_corpo = sec[0], sec[1]
# pre-textual: texto da UNIP entre duas linhas
sec_pre.footer.is_linked_to_previous = False
fp = sec_pre.footer.paragraphs[0]
for r in list(fp.runs): r._r.getparent().remove(r._r)
fp.paragraph_format.alignment = AL.JUSTIFY; fp.paragraph_format.line_spacing = 1.0
fp.paragraph_format.space_before = Pt(0); fp.paragraph_format.space_after = Pt(0)
r = fp.add_run(RODAPE); fonte(r, 'Calibri', 8.5, False, True)
borda(fp, 'top', 4, 6); borda(fp, 'bottom', 18, 6)
# corpo: numero da pagina a direita
sec_corpo.footer.is_linked_to_previous = False
fb = sec_corpo.footer.paragraphs[0]
for r in list(fb.runs): r._r.getparent().remove(r._r)
fb.paragraph_format.alignment = AL.RIGHT
for xml in ('<w:fldChar w:fldCharType="begin"/>', '<w:instrText xml:space="preserve"> PAGE </w:instrText>', '<w:fldChar w:fldCharType="end"/>'):
    rr = run_xml(xml); fb._p.append(rr)
d.save(SAIDA)
print('entradas do sumario:', len(entradas))
json.dump([t for _, t in entradas], open(SAIDA + '.entradas.json', 'w', encoding='utf-8'), ensure_ascii=False)
