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

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIO 5
#define TOTAL_MISSÕES 100
#define TAM_STRING 100

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct territorio{
    char nome [TAM_STRING];
    char cor [TAM_STRING];
    int tropas [TAM_STRING];
};
// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
void limparBufferEntrada(){
int c;
    while ((c =cgetchar())!= 'n' && c != EOF
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main(void) {
        struct territorio Territorio[MAX_TERRITORIO];
    int territorio = 0;
    int opcao;

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    do {
        printf("===========================\n");
        printf("   VAMOS CADASTRAR 5 TERRITÓRIOS INICIAIS DO NOSSO MUNDO!\n");
        printf("===========================\n");
        printf("------CADASTRANDO TERRITÓRIOS------\n");
        printf("Sair\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            opcao = -1;
        }
        limparBufferEntrada();
switch (opcao) {
            case 1:
                printf("--- Território 1 ---\n\n");
                if (territorio < MAX_TERRRITORIO) {
                    printf("Território: \n");
                    fgets(Territorio[territorio].nome, TAM_STRING, stdin);

                    printf("Cor do Exército: \n");
                    fgets(Territorio[territorio].cor, TAM_STRING, stdin);

                    printf("Número de Tropas: \n");
                    fgets(Territorio[territorio].tropa, TAM_STRING, stdin);

                    Territorio[territorio].nome[strcspn(Territorio[territorio].nome, "\n")] = '\0';
                    Territorio[territorio].cor[strcspn(Territorio[territorio].cor, "\n")] = '\0';
                    Territorio[territorio].tropa[strcspn(Territorio[territorio].tropa, "\n")] = '\0';

                    printf("Digite o número de tropas: ");
                    if (scanf("%d", &Territorio[territorio].tropa) != 1) {
                        Territorio[territorio].tropa = 0;
                    }
                    limparBufferEntrada();

                    territorio++;
                    printf("\nTerritótio cadastrado com sucesso!\n");
                } else {
                    printf("Não é possível cadastrar mais territórios.\n");
                }
                break;
        if (territorio =< 5) {
                    printf("Nenhum Território cadastrado\n");
                } else {
                    for (int i = 0; i < territorio; i++) {
                        printf("------------------------------------\n");
                        printf("Territorios %d\n", i + 1);
                        printf("Nome: %s\n", territorio[i].nome);
                        printf("cor: %s\n", territorio[i].cor);
                        printf("tropas: %s\n", territorio[i].tropa);
                       }
                }
                printf("------------------------------------\n");
                printf("Pressione ENTER para continuar\n");
                getchar();
                break;

            case 0:
                printf("Saindo do sistema\n");
                break;

            default:
                printf("OPÇÃO INVÁLIDA!\n");
                printf("Pressione ENTER para continuar\n");
                getchar();
                break;
        }
    } while (opcao != 0);

    return 0;
}
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
