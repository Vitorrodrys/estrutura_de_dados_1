#include <stdio.h>

#include "arvore.h"
#include <time.h>
#include <stdarg.h>
void verificaNumero(char *controle, void *ptr){
    int digCert = 0;
    do {

        digCert = 0;
        scanf(controle, ptr);

        while(fgetc(stdin)!= '\n')
            digCert++;
        if(digCert){
            printf("digite somente numeros!\n");
        }
    }while(digCert);
}
char *digText(FILE *f, char parar){




    int tamanho = 1;
    char *texto = (char *)malloc(sizeof(char));
    do{
        texto[tamanho-1] = fgetc(f);
        tamanho++;
        if(texto[tamanho-2] != parar){

            texto = (char *)realloc(texto, sizeof(char)*tamanho);

        }



    }while(texto[tamanho-2] != parar);
    texto[tamanho-2] = '\0';
    return texto;
}

void menu(int quantidade, char *frase, ...){
    va_list p;
    va_start(p, quantidade);

    char *fraseat;

    printf("\t%s\n", frase);
    for (int i = 0; i<quantidade; i++){
        fraseat = va_arg(p, char *);
        printf("%d-%s\n", i+1, fraseat);

    }
    va_end(p);
}
int main() {

//nao deu tempo de implementar o desenho de forma bem feita da impressao em nivel, vou tentar fazer e enviar depois, o unico problema é os tabs e enter, nao estao consistentes para
//ele desenhar a arvore corretamente.


    srand(time(NULL));
    arvore arv = cria_arvore();

    for(int i = 0; i<50; i++){
        insere(&arv, rand()%50);
    }

    int ancestrais = computa_nos_ancestrais(arv.raiz, 30);


    int resposta = is_abb(arv.raiz);


    int escolha=10;

    while (escolha != 6){

        menu(6, "digite uma opcao", "inserir elemento na arvore", "remover elemento", "pesquisar elemento", "imprimir em nivel", "rebalancear arvore", "sair");
        verificaNumero("%d",&escolha);
        switch (escolha) {

            case 1: {
                int dado;
                printf("digite um dado para inserir na arvore: ");
                verificaNumero("%d", &dado);
                insere(&arv, dado);
                break;
            }
            case 2:{
                int dadoremov;
                printf("digite um dado para remover: ");
                verificaNumero("%d",&dadoremov);
                retira(&arv, dadoremov);
                break;
            }
            case 3:{
                int dado_pesquisa;
                printf("digite um dado para pesquisar: ");
                verificaNumero("%d", &dado_pesquisa);
                pesquisa(&arv, dado_pesquisa);
                break;
            }
            case 4:
                imprime_em_nivel(&arv);
                break;
            case 5:{
                arvore arvb = balanceia(&arv);
                printf("arvore antes:\n");
                imprime_em_nivel(&arv);
                printf("\narvore depois:\n");
                imprime_em_nivel(&arvb);
                limpa_arvore(&arv);
                arv = arvb;
                break;

            }
        }
    }
}
