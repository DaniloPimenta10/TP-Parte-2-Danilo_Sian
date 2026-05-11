#ifndef BD_TIMES_H
#define BD_TIMES_H
#include "time.h"

typedef struct {
    Time times[10];
    int qtd;
} BDTimes;

void carrega_times(BDTimes *bd, char *caminho);
void buscar_time_(BDTimes *bd, char *prefixo);
void imprimir_tabela(BDTimes *bd);

#endif

