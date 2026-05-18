#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "time.h"

// TAD que guarda todos os times carregados do arquivo times.csv.
typedef struct {
    Time times[10];
    int qtd;
} BDTimes;

// Funcoes publicas do TAD BDTimes.
void carrega_times(BDTimes *bd, char *caminho);
void buscar_time(BDTimes *bd, char *prefixo);
void imprimir_tabela(BDTimes *bd);

#endif
