#ifndef TIME_H
#define TIME_H

// Representa um time e suas estatisticas no campeonato.
typedef struct {
    int id;
    char nome[50];
    int v;  // vitorias
    int e;  // empates
    int d;  // derrotas
    int gm; // gols marcados
    int gs; // gols sofridos
} Time;

// Funcoes publicas do TAD Time.
int pontos_ganhos(Time t);
int saldo_gols(Time t);
void dados_time(Time t);

#endif
