#include <stdio.h>
#include "bd_times.h"
#include "bd_partidas.h"

int main() {
    BDTimes bdt;
    BDPartidas bdp;
    carrega_times(&bdt, "times.csv");
    

    return 0;
}