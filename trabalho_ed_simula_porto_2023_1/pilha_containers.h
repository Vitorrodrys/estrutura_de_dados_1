//
// Created by vitor on 27/05/23.
//

#ifndef TRABALHO_ED_SIMULA_PORTO_PILHA_CONTAINERS_H
#define TRABALHO_ED_SIMULA_PORTO_PILHA_CONTAINERS_H
#define MT 16
#define CHEIA MT
#define VAZIA 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct pilha_Con{

    long int _pilha[MT];
    int _topo;
}pilha_Con;
void fpilhavazia(pilha_Con *ptr);
int eh_cheia_vazia(pilha_Con *ptr, int vazia_cheia);
int empilha(pilha_Con *self,long  int dado);
long int desimpilha(pilha_Con *self);
pilha_Con cria_container(int quantidade);

#endif //TRABALHO_ED_SIMULA_PORTO_PILHA_CONTAINERS_H
