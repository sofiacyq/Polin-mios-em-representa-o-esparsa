CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

ifeq ($(OS),Windows_NT)
RM = del /Q
EXE = .exe
else
RM = rm -f
EXE =
endif

all: main gerador

main: comandospoli.o tadelista.o tabela.o
	$(CC) $(CFLAGS) -o main$(EXE) comandospoli.o tadelista.o tabela.o

gerador: gerador.o
	$(CC) $(CFLAGS) -o gerador$(EXE) gerador.o

comandospoli.o: comandospoli.c tadelista.h tabela.h
	$(CC) $(CFLAGS) -c comandospoli.c

tadelista.o: tadelista.c tadelista.h
	$(CC) $(CFLAGS) -c tadelista.c

tabela.o: tabela.c tabela.h tadelista.h
	$(CC) $(CFLAGS) -c tabela.c

gerador.o: gerador.c
	$(CC) $(CFLAGS) -c gerador.c

clean:
	$(RM) *.o main$(EXE) gerador$(EXE)
