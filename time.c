#include "time.h"
#include <stdio.h>

int pontos_ganhos(Time t) {
    return (t.v * 3) + t.e;
}

int saldo_gols(Time t) {
    return t.gm - t.gs;
}

