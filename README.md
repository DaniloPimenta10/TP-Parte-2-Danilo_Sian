# Campeonato Computacional de Futebol — Parte II

Este projeto consiste no desenvolvimento de um sistema modular em Linguagem C projetado para o gerenciamento, persistência e processamento de dados de um campeonato de futebol de pontos corridos constituído por 10 clubes.

Esta segunda etapa expande o sistema com a manutenção completa dos dados (inserção, remoção e atualização de partidas), a ordenação da tabela de classificação e a migração das estruturas de dados para listas simplesmente encadeadas com alocação dinâmica de memória.

---

## Estrutura do Projeto

O projeto está organizado na raiz do diretório com a seguinte disposição de arquivos:

```text
├── main.c                # Ponto de entrada do programa e fluxo do menu principal
├── time.c / time.h       # TAD que define uma equipe e suas operações individuais
├── partida.c / partida.h # TAD que representa um confronto do campeonato
├── bd_times.c / bd_times.h     # Gerenciador da lista encadeada de clubes
├── bd_partidas.c / bd_partidas.h # Gerenciador da lista encadeada de partidas
├── times.csv             # Base de dados: Cadastro oficial dos 10 clubes participantes
├── partidas.csv          # Base de dados: Registro das partidas do campeonato
└── Makefile              # Script de automação de compilação e limpeza do sistema
```

---

## TADs (Tipos Abstratos de Dados)

O sistema foi estruturado de forma modular através de tipos abstratos de dados bem definidos:

### 1. Time
Representa uma equipe de futebol e encapsula seus acumuladores numéricos de desempenho. Expõe uma interface pública de acesso e manipulação de dados para uso por outros módulos.

```c
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

### 2. NodeTime
Nó da lista encadeada que envolve o TAD Time, permitindo o encadeamento dinâmico dos registros de clubes.

```c
typedef struct NodeTime {
    Time data;
    struct NodeTime *prox;
} NodeTime;
```

### 3. Partida
Estrutura elementar que representa uma linha do arquivo de confrontos, mapeando os times pelos seus respectivos IDs.

```c
typedef struct {
    int id;
    int idTime1; // ID do time Mandante
    int idTime2; // ID do time Visitante
    int gols1;   // Gols do Mandante
    int gols2;   // Gols do Visitante
} Partida;
```

### 4. NodePartida
Nó da lista encadeada que envolve o TAD Partida, permitindo o encadeamento dinâmico dos registros de confrontos.

```c
typedef struct NodePartida {
    Partida data;
    struct NodePartida *prox;
} NodePartida;
```

### 5. BDTimes
TAD responsável pelo gerenciamento da coleção de clubes por meio de uma lista simplesmente encadeada, substituindo o vetor estático da Parte I.

```c
typedef struct {
    NodeTime *inicio;
    int qtd;
} BDTimes;
```

### 6. BDPartidas
TAD responsável por armazenar e gerenciar o histórico completo de confrontos em uma lista simplesmente encadeada, habilitando inserção, remoção e atualização dinâmica de registros.

```c
typedef struct {
    NodePartida *inicio;
    int qtd;
} BDPartidas;
```

---

## Funcionalidades Implementadas

**Carga Automatizada de Dados:** Inicialização do sistema com leitura sequencial e tratamento de cabeçalhos de arquivos CSV (`times.csv` e `partidas.csv`), carregando os registros em listas encadeadas alocadas dinamicamente.

**Consulta Avançada de Times:** Mecanismo de busca textual por prefixo que exibe as estatísticas completas consolidadas de uma ou mais equipes.

**Filtragem Customizada de Partidas:** Histórico de confrontos pesquisável por equipe, permitindo ao usuário selecionar três modos de visualização: apenas jogos como Mandante, apenas como Visitante, ou Ambos.

**Atualização de Partida:** Localização de um registro por consulta prévia e edição dos placares, com suporte ao caractere `-` para manter o valor atual de um campo. As estatísticas dos times são recalculadas automaticamente.

**Remoção de Partida:** Exclusão definitiva de um registro após confirmação do usuário, com atualização automática das estatísticas dos times envolvidos e religamento da lista encadeada.

**Inserção de Partida:** Cadastro de novos confrontos com validação dos times informados, geração automática de ID por autoincremento e confirmação antes da persistência.

**Tabela de Classificação Ordenada:** Exibição do desempenho da liga ordenada decrescentemente por Pontos Ganhos (PG), com critérios de desempate por Vitórias (V) e Saldo de Gols (S), utilizando Selection Sort. A saída é paginada de 5 em 5 registros.

**Persistência:** Toda operação de inserção, remoção ou atualização confirmada é automaticamente refletida no arquivo `partidas.csv`.

---

## Decisões de Implementação

**Migração para Lista Encadeada:** As estruturas `BDTimes` e `BDPartidas` foram migradas de vetores estáticos para listas simplesmente encadeadas com alocação dinâmica (`malloc`), eliminando o limite fixo de registros e permitindo inserções e remoções sem deslocamento de elementos.

**Encapsulamento entre Módulos:** O módulo `bd_partidas.c` não acessa diretamente os campos internos do TAD `Time`. Toda manipulação de estatísticas é feita exclusivamente pelas funções públicas `time_atualizar_estatisticas` e `time_desfazer_estatisticas`, e o acesso ao nome do time é feito via `time_get_nome`.

**Aplicar e Desfazer Estatísticas:** Ao invés de reprocessar todas as partidas a cada operação, o sistema mantém as estatísticas acumuladas incrementalmente. Ao inserir uma partida, `time_atualizar_estatisticas` é chamada; ao remover ou atualizar, `time_desfazer_estatisticas` reverte o impacto antes de aplicar os novos valores.

**Autoincremento de ID:** O ID de uma nova partida é gerado percorrendo a lista e encontrando o maior ID existente, somando 1. Isso garante unicidade mesmo após remoções.

**Selection Sort para Ordenação:** A tabela de classificação é ordenada por meio do algoritmo Selection Sort aplicado sobre um vetor auxiliar de ponteiros para os nós da lista, sem modificar a lista original. Os critérios de ordenação são: Pontos Ganhos (PG) → Vitórias (V) → Saldo de Gols (S).

**Busca por Prefixo Insensível a Caso:** Utilização da função `strncasecmp` associada ao comprimento (`strlen`) do termo digitado pelo usuário, permitindo que buscas por `"java"` ou `"JAVA"` localizem corretamente o clube `"JAVAlis"`.

**Compilação Modular:** O Makefile compila cada módulo `.c` em um arquivo objeto `.o` separado antes da linkagem final, evitando recompilação desnecessária de módulos não alterados.

---

## Instruções para Execução

**Compilar o Projeto:** Execute o utilitário `make` na raiz do diretório:
```bash
make
```

**Executar o Programa:** Após a geração do executável:
```bash
./sistema
```

**Limpeza dos Arquivos Objeto:** Para apagar os binários compilados:
```bash
make clean
```

**Cenários de Teste:** Para testar diferentes estágios do campeonato, substitua o conteúdo de `partidas.csv` por um dos arquivos disponíveis:

| Arquivo | Descrição |
|---|---|
| `partidas_vazio.csv` | Campeonato sem partidas disputadas |
| `partidas_parcial.csv` | Campeonato em andamento |
| `partidas_completo.csv` | Campeonato finalizado |
