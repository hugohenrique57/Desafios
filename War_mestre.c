// Desafio WAR mestre

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 3
#define TOTAL_MISSOES 5

// --- ESTRUTURA ---
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
Territorio* cadastrarTerritorios(int qtd);
void exibirMapa(Territorio *mapa, int qtd);
void atacar(Territorio *atk, Territorio *def);
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
void exibirMissao(char *missao);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void verificarAndamentoMissao(char *missao, Territorio *mapa, int tamanho);
void liberarMemoria(Territorio *mapa, char *missao1, char *missao2);
void menuPrincipal(Territorio *mapa, int qtd, char *missao1, char *missao2);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    srand(time(NULL));

    // Criação do mapa e das missões
    Territorio *mapa = cadastrarTerritorios(MAX_TERRITORIOS);

    // Criação do vetor de missões disponíveis
    char *missoes[TOTAL_MISSOES] = {
        "Ter todos os territórios da mesma cor",
        "Ter pelo menos 10 tropas no total",
        "Conquistar um território azul",
        "Eliminar tropas vermelhas",
        "Ter mais de 3 territórios com 2 ou mais tropas"
    };

    // Aloca dinamicamente as missões de cada jogador
    char *missaoJog1 = (char*) malloc(100 * sizeof(char));
    char *missaoJog2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJog1, missoes, TOTAL_MISSOES);
    atribuirMissao(missaoJog2, missoes, TOTAL_MISSOES);

    printf("\n Missão do Jogador 1: ");
    exibirMissao(missaoJog1);
    printf(" Missão do Jogador 2: ");
    exibirMissao(missaoJog2);

    // Chama o menu principal (toda a interação do jogo)
    menuPrincipal(mapa, MAX_TERRITORIOS, missaoJog1, missaoJog2);

    // Libera a memória alocada
    liberarMemoria(mapa, missaoJog1, missaoJog2);
    return 0;
}

// --- FUNÇÃO: CADASTRAR TERRITÓRIOS ---
Territorio* cadastrarTerritorios(int qtd) {
    Territorio *mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    printf("\n--- CADASTRO DE TERRITÓRIOS ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("Nome do território %d: ", i + 1);
        scanf("%s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("------------------------------\n");
    }
    return mapa;
}

// --- FUNÇÃO: EXIBIR MAPA ---
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n--- LISTA DE TERRITÓRIOS ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("------------------------------\n");
}

// --- FUNÇÃO: SIMULAR ATAQUE ---
void atacar(Territorio *atk, Territorio *def) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n  Ataque de %s (%s) contra %s (%s)\n", atk->nome, atk->cor, def->nome, def->cor);
    printf(" Dado Atacante: %d |  Dado Defensor: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf(" O atacante venceu!\n");
        strcpy(def->cor, atk->cor);
        def->tropas = atk->tropas / 2;
    } else {
        printf(" O atacante perdeu!\n");
        atk->tropas--;
        if (atk->tropas < 0) atk->tropas = 0;
    }
}

// --- FUNÇÃO: ATRIBUI MISSÃO ALEATÓRIA ---
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// --- FUNÇÃO: EXIBE MISSÃO DO JOGADOR ---
void exibirMissao(char *missao) {
    printf("%s\n", missao);
}

// --- FUNÇÃO: VERIFICA SE MISSÃO FOI CUMPRIDA ---
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    // Missão 1: todos do mesmo exército
    if (strcmp(missao, "Ter todos os territórios da mesma cor") == 0) {
        for (int i = 1; i < tamanho; i++)
            if (strcmp(mapa[i].cor, mapa[0].cor) != 0) return 0;
        return 1;
    }

    // Missão 2: soma total >= 10 tropas
    if (strcmp(missao, "Ter pelo menos 10 tropas no total") == 0) {
        int soma = 0;
        for (int i = 0; i < tamanho; i++) soma += mapa[i].tropas;
        return (soma >= 10);
    }

    // Missão 3: possuir território azul
    if (strcmp(missao, "Conquistar um território azul") == 0) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "azul") == 0) return 1;
        return 0;
    }

    // Missão 4: eliminar tropas vermelhas
    if (strcmp(missao, "Eliminar tropas vermelhas") == 0) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "vermelha") == 0) return 0;
        return 1;
    }

    // Missão 5: ter pelo menos 3 territórios com 2+ tropas
    if (strcmp(missao, "Ter mais de 3 territórios com 2 ou mais tropas") == 0) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++)
            if (mapa[i].tropas >= 2) cont++;
        return (cont >= 3);
    }

    return 0;
}

// --- NOVA FUNÇÃO: MOSTRA ANDAMENTO DA MISSÃO ---
void verificarAndamentoMissao(char *missao, Territorio *mapa, int tamanho) {
    printf("\n Andamento da missão: ");

    if (strcmp(missao, "Ter todos os territórios da mesma cor") == 0) {
        int iguais = 1;
        for (int i = 1; i < tamanho; i++)
            if (strcmp(mapa[i].cor, mapa[0].cor) != 0) iguais = 0;
        printf("%s\n", iguais ? "Quase lá! A maioria é da mesma cor." : "Ainda há territórios de outras cores.");
    }

    else if (strcmp(missao, "Ter pelo menos 10 tropas no total") == 0) {
        int soma = 0;
        for (int i = 0; i < tamanho; i++) soma += mapa[i].tropas;
        printf("Atualmente possui %d tropas (precisa de 10).\n", soma);
    }

    else if (strcmp(missao, "Conquistar um território azul") == 0) {
        int achou = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "azul") == 0) achou = 1;
        printf("%s\n", achou ? "Você já possui um território azul!" : "Ainda não conquistou nenhum azul.");
    }

    else if (strcmp(missao, "Eliminar tropas vermelhas") == 0) {
        int vermelhos = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "vermelha") == 0) vermelhos++;
        printf("Restam %d territórios vermelhos no mapa.\n", vermelhos);
    }

    else if (strcmp(missao, "Ter mais de 3 territórios com 2 ou mais tropas") == 0) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++)
            if (mapa[i].tropas >= 2) cont++;
        printf("Você tem %d territórios com 2+ tropas (precisa de 3).\n", cont);
    }
}

// --- FUNÇÃO: MENU PRINCIPAL ---
void menuPrincipal(Territorio *mapa, int qtd, char *missao1, char *missao2) {
    int opcao, iAtk, iDef;

    do {
        printf("\n========= MENU =========\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Simular ataque\n");
        printf("3 - Ver andamento da missão\n");
        printf("4 - Sair\n");
        printf("========================\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMapa(mapa, qtd);
                break;

            case 2:
                exibirMapa(mapa, qtd);
                printf("\nEscolha o atacante: ");
                scanf("%d", &iAtk);
                printf("Escolha o defensor: ");
                scanf("%d", &iDef);

                if (iAtk == iDef) { printf(" Não pode atacar a si mesmo!\n"); break; }
                if (strcmp(mapa[iAtk-1].cor, mapa[iDef-1].cor) == 0) { printf(" Mesma cor!\n"); break; }

                atacar(&mapa[iAtk-1], &mapa[iDef-1]);

                // Verifica vitória automática
                if (verificarMissao(missao1, mapa, qtd)) { printf("\n Jogador 1 venceu!\n"); opcao = 4; }
                if (verificarMissao(missao2, mapa, qtd)) { printf("\n Jogador 2 venceu!\n"); opcao = 4; }
                break;

            case 3:
                verificarAndamentoMissao(missao1, mapa, qtd);
                verificarAndamentoMissao(missao2, mapa, qtd);
                break;

            case 4:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 4);
}

// --- FUNÇÃO: LIBERAR MEMÓRIA ---
void liberarMemoria(Territorio *mapa, char *missao1, char *missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
    printf("\nMemória liberada com sucesso.\n");
}
