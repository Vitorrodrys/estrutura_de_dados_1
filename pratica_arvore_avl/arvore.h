//
// Created by vitor on 23/06/23.
//

#ifndef UNTITLED56_ARVORE_H
#define UNTITLED56_ARVORE_H
#include <stdio.h>
#include <stdlib.h>
#include "funcoes_de_memoria.h"
#include "fila_celulas.h"
#include "lista.h"
typedef struct celula{

    int conteudo;
    int alt_esq;
    int alt_dir;
    struct celula *esq;
    struct celula *dir;
}celula;

typedef struct arvore{

    celula *raiz;
    int altura;
}arvore;


arvore cria_arvore();
int insere(arvore *self, int dado);
int retira(arvore *self, int dado);
int pesquisa(arvore *self, int dado);
arvore balanceia(arvore *self);
void imprime_em_nivel(arvore *self);
void limpa_arvore(arvore *self);
int is_abb(celula *raiz);
int computa_nos_ancestrais(celula *self, int dado);

#endif //UNTITLED56_ARVORE_H
