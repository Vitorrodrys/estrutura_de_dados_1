#include "pilha_containers.h"


int eh_cheia_vazia(pilha_Con *ptr, int vazia_cheia){
    return ptr->_topo == vazia_cheia;
}
int empilha(pilha_Con *self, long int dado){

    if(eh_cheia_vazia(self, CHEIA)){
        return 0;
    }
    self->_pilha[self->_topo] = dado;
    self->_topo++;
    return 1;

}
long int desimpilha(pilha_Con *self){

    if(eh_cheia_vazia(self, VAZIA)){
        return -1;
    }
    return self->_pilha[--self->_topo];
}


pilha_Con cria_container(int quantidade){
    pilha_Con new = {{0},0};
    if(quantidade < 4 || quantidade > 16){
        fprintf(stderr,"Houve uma criação de pilha com %d containers!\n", quantidade);
        exit(1);
    }
    static int srand_gerado = 0;
    if(!srand_gerado){
        srand(time(NULL));
        srand_gerado = 1;
    }

    for(int i = 0; i<quantidade; i++){

        empilha(&new, rand()%500);

    }
    return new;

}
void fpilhavazia(pilha_Con *ptr){
    ptr->_topo = 0;

}