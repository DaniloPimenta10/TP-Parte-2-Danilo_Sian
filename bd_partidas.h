#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H
#include "partida.h"
#include "bd_times.h"

typedef struct {
    Partida partida[100];
    int qtd;
} BDPartidas;

void carrega_partidas(BDPartidas *bdp, BDTimes *bdt, char *caminho);
void consulta_partidas(BDPartidas *bdp, BDTimes *bdt, char *nome, int modo);