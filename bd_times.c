#include "bd_times.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Carrega o arquivo times.csv para a lista encadeada de times.
void carrega_times(BDTimes *bd, char *caminho) {
    bd->inicio = NULL;
    bd->qtd = 0;

    FILE *f = fopen(caminho, "r");
    if (!f) {
        printf("Erro ao abrir arquivo de times: %s\n", caminho);
        return;
    }

    char buffer[100];

    // Pula a primeira linha, que e o cabecalho do CSV.
    fgets(buffer, sizeof(buffer), f);

    while (fgets(buffer, sizeof(buffer), f)) {
        Time t;
        if (sscanf(buffer, "%d,%[^\n\r]", &t.id, t.nome) == 2) {
            // Estatísticas começam zeradas.
            t.v = t.e = t.d = t.gm = t.gs = 0;

            // Aloca um novo nó.
            NodeTime *novo = (NodeTime *)malloc(sizeof(NodeTime));
                if (!novo) {
                printf("Erro de alocacao de memoria.\n");
                fclose(f);
                return;
                }

            novo->data = t;
            novo->prox = NULL;

            // Insere no final da lista para manter a ordem do CSV.
            if (bd->inicio == NULL) {
                bd->inicio = novo;
            } else {
                NodeTime *aux = bd->inicio;
                while (aux->prox != NULL) {
                    aux = aux->prox;
                }
                aux->prox = novo;
            }

            bd->qtd++;
        }
    }

    fclose(f);
}

// Retorna ponteiro para o time com o ID informado, ou NULL se não encontrar.
NodeTime *buscar_time_por_id_node(BDTimes *bd, int id) {
    NodeTime *aux = bd->inicio;
    while (aux != NULL) {
        if (aux->data.id == id) return aux;
        aux = aux->prox;
    }
    return NULL;
}

// Busca times cujo nome começa com o prefixo informado.
void buscar_time(BDTimes *bd, char *prefixo) {
    int found = 0;
    NodeTime *aux = bd->inicio;

    while (aux != NULL) {
        if (strncasecmp(aux->data.nome, prefixo, strlen(prefixo)) == 0) {
            if (!found) {
                printf("ID   Time         V   E   D  GM  GS   S PG\n");
            }
            dados_time(aux->data);
            found = 1;
        }
        aux = aux->prox;
    }

    if (!found) {
        printf("Time nao encontrado.\n");
    }
}

// Copia a lista para um vetor auxiliar e ordena por PG > V > Saldo de Gols.
static void ordenar_times(NodeTime **vetor, int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        int maior = i;

        // Procura o maior elemento no restante do vetor.
        for (int j = i + 1; j < qtd; j++) {
            Time a = vetor[j]->data;
            Time b = vetor[maior]->data;

            int pg_a = pontos_ganhos(a), pg_b = pontos_ganhos(b);
            int sg_a = saldo_gols(a),    sg_b = saldo_gols(b);

            // Verifica se j é maior que o atual maior, pelos critérios de desempate.
            if (pg_a > pg_b) maior = j;
            else if (pg_a == pg_b && a.v > b.v) maior = j;
            else if (pg_a == pg_b && a.v == b.v && sg_a > sg_b) maior = j;
        }

        // Troca o maior encontrado com a posição i.
        if (maior != i) {
            NodeTime *tmp = vetor[i];
            vetor[i] = vetor[maior];
            vetor[maior] = tmp;
        }
    }
}

// Imprime a tabela de classificação ordenada, com paginação de 5 em 5.
void imprimir_tabela(BDTimes *bd) {
    if (bd->qtd == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    // Copia ponteiros da lista para vetor auxiliar para ordenar.
    NodeTime **vetor = (NodeTime **)malloc(bd->qtd * sizeof(NodeTime *));
    if (!vetor) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    NodeTime *aux = bd->inicio;
    for (int i = 0; i < bd->qtd; i++) {
        vetor[i] = aux;
        aux = aux->prox;
    }

    ordenar_times(vetor, bd->qtd);

    int c;
    while ((c = getchar()) != '\n' && c != EOF); // limpa buffer

    printf("ID   Time         V   E   D  GM  GS   S PG\n");
    for (int i = 0; i < bd->qtd; i++) {
        dados_time(vetor[i]->data);

        if ((i + 1) % 5 == 0 && (i + 1) < bd->qtd) {
            char pausa[10];
            printf("\n--- Pressione [ENTER] para ver a proxima pagina ---");
            fgets(pausa, sizeof(pausa), stdin);
            printf("\n=== PROXIMA PAGINA ===\n\n");
            printf("ID   Time         V   E   D  GM  GS   S PG\n");
        }
    }

    free(vetor);
}

// Libera toda a memória alocada pela lista de times.
void liberar_times(BDTimes *bd) {
    NodeTime *aux = bd->inicio;
    while (aux != NULL) {
        NodeTime *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    bd->inicio = NULL;
    bd->qtd = 0;
}