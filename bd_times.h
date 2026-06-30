#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "time.h"

// TAD que gerencia a lista encadeada de times.
typedef struct {
    NodeTime *inicio;
    int qtd;
} BDTimes;

// Funcoes publicas do TAD BDTimes.
void carrega_times(BDTimes *bd, char *caminho);
void buscar_time(BDTimes *bd, char *prefixo);
void imprimir_tabela(BDTimes *bd);
void liberar_times(BDTimes *bd); 

// Busca interna por ID, usada pelo modulo de partidas.
NodeTime *buscar_id(BDTimes *bd, int id);

#endif