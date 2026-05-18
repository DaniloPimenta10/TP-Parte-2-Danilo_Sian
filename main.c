#include <stdio.h>
#include "bd_times.h"
#include "bd_partidas.h"

int main() {
    BDTimes bdt;      // banco de dados dos times
    BDPartidas bdp;  // banco de dados das partidas
    char acesso = 0; // guarda a opcao escolhida no menu

    /*
     * aqui escolhemos qual arquivo de partidas sera carregado.
     * para testar outros cenarios, basta trocar o nome abaixo por:
     * "partidas_vazio.csv", "partidas_parcial.csv" ou "partidas_completo.csv".
     */
    char arquivo_partidas[] = "partidas_completo.csv";

    // carrega os dados dos arquivos CSV para a memoria antes do menu iniciar
    carrega_times(&bdt, "times.csv");
    carrega_partidas(&bdp, &bdt, arquivo_partidas);

    while (acesso != 'Q' && acesso != 'q') { // repete ate o usuario escolher sair
        printf("Sistema de gerenciamento de Partidas \n");
        printf("1 - Consultar time \n");
        printf("2 - Consultar partidas \n");
        printf("3 - Atualizar partida (desabilitado nesta etapa) \n");
        printf("4 - Remover partida (desabilitado nesta etapa) \n");
        printf("5 - Inserir partida (desabilitado nesta etapa) \n");
        printf("6 - Imprimir tabela de classificacao \n");
        printf("Q - Sair \n");

        scanf(" %c", &acesso);

        if (acesso == 'Q' || acesso == 'q') {
            break;
        }

        if (acesso == '1') { // consulta estatisticas de um ou mais times
            char pref[50];

            printf("Prefixo: ");
            scanf("%49s", pref);
            buscar_time(&bdt, pref);
        } else if (acesso == '2') { // consulta partidas por time mandante/visitante
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
        } else if (acesso == '6') { // imprime todos os times com a pontuacao acumulada
            imprimir_tabela(&bdt);
            printf("\n");
        } else if (acesso == '3' || acesso == '4' || acesso == '5') {
            printf("Funcionalidade desabilitada nesta etapa.\n");
        } else {
            printf("Opção invalida.\n");
        }
        
        printf("\n");
    
    }


    return 0;
}
