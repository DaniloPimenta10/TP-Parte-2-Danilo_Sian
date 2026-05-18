#include "time.h"
#include <stdio.h>

// Calcula a pontuacao: cada vitoria vale 3 pontos e cada empate vale 1.
int pontos_ganhos(Time t) {
    return (t.v * 3) + t.e;
}

// Calcula o saldo de gols do time.
int saldo_gols(Time t) {
    return t.gm - t.gs;
}

// Imprime uma linha da tabela com todos os dados do time.
void dados_time(Time t) {
    printf("%2d %-20s %2d %2d %2d %3d %2d %2d %2d\n",
           t.id,
           t.nome,
           t.v,
           t.e,
           t.d,
           t.gm,
           t.gs,
           saldo_gols(t),
           pontos_ganhos(t));
}
