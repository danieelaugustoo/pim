@echo off
rem build.bat - compila o PIM II no Windows sem make (requer gcc do MinGW-w64 no PATH).
rem Rodar dentro de 05-programa-c\
rem   build.bat         compila bin\portaria.exe
rem   build.bat test    compila e roda os testes
setlocal

where gcc >nul 2>nul
if errorlevel 1 (
    echo ERRO: gcc nao encontrado no PATH.
    exit /b 1
)

set FLAGS=-std=c99 -Wall -Wextra -pedantic -Iinclude
set MODULOS=src\util.c src\estante.c src\codigo.c src\encomenda.c src\retirada.c src\persistencia.c

if not exist bin mkdir bin

if /I "%1"=="test" goto testes

gcc %FLAGS% -o bin\portaria.exe src\portaria.c %MODULOS%
if errorlevel 1 goto erro
echo Compilado: bin\portaria.exe
exit /b 0

:testes
for %%T in (test_util test_estante test_codigo test_encomenda test_persistencia) do (
    gcc %FLAGS% -o bin\%%T.exe tests\%%T.c %MODULOS%
    if errorlevel 1 goto erro
    bin\%%T.exe
    if errorlevel 1 goto erro
)
echo Todos os testes passaram.
exit /b 0

:erro
echo ERRO: a compilacao ou um teste falhou.
exit /b 1
