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
    } 
    else {
        NodePartida *aux = bdp->inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    bdp->qtd++;
}

// Compara somente o comeco do nome, ignorando maiusculas/minusculas.
static int prefixo_igual(char *nome, char *prefixo) {
    return strncasecmp(nome, prefixo, strlen(prefixo)) == 0;
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

        if (sscanf(buffer, "%d,%d,%d,%d,%d", &p.id, &p.idTime1, &p.idTime2, &p.gols1, &p.gols2) == 5) {
            NodeTime *n1 = buscar_id(bdt, p.idTime1);
            NodeTime *n2 = buscar_id(bdt, p.idTime2);

            // Se a partida tiver algum ID de time invalido, ela e ignorada.
            if (n1 != NULL && n2 != NULL) {
                time_atualizar_estatisticas(&n1->data, p.gols1, p.gols2);
                time_atualizar_estatisticas(&n2->data, p.gols2, p.gols1);
                inserir_no_final(bdp, p);
            }
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

    int found = 0;
    NodePartida *aux = bdp->inicio;

    while (aux != NULL) {
        Partida p = aux->data;

        NodeTime *n1 = buscar_id(bdt, p.idTime1);
        NodeTime *n2 = buscar_id(bdt, p.idTime2);

        if (n1 != NULL && n2 != NULL) {
            char *nome1 = time_get_nome(&n1->data);
            char *nome2 = time_get_nome(&n2->data);
            int match = 0;

            if (modo == 1 && prefixo_igual(nome1, nome)) {
                match = 1;
            } 
            else if (modo == 2 && prefixo_igual(nome2, nome)) {
                match = 1;
            } 
            else if (modo == 3 && (prefixo_igual(nome1, nome) || prefixo_igual(nome2, nome))) {
                match = 1;
            }

            if (match) {
                if (!found) {
                    printf("%-4s %-12s %-12s %3s   %3s\n", "ID", "Time1", "Time2", "Pl1", "Pl2");
                }
                printf("%-4d %-12s %-12s %3d x %3d\n", p.id, nome1, nome2, p.gols1, p.gols2);
                found = 1;
            }
        }

        aux = aux->prox;
    }

    if (!found) {
        printf("Nenhuma partida encontrada.\n");
    }
}

// Gera o proximo ID disponivel para uma nova partida (autoincremento).
static int proximo_id(BDPartidas *bdp) {
    int maior = -1;
    NodePartida *aux = bdp->inicio;

    while (aux != NULL) {
        if (aux->data.id > maior) {
            maior = aux->data.id;
        }
        aux = aux->prox;
    }

    return maior + 1;
}

// Insere uma nova partida no sistema, validando os times informados.
void inserir_partida(BDPartidas *bdp, BDTimes *bdt) {
    int idTime1, idTime2, gols1, gols2;

    printf("Para inserir um novo registro, digite os valores para os campos Time1, Time2, Placar1 e Placar2:\n");

    scanf("%d", &idTime1);
    scanf("%d", &idTime2);
    scanf("%d", &gols1);
    scanf("%d", &gols2);

    NodeTime *n1 = buscar_id(bdt, idTime1);
    NodeTime *n2 = buscar_id(bdt, idTime2);

    if (n1 == NULL || n2 == NULL) {
        printf("Erro: um ou ambos os times informados nao existem.\n");
        return;
    }

    if (gols1 < 0 || gols2 < 0) {
        printf("Erro: os placares nao podem ser negativos.\n");
        return;
    }

    Partida p;
    p.id = proximo_id(bdp);
    p.idTime1 = idTime1;
    p.idTime2 = idTime2;
    p.gols1 = gols1;
    p.gols2 = gols2;

    printf("Confirma a insercao do registro abaixo? (S/N)\n");
    printf("%-4s %-12s %-12s %7s %7s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
    printf("%-4d %-12s %-12s %7d %7d\n", p.id, time_get_nome(&n1->data), time_get_nome(&n2->data), p.gols1, p.gols2);

    char confirma;
    scanf(" %c", &confirma);

    if (confirma == 'S' || confirma == 's') {
        time_atualizar_estatisticas(&n1->data, gols1, gols2);
        time_atualizar_estatisticas(&n2->data, gols2, gols1);
        inserir_no_final(bdp, p);
        printf("O registro foi inserido com sucesso.\n");
    } else {
        printf("Insercao cancelada.\n");
    }
}

// Remove uma partida existente, atualizando as estatisticas dos times.
void remover_partida(BDPartidas *bdp, BDTimes *bdt) {
    int modo;
    char nome[50];

    printf("Modo (1-Mandante, 2-Visitante, 3-Ambos, 4-Voltar): ");
    scanf("%d", &modo);

    if (modo == 4) {
        return;
    }

    printf("Nome/Prefixo: ");
    scanf("%49s", nome);
    consulta_partidas(bdp, bdt, nome, modo);

    int id;
    printf("Digite o ID do registro a ser removido: ");
    scanf("%d", &id);

    // Procura o no a remover e o no anterior a ele (para religar a lista).
    NodePartida *atual = bdp->inicio;
    NodePartida *anterior = NULL;

    while (atual != NULL && atual->data.id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Erro: partida com ID %d nao encontrada.\n", id);
        return;
    }

    NodeTime *n1 = buscar_id(bdt, atual->data.idTime1);
    NodeTime *n2 = buscar_id(bdt, atual->data.idTime2);

    printf("Tem certeza de que deseja excluir o registro abaixo? (S/N)\n");
    printf("%-4s %-12s %-12s %7s %7s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
    printf("%-4d %-12s %-12s %7d %7d\n", atual->data.id, time_get_nome(&n1->data), time_get_nome(&n2->data), atual->data.gols1, atual->data.gols2);

    char confirma;
    scanf(" %c", &confirma);

    if (confirma == 'S' || confirma == 's') {
        // Desfaz o impacto da partida nas estatisticas dos times.
        if (n1 != NULL && n2 != NULL) {
            time_desfazer_estatisticas(&n1->data, atual->data.gols1, atual->data.gols2);
            time_desfazer_estatisticas(&n2->data, atual->data.gols2, atual->data.gols1);
        }

        // Religa a lista pulando o no removido.
        if (anterior == NULL) {
            bdp->inicio = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }

        free(atual);
        bdp->qtd--;

        printf("Registro removido com sucesso.\n");
    } else {
        printf("Remocao cancelada.\n");
    }
}

// Atualiza o placar de uma partida existente, recalculando as estatisticas.
void atualizar_partida(BDPartidas *bdp, BDTimes *bdt) {
    int modo;
    char nome[50];

    printf("Modo (1-Mandante, 2-Visitante, 3-Ambos, 4-Voltar): ");
    scanf("%d", &modo);

    if (modo == 4) {
        return;
    }

    printf("Nome/Prefixo: ");
    scanf("%49s", nome);
    consulta_partidas(bdp, bdt, nome, modo);

    int id;
    printf("Digite o ID do registro a ser atualizado: ");
    scanf("%d", &id);

    // Procura a partida na lista.
    NodePartida *atual = bdp->inicio;
    while (atual != NULL && atual->data.id != id) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Erro: partida com ID %d nao encontrada.\n", id);
        return;
    }

    NodeTime *n1 = buscar_id(bdt, atual->data.idTime1);
    NodeTime *n2 = buscar_id(bdt, atual->data.idTime2);

    if (n1 == NULL || n2 == NULL) {
        printf("Erro: times da partida nao encontrados.\n");
        return;
    }

    // Le os novos valores. "-" mantem o valor atual.
    char entrada1[10], entrada2[10];
    int novoGols1 = atual->data.gols1;
    int novoGols2 = atual->data.gols2;

    printf("Digite o novo valor para os campos Placar1 e Placar2 (para manter o valor atual de um campo, digite '-'):\n");

    scanf("%9s", entrada1);
    scanf("%9s", entrada2);

    if (strcmp(entrada1, "-") != 0) {
        novoGols1 = atoi(entrada1);
    }
    if (strcmp(entrada2, "-") != 0) {
        novoGols2 = atoi(entrada2);
    }

    printf("Confirma os novos valores para o registro abaixo? (S/N)\n");
    printf("%-4s %-12s %-12s %7s %7s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
    printf("%-4d %-12s %-12s %7d %7d\n", atual->data.id, time_get_nome(&n1->data), time_get_nome(&n2->data),novoGols1, novoGols2);

    char confirma;
    scanf(" %c", &confirma);

    if (confirma == 'S' || confirma == 's') {
        // Desfaz o impacto do placar antigo e aplica o novo.
        time_desfazer_estatisticas(&n1->data, atual->data.gols1, atual->data.gols2);
        time_desfazer_estatisticas(&n2->data, atual->data.gols2, atual->data.gols1);

        time_atualizar_estatisticas(&n1->data, novoGols1, novoGols2);
        time_atualizar_estatisticas(&n2->data, novoGols2, novoGols1);

        atual->data.gols1 = novoGols1;
        atual->data.gols2 = novoGols2;

        printf("Registro atualizado com sucesso.\n");
    } else {
        printf("Atualizacao cancelada.\n");
    }
}

// Salva o estado atual da lista de partidas de volta no arquivo CSV.
void salvar_partidas(BDPartidas *bdp, char *caminho) {
    FILE *f = fopen(caminho, "w");
    if (!f) {
        printf("Erro ao salvar arquivo de partidas: %s\n", caminho);
        return;
    }

    // Escreve o cabecalho, no mesmo formato do arquivo original.
    fprintf(f, "ID,Time1,Time2,GolsTime1,GolsTime2\n");

    NodePartida *aux = bdp->inicio;
    while (aux != NULL) {
        fprintf(f, "%d,%d,%d,%d,%d\n",
                aux->data.id,
                aux->data.idTime1,
                aux->data.idTime2,
                aux->data.gols1,
                aux->data.gols2);
        aux = aux->prox;
    }

    fclose(f);
}

// Libera toda a memoria alocada pela lista de partidas.
void liberar_partidas(BDPartidas *bdp) {
    NodePartida *aux = bdp->inicio;
    while (aux != NULL) {
        NodePartida *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    bdp->inicio = NULL;
    bdp->qtd = 0;
}