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
    Estrutura de dados que representa um território.
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* -------------------------------------------------------------------
    Função: atribuirMissao
    Objetivo: sortear uma missão do vetor de missões e copiar para o destino
--------------------------------------------------------------------*/
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

/* -------------------------------------------------------------------
    Função: exibirMissao
    Objetivo: exibir a missão do jogador (somente no início)
--------------------------------------------------------------------*/
void exibirMissao(char* missao) {
    printf("Sua missão: %s\n\n", missao);
}

/* -------------------------------------------------------------------
    Função: verificarMissao
    Objetivo: verificar se a missão foi cumprida
    Observação: Implementação simples, pode ser expandida depois.
--------------------------------------------------------------------*/
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Regra 1: "Conquistar 3 territórios seguidos"
    if (strstr(missao, "Conquistar 3") != NULL) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) cont++;
        }
        if (cont >= 3) return 1;
    }

    // Regra 2: "Eliminar tropas vermelhas"
    if (strstr(missao, "vermelha") != NULL) {
        int existe = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) existe = 1;
        }
        if (!existe) return 1;
    }

    // Regra 3: "Dominar todos os territórios"
    if (strstr(missao, "todos") != NULL) {
        int dominio = 1;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") != 0) dominio = 0;
        }
        if (dominio) return 1;
    }

    return 0;
}

/* -------------------------------------------------------------------
    Função: exibirMapa
    Objetivo: mostrar todos os territórios atualizados
--------------------------------------------------------------------*/
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

/* -------------------------------------------------------------------
    Função: atacar
    Objetivo: simular ataque entre territórios
--------------------------------------------------------------------*/
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- ATAQUE INICIADO ---\n");

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoA);
    printf("Dado do defensor: %d\n", dadoD);

    if (dadoA > dadoD) {
        printf("Resultado: Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Resultado: Defensor resistiu!\n");
        if (atacante->tropas > 0) atacante->tropas -= 1;
    }

    printf("-------------------------\n\n");
}

/* -------------------------------------------------------------------
    Função: liberarMemoria
    Objetivo: liberar todas as alocações dinâmicas do sistema
--------------------------------------------------------------------*/
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

/* -------------------------------------------------------------------
    Função principal
--------------------------------------------------------------------*/
int main() {
    srand(time(NULL));

    // Missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Dominar todos os territorios do mapa",
        "Conquistar qualquer territorio inimigo",
        "Manter ao menos 2 territorios por 3 turnos"
    };
    int totalMissoes = 5;

    // Alocação dinâmica da missão do jogador
    char* missaoJogador = (char*) malloc(100 * sizeof(char));

    // Atribuir missão ao jogador
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    printf("\n=== WAR ESTRUTURADO — DESAFIO FINAL ===\n");
    exibirMissao(missaoJogador);  // Exibe missão apenas no início

    // Quantidade de territórios
    int n;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

    // Cadastro
    printf("\n=== Cadastro de Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }

    int turno = 1;

    while (1) {
        printf("\n=== TURNO %d ===\n", turno);
        exibirMapa(mapa, n);

        int at, df;
        printf("Escolha o territorio atacante: ");
        scanf("%d", &at);

        printf("Escolha o territorio defensor: ");
        scanf("%d", &df);

        // Validações
        if (strcmp(mapa[at].cor, mapa[df].cor) == 0) {
            printf("ERRO: Não pode atacar um território da mesma cor!\n");
        } else {
            atacar(&mapa[at], &mapa[df]);
        }

        // Verificação silenciosa da missão
        if (verificarMissao(missaoJogador, mapa, n)) {
            printf("\n=== MISSÃO CUMPRIDA! ===\n");
            printf("Você venceu o jogo!\n");
            break;
        }

        turno++;
    }

    // Liberar memória
    liberarMemoria(mapa, missaoJogador);

    printf("\nMemoria liberada. Jogo encerrado.\n");
    return 0;
}
