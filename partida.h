#ifndef PARTIDA_H
#define PARTIDA_H

// representa uma  partidas do campeonato.
typedef struct {
    int id;
    int idTime1;
    int idTime2;
    int gols1;
    int gols2;
} Partida;

// Nó da lista encadeada de partidas
typedef struct NodePartida {
    Partida data;
    struct NodePartida *prox;
} NodePartida;


#endif
