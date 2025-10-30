#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// ======== STRUCTS ========

// Peça do Tetris
typedef struct {
    char nome[5];
    int id;
} pecas;

// Fila de peças
typedef struct {
    pecas itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} fila;

// Pilha de peças reservadas
typedef struct {
    pecas itens[MAX_PILHA];
    int topo;
} pilha;

// ======== PROTÓTIPOS ========
void iniciarFila(fila *f);
void iniciarPilha(pilha *p);
int filaCheia(fila *f);
int filaVazia(fila *f);
int pilhaCheia(pilha *p);
int pilhaVazia(pilha *p);

void enfileirar(fila *f, pecas p);
pecas desenfileirar(fila *f);
void mostrarFila(fila *f);

void push(pilha *p, pecas peca);
pecas pop(pilha *p);
pecas topoPilha(pilha *p);
void mostrarPilha(pilha *p);

void gerarPeca(pecas *p);
void preencherFila(fila *f);

void jogarPeca(fila *f);
void reservarPeca(fila *f, pilha *p);
void usarPecaReservada(pilha *p);
void trocarPecaAtual(fila *f, pilha *p);
void trocaMultipla(fila *f, pilha *p);

// ======== MAIN ========
int main() {
    srand(time(NULL));

    fila f;
    pilha p;
    iniciarFila(&f);
    iniciarPilha(&p);

    // Preenche a fila inicialmente com 5 peças
    preencherFila(&f);

    int opcao;

    do {
        printf("\n==== Tetris Stack ====\n");
        mostrarFila(&f);
        mostrarPilha(&p);
        printf("\n=== MENU ===\n");
        printf("1 - Jogar Peça\n");
        printf("2 - Reservar Peça\n");
        printf("3 - Usar Peça Reservada\n");
        printf("4 - Trocar Peça Atual\n");
        printf("5 - Troca Múltipla\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: jogarPeca(&f); break;
            case 2: reservarPeca(&f, &p); break;
            case 3: usarPecaReservada(&p); break;
            case 4: trocarPecaAtual(&f, &p); break;
            case 5: trocaMultipla(&f, &p); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ======== FUNÇÕES ========

// Inicializa fila e pilha
void iniciarFila(fila *f) {
    f->inicio = f->fim = f->total = 0;
}
void iniciarPilha(pilha *p) {
    p->topo = -1;
}

// Verificações
int filaCheia(fila *f) { return f->total == MAX_FILA; }
int filaVazia(fila *f) { return f->total == 0; }
int pilhaCheia(pilha *p) { return p->topo == MAX_PILHA - 1; }
int pilhaVazia(pilha *p) { return p->topo == -1; }

// Fila
void enfileirar(fila *f, pecas p) {
    if (filaCheia(f)) return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

pecas desenfileirar(fila *f) {
    pecas p = {" ", -1};
    if (filaVazia(f)) return p;
    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    return p;
}

void mostrarFila(fila *f) {
    printf("\nFila: ");
    if (filaVazia(f)) { printf("[vazia]"); return; }

    int i = f->inicio;
    for (int c = 0; c < f->total; c++) {
        printf("{%s, %d} ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % MAX_FILA;
    }
}

// Pilha
void push(pilha *p, pecas peca) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Não é possível reservar mais.\n");
        return;
    }
    p->itens[++p->topo] = peca;
}

pecas pop(pilha *p) {
    pecas peca = {" ", -1};
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return peca;
    }
    return p->itens[p->topo--];
}

pecas topoPilha(pilha *p) {
    pecas peca = {" ", -1};
    if (!pilhaVazia(p)) peca = p->itens[p->topo];
    return peca;
}

void mostrarPilha(pilha *p) {
    printf("\nPilha: ");
    if (pilhaVazia(p)) { printf("[vazia]"); return; }

    for (int i = p->topo; i >= 0; i--) {
        printf("{%s, %d} ", p->itens[i].nome, p->itens[i].id);
    }
}

// Gera peças automáticas
void gerarPeca(pecas *p) {
    static int proximoID = 1;
    char tipos[4] = {'I', 'O', 'L', 'T'};
    int idx = rand() % 4;
    p->nome[0] = tipos[idx];
    p->nome[1] = '\0';
    p->id = proximoID++;
}

void preencherFila(fila *f) {
    while (!filaCheia(f)) {
        pecas nova;
        gerarPeca(&nova);
        enfileirar(f, nova);
    }
}

// ======== AÇÕES DO JOGO ========

void jogarPeca(fila *f) {
    if (filaVazia(f)) { printf("Fila vazia!\n"); return; }
    pecas jogada = desenfileirar(f);
    printf("Jogando peça: {%s, %d}\n", jogada.nome, jogada.id);
    gerarPeca(&jogada);
    enfileirar(f, jogada);
}

void reservarPeca(fila *f, pilha *p) {
    if (filaVazia(f)) { printf("Fila vazia!\n"); return; }
    if (pilhaCheia(p)) { printf("Pilha cheia! Não é possível reservar.\n"); return; }

    pecas reservada = desenfileirar(f);
    push(p, reservada);
    printf("Peça {%s, %d} movida para reserva!\n", reservada.nome, reservada.id);

    // Gera nova peça na fila
    pecas nova;
    gerarPeca(&nova);
    enfileirar(f, nova);
}

void usarPecaReservada(pilha *p) {
    if (pilhaVazia(p)) { printf("Pilha vazia!\n"); return; }
    pecas usada = pop(p);
    printf("Usando peça reservada: {%s, %d}\n", usada.nome, usada.id);
}

void trocarPecaAtual(fila *f, pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Impossível trocar — fila ou pilha vazia!\n");
        return;
    }

    pecas topo = topoPilha(p);
    p->itens[p->topo] = f->itens[f->inicio];
    f->itens[f->inicio] = topo;
    printf("Peça atual trocada com o topo da pilha!\n");
}

void trocaMultipla(fila *f, pilha *p) {
    if (f->total < 3 || p->topo < 2) {
        printf("É necessário ter ao menos 3 peças em cada estrutura!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (f->inicio + i) % MAX_FILA;
        int idxPilha = p->topo - i;
        pecas temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[idxPilha];
        p->itens[idxPilha] = temp;
    }

    printf("Troca múltipla realizada!\n");
}
