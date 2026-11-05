# -*- coding: utf-8 -*-
"""Gera os fluxogramas das Figuras 2, 3, 10 e 16 em grade (largos e legiveis em A4).

Uso: python3 fluxogramas_grade.py <pasta_de_saida>
Escreve os SVG; svg_para_png.js (Node + Playwright) converte para PNG.
Os fluxogramas Mermaid em */diagramas/*.mmd continuam sendo a fonte "vertical"
de cada processo; estes sao as versoes compactas usadas no documento final.
"""
import os, sys, html

CW, CH = 372, 176          # passo da grade (largura, altura)
NW, NH = 296, 112          # tamanho padrao de uma caixa
FS, LH = 22, 27            # tamanho da fonte e espaco entre linhas
FONTE = 'DejaVu Sans, Arial, sans-serif'

class Diagrama:
    def __init__(self, margem_dir=0):
        self.nos = {}; self.arestas = []; self.margem_dir = margem_dir
    def no(self, nid, col, row, linhas, tipo='caixa'):
        self.nos[nid] = dict(col=col, row=row, linhas=linhas.split('|'), tipo=tipo)
    def liga(self, a, b, rotulo='', de='auto', para='auto', duplo=False, rota=None):
        self.arestas.append((a, b, rotulo, de, para, duplo, rota))
    def grade(self, col, row):
        return 40 + col * CW + NW / 2, 30 + row * CH + NH / 2
    def centro(self, nid):
        n = self.nos[nid]; return self.grade(n['col'], n['row'])
    def dims(self, nid):
        return (NW + 12, NH + 40) if self.nos[nid]['tipo'] == 'dec' else (NW, NH)
    def ponto(self, nid, lado):
        x, y = self.centro(nid); w, h = self.dims(nid)
        return {'t': (x, y - h / 2), 'b': (x, y + h / 2), 'l': (x - w / 2, y), 'r': (x + w / 2, y)}[lado]
    def svg(self):
        maxc = max(n['col'] for n in self.nos.values()); maxr = max(n['row'] for n in self.nos.values())
        W = int(40 + maxc * CW + NW + 40 + self.margem_dir); H = int(30 + maxr * CH + NH + 50)
        o = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" font-family="{FONTE}">',
             '<defs><marker id="s" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto-start-reverse"><path d="M0,0 L10,5 L0,10 z" fill="#333"/></marker></defs>',
             f'<rect width="{W}" height="{H}" fill="white"/>']
        for a, b, rot, de, para, duplo, rota in self.arestas:
            ca, cb = self.centro(a), self.centro(b)
            if de == 'auto':
                if abs(ca[1] - cb[1]) < 1: de, para = ('r', 'l') if cb[0] > ca[0] else ('l', 'r')
                else: de, para = ('b', 't') if cb[1] > ca[1] else ('t', 'b')
            p1 = self.ponto(a, de); p2 = self.ponto(b, para)
            pts = [p1]
            if rota:
                pts += [self.grade(c, r) for c, r in rota]
            elif de in 'bt' and para in 'bt':
                if abs(p1[0] - p2[0]) > 1:
                    ym = (p1[1] + p2[1]) / 2; pts += [(p1[0], ym), (p2[0], ym)]
            elif de in 'lr' and para in 'lr':
                if abs(p1[1] - p2[1]) > 1:
                    xm = (p1[0] + p2[0]) / 2; pts += [(xm, p1[1]), (xm, p2[1])]
            elif de in 'bt' and para in 'lr':
                pts += [(p1[0], p2[1])]
            elif de in 'lr' and para in 'bt':
                pts += [(p2[0], p1[1])]
            pts.append(p2)
            d = 'M' + ' L'.join(f'{x:.0f},{y:.0f}' for x, y in pts)
            ini = ' marker-start="url(#s)"' if duplo else ''
            o.append(f'<path d="{d}" fill="none" stroke="#333" stroke-width="2.4" marker-end="url(#s)"{ini}/>')
            if rot:
                (x0, y0), (x1, y1) = pts[-2], pts[-1]
                if abs(x1 - x0) < 1:     # ultimo trecho vertical: rotulo a direita
                    lx, ly, anc = x1 + 8, y0 + (y1 - y0) * 0.5 + 7, 'start'
                else:                     # horizontal: rotulo acima do trecho
                    lx, ly, anc = x0 + (x1 - x0) * 0.5, y0 - 9, 'middle'
                o.append(f'<text x="{lx:.0f}" y="{ly:.0f}" font-size="{FS-2}" font-weight="bold" fill="#222" text-anchor="{anc}" paint-order="stroke" stroke="white" stroke-width="5">{html.escape(rot)}</text>')
        for nid, n in self.nos.items():
            x, y = self.centro(nid); w, h = self.dims(nid)
            if n['tipo'] == 'dec':
                pts = f'{x},{y-h/2} {x+w/2},{y} {x},{y+h/2} {x-w/2},{y}'
                o.append(f'<polygon points="{pts}" fill="#fff4d6" stroke="#8a6d1d" stroke-width="2.4"/>')
            elif n['tipo'] == 'term':
                o.append(f'<rect x="{x-w/2}" y="{y-h/2}" width="{w}" height="{h}" rx="{h/2}" fill="#dcefe0" stroke="#3c7a4a" stroke-width="2.4"/>')
            else:
                o.append(f'<rect x="{x-w/2}" y="{y-h/2}" width="{w}" height="{h}" rx="9" fill="#e8eefc" stroke="#4a5d9a" stroke-width="2.4"/>')
            k = len(n['linhas']); y0 = y - (k - 1) * LH / 2 + FS * 0.35
            for i, l in enumerate(n['linhas']):
                o.append(f'<text x="{x}" y="{y0 + i*LH:.0f}" font-size="{FS}" text-anchor="middle" fill="#111">{html.escape(l)}</text>')
        o.append('</svg>')
        return '\n'.join(o)

def fig02():
    d = Diagrama()
    d.no('A', 0, 0, 'Entregador chega|à portaria', 'term')
    d.no('B', 1, 0, 'Porteiro anota:|data, nome, bloco/apto|e transportadora')
    d.no('C', 2, 0, 'Pacote vai para sala|ou armário (sem|posição definida)')
    d.no('D', 3, 0, 'Consegue avisar|pelo interfone?', 'dec')
    d.no('F', 2, 1, 'Morador não é avisado|(descobre depois)')
    d.no('E', 3, 1, 'Morador é avisado')
    d.no('G', 2.5, 2, 'Morador retira|o pacote')
    d.no('H', 1, 2, 'Assina o|caderno?', 'dec')
    d.no('I', 0, 3, 'Retirada registrada', 'term')
    d.no('J', 1, 3, 'Retirada|sem registro')
    d.no('K', 2, 3, 'Extravio ou reclamação|por telefone ou|WhatsApp, para a sede')
    for a, b in [('A','B'),('B','C'),('C','D')]: d.liga(a, b)
    d.liga('D','E','Sim'); d.liga('D','F','Não','b','t')
    d.liga('E','G','', 'b','t'); d.liga('F','G','', 'b','t')
    d.liga('G','H','','l','r'); d.liga('H','I','Sim','b','t'); d.liga('H','J','Nem sempre','b','t'); d.liga('J','K')
    return d

def fig03():
    d = Diagrama()
    d.no('A',0,0,'Encomenda chega|à portaria','term')
    d.no('B',1,0,'Porteiro registra:|unidade, destinatário,|transportadora, tamanho')
    d.no('C',2,0,'Sistema indica|posição livre|na estante')
    d.no('D',3,0,'Sistema gera código|de retirada|(6 dígitos)')
    d.no('E',3,1,'Sistema avisa o|morador pelo canal|cadastrado')
    d.no('F',2,1,'Canal?','dec')
    d.no('G',1,1,'APP ou SMS:|aviso enviado')
    d.no('H',1,2,'INTERFONE: código|impresso ou informado|pelo porteiro')
    d.no('I',0,2,'Morador informa|o código')
    d.no('J',0,3,'Código|confere?|(até 3 vezes)','dec')
    d.no('L',0,4,'Retirada negada','term')
    d.no('K',1,3,'Sistema registra|a retirada: data,|hora e quem retirou')
    d.no('M',2,3,'Operações de registro|e de retirada entram|na fila (sincronização)')
    d.no('N',3,3,'Portaria|online?','dec')
    d.no('O',3,2,'Operações aguardam|na fila')
    d.no('P',3,4,'Fila é enviada|à central')
    d.no('Q',2,4,'Central consolida|sem duplicar')
    d.no('R',1,4,'Relatórios|consolidados','term')
    for a,b in [('A','B'),('B','C'),('C','D'),('D','E'),('E','F'),('F','G')]: d.liga(a,b)
    d.liga('F','H','','b','r')
    d.liga('G','I','','l','t')
    d.liga('H','I')
    d.liga('I','J'); d.liga('J','L','Não'); d.liga('J','K','Sim')
    d.liga('K','M'); d.liga('M','N')
    d.liga('N','O','Não','t','b',duplo=True)
    d.liga('N','P','Sim')
    d.liga('P','Q'); d.liga('Q','R')
    return d

def fig10():
    d = Diagrama(margem_dir=70)
    d.no('I',0,0,'Início','term')
    d.no('B',1,0,'preferida = posição|do bloco no alfabeto|MOD NUM_ESTANTES')
    d.no('T',2,0,'Tamanho = G?','dec')
    d.no('T1',3,0,'faixa = prateleiras|10 a 11')
    d.no('T2',2,1,'faixa = prateleiras|0 a 9')
    d.no('K',3,1,'k = 0')
    d.no('C',3,2,'k < NUM_ESTANTES?','dec')
    d.no('D',2,2,'candidata =|(preferida + k)|MOD NUM_ESTANTES')
    d.no('E',1,2,'Há prateleira|livre na faixa|em candidata?','dec')
    d.no('G',0,2,'Gravar id_encomenda|na célula e retornar|(candidata, prateleira)','term')
    d.no('H',1,3,'k = k + 1')
    d.no('N',3,3,'Retornar:|sem vaga','term')
    d.liga('I','B'); d.liga('B','T'); d.liga('T','T1','Sim'); d.liga('T','T2','Não','b','t')
    d.liga('T1','K','','b','t'); d.liga('T2','K','','r','l')
    d.liga('K','C'); d.liga('C','D','Sim'); d.liga('C','N','Não','b','t')
    d.liga('D','E'); d.liga('E','G','Sim'); d.liga('E','H','Não','b','t')
    d.liga('H','C','','b','r', rota=[(1,3.5),(3.6,3.5),(3.6,2)])
    return d

def fig16():
    d = Diagrama()
    d.no('A',0,0,'1. Porteiro registra|a encomenda (US01)')
    d.no('B',1,0,'2. Sistema escolhe a|posição (A1) e gera|o código (A2)')
    d.no('C',2,0,'3. Grava em arquivo|(protótipo) ou banco|(sistema completo)')
    d.no('D',3,0,'4. Aviso ao morador:|app, SMS ou interfone')
    d.no('E',3,1,'5. Morador informa|o código')
    d.no('F',2,1,'Código|confere?|(até 3 vezes)','dec')
    d.no('G',1,1,'Retirada negada;|encomenda continua|pendente','term')
    d.no('H',2,2,'6. Retirada registrada|e posição liberada|(A3)')
    d.no('Q',1,2,'Registro e retirada|entram na fila|de operações (US09)')
    d.no('R',0,2,'Há|conexão?','dec')
    d.no('S',0,1,'A fila espera; a|portaria continua|trabalhando')
    d.no('T',0,3,'Envio da fila (A4):|VPN e HTTPS no|sistema completo')
    d.no('U',1,3,'id da operação|já foi|aplicado?','dec')
    d.no('V',2,3,'Ignora a operação|(ADR-003)')
    d.no('W',1,4,'Aplica a operação|(A5)')
    d.no('X',2,4,'Consolidado e|relatórios|(A6, US12 a US14)')
    d.no('Y',3,4,'Indicadores: tempo,|pendências antigas|e extravios','term')
    d.liga('A','B'); d.liga('B','C'); d.liga('C','D'); d.liga('D','E')
    d.liga('E','F'); d.liga('F','G','Não'); d.liga('F','H','Sim')
    d.liga('H','Q'); d.liga('Q','R')
    d.liga('R','S','Não','t','b',duplo=True)
    d.liga('R','T','Sim')
    d.liga('T','U'); d.liga('U','V','Sim'); d.liga('U','W','Não','b','t')
    d.liga('W','X'); d.liga('X','Y')
    return d

if __name__ == '__main__':
    saida = sys.argv[1]; os.makedirs(saida, exist_ok=True)
    figs = {'figura-02-processo-atual': fig02, 'figura-03-processo-proposto': fig03,
            'figura-10-fluxograma-a1': fig10, 'figura-15-fluxo-ponta-a-ponta': fig16}
    for nome, f in figs.items():
        open(f'{saida}/{nome}.svg', 'w', encoding='utf-8').write(f().svg())
    print('SVG gerados em', saida, '- converta para PNG com svg_para_png.js')
