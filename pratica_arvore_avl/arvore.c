#include "arvore.h"



#define pilha(tamanho, tipo, nome) typedef struct nome{ \
    tipo dado[tamanho];                                                        \
    int _topo;                                                        \
    }nome;\
//operacoes TAD celula

pilha(10, int, teste);

pilha(20, float, teste2);
int altura(celula **raiz);
celula* cria_celula(int dado){

    teste a;
    teste2 b;
    celula *ptr = aloca_memoria(NULL, sizeof(celula));
    *ptr = (celula)
            {
                .conteudo= dado,
                .esq=NULL,
                .dir=NULL,
                .alt_esq=0,
                .alt_dir=0
            };
    return ptr;
}

celula **pesquisa_cel(celula **raiz, int dado){

    if(*raiz == NULL){
        return NULL;
    }
    if((*raiz)->conteudo == dado){
        return raiz;
    }
    if((*raiz)->conteudo > dado ){
        return pesquisa_cel(&(*raiz)->esq, dado);
    }
    if((*raiz)->conteudo < dado){
        return pesquisa_cel(&(*raiz)->dir, dado);
    }
}
celula *destroi_celula(celula **raiz){
    if(*raiz == NULL){
        return NULL;
    }

    if((*raiz)->esq != NULL && (*raiz)->dir != NULL){
        clear_memory((void **)raiz);
        return NULL;
    }
    (*raiz)->esq = destroi_celula(&(*raiz)->esq);
    (*raiz)->dir = destroi_celula(&(*raiz)->dir);
    clear_memory((void **)raiz);
    return NULL;

}
void rotaciona_a_esquerda(celula **ptr){

    celula *aux_raiz = *ptr;
    *ptr = (*ptr)->esq;
    celula *aux_dir = (*ptr)->dir;
    (*ptr)->dir = aux_raiz;
    (*ptr)->dir->esq = aux_dir;
}
void rotaciona_a_direita(celula **ptr){

    celula *aux_raiz = *ptr;
    *ptr = (*ptr)->dir;
    celula *aux_esq = (*ptr)->esq;
    (*ptr)->esq = aux_raiz;
    (*ptr)->esq->dir = aux_esq;
}

void rotacao(celula **ptr){
    if((*ptr)->alt_esq - (*ptr)->alt_dir >= 2){
        if((*ptr)->esq->alt_esq-(*ptr)->esq->alt_dir == 1){
            rotaciona_a_esquerda(ptr);
            (*ptr)->alt_dir = altura(&(*ptr)->dir);
            (*ptr)->alt_esq = altura(&(*ptr)->esq);
        }else{
            rotaciona_a_direita(&(*ptr)->esq);
            rotaciona_a_esquerda(ptr);
            (*ptr)->alt_esq = altura(&(*ptr)->esq);
            (*ptr)->alt_dir = altura(&(*ptr)->dir);
        }

    }else if((*ptr)->alt_esq - (*ptr)->alt_dir <=-2){

        if((*ptr)->dir->alt_esq-(*ptr)->dir->alt_dir == -1){
            rotaciona_a_direita(ptr);
            (*ptr)->alt_dir = altura(&(*ptr)->dir);
            (*ptr)->alt_esq = altura(&(*ptr)->esq);
        }else{
            rotaciona_a_esquerda(&(*ptr)->dir);
            rotaciona_a_direita(ptr);
            (*ptr)->alt_dir = altura(&(*ptr)->dir);
            (*ptr)->alt_esq = altura(&(*ptr)->esq);
        }
    }

}
int insere_cel(celula **ptr, int dado){
    if(*ptr == NULL){
        *ptr = cria_celula(dado);
        return 1;
    }

    if((*ptr)->conteudo < dado){
        insere_cel(&(*ptr)->dir, dado);
        (*ptr)->alt_dir = altura(&(*ptr)->dir);
        (*ptr)->alt_esq = altura(&(*ptr)->esq);
        rotacao(ptr);

        return 1;
    }
    if((*ptr)->conteudo > dado){
        insere_cel(&(*ptr)->esq, dado);
        (*ptr)->alt_dir = altura(&(*ptr)->dir);
        (*ptr)->alt_esq = altura(&(*ptr)->esq);
        rotacao(ptr);
        return 1;
    }
    
}
celula **antecessor(celula **raiz){
    celula **aux = &(*raiz)->esq;
    while((*aux)->dir != NULL){
        aux = &(*aux)->dir;
    }
    return aux;

}

int remove_cel(celula **raiz, int dado){
    celula **aux =pesquisa_cel(raiz, dado);
    if(!aux){
        return 0;
    }
    int dado_return;
    celula *aux1;
    if((*aux)->dir == NULL){
        aux1 = *aux;
        *aux = aux1->esq;
        dado_return = aux1->conteudo;
        clear_memory((void **)&aux1);
        return dado_return;
    }
    if((*aux)->esq != NULL){
        celula **aux_antecessor= antecessor(aux);
        dado_return = (*aux)->conteudo;
        swap(&(*aux)->conteudo, &(*aux_antecessor)->conteudo, sizeof (int));
        aux1 = *aux_antecessor;
        *aux_antecessor = aux1->esq;
        clear_memory((void **)aux_antecessor);
        return dado_return;
    }
    dado_return = (*aux)->conteudo;
    aux1 = *aux;
    *aux = aux1->dir;
    clear_memory((void **)&aux1);
    return dado_return;

}
void printa_tabs(int tabs, int dec){
    for(int i = 0; i<tabs+dec; i++){
        printf("    ");
    }

}
void imprime_em_nivel_cel(celula **raiz){
    dado_celula aux;
    fila_celulas fila = cria_fila();
    int tabs = 0;

    adicina_celula_fila(&fila, Cria_dado_celula(*raiz, 1, tabs));
    while(!eh_vazia(&fila)){
        aux = remove_dado_fila(&fila);

        printa_tabs(20, aux.tabs);
        printf("%d%c", aux.dado->conteudo, aux.enter);
        tabs++;

        adicina_celula_fila(&fila, Cria_dado_celula(aux.dado->esq, 1, aux.tabs-tabs));
        adicina_celula_fila(&fila, Cria_dado_celula(aux.dado->dir, 0, aux.tabs+ tabs));
    }
}
void percorre_in_ordem(celula **raiz, lista *lista){

    if(*raiz == NULL){
        return;
    }
    percorre_in_ordem(&(*raiz)->esq, lista);
    adiciona_dado(lista, &(*raiz)->conteudo);
    percorre_in_ordem(&(*raiz)->dir, lista);
}

celula *cria_celula_balanceada(int *vetor, int inicio, int fim){

    if(fim<=inicio){
       return cria_celula(vetor[inicio]);
    }
    celula *ptr = cria_celula(vetor[(inicio+fim)/2]);
    ptr->esq = cria_celula_balanceada(vetor, inicio, (inicio+fim)/2-1);
    ptr->dir = cria_celula_balanceada(vetor, (inicio+fim)/2+1, fim);
    ptr->alt_dir = altura(&ptr->dir);
    ptr->alt_esq = altura(&ptr->esq);
    return ptr;
}

int altura(celula **raiz){
    if(*raiz == NULL){
        return 0;
    }
    int alturaesq = altura(&(*raiz)->esq);
    int alturadir = altura(&(*raiz)->dir);
    return (alturadir>alturaesq?alturadir:alturaesq)  +1;


}
arvore cria_arvore(){

    return (arvore){
        .raiz = NULL,
        .altura = 0
    };
}
int insere(arvore *self, int dado){

    int retorno = insere_cel(&self->raiz, dado);
    self->altura = altura(&self->raiz);
    return retorno;
}
int retira(arvore *self, int dado){
    int retorno = remove_cel(&self->raiz, dado);
    self->altura = altura(&self->raiz);
    return retorno;

}
int pesquisa(arvore *self, int dado){
    return (*pesquisa_cel(&self->raiz, dado))->conteudo;
}
void imprime_em_nivel(arvore *self){
    imprime_em_nivel_cel(&self->raiz);
}



arvore balanceia(arvore *self){

    lista list = CriaLista(sizeof(int));

    percorre_in_ordem(&self->raiz, &list);

    arvore arv = cria_arvore();
    arv.raiz = cria_celula_balanceada(converte_lista(&list, int), 0, list.quantidade-1);
    arv.altura = altura(&arv.raiz);
    limpa_lista(&list);
    return arv;





}

int is_abb(celula *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(raiz->esq && raiz->esq->conteudo > raiz->conteudo){
        return 0;
    }
    if(raiz->dir && raiz->dir->conteudo < raiz->conteudo){
        return 0;
    }

    return is_abb(raiz->esq) && is_abb(raiz->dir);





}

int computa_nos_ancestrais(celula *self, int dado){

    if (self == NULL || self->conteudo == dado){
        return 0;
    }
    if (self->esq && self->esq->conteudo == dado || self->dir && self->dir->conteudo == dado){
        return 1;
    }

    int ancestrais_esquerda = computa_nos_ancestrais(self->esq, dado);
    int ancestrais_dir = computa_nos_ancestrais(self->dir, dado);
    if(ancestrais_dir || ancestrais_esquerda){
        return ancestrais_dir+ancestrais_esquerda+1;

    }
    return 0;
}

void limpa_arvore(arvore *self){
    self->raiz = destroi_celula(&self->raiz);
    self->altura = 0;
}