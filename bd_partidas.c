#include "bd_partidas.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

void carrega_partidas(BDPartidas *bdp, BDTimes *bdt, char *caminho) {
    
    FILE *f = fopen(caminho, "r");
    if (!f) return; //caso o arquivo não exista ou tenha algum problema
    
    bdp->qtd = 0; //cont de times começa com 0
    char buffer[100]; //espaço para ler as linhas do arq

    //pula a primeira linha
    fgets(buffer, sizeof(buffer), f);

    //continua lendo linha por linh ate o final do arquivo ou ate a linha 10
    while (fgets(buffer, sizeof(buffer), f))
    {
        if (sscanf(buffer, "%d,%d,%d,%d,%d" , // Checa se a linha com os times esta correta
            &bdp->partida[bdp->qtd].id,      // Se estiver correta atribui um valor as variaveis
            &bdp->partida[bdp->qtd].idTime1,
            &bdp->partida[bdp->qtd].idTime2,
            &bdp->partida[bdp->qtd].gols1,
            &bdp->partida[bdp->qtd].gols2) == 5)
        {
            bdp->qtd++;
        }
    }

    fclose(f);
}

void consulta_partidas(BDPartidas *bdp, BDTimes *bdt, char *nome, int modo) {

}