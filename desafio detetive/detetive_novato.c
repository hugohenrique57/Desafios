#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct que representa uma sala da mansão (nó da árvore binária)
typedef struct sala {
    char nome[50];              // Nome da sala
    struct sala *esquerda;      // Caminho para a esquerda
    struct sala *direita;       // Caminho para a direita
} Sala;

/*
 * Função: criarSala
 * Objetivo: alocar dinamicamente uma sala e definir seu nome.
 */
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/*
 * Função: explorarSalas
 * Objetivo: permite que o jogador explore a mansão, caminhando pela árvore.
 */
void explorarSalas(Sala *atual) {
    char opcao;

    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Verifica se é um nó folha (sem caminhos)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Não há mais caminhos. Fim da exploração!\n");
            return;
        }

        printf("Para onde deseja ir?\n");
        if (atual->esquerda != NULL) printf(" (e) Ir para a ESQUERDA -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf(" (d) Ir para a DIREITA  -> %s\n", atual->direita->nome);
        printf(" (s) Sair do jogo\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'e' || opcao == 'E') {
            if (atual->esquerda != NULL) atual = atual->esquerda;
            else printf("Não há sala à esquerda!\n");
        } 
        else if (opcao == 'd' || opcao == 'D') {
            if (atual->direita != NULL) atual = atual->direita;
            else printf("Não há sala à direita!\n");
        }
        else if (opcao == 's' || opcao == 'S') {
            printf("\nExploração encerrada pelo jogador.\n");
            return;
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

/*
 * Função: main
 * Objetivo: monta a árvore da mansão e inicia a exploração.
 */
int main() {
    // Criando salas (manual, pois o mapa é fixo)
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *jardim = criarSala("Jardim");
    Sala *biblioteca = criarSala("Biblioteca");

    // Montando o mapa (árvore binária)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = jardim;
    salaEstar->direita = biblioteca;
    // cozinha e as demais folhas não possuem filhos

    printf("=== EXPLORADOR DA MANSÃO ===\n");
    explorarSalas(hall);

    printf("\nObrigado por jogar!\n");
    return 0;
}
