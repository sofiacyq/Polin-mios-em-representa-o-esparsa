CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

all: main gerador

main: comandospoli.o tadelista.o tabela.o
	$(CC) $(CFLAGS) -o main comandospoli.o tadelista.o tabela.o

gerador: gerador.o
	$(CC) $(CFLAGS) -o gerador gerador.o

comandospoli.o: comandospoli.c tadelista.h tabela.h
	$(CC) $(CFLAGS) -c comandospoli.c

tadelista.o: tadelista.c tadelista.h
	$(CC) $(CFLAGS) -c tadelista.c

tabela.o: tabela.c tabela.h tadelista.h
	$(CC) $(CFLAGS) -c tabela.c

gerador.o: gerador.c
	$(CC) $(CFLAGS) -c gerador.c

clean:
	rm -f *.o main gerador
