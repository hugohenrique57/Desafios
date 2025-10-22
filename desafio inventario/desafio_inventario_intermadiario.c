#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 30
#define TAM_TIPO 20
#define QTD_MAX 10 // limite máximo de itens

// Estrutura de um item
struct item {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
};

// ====== PROTÓTIPOS DAS FUNÇÕES ======
void adicionarItem(struct item **inventario, int *contador);
void removerItem(struct item **inventario, int *contador);
void listarItens(struct item *inventario, int contador);
void buscarItem(struct item *inventario, int contador);


// ====== FUNÇÃO PRINCIPAL ======
int main() {
    struct item* inventario = NULL;
    int contador = 0;
    int opcao;

    do {
        printf("\n======= INVENTÁRIO =======\n");
        printf("Espaço usado: %d/%d\n", contador, QTD_MAX);
        printf("--------------------------\n");
        printf("(1) Adicionar item\n");
        printf("(2) Remover item (por nome)\n");
        printf("(3) Listar itens\n");
        printf("(4) Buscar item (por nome)\n");
        printf("(0) Sair\n");
        printf("--------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o \n do buffer

        switch (opcao) {
            case 1:
                adicionarItem(&inventario, &contador);
                break;
            case 2:
                removerItem(&inventario, &contador);
                break;
            case 3:
                listarItens(inventario, contador);
                break;
            case 4:
                buscarItem(inventario, contador);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    free(inventario);
    return 0;
}


// ====== IMPLEMENTAÇÃO DAS FUNÇÕES ======

// Adicionar item
void adicionarItem(struct item **inventario, int *contador) {
    if (*contador >= QTD_MAX) {
        printf("Inventário cheio!\n");
        return;
    }

    *inventario = realloc(*inventario, (*contador + 1) * sizeof(struct item));

    printf("Digite o nome do item: ");
    fgets((*inventario)[*contador].nome, TAM_NOME, stdin);
    (*inventario)[*contador].nome[strcspn((*inventario)[*contador].nome, "\n")] = 0;

    printf("Digite o tipo do item (ex: cura, arma, munição...): ");
    fgets((*inventario)[*contador].tipo, TAM_TIPO, stdin);
    (*inventario)[*contador].tipo[strcspn((*inventario)[*contador].tipo, "\n")] = 0;

    printf("Digite a quantidade: ");
    scanf("%d", &(*inventario)[*contador].quantidade);
    getchar();

    (*contador)++;
    printf("Item adicionado com sucesso!\n");
}


// Remover item
void removerItem(struct item **inventario, int *contador) {
    if (*contador == 0) {
        printf("Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    int encontrado = -1;

    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < *contador; i++) {
        if (strcmp((*inventario)[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int i = encontrado; i < *contador - 1; i++) {
            (*inventario)[i] = (*inventario)[i + 1];
        }
        (*contador)--;
        *inventario = realloc(*inventario, (*contador) * sizeof(struct item));
        printf("Item '%s' removido com sucesso!\n", nomeBusca);
    } else {
        printf("Item '%s' não encontrado.\n", nomeBusca);
    }
}


// Listar itens
void listarItens(struct item *inventario, int contador) {
    if (contador == 0) {
        printf("Inventário vazio.\n");
        return;
    }

    printf("\n--- LISTA DE ITENS ---\n");
    for (int i = 0; i < contador; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i, inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
}


// Buscar item
void buscarItem(struct item *inventario, int contador) {
    if (contador == 0) {
        printf("Nenhum item no inventário para buscar!\n");
        return;
    }

    char ITEM_BUSCA[TAM_NOME];
    int encontrado = -1;

    printf("--- BUSCAR ITEM POR NOME ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    fgets(ITEM_BUSCA, TAM_NOME, stdin);
    ITEM_BUSCA[strcspn(ITEM_BUSCA, "\n")] = 0;

    for (int i = 0; i < contador; i++) {
        if (strcmp(inventario[i].nome, ITEM_BUSCA) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        printf("Item encontrado!\n");
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               inventario[encontrado].nome,
               inventario[encontrado].tipo,
               inventario[encontrado].quantidade);
    } else {
        printf("Item '%s' não encontrado.\n", ITEM_BUSCA);
    }
}
