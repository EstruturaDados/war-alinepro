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

#include <stdio.h>   // entrada e saída (printf, scanf, fgets)
#include <stdlib.h>  // para alocação dinâmica (calloc, free) e rand
#include <string.h>  // para manipulação de strings (strcpy)
#include <time.h>    // para usar o tempo como semente do rand

#define QTD_TERRITORIOS 5  // Quantidade fixa de territórios
#define TAM 50             // Tamanho máximo para strings

/* Estrutura que representa um território do jogo */
typedef struct {
    char nome[TAM];   // Nome do território
    char cor[TAM];    // Cor do exército dominante
    int tropas;       // Quantidade de tropas no território
} Territorio;

/* Função responsável por exibir o estado atual do mapa */
void exibirMapa(Territorio *t) {

    // Percorre todos os territórios
    printf("\n📍 ESTADO ATUAL DO MAPA 📍\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {

        // Exibe os dados de cada território
        printf("Território %d\n", i + 1);
        printf("Nome: %s", t[i].nome);
        printf("Cor do Exército: %s", t[i].cor);
        printf("Tropas: %d\n\n", t[i].tropas);
    }
}

//Função que simula uma batalha entre dois territórios 
void atacar(Territorio *t, int atk, int def) {

    // Gera valores aleatórios entre 1 e 6 para ataque e defesa
    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    // Exibe os dados sorteados
    printf("\n==== BATALHA =====\n");
    printf("Atacante (%s) rolou: %d\n", t[atk].nome, dadoAtk);
    printf("Defensor (%s) rolou: %d\n", t[def].nome, dadoDef);

    // Verifica o resultado da batalha
    // Empate favorece o atacante
    if (dadoAtk >= dadoDef) {

        // Defensor perde uma tropa
        t[def].tropas--;
        printf("Atacante venceu! Defensor perde 1 tropa.\n");

        // Se o defensor ficar sem tropas, o território é conquistado
        if (t[def].tropas <= 0) {
            printf("Território conquistado!\n");

            // A cor do território passa a ser a do atacante
            strcpy(t[def].cor, t[atk].cor);

            // Território conquistado inicia com 1 tropa
            t[def].tropas = 1;
        }

    } else {
        // Caso o defensor vença
        printf("Defensor resistiu ao ataque.\n");
    }
}

int main() {

    // Ponteiro para armazenar os territórios alocados dinamicamente
    Territorio *territorios;

    // Alocação dinâmica de memória para 5 territórios
    territorios = (Territorio *) calloc(QTD_TERRITORIOS, sizeof(Territorio));

    // Verificação de erro na alocação
    if (territorios == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    // Cadastro dos territórios 
    for (int i = 0; i < QTD_TERRITORIOS; i++) {

        printf("\nCadastro do Território %d\n", i + 1);

        // Leitura do nome do território
        printf("Nome: ");
        fgets(territorios[i].nome, TAM, stdin);

        // Leitura da cor do exército
        printf("Cor do Exército: ");
        fgets(territorios[i].cor, TAM, stdin);

        // Leitura da quantidade de tropas
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        // Limpa o buffer do teclado para evitar problemas com fgets
        getchar();
    }

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Exibe o mapa inicial
    exibirMapa(territorios);

    /* Loop principal da fase de batalhas */
    int atacante, defensor;
    char continuar;

    do {
        // Usuário escolhe o território atacante
        printf("Escolha o território ATACANTE (1 a 5): ");
        scanf("%d", &atacante);

        // Usuário escolhe o território defensor
        printf("Escolha o território DEFENSOR (1 a 5): ");
        scanf("%d", &defensor);

        // Limpa o buffer
        getchar();

        // Verifica se a escolha é válida
        if (atacante >= 1 && atacante <= 5 &&
            defensor >= 1 && defensor <= 5 &&
            atacante != defensor) {

            // Executa a batalha
            atacar(territorios, atacante - 1, defensor - 1);

        } else {
            printf("❌ Escolha inválida.\n");
        }

        // Exibe o mapa após a batalha
        exibirMapa(territorios);

        // Pergunta se o jogador deseja continuar
        printf("Deseja continuar atacando? (s/n): ");
        scanf("%c", &continuar);
        getchar();

    } while (continuar == 's' || continuar == 'S');

    // Libera a memória alocada dinamicamente
    free(territorios);
    printf("Memória liberada. Fim do jogo.\n");

    return 0; 
}
    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

// --- Implementação de funções auxiliares ---

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

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

// --- Implementação de funções auxiliares ---

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
