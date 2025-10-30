#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ======================= DEFINIÇÕES ==========================
#define MAX 5

typedef struct {
    char nome[5];
    int id;
} pecas;

typedef struct {
    pecas itens[MAX];
    int inicio;
    int fim;
    int total;
} fila;

// ======================= PROTÓTIPOS ==========================
void iniciarFila(fila *f);
int filaCheia(fila *f);
int filaVazia(fila *f);
void inserir(fila *f, pecas p);
void remover(fila *f, pecas *p);
void exibir(fila *f);
pecas gerarPecaAleatoria(int idBase);

// ======================= FUNÇÃO PRINCIPAL ====================
int main() {
    fila f;
    iniciarFila(&f);
    srand(time(NULL));

    int contadorID = 1; // IDs automáticos
    int opcao;
    pecas jogada;

    // Inicializa com 5 peças
    for (int i = 0; i < MAX; i++) {
        inserir(&f, gerarPecaAleatoria(contadorID++));
    }

    do {
        printf("==== TETRIS STACK ====\n");
        exibir(&f);
        printf("1 - Jogar peça\n");
        printf("2 - Inserir manualmente\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Jogar peça
                if (filaVazia(&f)) {
                    printf("A fila está vazia!\n");
                } else {
                    remover(&f, &jogada);
                    printf("Peça jogada: [%s, %d]\n", jogada.nome, jogada.id);

                    // Adiciona nova peça automaticamente
                    inserir(&f, gerarPecaAleatoria(contadorID++));
                }
                break;

            case 2: // Inserir manualmente
                if (filaCheia(&f)) {
                    printf("Fila cheia! Não é possível inserir.\n");
                } else {
                    pecas nova;
                    printf("Digite o nome da peça (I, O, T, L): ");
                    scanf("%s", nova.nome);
                    nova.id = contadorID++;
                    inserir(&f, nova);
                    printf("Peça adicionada!\n");
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}

// ======================= FUNÇÕES AUXILIARES ==================

void iniciarFila(fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(fila *f) {
    return f->total == MAX;
}

int filaVazia(fila *f) {
    return f->total == 0;
}

void inserir(fila *f, pecas p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(fila *f, pecas *p) {
    if (filaVazia(f)) {
        printf("A fila está vazia! Não é possível remover.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void exibir(fila *f) {
    printf("\nFila de peças (%d/%d): ", f->total, MAX);
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf(" [%s,%d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n\n");
}

pecas gerarPecaAleatoria(int idBase) {
    pecas nova;
    char tipos[4][5] = {"I", "O", "T", "L"};
    strcpy(nova.nome, tipos[rand() % 4]);
    nova.id = idBase;
    return nova;
}
