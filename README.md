# Trabalho Prático: Campeonato Computacional de Futebol — Parte I

Este trabalho prático consiste no desenvolvimento de um sistema modular em Linguagem C voltado para o gerenciamento e processamento de dados de um campeonato computacional de futebol de pontos corridos, constituído por 10 clubes (indexados de 0 a 9). 

Esta primeira etapa contempla a carga automática de dados a partir de arquivos no formato CSV, rotinas de consulta textual de equipes e partidas, e a exibição controlada e paginada da tabela de classificação geral da competição.

---

## 🚀 Passo-a-passo para Execução

O projeto dispõe de um arquivo `Makefile` que automatiza e padroniza o fluxo de compilação em conformidade com as diretrizes da disciplina (utilizando as flags de erro `-Wall -Wextra -std=c11 -pedantic`).

### Pré-requisitos
* Ambiente operacional Linux Ubuntu 22.04 (ou subsistema WSL).
* Compilador GCC e utilitário GNU Make instalados.

### Instruções no Terminal

1. **Compilar o Projeto:**
   Certifique-se de estar no diretório raiz que contém o arquivo `Makefile` e execute:
   ```bash
   make
Este comando invocará o GCC para processar os módulos de código e gerará o binário executável final denominado sistema.

Iniciar o Sistema:
Para rodar a aplicação carregando as estruturas em memória, execute:

Bash
./sistema
Limpeza do Diretório:
Para remover o arquivo binário gerado e redefinir o ambiente de compilação, utilize:

Bash
make clean
🏗️ Explicação dos Principais TADs
O sistema foi concebido sob o paradigma da modularização abstrata de dados, mapeando as entidades lógicas do campeonato em arquivos de interface (.h) e implementação (.c) distintos:

TAD Time (Time): Mapeia a estrutura individual de uma agremiação desportiva, armazenando suas propriedades fixas (id e nome) e os acumuladores numéricos variáveis de desempenho de liga (v, e, d, gm, gs). Suas funções públicas calculam sob demanda propriedades derivadas como o Saldo de Gols e os Pontos Ganhos.

TAD BDTimes (BDTimes): Atua como o nível de persistência e gerenciamento da coleção global de equipes. Coordena a leitura e parseamento gramatical do arquivo times.csv para o vetor interno, além de concentrar os algoritmos de varredura textual e exibição de tabelas.

TAD Partida (Partida): Estrutura de dados elementar que encapsula os registros textuais de um confronto direto, documentando o identificador do jogo, os índices numéricos das duas equipes envolvidas (idTime1 para mandante e idTime2 para visitante) e os respectivos tentos assinalados (gols1 e gols2).

TAD BDPartidas (BDPartidas): Funciona como o repositório em memória de todos os confrontos do campeonato. Sua responsabilidade principal reside em abrir e interpretar o arquivo de partidas executadas, efetuando o acoplamento com o BDTimes para computar retroativamente as estatísticas gerais da liga.

🧠 Principais Decisões de Implementação
Durante a fase de engenharia e codificação desta primeira etapa, adotou-se um conjunto de premissas de design para assegurar conformidade operacional e robustez:

Processamento Incremental Prévio de Pontuação: Em vez de recalcular todo o campeonato a cada interação de menu, a função carrega_partidas faz o mapeamento inverso nos ponteiros das structs de cada time à medida que lê o arquivo CSV. Através do método buscar_time_por_id, o sistema atualiza cumulativamente os campos de desempenho das equipes de forma assintótica linear, permitindo que a tabela de classificação esteja sempre pronta para exibição imediata.

Paginação Estrita por Interrupção de Teclado: Obedecendo ao requisito de usabilidade para evitar o estouro de tela de terminais convencionais, implementou-se em imprimir_tabela uma lógica de controle de fluxo de blocos de 5 em 5 registros. Para prevenir falhas lógicas e páginas vazias em campeonatos de dimensões customizadas, o laço de exibição calcula o limite exato baseado em bd->qtd, mitigando exibições fantasma após o décimo clube.

Saneamento Preventivo de Buffer do stdin: A transição de leitura entre escolhas numéricas via caractere no menu (scanf) e a requisição de strings de paginação gera quebras de linha residuais (\n) na memória volátil. Para impossibilitar o comportamento anômalo de pular telas automaticamente, foi embutida uma rotina de expurgo de buffer baseada em um laço de repetição condicional ativo while ((c = getchar()) != '\n' && c != EOF); imediatamente antes das exibições tabulares.

Alinhamento Estético Homogêneo: Para anular distorções visuais decorrentes do comprimento variável dos nomes dos clubes e manter as colunas numéricas rigorosamente posicionadas abaixo de seus respectivos cabeçalhos, aplicou-se um modelo híbrido de máscara de formatação no printf. O nome do clube recebe uma reserva elástica estática alinhada à esquerda (%-20s), enquanto as estatísticas subsequentes são empurradas de forma simétrica com limites explícitos de casas inteiras (%2d, %3d).

Busca por Prefixo Insensível a Caixa (Case-Insensitive): As consultas textuais de equipes e partidas foram dotadas de flexibilidade por meio da função padrão strncasecmp combinada dinamicamente com o comprimento exato (strlen) do termo digitado. Isso garante o casamento de padrões ideal mesmo que o usuário insira termos de busca em letras inteiramente minúsculas ou maiúsculas, capturando o prefixo com precisão computacional.