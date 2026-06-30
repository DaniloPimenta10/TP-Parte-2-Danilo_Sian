#include "bd_partidas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Insere uma partida no final da lista encadeada.
static void inserir_no_final(BDPartidas *bdp, Partida p) {
    NodePartida *novo = (NodePartida *)malloc(sizeof(NodePartida));
    if (!novo) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    novo->data = p;
    novo->prox = NULL;

    if (bdp->inicio == NULL) {
        bdp->inicio = novo;
    } else {
        NodePartida *aux = bdp->inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    bdp->qtd++;
}

// Aplica o resultado de uma partida nas estatisticas dos times envolvidos.
static void aplicar_estatisticas(Time *t1, Time *t2, int gols1, int gols2) {
    t1->gm += gols1;
    t1->gs += gols2;
    t2->gm += gols2;
    t2->gs += gols1;

    if (gols1 > gols2) {
        t1->v += 1;
        t2->d += 1;
    } else if (gols1 < gols2) {
        t2->v += 1;
        t1->d += 1;
    } else {
        t1->e += 1;
        t2->e += 1;
    }
}

// Carrega as partidas do CSV e atualiza as estatisticas dos times.
void carrega_partidas(BDPartidas *bdp, BDTimes *bdt, char *caminho) {
    bdp->inicio = NULL;
    bdp->qtd = 0;

    FILE *f = fopen(caminho, "r");
    if (!f) {
        printf("Erro ao abrir arquivo de partidas: %s\n", caminho);
        return;
    }

    char buffer[100];

    // Pula a primeira linha, que e o cabecalho do CSV.
    fgets(buffer, sizeof(buffer), f);

    while (fgets(buffer, sizeof(buffer), f)) {
        Partida p;

        if (sscanf(buffer, "%d,%d,%d,%d,%d",
                   &p.id, &p.idTime1, &p.idTime2, &p.gols1, &p.gols2) == 5) {
            NodeTime *n1 = buscar_time_por_id_node(bdt, p.idTime1);
            NodeTime *n2 = buscar_time_por_id_node(bdt, p.idTime2);

            // Se a partida tiver algum ID de time invalido, ela e ignorada.
            if (n1 != NULL && n2 != NULL) {
                aplicar_estatisticas(&n1->data, &n2->data, p.gols1, p.gols2);
                inserir_no_final(bdp, p);
            }
        }
    }

    fclose(f);
}