#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

// ======== STRUCTS ========

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

typedef struct {
    pecas itens[MAX];
    int topo;
} pilha;

// ======== PROTÓTIPOS ========
void iniciarFila(fila *f);
int filaCheia(fila *f);
int filaVazia(fila *f);
void enfileirar(fila *f, pecas p);
pecas desenfileirar(fila *f);
void mostrarFila(fila *f);

void iniciarPilha(pilha *p);
int pilhaCheia(pilha *p);
int pilhaVazia(pilha *p);
void empilhar(pilha *p, pecas val);
pecas desempilhar(pilha *p);
void mostrarPilha(pilha *p);

void gerarPeca(pecas *p);

// ======== FUNÇÃO PRINCIPAL ========
int main() {
    fila f;
    pilha reserva;

    iniciarFila(&f);
    iniciarPilha(&reserva);
    srand(time(NULL));

    // inicia com 5 peças automáticas na fila
    for (int i = 0; i < MAX; i++) {
        pecas nova;
        gerarPeca(&nova);
        enfileirar(&f, nova);
    }

    int opcao;
    do {
        printf("\n==== Tetris Stack ====\n");
        printf("Fila: ");
        mostrarFila(&f);
        printf("Pilha reserva: ");
        mostrarPilha(&reserva);

        printf("=== MENU ===\n");
        printf("(1) Jogar peça da fila\n");
        printf("(2) Mover peça da fila para pilha reserva\n");
        printf("(3) Jogar peça da pilha reserva\n");
        printf("(4) Inserir peça manualmente na fila\n");
        printf("(0) Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&f)) {
                    pecas jogada = desenfileirar(&f);
                    printf("\nPeça escolhida da fila: {%s, %d}\n", jogada.nome, jogada.id);

                    // adiciona nova peça automaticamente
                    pecas nova;
                    gerarPeca(&nova);
                    enfileirar(&f, nova);
                    printf("Nova peça adicionada automaticamente à fila!\n");
                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 2:
                if (!filaVazia(&f) && !pilhaCheia(&reserva)) {
                    pecas p = desenfileirar(&f);
                    empilhar(&reserva, p);
                    printf("Peça {%s,%d} movida para a pilha reserva.\n", p.nome, p.id);
                } else if (filaVazia(&f)) {
                    printf("Fila vazia!\n");
                } else {
                    printf("Pilha reserva cheia!\n");
                }
                break;

            case 3:
                if (!pilhaVazia(&reserva)) {
                    pecas p = desempilhar(&reserva);
                    printf("Peça jogada da pilha reserva: {%s, %d}\n", p.nome, p.id);

                    // adiciona nova peça automaticamente na fila
                    pecas nova;
                    gerarPeca(&nova);
                    enfileirar(&f, nova);
                    printf("Nova peça adicionada automaticamente à fila!\n");
                } else {
                    printf("Pilha reserva vazia!\n");
                }
                break;

            case 4: {
                if (!filaCheia(&f)) {
                    pecas nova;
                    gerarPeca(&nova);
                    enfileirar(&f, nova);
                    printf("Peça adicionada manualmente à fila: {%s, %d}\n", nova.nome, nova.id);
                } else {
                    printf("Fila cheia! Não é possível adicionar mais peças.\n");
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ======== FUNÇÕES FILA ========
void iniciarFila(fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(fila *f) { return (f->total == MAX); }
int filaVazia(fila *f) { return (f->total == 0); }

void enfileirar(fila *f, pecas p) {
    if (filaCheia(f)) return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

pecas desenfileirar(fila *f) {
    pecas p;
    p.nome[0] = '\0';
    p.id = -1;
    if (filaVazia(f)) return p;

    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return p;
}

void mostrarFila(fila *f) {
    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }
    int i = f->inicio;
    for (int count = 0; count < f->total; count++) {
        printf("{%s, %d} ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// ======== FUNÇÕES PILHA ========
void iniciarPilha(pilha *p) { p->topo = -1; }
int pilhaCheia(pilha *p) { return (p->topo == MAX - 1); }
int pilhaVazia(pilha *p) { return (p->topo == -1); }

void empilhar(pilha *p, pecas val) {
    if (pilhaCheia(p)) return;
    p->itens[++p->topo] = val;
}

pecas desempilhar(pilha *p) {
    pecas peca;
    peca.nome[0] = '\0';
    peca.id = -1;
    if (pilhaVazia(p)) return peca;
    return p->itens[p->topo--];
}

void mostrarPilha(pilha *p) {
    if (pilhaVazia(p)) {
        printf("[vazia]\n");
        return;
    }
    for (int i = 0; i <= p->topo; i++) {
        printf("{%s, %d} ", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n");
}

// ======== FUNÇÃO GERAR PEÇA ========
void gerarPeca(pecas *p) {
    static int proximoID = 1;
    char tipos[4] = {'I', 'O', 'L', 'T'};
    int idx = rand() % 4;
    p->nome[0] = tipos[idx];
    p->nome[1] = '\0';
    p->id = proximoID++;
}
