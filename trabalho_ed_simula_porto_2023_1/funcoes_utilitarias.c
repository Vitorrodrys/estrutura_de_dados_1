#include "funcoes_utilitarias.h"

void *aloca_memoria(void *ptr, size_t tamanho){

    void *ptrReall = realloc(ptr, tamanho);

    if(!ptrReall){
        fprintf(stderr, "ERRO: Memoria indisponivel!\n");
        exit(1);
    }
    if(!ptr) {
        char *byte = ptrReall;
        for (; byte < (char *)ptrReall+tamanho; byte++) {
            *byte = 0;
        }
    }
    return ptrReall;
}
void clear_memory(void **ptr){
    free(*ptr);
    *ptr= NULL;
}

void swap(void *ptr, void *ptr2, size_t tam){


    char temp[tam];

    memmove(temp, ptr, tam);
    memmove(ptr, ptr2, tam);
    memmove(ptr2, temp, tam);

}