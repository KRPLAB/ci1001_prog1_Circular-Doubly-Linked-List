# Makefile básico
     
CFLAGS = -Wall -std=c99 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = testa_lista_circular.o liblista_circular.o 
     
all: testa_lista_circular.o liblista_circular.o
	$(CC) -o testa_lista_circular testa_lista_circular.o liblista_circular.o $(LDFLAGS)

liblista_circular.o: liblista_circular.c
	$(CC) -c $(CFLAGS) liblista_circular.c

testa_lista_circular.o: testa_lista_circular.c
	$(CC) -c $(CFLAGS) testa_lista_circular.c

clean:
	rm -f $(objects) testa_lista_circular