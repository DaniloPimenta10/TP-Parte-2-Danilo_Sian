#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partida.h"
#include "bd_times.h"

// TAD que guarda todas as partidas carregadas do arquivo CSV.
typedef struct {
    Partida partida[100];
    int qtd;
} BDPartidas;

// Funcoes publicas do TAD BDPartidas.
void carrega_partidas(BDPartidas *bdp, BDTimes *bdt, char *caminho);
void consulta_partidas(BDPartidas *bdp, BDTimes *bdt, char *nome, int modo);

#endif
