#include <stdio.h>
#include "bd_times.h"
#include "bd_partidas.h"

int main() {
    BDTimes bdt;
    BDPartidas bdp;
    carrega_times(&bdt, "times.csv");
    char acesso = 0;
    
    while(acesso != 'Q' && acesso != 'q'){ // Condição para sair

    printf("Sistema de gerenciamento de Partidas \n");
    printf("1 - Consultar Times \n");
    printf("2 - Consultar Partidas \n");
    printf("3 - Imprimir Tabela de Classificação \n");
    printf("Q - Sair \n");

    scanf(" %c" , &acesso);
    //if(acesso == '1') //Acesso a consulta dos times

    //if(acesso == '2') //Acesso a consulta das partidas

    //if(acesso == '3') //Acesso a tabela
    

    }

    return 0;
}