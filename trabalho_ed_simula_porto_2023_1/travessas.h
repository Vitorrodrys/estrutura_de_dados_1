//
// Created by vitor on 27/05/23.
//

#ifndef TRABALHO_ED_SIMULA_PORTO_TRAVESSAS_H
#define TRABALHO_ED_SIMULA_PORTO_TRAVESSAS_H
#include "pilha_containers.h"
#include "fila_navios.h"
#define QTMAXTRAV 5
#define TRAVVAZIA 0
#define TRAVCHEIA QTMAXTRAV


typedef enum carregado{
    FOICARREGADA,
    VOLTANDO,
    DISPONIVEL

}carregado;

typedef struct pilha_trav{

    long int pilha[QTMAXTRAV];
    int _topo;
}pilha_trav;



typedef struct travessas{
    pilha_trav _travessas[QTMAXTRAV];
    int _at;
    int _signal;
    carregado _foi_carregada[QTMAXTRAV];

}travessas;



void retira_container(travessas *self, navio *nav);
travessas criaTravessa();
void printa_situacao_travessas(travessas *self);
int vtravessas_vazia_cheia(travessas *self, int vazia_cheia);


#endif //TRABALHO_ED_SIMULA_PORTO_TRAVESSAS_H
