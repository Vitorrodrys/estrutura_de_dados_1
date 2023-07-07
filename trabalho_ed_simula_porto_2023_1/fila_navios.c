#include "fila_navios.h"


navio CriaNavio(  long int time_at){
    /*funcao que cria um navio, usa uma variavel estatica para guardar o id do ultimo navio criado, e assim criar navios sequenciais*/
    static int id = 1;
    return (navio){cria_container(rand()%13+4),id++,time_at};
}

void *limpaCelula(key_navio*ptr){
    //limpa uma celula da fila encadeada de key navios, deve ser chamada após reajustar os ponteiros do proximo na hora de retirar uma navio da fila, pois ela excluira a
    //referencia para o proximo
    ptr->prox = NULL;
    ptr->dado = (navio){.containers = {0},.id=0,.tempo_chegada = 0};
    clear_memory((void **)&ptr);
    return NULL;

}

fila_navio cria_fila(){
    //funcao responsavel por criar uma fila, seta valores zerados para o ponteiro para o primeiro da fila, ult e quantidade, e seta um valor padrao para
    //a estrutura que guarda o navio que esta sendo tratado, com esses valores padroes e possivel saber que nao tem navios sendo tratados
    return (fila_navio){NULL,NULL, {{0},-1,-1},0,0};
}
int eh_vazia(fila_navio *ptr){
    return !ptr->quantidade;
}
int enfileira(fila_navio *self, navio dado){

    self->quantidade_containers+=dado.containers._topo;
    //enfileira um navio no fim da fila, se a fila e vazia, enfileira na primeira posicao e iguala os ponteiros de ultimo e primeiro
    if(eh_vazia(self)){
        self->pri = aloca_memoria(NULL, sizeof(key_navio));
        self->pri->dado = dado;
        self->pri->prox = NULL;
        self->ult = self->pri;
        self->quantidade++;
        return 1;
    }
    //se nao e vazia, entao desereferencia o ponetiro do ult, vai no seu campo proximo e guarda o endereco de uma nova celula, atualiza o ponteiro do proximo
    //e incrementa a quantidade
    self->ult->prox = aloca_memoria(NULL, sizeof(key_navio));
    self->ult->prox->dado = dado;
    self->ult->prox->prox = NULL;
    self->ult = self->ult->prox;
    self->quantidade++;
    return 1;

}
long int soma_container_fila(const fila_navio *self){

    return self->quantidade_containers + self->tratando.containers._topo;
    //funcao responsavel por calcular a quantidade de containers em uma fila
    long int soma = 0;
    key_navio *aux = self->pri;
    while(aux != NULL){
        soma += aux->dado.containers._topo;
        aux = aux->prox;
    }
    return soma+self->tratando.containers._topo;
}
navio desenfileira(fila_navio *self){
    //funcao responsavel por desenfileirar o primeiro navio de uma fila, retorna um sinal caso a fila ja estava vazia
    if(eh_vazia(self)){
        return (navio){{{0},0}, -1,-1};
    }
    //salva uma copia do dado do primeiro navio
    navio desenfileirar = self->pri->dado;
    key_navio *limpar =self->pri;
    //salva o endereco da celula que deve limpar
    //atualiza o ponteiro do primeiro para o ponteiro do segundo item da lista
    self->pri = self->pri->prox;
    //limpa a chave do primeiro
    limpar = limpaCelula(limpar);
    //atualiza a quantidade
    self->quantidade--;
    self->quantidade_containers-=desenfileirar.containers._topo;
    //se a quantidade era 0, entao a fila ficou vazia, seta o ponteiro do ultimo para NULL
    if(self->quantidade == 0){
        self->ult = NULL;
    }
    return desenfileirar;

}
void printa_fila(fila_navio *self){
    key_navio *aux = self->pri;
    printf("\tQuantidade de navios nesta fila %d\n", self->quantidade);
    if(self->quantidade == 0){
        return;
    }
    printf("\tnavios nesta fila:\n");
    while(aux != NULL){
        printf("\t\t|id: %ld, tempo_chegada: %ld, quantidade de container neste navio: %d|\n", aux->dado.id, aux->dado.tempo_chegada, aux->dado.containers._topo);
        aux = aux->prox;
    }

}

//TAD atracamentos:
int atr_vazio(atracamentos *ptr){
    //verifica se o atracamento de filas esta vazio chamando cada funcao boleana que verifica se cada fila do atracamento esta vazia, e faz um and entre as respostas
    return eh_vazia(ptr->_filas) && eh_vazia(ptr->_filas+1) && eh_vazia(ptr->_filas+2) && eh_vazia(ptr->_filas+3);
}

atracamentos CriaAtracamentos(){
    //cria um atracamento chamando cada funcao que cria cada fila
    return (atracamentos){{cria_fila(), cria_fila(), cria_fila(), cria_fila()}, 0};
    //fila_at_desenfileiramento e a fila atual do loop que tem o direito de desenfileirar um navio, a logica sera melhor explicada na funcao de desenfileirar atracamento
}
int enfileira_atracamento(atracamentos *self, navio dado){

    //funcao responsavel por enfileirar um navio na fila que tem menor containers

    int menos_containers = 0;
    long int quantidadeContainers = soma_container_fila(self->_filas);

    for(int i = 1; i<QT_FILA; i++){
        //se a fila atual do loop tiver menos containers que a fila 0, entao ela sera a nova fila que tem menos containers
        if(soma_container_fila(self->_filas+i) < quantidadeContainers){
            menos_containers = i;
            quantidadeContainers = soma_container_fila(self->_filas+i);
        }
    }
    //enfileira na fila que tem menos
    enfileira(self->_filas+menos_containers, dado);



    return 1;

}

int desenfileira_atracamento(atracamentos *self){

    //funcao responsavel por desenfileirar o atracamento, recebe um ponteiro para o atracamento e consulta a variavel __fila_at_desenfileiramento para
    //ver de qual fila é a vez de desenfileirar, se essa fila nao poder desenfileirar o navio pelo motivo de que o container do navio que esta na estacao de tratamento
    //destinado a ela ainda tiver containers para serem desempilhados, entao ela passa a vez para a proxima fila e nao faz nada
    if(!eh_cheia_vazia(&self->_filas[self->_fila_at_desenfileiramento].tratando.containers, VAZIA)){
        self->_fila_at_desenfileiramento = (self->_fila_at_desenfileiramento+1)%QT_FILA;
        return 0;
    }
    //se o navio que esta na estacao de tratamento ja tiver desempilhado todos os containers, entao o navio da fila sera desenfieirado para a estacao de tratamento

    self->_filas[self->_fila_at_desenfileiramento].tratando = desenfileira(self->_filas + self->_fila_at_desenfileiramento);
    self->_fila_at_desenfileiramento = (self->_fila_at_desenfileiramento+1)%QT_FILA;//passa a vez para a proxima fila
    //se o id do navio desenfileirado for igual a -1, entao nao desenfileirou, entao retorna falso, caso nao seja igual, entao desenfileirou
    return self->_filas[(self->_fila_at_desenfileiramento+QT_FILA-1)%QT_FILA].tratando.id == -1?0:1;

}

int chegada_de_navios(atracamentos *self,   long int time_at){
    //funcao que faz a chegada de navios ao porto, recebe o tempo atual que o programa esta rodando para repassar esse parametro para a funcao que Cria o navio
    //logo o navio criado tera como tempo de criacao o tempo recebido
    static int srand_generated = 0;

    if(!srand_generated){
        srand(time(NULL));
        srand_generated = 1;
    }
    //gera um numero de 0 a 3 para sortear os navios
    int quantidade_navios_chegados = rand()%4;

    for(int i = 0; i<quantidade_navios_chegados;i++){
        enfileira_atracamento(self, CriaNavio(time_at));
    }
    return quantidade_navios_chegados;


}
void printa_atracamento(atracamentos *self){
    for(int i = 0; i<QT_FILA; i++){

        printf("\nFila de atracamento %d, ", i+1);
        if(self->_filas[i].quantidade)
            printf("o tempo medio de espera nessa fila %ld unidades de tempo: \n", soma_container_fila(self->_filas+i));
        printa_fila(self->_filas+i);
        printf("\n\n");

    }
}
int verifica_descarregou_navios(atracamentos *self ){

    //se encontrar um navio tratando que nao esta com os containers vazios, entao ja é o suficiente pra dizer que nao terminou de desenfileirar todos os navios do porto
    for(int i = 0; i<QT_FILA; i++){
        if(!eh_cheia_vazia(&self->_filas[i].tratando.containers, VAZIA)){
            return 1;
        }
    }
    return 0;
}