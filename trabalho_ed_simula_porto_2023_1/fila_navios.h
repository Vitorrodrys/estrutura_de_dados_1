//
// Created by vitor on 27/05/23.
//

#ifndef TRABALHO_ED_SIMULA_PORTO_FILA_NAVIOS_H
#define TRABALHO_ED_SIMULA_PORTO_FILA_NAVIOS_H
#include "pilha_containers.h"
#define QT_FILA 4
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_utilitarias.h"
typedef struct navio{
    pilha_Con containers;
    long int id;
    long int tempo_chegada;
}navio;

typedef struct key_navio{

    navio dado;
    struct key_navio *prox;
}key_navio;

typedef struct fila_navio{

    key_navio *pri;
    key_navio *ult;


    navio tratando;

    int quantidade;
    int quantidade_containers;

}fila_navio;



typedef struct atracamentos{
    fila_navio _filas[QT_FILA];
    int _fila_at_desenfileiramento;
}atracamentos;
int desenfileira_atracamento(atracamentos *self);
int enfileira_atracamento(atracamentos *self, navio dado);
atracamentos CriaAtracamentos();
int atr_vazio(atracamentos *ptr);
int chegada_de_navios(atracamentos *self,  long int time_at);
void printa_atracamento(atracamentos *self);
int verifica_descarregou_navios(atracamentos *self );

navio CriaNavio();

#endif //TRABALHO_ED_SIMULA_PORTO_FILA_NAVIOS_H
