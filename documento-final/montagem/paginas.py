import json, subprocess, sys, re
pdf, entradas, saida = sys.argv[1:4]
ent = json.load(open(entradas, encoding='utf-8'))
n = int(re.search(r'Pages:\s+(\d+)', subprocess.run(['pdfinfo', pdf], capture_output=True, text=True).stdout).group(1))
txt = [subprocess.run(['pdftotext', '-f', str(p), '-l', str(p), '-layout', pdf, '-'], capture_output=True, text=True).stdout for p in range(1, n + 1)]
ini = next(i for i, t in enumerate(txt) if 'MARCADOR_INICIO' in t or re.search(r'^\s*1 INTRODUÇÃO\s*$', t, re.M))
# a primeira pagina do corpo vem depois do sumario: procura "1 INTRODUÇÃO" sem pontilhado
for i, t in enumerate(txt):
    if re.search(r'^\s*1 INTRODUÇÃO\s*$', t, re.M): ini = i; break
res = {}; cur = ini
def norm(s): return re.sub(r'\s+', ' ', s).strip()
for e in ent:
    chave = norm(e)[:28]
    for p in range(cur, n):
        linhas = [norm(l) for l in txt[p].split('\n')]
        if any(l.startswith(chave) and '....' not in l for l in linhas): res[e] = p + 1; cur = p; break
    else: res[e] = 0
faltam = [e for e, v in res.items() if v == 0]
json.dump(res, open(saida, 'w', encoding='utf-8'), ensure_ascii=False)
print('entradas', len(ent), 'sem pagina:', faltam)
