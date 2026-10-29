# Makefile do PIM II - rodar dentro de 05-programa-c/
#   make         compila bin/portaria e bin/central
#   make test    compila e roda os testes
#   make clean   apaga executaveis e objetos

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Iinclude

ifeq ($(OS),Windows_NT)
EXE = .exe
else
EXE =
endif

# Modulos compartilhados (um .c por modulo em src/)
MODULOS = util estante codigo encomenda retirada persistencia morador aviso sincronizacao consolidacao relatorio
OBJ_MODULOS = $(patsubst %,bin/%.o,$(MODULOS))

PROGRAMAS = bin/portaria$(EXE) bin/central$(EXE)

TESTES = test_util test_estante test_codigo test_encomenda test_persistencia test_morador test_sincronizacao test_consolidacao test_relatorio
EXE_TESTES = $(patsubst %,bin/%$(EXE),$(TESTES))
RODAR_TESTES = $(patsubst %,rodar-%,$(TESTES))

.PHONY: all test clean $(RODAR_TESTES)

all: $(PROGRAMAS)

bin/portaria$(EXE): bin/portaria.o $(OBJ_MODULOS)
	$(CC) $(CFLAGS) -o $@ $^

bin/central$(EXE): bin/central.o $(OBJ_MODULOS)
	$(CC) $(CFLAGS) -o $@ $^

bin/%.o: src/%.c $(wildcard include/*.h)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE_TESTES): bin/%$(EXE): tests/%.c $(OBJ_MODULOS) $(wildcard include/*.h)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ_MODULOS)

test: $(RODAR_TESTES)
	@echo Todos os testes passaram.

$(RODAR_TESTES): rodar-%: bin/%$(EXE)
	bin/$*$(EXE)

# Apaga so objetos e executaveis; bin/README.md permanece.
ifeq ($(OS),Windows_NT)
# No Windows, o make so acha o sh se ele estiver no PATH; nesse caso SHELL vem com o
# caminho completo (tem '/'). Sem sh, o make usa o cmd e o comando de apagar e o del.
ifneq ($(findstring /,$(SHELL)),)
LIMPAR = rm -f bin/*.o bin/*.exe
else
LIMPAR = del /Q bin\*.o bin\*.exe 2>nul
endif
else
LIMPAR = rm -f bin/*.o bin/portaria bin/central bin/test_*
endif

clean:
	-$(LIMPAR)
