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

    
    while (fgets(buffer, sizeof(buffer), f)) 
    {
        if (sscanf(buffer, "%d,%d,%d,%d,%d" , // Checa se a linha com os times esta correta
            &bdp->partida[bdp->qtd].id,      // Se estiver correta atribui um valor as variaveis
            &bdp->partida[bdp->qtd].idTime1,
            &bdp->partida[bdp->qtd].idTime2,
            &bdp->partida[bdp->qtd].gols1,
            &bdp->partida[bdp->qtd].gols2) == 5)
        {
            Partida p = bdp->partidas[bdp->qtd];
            Time *t1 = &bdt->times[p.idTime1];
            Time *t2 = &bdt->times[p.idTime2];
            t1->gm += p.gols1;
            t1->gs += p.gols2;
            t2->gm += p.gols2;
            t2->gs += p.gols1;

            if (p.gols1 > p.gols2) {
                t1->v += 1;
                t2->d += 1;
            } else if (p.gols1 < p.gols2)
            {
                t2->v += 1;
                t1->d += 1;
            }
            else {
                t1->e += 1;
                t2->e += 1;
            }
            
            bdp->qtd++;
        }
    }

    fclose(f);
}

void consulta_partidas(BDPartidas *bdp, BDTimes *bdt, char *nome, int modo) {

    int found = 0; //bandeira "flag". muda para 1 se encontrado o time

    for (int i = 0; i < bdp->qtd; i++) {
        Partida p = bdp->partidas[i];
        char nome1 = bdt->times[p->idTime1].nome;
        char nome2 = bdt->times[p->idTime2].nome;

        int match = 0; //muda de valor se der match

        if (modo == 1 && strncasecmp(n1, nome, strlen(nome)) == 0) {
            match = 1;
        } else if (modo == 2 && strncasecmp(n2, nome, strlen(nome)) == 0)
        {
            match = 1;
        } else if (modo == 3 && strncasecmp(n1, nome, strlen(nome)) == 0 || strncasecmp(n2, nome, strlen(nome))) {
            match = 1;
        }

        if (match) {
            printf("%d %s %d x %d %s\n", p.id, n1, p.gols1, p.gols2, n2);
            found = 1;
        }

        
    }
    if (!found) {
        printf("Nenhuma partida encontrada. \n")
    }


}