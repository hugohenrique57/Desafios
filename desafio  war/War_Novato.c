// Desafio novato, tentativa de reproduzir o jogo "War"

//-----------------------------------------------------

//bibliotecas
#include <stdio.h>
#include <string.h>

#define TamMAX 2

//estrutura  
struct territorios{
    char nome[30];
    char cor[10];
    int tropas;
};

int main(){
    int Escolha;
    // menu
    printf("---Bem Vindo ao jogo war---\n");
    printf("Escolha uma das Opcoes abaixo\n");
    printf("(1) JOGAR\n");
    printf("(2) Regras!\n");
    printf("(3) SAIR!...\n");
    scanf("%d" , &Escolha);
   
    switch (Escolha)
    {
    case 1:
    struct territorios times[TamMAX];//cria o vetor paises

        // estrutura para cadastro
        printf("Vamos cadastrar os 5 territorios inicias do nosso mundo.\n");
        printf("\n--------------------------------------------------------\n");
        for ( int i = 0; i < TamMAX; i++)
        {
            printf("Digite o nome: ");
            scanf("%s", &times[i].nome);

            printf("\n");

            printf("Digite a Cor do exercito: ");
            scanf("%s" , &times[i].cor);

            printf("\n");

            printf("Digite o numero de tropas: ");
            scanf("%d", &times[i].tropas);
            
            printf("\n--------------------------------------------------------\n");
        
        }
        // estrtura para printar no terminal
        for (int i = 0; i < TamMAX; i++)
        {
            printf("TERRITORIO %d: \n", i+1);
            printf("  - Nome: %s \n",times[i].nome);
            printf("  - Cor do exercito: %s \n",times[i].cor );
            printf("  - Tropas %d \n",times[i].tropas );
            printf("\n--------------------------------------------------------\n");
        }
        
        break;
    case 2:
        printf("...\n");
        break;
    case 3: 
        printf("Saindo...\n");
    break;
    default:
        printf("Opcao Invalida!\n");
        break;
    }


    return 0;
}