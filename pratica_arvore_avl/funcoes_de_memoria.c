#include "funcoes_de_memoria.h"
#include <stdio.h>
#include <string.h>
void *aloca_memoria(void *ptr, size_t tam){
    void *ptr_reall = realloc(ptr, tam);
    if(!ptr_reall){
        fprintf(stderr, "ERRO: Mémoria indisponivel!\n");
        exit(1);
    }
    return ptr_reall;
}
void clear_memory(void **ptr){

    free(*ptr);
    *ptr = NULL;
}
void swap(void *ptr, void *ptr1, size_t tam){
    char temp[tam];
    memmove(temp, ptr, tam);
    memmove(ptr, ptr1, tam);
    memmove(ptr1, temp, tam);
}