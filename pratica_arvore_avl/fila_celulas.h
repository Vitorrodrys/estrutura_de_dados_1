//
// Created by vitor on 25/06/23.
//

#ifndef UNTITLED56_FILA_CELULAS_H
#define UNTITLED56_FILA_CELULAS_H
#include "arvore.h"
typedef struct celula celula;

typedef struct dado_celula{
    celula *dado;
    int is_filho_esq;
    int tabs;
    char enter;
}dado_celula;
typedef struct key_fila{

    dado_celula dado;
    struct key_fila*prox;
}key_fila;
typedef struct fila_celulas{
    key_fila *pri;
    key_fila *ult;
    int quant;
}fila_celulas;
dado_celula remove_dado_fila(fila_celulas *self);
int adicina_celula_fila(fila_celulas *self, dado_celula dado);
int eh_vazia(fila_celulas *self);
key_fila *Cria_chave_fila(dado_celula dado);
fila_celulas cria_fila();
dado_celula Cria_dado_celula(celula *address, int is_filho_esq, int tabs);
#endif //UNTITLED56_FILA_CELULAS_H
