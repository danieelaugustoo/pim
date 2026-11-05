// Converte os SVG de uma pasta em PNG (escala 2). Uso: node svg_para_png.js <pasta>
const { chromium } = require('playwright');
const fs = require('fs'), path = require('path');
(async () => {
  const dir = process.argv[2];
  const nav = await chromium.launch();
  for (const f of fs.readdirSync(dir).filter(n => n.endsWith('.svg'))) {
    const svg = fs.readFileSync(path.join(dir, f), 'utf8');
    const w = +svg.match(/width="(\d+)"/)[1], h = +svg.match(/height="(\d+)"/)[1];
    const pg = await nav.newPage({ viewport: { width: w, height: h }, deviceScaleFactor: 2 });
    await pg.setContent('<body style="margin:0">' + svg + '</body>');
    await pg.screenshot({ path: path.join(dir, f.replace('.svg', '.png')) });
    await pg.close();
  }
  await nav.close();
})();
