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

void imprimir_tabela(BDTimes *bd) {
    int times_por_pagina = 5;

    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpando o Buffer


    printf("ID Nome                    V  E  D  GM GS  S PG\n");
    for (int i = 0; i < bd->qtd; i++) {
        dados_time(bd->times[i]);
    
    if ((i + 1) % times_por_pagina == 0 && (i + 1) < bd->qtd) { // Paginação da saida 
    char pausa[10];
    
    printf("\n--- Pressione [ENTER] para ver a próxima página ---");
    
    
    fgets(pausa, sizeof(pausa), stdin);
    
    printf("\n=== PRÓXIMA PÁGINA ===\n\n");
    printf("ID Nome                    V  E  D  GM GS  S PG\n");
    }
    }
}