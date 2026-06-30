#include <stdio.h>
#include "bd_times.h"
#include "bd_partidas.h"

int main() {
    BDTimes bdt;
    BDPartidas bdp;
    char acesso = 0;

    char arquivo_times[] = "times.csv";
    char arquivo_partidas[] = "partidas.csv";

    carrega_times(&bdt, arquivo_times);
    carrega_partidas(&bdp, &bdt, arquivo_partidas);

    while (acesso != 'Q' && acesso != 'q') {
        printf("Sistema de gerenciamento de Partidas \n");
        printf("1 - Consultar time \n");
        printf("2 - Consultar partidas \n");
        printf("3 - Atualizar partida \n");
        printf("4 - Remover partida \n");
        printf("5 - Inserir partida \n");
        printf("6 - Imprimir tabela de classificacao \n");
        printf("Q - Sair \n");

        scanf(" %c", &acesso);

        if (acesso == 'Q' || acesso == 'q') {
            break;
        }

        if (acesso == '1') {
            char pref[50];
            printf("Prefixo: ");
            scanf("%49s", pref);
            buscar_time(&bdt, pref);
        } else if (acesso == '2') {
            int modo;
            char nome[50];

            printf("Modo (1-Mandante, 2-Visitante, 3-Ambos, 4-Voltar): ");
            scanf("%d", &modo);

            if (modo == 4) {
                continue;
            }

            printf("Nome/Prefixo: ");
            scanf("%49s", nome);
            consulta_partidas(&bdp, &bdt, nome, modo);
        } else if (acesso == '3') {
            atualizar_partida(&bdp, &bdt);
            salvar_partidas(&bdp, arquivo_partidas);
        } else if (acesso == '4') {
            remover_partida(&bdp, &bdt);
            salvar_partidas(&bdp, arquivo_partidas);
        } else if (acesso == '5') {
            inserir_partida(&bdp, &bdt);
            salvar_partidas(&bdp, arquivo_partidas);
        } else if (acesso == '6') {
            imprimir_tabela(&bdt);
            printf("\n");
        } else {
            printf("Opcao invalida.\n");
        }

        printf("\n");
    }

    // Libera toda a memoria alocada antes de encerrar.
    liberar_times(&bdt);
    liberar_partidas(&bdp);

    return 0;
}