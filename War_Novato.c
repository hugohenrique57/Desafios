// Desafio novato, tentativa de reproduzir o jogo "War"

//-----------------------------------------------------

//bibliotecas
#include <stdio.h>
#include <string.h>



//estrutura  
struct territorios
{
    char nome[30];
    char cor[10];
    int tropas;
};

int main(){
    int Escolha;
    int TotalPaises;
    
    printf("---Bem Vindo ao jogo war---\n");
    printf("Escolha uma das Opcoes abaixo\n");
    printf("(1) JOGAR\n");
    printf("(2) Regras!\n");
    printf("(3) SAIR!...\n");
    scanf("%d" , &Escolha);
   
    switch (Escolha)
    {
    case 1:
        printf("Vamos cadastrar os 5 territorios inicias do nosso mundo.\n");
        printf("--------------------------------------------------------");
        for ( int i = 0; i < 5; i++)
        {
        struct territorios paises; 
            printf("Digite o nome:");
            scanf("%s", &paises.nome);

            printf("\n");

            printf("Digite a Cor:");
            scanf("%s" , &paises.cor);

            printf("\n");

            printf("Digite o numero de tropas:");
            scanf("%d", &paises.tropas);
        
        }
        
        for (int i = 0; i < 5; i++)
        {
            printf("paise %d \n", i+1);
            printf("")
            printf("")
            printf("")
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