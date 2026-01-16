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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIO 5
#define TOTAL_MISSOES 100
#define TAM_STRING 100

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
// Tipo para representar um território
typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territorio;
// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Limpa o buffer de entrada até o fim da linha (usada após scanf)
void limparBufferEntrada(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
// Função responsável por exibir o estado atual do mapa 
void exibirMapa(Territorio *t)

// Protótipos (mínimos para este exemplo)
void listarTerritorios(const Territorio mapa[], int qtd);
void cadastrarTerritorio(Territorio mapa[], int *pQtd);

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main(void) {
    Territorio mapa[MAX_TERRITORIO];
    int qtd = 0;
    int opcao;

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    do {
        printf("===========================\n");
        printf("   MENU - CADASTRO DE TERRITÓRIOS\n");
        printf("===========================\n");
        printf("1 - Cadastrar território\n");
        printf("2 - Listar territórios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            opcao = -1;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarTerritorio(mapa, &qtd);
                break;
            case 2:
                listarTerritorios(mapa, qtd);
                break;
            case 0:
                printf("Saindo do sistema\n");
                break;
            default:
                printf("OPÇÃO INVÁLIDA!\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (opcao != 0);

  
    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.
    /* Função que simula uma batalha entre dois territórios */
void atacar(Territorio *t, int atk, int def) {

    // Gera valores aleatórios entre 1 e 6 para ataque e defesa
    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    // Exibe os dados sorteados
    printf("\n⚔️ BATALHA ⚔️\n");
    printf("Atacante (%s) rolou: %d\n", t[atk].nome, dadoAtk);
    printf("Defensor (%s) rolou: %d\n", t[def].nome, dadoDef);

    // Verifica o resultado da batalha
    // Empate favorece o atacante
    if (dadoAtk >= dadoDef) {

        // Defensor perde uma tropa
        t[def].tropas--;
        printf("➡️ Atacante venceu! Defensor perde 1 tropa.\n");

        // Se o defensor ficar sem tropas, o território é conquistado
        if (t[def].tropas <= 0) {
            printf("🏳️ Território conquistado!\n");

            // A cor do território passa a ser a do atacante
            strcpy(t[def].cor, t[atk].cor);

            // Território conquistado inicia com 1 tropa
            t[def].tropas = 1;
        }

    } else {
        // Caso o defensor vença
        printf("🛡️ Defensor resistiu ao ataque.\n");
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

    /* Cadastro dos territórios */
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
