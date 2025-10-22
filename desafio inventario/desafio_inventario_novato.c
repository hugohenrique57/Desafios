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
        printf("(0) Sair\n");
        printf("--------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o \n do buffer

        switch (opcao) {

            // Adicionar item
            case 1:
                if (contador >= QTD_MAX) {
                    printf("Inventário cheio!\n");
                } else {
                    inventario = realloc(inventario, (contador + 1) * sizeof(struct item));

                    printf("Digite o nome do item: ");
                    fgets(inventario[contador].nome, TAM_NOME, stdin);
                    inventario[contador].nome[strcspn(inventario[contador].nome, "\n")] = 0;

                    printf("Digite o tipo do item (ex: cura, arma, munição...): ");
                    fgets(inventario[contador].tipo, TAM_TIPO, stdin);
                    inventario[contador].tipo[strcspn(inventario[contador].tipo, "\n")] = 0;

                    printf("Digite a quantidade: ");
                    scanf("%d", &inventario[contador].quantidade);
                    getchar();
                    //conta a quantidade de itens e serve como indice 
                    contador++;
                    printf("Item adicionado com sucesso!\n");
                }
                break;

            // Remover item 
            case 2:
                if (contador == 0) {
                    printf("Nenhum item para remover.\n");
                } else {
                    char nomeBusca[TAM_NOME];
                    int encontrado = -1;

                    printf("Digite o nome do item a remover: ");
                    fgets(nomeBusca, TAM_NOME, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // remove o \n

                    // Busca pelo nome
                    for (int i = 0; i < contador; i++) {
                        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
                            encontrado = i;
                            break;
                        }
                    }

                    if (encontrado != -1) {
                        // reorganiza os itens no vetor
                        for (int i = encontrado; i < contador - 1; i++) {
                            inventario[i] = inventario[i + 1];
                        }
                        contador--;
                        inventario = realloc(inventario, contador * sizeof(struct item));
                        printf("Item '%s' removido com sucesso!\n", nomeBusca);
                    } else {
                        printf("Item '%s' não encontrado no inventário.\n", nomeBusca);
                    }
                }
                break;

            // Listar itens
            case 3:
                if (contador == 0) {
                    printf("Inventário vazio.\n");
                } else {
                    printf("\n--- LISTA DE ITENS ---\n");
                    for (int i = 0; i < contador; i++) {
                        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
                               i, inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
                    }
                }
                break;

            // Sair
            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida, tente novamente.\n");
        }

    } while (opcao != 0);

    free(inventario);
    return 0;
}