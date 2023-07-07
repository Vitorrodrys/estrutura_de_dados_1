#include "travessas.h"

int empilha_trav(pilha_trav *ptr, long int dado);
void ftravessavazia(pilha_trav *ptr);
int eh_vazia_cheia(pilha_trav *ptr, int vazia_cheia);
pilha_trav cria_ptravessa();

void retira_container(travessas *self, navio *nav){
    //tenta retirar um container, existe uma variavel de sinal dentro do objeto travessas que informa se a travessa que esta sendo ignorada atualmente (travessa reserva) é a quinta e a quarta
    //, ou a primeira e a segunda, se for 1 é a primeira e a segunda, se nao é a quarta e a quinta
    //existe tambem uma variavel que conta a travessa atual que tentara depositar um container
    //funcao que usa uma operação de mod que desconsidera o numero 4 e o 3, ou seja, os numeros gerados por ela serão 0,1,2 e volta para o 0
    int prox4(){
        return (self->_at+(QTMAXTRAV-3))%(QTMAXTRAV-2);

    };
    //funcao que usa uma operacao de mod que desconsidera o numero 0 e 1
    int prox0(){
        return self->_at%(QTMAXTRAV-2)+2;
    }

    //vetor de operacoes de mod
    int (*proxs[2])(void) = {prox0, prox4};

        if(nav->id == -1 && nav->tempo_chegada == -1){
            //se o id do navio e tempo de chegada forem iguais a menos um, quer dizer que nao haviam navios nas filas, entao nao foi desenfileirado nenhum navio,
            //logo a funcao nao deve prosseguir com o processo de retirar um container do topo da pilha do navio
            return;
        }
        //se a pilha de container do navio for vazia, retorna
        if(eh_cheia_vazia(&nav->containers, VAZIA)){
            return;
        }

        long int container;
        //desempilha o ultimo container da pilha do navio
        container = desimpilha(&nav->containers);

        //procura uma travessa vazia
        while(eh_vazia_cheia(self->_travessas+self->_at, TRAVCHEIA)){
            self->_at=proxs[self->_signal]();//proxs é um vetor de funcoes, entao ele está selecionando do vetor a funcao correta
        }
        //a cada loop while em que a travessa for cheia, chamara a funcao correta segundo o signal para pegar a proxima travessa em uso

        //depois que achar a travessa que nao esta cheia, empilha o container nela
        empilha_trav(self->_travessas+self->_at, container);
        //passa a vez para a proxima travessa usando a funcao correta dentro do vetor de funcoes
        self->_at = proxs[self->_signal]();

        //verifica se apos a adicao desse container as travessas encheram, se sim manda o carrinho levalas e inverte o sinal
        if(vtravessas_vazia_cheia(self, TRAVCHEIA)) {
            //percorre todas as filas atuais em uso
            for (int i = 0; i < QTMAXTRAV - 2; i++) {

                self->_at = proxs[self->_signal]();//pega a proxima fila em uso, e marca que ela foi carregada
                self->_foi_carregada[self->_at] = FOICARREGADA;
            }
            //inverte o sinal, para inverter a travessa vazia
            self->_signal = !self->_signal;
            self->_at=2;//seleciona como fila at uma fila que sera usada quando sinal é 0 ou 1

        }


}
void printa_situacao_travessas(travessas *self){

    for(int i = 0; i<QTMAXTRAV; i++) {
        if (self->_foi_carregada[i] == FOICARREGADA) {
            self->_foi_carregada[i] = VOLTANDO;
            printf("O carrinho %d levou a travessa %d.\n", i+1, i+1);
            continue;
        }else if (self->_foi_carregada[i] == VOLTANDO){
            printf("O carrinho %d esta voltando com a travessa %d\n", i+1, i+1);

            self->_foi_carregada[i] = DISPONIVEL;
            ftravessavazia(self->_travessas + i);
            continue;

        }
        printf("travessa %d tem %d containers.\n", i + 1, self->_travessas[i]._topo);

    }
}

travessas criaTravessa(){
    return  (travessas)
    {
        {cria_ptravessa(),cria_ptravessa(),cria_ptravessa(),cria_ptravessa(),cria_ptravessa() },
                       0,
                       1,
                       {DISPONIVEL, DISPONIVEL, DISPONIVEL, DISPONIVEL, DISPONIVEL}
    };


}


//TAD pilha travessas


pilha_trav cria_ptravessa(){
    return (pilha_trav){{0},0};
}
int eh_vazia_cheia(pilha_trav *ptr, int vazia_cheia){
    return ptr->_topo == vazia_cheia;
}
int vtravessas_vazia_cheia(travessas *self, int vazia_cheia){

    return eh_vazia_cheia(self->_travessas+(self->_signal == 1?0:4), vazia_cheia) && eh_vazia_cheia(self->_travessas+(self->_signal == 1?1:3), vazia_cheia) &&
            eh_vazia_cheia(self->_travessas+2, vazia_cheia);

}

int empilha_trav(pilha_trav *ptr, long int dado){

    if(eh_vazia_cheia(ptr, TRAVCHEIA)){
        return 0;
    }
    ptr->pilha[ptr->_topo++] = dado;
    return 1;


}
void ftravessavazia(pilha_trav *ptr){
    ptr->_topo = TRAVVAZIA;
}
