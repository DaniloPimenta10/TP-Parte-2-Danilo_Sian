# Campeonato Computacional de Futebol — Parte I

Este projeto consiste no desenvolvimento de um sistema modular em Linguagem C projetado para o gerenciamento, persistência e processamento de dados de um campeonato de futebol de pontos corridos constituído por 10 clubes. 

Esta primeira etapa contempla a carga automatizada de arquivos no formato CSV, rotinas de busca textual de equipes por prefixo, filtragem avançada de confrontos e a exibição da tabela de classificação geral da competição.

---

## Estrutura do Projeto

O projeto está organizado na raiz do diretório com a seguinte disposição de arquivos:

```text
├── main.c             # Ponto de entrada do programa e fluxo do menu principal
├── time.c / time.h    # TAD que define uma equipe e suas operações individuais
├── partida.c / partida.h # TAD que representa um confronto do campeonato
├── bd_times.c / bd_times.h # Gerenciador e persistência da coleção de clubes
├── bd_partidas.c / bd_partidas.h # Gerenciador e processamento do histórico de jogos
├── times.csv          # Base de dados: Cadastro oficial dos 10 clubes participantes
├── partidas_completo.csv # Base de dados: Relatório completo de partidas executadas
└── Makefile           # Script de automação de compilação e limpeza do sistema
```
---

## TADs (Tipos Abstratos de Dados)

O sistema foi estruturado de forma modular através de tipos abstratos de dados bem definidos:

1. Time
Representa uma agremiação desportiva unidade e encapsula os seus acumuladores numéricos de desempenho.

```C
typedef struct {
    int id;
    char nome[50];
    int v;  // Vitórias
    int e;  // Empates
    int d;  // Derrotas
    int gm; // Gols marcados
    int gs; // Gols sofridos
} Time;
```

2. Partida
Estrutura elementar que representa uma linha do arquivo de confrontos, mapeando os times pelos seus respectivos IDs.
```C
typedef struct {
    int id;
    int idTime1; // ID do time Mandante
    int idTime2; // ID do time Visitante
    int gols1;   // Gols do Mandante
    int gols2;   // Gols do Visitante
} Partida;
```

3. BDTimes
TAD responsável pelo gerenciamento da coleção de clubes, controlando a persistência e as buscas na memória.
```c
typedef struct {
    Time times[10];
    int qtd;
} BDTimes;
```

4. BDPartidas
TAD responsável por armazenar o histórico completo de confrontos e gerenciar o processamento de dados da liga.
```c
typedef struct {
    Partida partida[100];
    int qtd;
} BDPartidas;
```
---

### Funcionalidades Implementadas
Carga Automatizada de Dados: Inicialização do sistema com leitura sequencial e tratamento de cabeçalhos de arquivos CSV (times.csv e partidas_completo.csv) carregados diretamente na memória volátil.

Consulta Avançada de Times: Mecanismo de busca textual por prefixo que exibe as estatísticas completas consolidadas de uma ou mais equipes.

Filtragem Customizada de Partidas: Histórico de confrontos pesquisável por equipe, permitindo ao usuário selecionar três modos de visualização: apenas jogos como Mandante, apenas como Visitante, ou Ambos.

Tabela de Classificação Dinâmica: Exibição ordenada do desempenho da liga com pontuações calculadas em tempo de execução, contando com paginação de 5 em 5 registros para manter a legibilidade do terminal.

---

#### Decisões de Implementação
Processamento Incremental Prévio: Ao invés de recalcular todo o campeonato a cada interação do menu, a função carrega_partidas() faz o mapeamento reverso atualizando cumulativamente os campos de desempenho das structs de cada time (v, e, d, gm, gs) logo no início da execução.

Busca por Prefixo Insensível a Caso (Case‑Insensitive): Utilização da função strncasecmp associada ao comprimento (strlen) do termo digitado pelo usuário. Isso possibilita que buscas por "java" ou "JAVA" localizem corretamente o clube "JAVAlis".

Saneamento Preventivo do Buffer do stdin: A transição de leitura entre opções capturadas via caractere (scanf) e comandos por tecla gera quebras de linha residuais (\n) na memória. Foi embutido um laço while ((c = getchar()) != '\n' && c != EOF); antes de exibir tabelas para impedir que o sistema pule opções automaticamente.

Máscaras de Formatação Fixa: Alinhamento estético homogêneo no terminal utilizando formatação elástica à esquerda (%-10s) para nomes de clubes e reservas simétricas à direita (%3d) para as colunas numéricas, replicando o visual de uma planilha de dados.

---

##### Instruções para Execução
Compilar o Projeto Execute o utilitário make na raiz do diretório para invocar o roteiro de compilação automática:
```Bash
make
```

Executar o Programa Após a geração bem-sucedida do executável binário, inicialize o sistema com o comando:
```Bash
./sistema
```

Limpeza dos Arquivos Objeto Caso queira apagar os binários compilados e redefinir o diretório de trabalho, utilize:
```Bash
make clean
```