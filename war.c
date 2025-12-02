// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Estrutura que representa um território no jogo.
    Possui nome, cor do exército e quantidade de tropas.
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


/*----------------------------------------------------------
    Função: cadastrarTerritorios
    Objetivo: preencher o vetor de territórios usando ponteiros
----------------------------------------------------------*/
void cadastrarTerritorios(Territorio* mapa, int total) {
    printf("\n=== Cadastro de Territórios ===\n\n");

    for (int i = 0; i < total; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}


/*----------------------------------------------------------
    Função: exibirTerritorios
    Objetivo: mostrar os dados de todos os territórios
----------------------------------------------------------*/
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n=== Territórios no Mapa ===\n\n");

    for (int i = 0; i < total; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    printf("\n");
}


/*----------------------------------------------------------
    Função: atacar
    Objetivo: simular combate entre dois territórios usando dados
----------------------------------------------------------*/
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== Ataque Iniciado ===\n");

    printf("Atacante: %s (%s) com %d tropas\n",
           atacante->nome, atacante->cor, atacante->tropas);

    printf("Defensor: %s (%s) com %d tropas\n",
           defensor->nome, defensor->cor, defensor->tropas);

    // Rolagem de "dados"
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nDado do atacante: %d\n", dadoA);
    printf("Dado do defensor: %d\n", dadoD);

    // Lógica do combate
    if (dadoA > dadoD) {
        printf("\nResultado: O atacante VENCEU!\n");

        // Transferência de domínio e tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;  
        printf("O território %s foi conquistado!\n", defensor->nome);

    } else {
        printf("\nResultado: O defensor RESISTIU!\n");

        // Atacante perde 1 tropa, mas nunca menos que 0
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }

        printf("O atacante perdeu 1 tropa!\n");
    }

    printf("\n=== Fim do Ataque ===\n\n");
}


/*----------------------------------------------------------
    Função: liberarMemoria
    Objetivo: liberar a memória alocada dinamicamente
----------------------------------------------------------*/
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}


/*----------------------------------------------------------
    Função principal
----------------------------------------------------------*/
int main() {
    srand(time(NULL)); // Garantir aleatoriedade

    int total;

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &total);

    // Alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(total, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(mapa, total);

    // Exibição inicial
    exibirTerritorios(mapa, total);

    // Escolha do ataque
    int ia, id;

    printf("Escolha o índice do território ATACANTE: ");
    scanf("%d", &ia);

    printf("Escolha o índice do território DEFENSOR: ");
    scanf("%d", &id);

    // Validações
    if (ia < 0 || ia >= total || id < 0 || id >= total) {
        printf("Índice inválido! Encerrando...\n");
        liberarMemoria(mapa);
        return 0;
    }

    if (strcmp(mapa[ia].cor, mapa[id].cor) == 0) {
        printf("\nERRO: não é permitido atacar um território da mesma cor!\n");
        liberarMemoria(mapa);
        return 0;
    }

    // Realizar ataque
    atacar(&mapa[ia], &mapa[id]);

    // Exibir mapa após ataque
    exibirTerritorios(mapa, total);

    // Liberar memória
    liberarMemoria(mapa);

    return 0;
}

