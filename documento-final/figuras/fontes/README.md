# Fontes das figuras gradeadas

`fluxogramas_grade.py` gera em SVG os fluxogramas das Figuras 2, 3, 10 e 15 do documento final
(`python3 fluxogramas_grade.py <pasta>`), e `svg_para_png.js` converte para PNG
(`NODE_PATH=$(npm root -g) node svg_para_png.js <pasta>`, com Node e Playwright). Os SVG
versionados nesta pasta são a saída atual. As versões verticais em Mermaid
(`*/diagramas/*.mmd`) continuam no repositório.
