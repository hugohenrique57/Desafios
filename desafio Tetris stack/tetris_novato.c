#include <stdio.h>
#include <stdlib.h>

//struct para definir compontes das pecas
typedef struct {
    char nome[5];
    int id;
}pecas;

#define MAX 5
//struct para definir compontes da fila
typedef struct {
    pecas itens[MAX];
    int inicio;
    int fim; 
    int total;
}fila;


//funcao para inicializar fila
void iniciarFila(fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}
//funcao para checar se a lista esta cheia
int filaCheia(fila *f){
  return f->total == MAX;
}
//funcao para checar se a lista esta vazia
int filaVazia(fila *f){
    return f->total == 0;
}

//== dequeue funcao para adcionar elemento no final da fila
void inserir(fila *f, pecas p){
   if(filaCheia(f)){
    printf("lista cheia!, nao é possivel inserir! \n");
    return;
   }

   f->itens[f->fim] = p;
   f->fim = (f->fim + 1) % MAX;
   f->total++;
}

//funcao para remover pecas, servira para jogar pecas
void remover(fila *f, pecas *p){
    if(filaVazia(f)){
        printf("A fila esta vazia, nao e possivel lançar peça\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio =(f->inicio + 1) % MAX;
    f->total--;

}

void exibir(fila *f){
    printf("Peças : ");

    for(int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX){
        printf(" {%s, %d} ", f->itens[idx].nome, f->itens[idx].id);

    }

    printf("\n");


}

// funcao pricipal
int main(){
    fila f;

    iniciarFila(&f);

    int menu = 0;

    pecas escolhida;

    //adcionando pecas inicias manualmente 
    pecas p1 = {"I",0};
    pecas p2 = {"O",1};
    pecas p3 = {"T",2};
    pecas p4 = {"L",3};
    inserir(&f,p1);
    inserir(&f,p2);
    inserir(&f,p3);  
    inserir(&f,p4); 


    do {
        
    //menu interativo
    printf("==== Tetris Stack ==== \n");
    exibir(&f);
    printf("=== MENU ==\n");
    printf("(1) Jogar Peça\n");    
    printf("(2) Inserir Peça\n");    
    printf("(0) sair\n");    
    scanf("%d", &menu);

    switch (menu)
    {
    case 1://opcao jogar peca

        remover(&f,&escolhida);
        printf("Peça escolhida: [%s, %d]\n", escolhida.nome, escolhida.id);
        
        break;
    case 2: //opcao adcionar peca
        if (filaCheia(&f)) {
        printf("A fila está cheia, não é possível inserir nova peça!\n");
    } else {
        pecas nova;
        printf("Digite o nome da peça, ex(I,O,L,T): ");
        scanf("%s", nova.nome);
        printf("Digite o ID da peça: ");
        scanf("%d", &nova.id);
        inserir(&f, nova);
        printf("Peça adicionada com sucesso!\n");
    }
        break;
    case 0:
        printf("saindo....\n");
        break;
    default:
        printf("Opção invalida");
        break;
    }

    printf("\n\n");

   }while(menu != 0);
    return 0;
}

/*
pecas p1 = {"I",0};
pecas p2 = {"O",1};
pecas p3 = {"T",2};
pecas p4 = {"L",3};
    inserir(&f,p1);
    inserir(&f,p2);
    inserir(&f,p3);
    inserir(&f,p4);   

    exibir(&f);
*/