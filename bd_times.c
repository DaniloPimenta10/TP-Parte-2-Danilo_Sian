#include "bd_times.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

void carrega_times(BDTimes *bd, char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return; //caso o arquivo não exista ou tenha algum problema

    bd->qtd = 0; //cont de times começa com 0
    char buffer[100]; //espaço para ler as linhas do arq

    //pula a primeira linha
    fgets(buffer, sizeof(buffer), f);

    //continua lendo linha por linh ate o final do arquivo ou ate a linha 10
    while (fgets(buffer, sizeof(buffer), f)) {
        if (sscanf(buffer, "%d,%[^\n\r]", &bd->times[bd->qtd].id, bd->times[bd->qtd].nome) == 2) { //sscanf extrai o conteudo da linha ate a quebra de linha
            //inicializa tudo como zerado de inicio
            bd->times[bd->qtd].v = 0;
            bd->times[bd->qtd].e = 0;
            bd->times[bd->qtd].d = 0;
            bd->times[bd->qtd].gm = 0;
            bd->times[bd->qtd].gs = 0;

            //adiciona mais 1 time a qtd de times
            bd->qtd++;
        }
    }
    fclose(f);
}

void 