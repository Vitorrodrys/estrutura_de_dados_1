//
// Created by vitor on 25/06/23.
//

#ifndef UNTITLED56_LISTA_H
#define UNTITLED56_LISTA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct lista{

    size_t tam_dado;
    void *dados;
    int quantidade;
}lista;
lista CriaLista(size_t tam_dado);
void adiciona_dado(lista *self,void *dado);
void limpa_lista(lista *self);
#define converte_lista(self, type) (type*)(self)->dados
#endif //UNTITLED56_LISTA_H
