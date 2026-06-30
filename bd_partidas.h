#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partida.h"
#include "bd_times.h"

// TAD que gerencia a lista encadeada de partidas.
typedef struct {
    NodePartida *inicio;
    int qtd;
} BDPartidas;

// Funcoes publicas do TAD BDPartidas.
void carrega_partidas(BDPartidas *bdp, BDTimes *bdt, char *caminho);
void consulta_partidas(BDPartidas *bdp, BDTimes *bdt, char *nome, int modo);

// Novas funcoes de manutencao (Parte II).
void inserir_partida(BDPartidas *bdp, BDTimes *bdt);
void atualizar_partida(BDPartidas *bdp, BDTimes *bdt);
void remover_partida(BDPartidas *bdp, BDTimes *bdt);

// Persistencia: salva o estado atual da lista de volta no CSV.
void salvar_partidas(BDPartidas *bdp, char *caminho);

// Libera toda a memoria alocada pela lista de partidas.
void liberar_partidas(BDPartidas *bdp);

#endif