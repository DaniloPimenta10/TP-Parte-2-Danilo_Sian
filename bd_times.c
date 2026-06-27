#include "bd_times.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Carrega o arquivo times.csv para o vetor de times do banco.
void carrega_times(BDTimes *bd, char *caminho) {
    bd->qtd = 0; // cont de times comeca com 0

    FILE *f = fopen(caminho, "r");
    if (!f) {
        printf("Erro ao abrir arquivo de times: %s\n", caminho);
        return;
    }

    char buffer[100]; // espaco usado para ler uma linha por vez

    // Pula a primeira linha, que e o cabecalho do CSV.
    fgets(buffer, sizeof(buffer), f);

    // Le os times ate acabar o arquivo ou ate preencher as 10 posicoes.
    while (bd->qtd < 10 && fgets(buffer, sizeof(buffer), f)) {
        if (sscanf(buffer, "%d,%[^\n\r]", &bd->times[bd->qtd].id, bd->times[bd->qtd].nome) == 2) {
            // As estatisticas comecam zeradas e serao atualizadas pelas partidas.
            bd->times[bd->qtd].v = 0;
            bd->times[bd->qtd].e = 0;
            bd->times[bd->qtd].d = 0;
            bd->times[bd->qtd].gm = 0;
            bd->times[bd->qtd].gs = 0;

            // Adiciona mais 1 time na quantidade cadastrada.
            bd->qtd++;
        }
    }

    fclose(f);
}

// Busca times cujo nome comeca com o prefixo informado pelo usuario.
void buscar_time(BDTimes *bd, char *prefixo) {
    int found = 0; // controla se algum time foi encontrado

    for (int i = 0; i < bd->qtd; i++) {
        if (strncasecmp(bd->times[i].nome, prefixo, strlen(prefixo)) == 0) {
            if (!found) {
                printf("ID   Time         V   E   D  GM  GS   S PG\n");
            }

            dados_time(bd->times[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Time nao encontrado.\n");
    }
}

// Imprime a tabela de classificacao na ordem dos IDs dos times.
void imprimir_tabela(BDTimes *bd) {
    int times_por_pagina = 5;
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpando o Buffer


    printf("ID   Time         V   E   D  GM  GS   S PG\n");
    for (int i = 0; i < bd->qtd; i++) {
        dados_time(bd->times[i]);

    if ((i + 1) % times_por_pagina == 0 && (i + 1) < bd->qtd) { // Paginação da saida 
    char pausa[10];

    printf("\n--- Pressione [ENTER] para ver a próxima página ---");


    fgets(pausa, sizeof(pausa), stdin);

    printf("\n=== PRÓXIMA PÁGINA ===\n\n");
    printf("ID   Time         V   E   D  GM  GS   S PG\n");
    }
    }
}