
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura dos territórios
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
Territorio* cadastrarTerritorios(int *qtd);
void exibirTerritorios(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    srand(time(NULL)); // inicializa um numero aleatorio
    int qtdTerritorios;
    int escolha;
    Territorio *mapa = NULL;

    printf("--- BEM-VINDO AO JOGO WAR ESTRUTURADO ---\n\n");
    
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);

    // Alocação dinâmica de memória
    mapa = cadastrarTerritorios(&qtdTerritorios);

    do {
        printf("\n========= MENU =========\n");
        printf("(1) Exibir territórios\n");
        printf(" (2) Simular ataque\n");
        printf("(3) Sair\n");
        printf("========================\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                exibirTerritorios(mapa, qtdTerritorios);
                break;

            case 2: {
                int iAtk, iDef;
                exibirTerritorios(mapa, qtdTerritorios);

                printf("\nEscolha o número do território atacante: ");
                scanf("%d", &iAtk);
                printf("Escolha o número do território defensor: ");
                scanf("%d", &iDef);

                // Valida índices
                if (iAtk < 1 || iAtk > qtdTerritorios || iDef < 1 || iDef > qtdTerritorios) {
                    printf("Escolha inválida!\n");
                    break;
                }

                // Evita autoataque
                if (strcmp(mapa[iAtk-1].cor, mapa[iDef-1].cor) == 0) {
                    printf("Você não pode atacar um território da mesma cor!\n");
                    break;
                }

                atacar(&mapa[iAtk-1], &mapa[iDef-1]);
                break;
            }

            case 3:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (escolha != 3);

    liberarMemoria(mapa);
    return 0;
}

// --- FUNÇÃO PARA CADASTRAR TERRITÓRIOS ---
Territorio* cadastrarTerritorios(int *qtd) {
    Territorio *mapa = (Territorio*) calloc(*qtd, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    printf("\n--- Cadastro de Territórios ---\n");
    for (int i = 0; i < *qtd; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("---------------------------\n");
    }
    return mapa;
}

// --- FUNÇÃO PARA EXIBIR OS TERRITÓRIOS ---
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n--- LISTA DE TERRITÓRIOS ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("-------------------------------\n");
}

// --- FUNÇÃO DE ATAQUE ENTRE TERRITÓRIOS ---
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\nSimulando ataque de %s (%s) contra %s (%s)...\n", 
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtk = rand() % 6 + 1; // número de 1 a 6
    int dadoDef = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtk);
    printf("Dado do defensor: %d\n", dadoDef);

    if (dadoAtk > dadoDef) {
        printf("\nO atacante venceu a batalha!\n");

        // Atualiza dados: defensor muda de cor e perde metade das tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        printf("O território %s agora pertence ao exército %s!\n", defensor->nome, defensor->cor);
    } else {
        printf("\nO atacante perdeu a batalha!\n");
        atacante->tropas--;

        if (atacante->tropas < 0)
            atacante->tropas = 0;

        printf("%s perdeu uma tropa e agora possui %d tropas.\n", atacante->nome, atacante->tropas);
    }
}

// --- FUNÇÃO PARA LIBERAR MEMÓRIA ---
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso.\n");
}
