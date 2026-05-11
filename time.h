#ifndef TIME.H
#define TIME_h

typedef struct {
    int id;
    char nome[50];
    int v, e, d, gm, gs; //vitórias, empates, derrotas, gol marcados e gols sofridos
} Time;

int pontos_ganhos(Time t);
int saldo_gols(Time t);

#endif
