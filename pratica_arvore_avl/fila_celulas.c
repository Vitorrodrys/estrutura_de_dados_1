//
// Created by vitor on 25/06/23.
//
#include "fila_celulas.h"
fila_celulas cria_fila(){
    return (fila_celulas){
        .pri=NULL,
        .ult=NULL,
        .quant=0
    };
}
dado_celula Cria_dado_celula(celula *address, int is_filho_esq, int tabs){
    return (dado_celula){
        .dado = address,
        .is_filho_esq = is_filho_esq,
        .tabs = tabs,
        .enter = (!is_filho_esq)?'\n':' '
    };
}
key_fila *Cria_chave_fila(dado_celula dado){

    key_fila *ptr = aloca_memoria(NULL, sizeof(key_fila));
    *ptr =(key_fila)
            {
                .dado = dado,
                .prox = NULL
            };
    return ptr;
}
int eh_vazia(fila_celulas *self){
    return self->quant == 0;
}

int adicina_celula_fila(fila_celulas *self, dado_celula dado){
    if(dado.dado == NULL){
        return 0;
    }
    if(eh_vazia(self)){
        self->pri = Cria_chave_fila(dado);
        self->ult = self->pri;
        self->quant++;
        return 1;
    }
    self->ult->prox = Cria_chave_fila(dado);
    self->ult = self->ult->prox;
    self->quant++;
    return 1;

}
dado_celula remove_dado_fila(fila_celulas *self){
    if(eh_vazia(self)){
        return (dado_celula){.dado=NULL, .tabs=-1, .is_filho_esq=-1};
    }
    dado_celula aux = self->pri->dado;
    key_fila *remover = self->pri;
    self->pri = self->pri->prox;
    clear_memory((void **)&remover);
    self->quant--;
    if(self->pri == NULL){
        self->ult = NULL;
    }
    return aux;
}