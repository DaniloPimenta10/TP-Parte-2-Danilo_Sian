CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -I.

# Lista de arquivos objeto a partir dos fontes .c.
OBJS = main.o time.o bd_times.o bd_partidas.o partida.o

# Regra principal: gera o executavel a partir dos objetos.
all: sistema

sistema: $(OBJS)
	$(CC) $(CFLAGS) -o sistema $(OBJS)

# Regras implicitas: cada .c gera seu .o correspondente.
main.o: main.c bd_times.h bd_partidas.h
	$(CC) $(CFLAGS) -c main.c

time.o: time.c time.h
	$(CC) $(CFLAGS) -c time.c

bd_times.o: bd_times.c bd_times.h time.h
	$(CC) $(CFLAGS) -c bd_times.c

bd_partidas.o: bd_partidas.c bd_partidas.h partida.h bd_times.h time.h
	$(CC) $(CFLAGS) -c bd_partidas.c

partida.o: partida.c partida.h
	$(CC) $(CFLAGS) -c partida.c

# Remove o executavel e os arquivos objeto gerados pela compilacao.
clean:
	rm -f sistema $(OBJS)

.PHONY: all clean