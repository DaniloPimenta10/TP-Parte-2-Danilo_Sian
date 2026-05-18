#include "bd_partidas.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Procura um time pelo ID. Retorna NULL se nao encontrar.
static Time *buscar_time_por_id(BDTimes *bdt, int id) {
    for (int i = 0; i < bdt->qtd; i++) {
        if (bdt->times[i].id == id) {
            return &bdt->times[i];
        }
    }

    return NULL;
}

// Compara somente o comeco do nome, ignorando maiusculas/minusculas.
static int prefixo_igual(char *nome, char *prefixo) {
    return strncasecmp(nome, prefixo, strlen(prefixo)) == 0;
}

// Carrega as partidas do CSV e atualiza as estatisticas dos times.
void carrega_partidas(BDPartidas *bdp, BDTimes *bdt, char *caminho) {
    bdp->qtd = 0; // cont de partidas comeca com 0

    FILE *f = fopen(caminho, "r");
    if (!f) {
        printf("Erro ao abrir arquivo de partidas: %s\n", caminho);
        return;
    }

    char buffer[100]; // espaco usado para ler uma linha por vez

    // Pula a primeira linha, que e o cabecalho do CSV.
    fgets(buffer, sizeof(buffer), f);

    // Le as partidas ate acabar o arquivo ou ate preencher o vetor.
    while (bdp->qtd < 100 && fgets(buffer, sizeof(buffer), f)) {
        Partida p; // partida temporaria lida da linha atual

        if (sscanf(buffer, "%d,%d,%d,%d,%d",
                   &p.id,
                   &p.idTime1,
                   &p.idTime2,
                   &p.gols1,
                   &p.gols2) == 5) {
            Time *t1 = buscar_time_por_id(bdt, p.idTime1);
            Time *t2 = buscar_time_por_id(bdt, p.idTime2);

            // Se a partida tiver algum ID de time invalido, ela e ignorada.
            if (!t1 || !t2) {
                continue;
            }

            bdp->partida[bdp->qtd] = p;

            // Atualiza gols marcados e sofridos dos dois times.
            t1->gm += p.gols1;
            t1->gs += p.gols2;
            t2->gm += p.gols2;
            t2->gs += p.gols1;

            // Atualiza vitorias, empates e derrotas conforme o placar.
            if (p.gols1 > p.gols2) {
                t1->v += 1;
                t2->d += 1;
            } else if (p.gols1 < p.gols2) {
                t2->v += 1;
                t1->d += 1;
            } else {
                t1->e += 1;
                t2->e += 1;
            }

            bdp->qtd++;
        }
    }

    fclose(f);
}

// Consulta partidas por time mandante, visitante ou pelos dois modos.
void consulta_partidas(BDPartidas *bdp, BDTimes *bdt, char *nome, int modo) {
    if (modo == 4) {
        return;
    }

    if (modo < 1 || modo > 3) {
        printf("Modo invalido.\n");
        return;
    }

    int found = 0; // flag: muda para 1 se encontrar partida

    for (int i = 0; i < bdp->qtd; i++) {
        Partida p = bdp->partida[i];

        // Recupera os dados completos dos times envolvidos na partida.
        Time *time1 = buscar_time_por_id(bdt, p.idTime1);
        Time *time2 = buscar_time_por_id(bdt, p.idTime2);

        if (!time1 || !time2) {
            continue;
        }

        char *nome1 = time1->nome;
        char *nome2 = time2->nome;
        int match = 0;

        // Decide se a partida atual entra no resultado da consulta.
        if (modo == 1 && prefixo_igual(nome1, nome)) {
            match = 1;
        } else if (modo == 2 && prefixo_igual(nome2, nome)) {
            match = 1;
        } else if (modo == 3 && (prefixo_igual(nome1, nome) || prefixo_igual(nome2, nome))) {
            match = 1;
        }

        if (match) {
            if (!found) {
                printf("ID Time1                Placar Time2\n");
            }

            printf("%d %s %d x %d %s\n", p.id, nome1, p.gols1, p.gols2, nome2);
            found = 1;
        }
    }

    if (!found) {
        printf("Nenhuma partida encontrada.\n");
    }
}
