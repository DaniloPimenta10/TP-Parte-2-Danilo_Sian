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

// No da lista encadeada de times.
typedef struct NodeTime {
    Time data;
    struct NodeTime *prox;
} NodeTime;

// Funcoes publicas do TAD Time.
int pontos_ganhos(Time *t);
int saldo_gols(Time *t);
void dados_time(Time *t);

// Funcoes de acesso aos campos de Time, usadas por outros modulos.
int time_get_id(Time *t);
char *time_get_nome(Time *t);
void time_atualizar_estatisticas(Time *t, int gols_marcados, int gols_sofridos);
void time_desfazer_estatisticas(Time *t, int gols_marcados, int gols_sofridos);

#endif