//
// Created by vitor on 27/05/23.
//

#ifndef TRABALHO_ED_SIMULA_PORTO_FUNCOES_UTILITARIAS_H
#define TRABALHO_ED_SIMULA_PORTO_FUNCOES_UTILITARIAS_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>


void *aloca_memoria(void *ptr, size_t tamanho);
void clear_memory(void **ptr);
void swap(void *ptr, void *ptr2, size_t tam);

#endif //TRABALHO_ED_SIMULA_PORTO_FUNCOES_UTILITARIAS_H
