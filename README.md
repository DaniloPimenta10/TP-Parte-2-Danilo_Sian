# Campeonato Computacional de Futebol — Parte I

Este projeto consiste no desenvolvimento de um sistema modular em Linguagem C projetado para o gerenciamento, persistência e processamento de dados de um campeonato de futebol de pontos corridos constituído por 10 clubes. 

Esta primeira etapa contempla a carga automatizada de arquivos no formato CSV, rotinas de busca textual de equipes por prefixo, filtragem avançada de confrontos e a exibição controlada e paginada da tabela de classificação geral da competição.

---

## Estrutura do Projeto

O projeto está organizado na seguinte estrutura de arquivos e diretórios:

```text
├── codigo/                # Diretório contendo o código-fonte do sistema
│   ├── main.c             # Ponto de entrada do programa e fluxo do menu principal
│   ├── time.c / time.h    # TAD que define uma equipe e suas operações individuais
│   ├── partida.c / partida.h # TAD que representa um confronto do campeonato
│   ├── bd_times.c / bd_times.h # Gerenciador e persistência da coleção de clubes
│   └── bd_partidas.c / bd_partidas.h # Gerenciador e processamento do histórico de jogos
├── dados/                 # Arquivos de persistência (Banco de Dados CSV)
│   ├── times.csv          # Cadastro oficial dos 10 clubes participantes
│   └── partidas_completo.csv # Relatório de partidas parciais ou completas
└── Makefile               # Script de automação de compilação e limpeza
    TADs (Tipos Abstratos de Dados)
O sistema foi estruturado de forma modular através de tipos abstratos de dados bem definidos:

1. Time
Representa uma agremiação desportiva individual e encapsula seus acumuladores numéricos de desempenho.

C
typedef struct {
    int id;
    char nome[50];
    int v;  // Vitórias
    int e;  // Empates
    int d;  // Derrotas
    int gm; // Gols marcados
    int gs; // Gols sofridos
} Time;
2. Partida
Estrutura elementar que representa uma linha do arquivo de confrontos, mapeando os times pelos seus respectivos IDs.

C
typedef struct {
    int id;
    int idTime1; // ID do time Mandante
    int idTime2; // ID do time Visitante
    int gols1;   // Gols do Mandante
    int gols2;   // Gols do Visitante
} Partida;
Funcionalidades Implementadas
Carga de Dados Automática: Leitura sequencial e tratamento de cabeçalhos de arquivos CSV (times.csv e partidas_completo.csv).

Consulta de Times: Mecanismo de busca que lista dados consolidados de uma equipe filtrando pelo começo de seu nome.

Consulta de Partidas: Filtragem customizada de jogos onde o usuário pode escolher ver apenas partidas como Mandante, apenas como Visitante ou Ambos.

Exibição Paginada da Classificação: Renderização organizada de 5 em 5 registros para evitar o estouro de tela do terminal.

    Decisões de Implementação
Processamento Incremental Prévio: Ao invés de recalcular todo o campeonato a cada interação do menu, a função carrega_partidas() faz o mapeamento reverso atualizando cumulativamente os campos de desempenho das structs de cada time (v, e, d, gm, gs) logo no início da execução.

Busca por Prefixo Insensível a Caso (Case‑Insensitive): Utilização da função strncasecmp associada ao comprimento (strlen) do termo digitado pelo usuário. Isso possibilita que buscas por "java" ou "JAVA" localizem corretamente o clube "JAVAlis".

Saneamento Preventivo do Buffer do stdin: A transição de leitura entre opções capturadas via caractere (scanf) e comandos de paginação por tecla gera quebras de linha residuais (\n) na memória. Foi embutido um laço while ((c = getchar()) != '\n' && c != EOF); antes de exibir tabelas para impedir que o sistema pule páginas automaticamente.

Máscaras de Formatação Fixa: Alinhamento estético homogêneo no terminal utilizando formatação elástica à esquerda (%-20s) para nomes de clubes e reservas simétricas à direita (%2d, %3d) para as colunas numéricas, replicando o visual de uma planilha de dados.

    Como Executar o Programa
O projeto foi projetado e validado para execução em ambiente Linux Ubuntu 22.04 utilizando as flags rigorosas de erro do GCC (-Wall -Wextra -std=c11 -pedantic).

1. Compilar o Projeto
Execute o utilitário make na raiz do diretório para invocar o roteiro de compilação automática:

Bash
make
2. Executar o Sistema
Após a geração bem-sucedida do executável binário, inicialize o sistema com o comando:

Bash
./main