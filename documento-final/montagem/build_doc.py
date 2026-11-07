import re, os, sys, subprocess, shutil
from PIL import Image, ImageDraw, ImageFont
ROOT='/home/user/pim'
W='/tmp/claude-0/-home-user-pim/1eb6241f-b33c-5a31-a9e2-e4e8ae5fb8f3/scratchpad/doc'
FIG=ROOT+'/documento-final/figuras'
CAP=ROOT+'/documento-final/capitulos'
os.makedirs(W+'/fig',exist_ok=True)

def texto(path):
    s=open(path,encoding='utf-8').read()
    i=s.index('## Texto do grupo')
    t=s[i+len('## Texto do grupo'):].strip('\n')
    # remove a nota de rascunho (linhas de citacao no topo)
    linhas=t.split('\n'); out=[]; topo=True
    for l in linhas:
        if topo and (l.startswith('>') or l.strip()==''): continue
        topo=False; out.append(l)
    return '\n'.join(out)

def placeholder(nome,rotulo,w=690,h=420):
    p=f'{W}/fig/{nome}.png'
    im=Image.new('RGB',(w,h),(235,235,235)); d=ImageDraw.Draw(im)
    d.rectangle([4,4,w-5,h-5],outline=(120,120,120),width=4)
    try: f=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',44)
    except: f=ImageFont.load_default()
    d.text((40,h//2-30),rotulo+' (imagem pendente)',fill=(80,80,80),font=f)
    im.save(p); return p

def imagem(caminho,legenda):
    im=Image.open(caminho); w,h=im.size
    base=os.path.basename(caminho)
    lim={'figura-01-organograma.png':(10.0,6.8),'figura-02-processo-atual.png':(14.0,6.5),'figura-03-processo-proposto.png':(14.0,7.6),'figura-08-fluxograma-a1.png':(14.0,6.8),'figura-09-topologia.png':(13.0,7.4),'figura-04-casos-de-uso.png':(9.8,9.0),'figura-05-sequencia-sincronizacao.png':(12.5,11.8),'figura-06-der.png':(16.0,10.0)}
    MAXW,MAXH=lim.get(base,(min(16.0,w/60.0),8.5))
    esc=min(MAXW/(w/100.0),MAXH/(h/100.0))
    wc=w/100.0*esc; hc=h/100.0*esc
    return f'![{legenda}]({caminho}){{width={wc:.1f}cm height={hc:.1f}cm}}\n'

def figuras(t):
    # marcador simples: **[Figura N – cap. Fonte: X. Arquivo: `figuras/arq`]**
    def um(m):
        n=m.group(1); cap=m.group(2).strip(); fonte=m.group(3).strip(); arq=m.group(4)
        caminho=f'{FIG}/{os.path.basename(arq)}'
        if not os.path.exists(caminho):
            caminho=placeholder(f'f{n}',f'Figura {n}')
        return imagem(caminho,f'Figura {n} – {cap}. Fonte: {fonte}.')
    t=re.sub(r'\*\*\[Figura (\d+) – (.*?)\. Fonte: (.*?)\. Arquivo: `figuras/([^`]+)`\]\*\*',um,t)
    return t

partes=[]
# capa e sumario (marcadores)
for arq,titulo in [('00-resumo.md','RESUMO'),('00-abstract.md','ABSTRACT')]:
    t=texto(f'{CAP}/{arq}')
    t=re.sub(r'^\*\*(RESUMO|ABSTRACT)\*\*\s*','',t.strip())
    partes.append(f'# {titulo} {{.unnumbered}}\n\n{t}\n\n\\newpage\n')
partes.append('# SUMÁRIO {.unnumbered}\n\n(gerado pelo editor)\n\n\\newpage\n')
partes.append('MARCADOR_INICIO_DESENVOLVIMENTO\n')
caps=['01-introducao.md','02-organizacao.md','03-pesquisa.md','04-engenharia-software.md','05-banco-de-dados.md','06-programacao-c.md','07-redes.md','08-seguranca-privacidade-acessibilidade.md','09-integracao.md','10-conclusao.md']
for c in caps:
    t=figuras(texto(f'{CAP}/{c}'))
    partes.append(t+'\n\n')
partes.append('MARCADOR_FIM_DESENVOLVIMENTO\n')
# referencias
ref=open(ROOT+'/documento-final/referencias.md',encoding='utf-8').read()
refl=[l for l in ref.split('\n') if re.match(r'^[A-ZÀ-Ú]{3,}',l)]
partes.append('\\newpage\n\n# REFERÊNCIAS {.unnumbered}\n\n'+'\n\n'.join(refl)+'\n')
md='\n'.join(partes)
# MARCADORES como paragrafos simples
open(W+'/trabalho.md','w',encoding='utf-8').write(md)
print('md gerado',len(md.split()),'palavras')
