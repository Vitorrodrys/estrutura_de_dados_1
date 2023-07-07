#include "lista.h"
#include "funcoes_de_memoria.h"
#include <string.h>

lista CriaLista(size_t tam_dado){
    return (lista){
        .tam_dado=tam_dado,
        .quantidade=0,
        .dados=NULL
    };
}
void adiciona_dado(lista *self,void *dado){
    int quantidade_temp = self->quantidade;
    ++self->quantidade;
    self->dados = aloca_memoria(self->dados, self->quantidade*self->tam_dado);
    memmove(
            (char *)(self->dados+(quantidade_temp*self->tam_dado)),
            dado,
            self->tam_dado
            );
}
void limpa_lista(lista *self){
    clear_memory(&self->dados);
    self->quantidade=0;

}