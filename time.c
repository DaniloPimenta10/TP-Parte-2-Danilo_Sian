#include "time.h"
#include <stdio.h>

// Calcula a pontuacao: cada vitoria vale 3 pontos e cada empate vale 1.
int pontos_ganhos(Time *t) {
    return (t->v * 3) + t->e;
}

// Calcula o saldo de gols do time.
int saldo_gols(Time *t) {
    return t->gm - t->gs;
}

// Imprime uma linha da tabela com todos os dados do time.
void dados_time(Time *t) {
    printf("%-4d %-10s %3d %3d %3d %3d %3d %3d %2d\n",
           t->id,
           t->nome,
           t->v,
           t->e,
           t->d,
           t->gm,
           t->gs,
           saldo_gols(t),
           pontos_ganhos(t));
}

// Retorna o ID do time.
int time_get_id(Time *t) {
    return t->id;
}

// Retorna o nome do time.
char *time_get_nome(Time *t) {
    return t->nome;
}

// Atualiza as estatisticas do time a partir dos gols marcados e sofridos.
void time_atualizar_estatisticas(Time *t, int gols_marcados, int gols_sofridos) {
    t->gm += gols_marcados;
    t->gs += gols_sofridos;

    if (gols_marcados > gols_sofridos) {
        t->v += 1;
    } else if (gols_marcados < gols_sofridos) {
        t->d += 1;
    } else {
        t->e += 1;
    }
}

// Desfaz as estatisticas do time, revertendo um resultado ja aplicado.
void time_desfazer_estatisticas(Time *t, int gols_marcados, int gols_sofridos) {
    t->gm -= gols_marcados;
    t->gs -= gols_sofridos;

    if (gols_marcados > gols_sofridos) {
        t->v -= 1;
    } else if (gols_marcados < gols_sofridos) {
        t->d -= 1;
    } else {
        t->e -= 1;
    }
}