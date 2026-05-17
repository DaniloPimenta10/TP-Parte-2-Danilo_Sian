#include "time.h"
#include <stdio.h>

int pontos_ganhos(Time t) {
    return (t.v * 3) + t.e;
}

int saldo_gols(Time t) {
    return t.gm - t.gs;
}

void dados_time(Time t) {
    printf("%2d %-20s %2d %2d %2d %3d %2d %2d %2d\n", t.id, t.nome, t.v, t.e, t.d, t.gm, t.gs, saldo_gols(t), pontos_ganhos(t));
}