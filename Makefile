CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -I.

# Regra principal: compila o programa inteiro.
all: sistema

# Gera o executavel sistema a partir dos arquivos .c.
sistema: main.c time.c bd_times.c bd_partidas.c time.h partida.h bd_times.h bd_partidas.h
	$(CC) $(CFLAGS) -o sistema main.c time.c bd_times.c bd_partidas.c

# Remove o executavel gerado pela compilacao.
clean:
	rm -f sistema

.PHONY: all clean
