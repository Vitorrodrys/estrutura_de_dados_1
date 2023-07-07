#include <stdio.h>
#include "fila_navios.h"
#include "travessas.h"
#include <unistd.h>



int main() {



    long int time_at = 0;



    atracamentos porto = CriaAtracamentos();
    travessas trav = criaTravessa();

    int quantidade_navios_chegados;
    do{
        quantidade_navios_chegados = chegada_de_navios(&porto, time_at);
        printf("\n\n___________________________________________________________________________________________________________________________________________\nUNIDADE DE TEMPO ATUAL QUE O PROGRAMA ESTA RODANDO: %ld\n", time_at);
        for(int i = 0; i<QT_FILA; i++) {
            //tenta desenfileirar navios um de cada navio a cada iteracao do loop, se der certo, retornara um, e informara qual navio foi desenfileirado
            if(desenfileira_atracamento(&porto)){
                printf("O navio de ID %ld esperou %ld unidades de tempo na fila\n", porto._filas[(porto._fila_at_desenfileiramento+QT_FILA-1)%QT_FILA].tratando.id, time_at -  porto._filas[(porto._fila_at_desenfileiramento+QT_FILA-1)%QT_FILA].tratando.tempo_chegada);
            }
        }

        //tenta retirar um container de cada navio tratando, e guardar em alguma travessa
        for(int i = 0; i<QT_FILA; i++){

            //a logica de qual travessa sera escolhido, e de como foi resolvido o problema de nao deixar nenhum navio esperando que exista uma travessa nao cheia pra descarregar
            //foi explicado dentro da funcao, mas basicamente ele sempre alterna a travessa que esta sendo usada como reserva (1 ou 5) a cada vez que enche as 4 travessas em uso,
            //quando enche as 4 travessas em uso, os carrinhos iram levar elas para o patio, e na unidade de tempo em que os carrinhos estiverem levando, qualquer tentativa de
            //desempilhamento de containers de qualquer um dos 4 navios, sera escolhido a travessa reserva, quando os carrinhos voltarem, sera feita uma troca de travessa reserva, se a 1
            //era a reserva antes, agora ela sera usada, e a 5 sera reserva
            retira_container(&trav, &porto._filas[i].tratando);
        }


        printf("A quantidade de navios chegados foram: %d\n",quantidade_navios_chegados);

        printa_atracamento(&porto);
        printa_situacao_travessas(&trav);
        printf("Situação dos navios atuais que estão sendo desempilhados:\n");
        for(int i = 0; i<QT_FILA;i++){

            if(porto._filas[i].tratando.containers._topo){
                printf("\t|Navio %d, com id %ld  tem %d containers ainda.|\n", i+1, porto._filas[i].tratando.id,porto._filas[i].tratando.containers._topo);
            }else{
                if(porto._filas[i].tratando.id != -1){
                    printf("\t|Navio %d, com id %ld ja foi descarregado.|\n", i+1,porto._filas[i].tratando.id);

                }else{
                    printf("\t|Na regiao de tratamento %d nao tem navios desenfileirados para serem tratados!|\n", i+1);
                }
            }

        }

        time_at++;


        printf("\n_________________________________________________________________________________________\n\n\n\n");
//fgetc(stdin);


//
  usleep(3000000);


    }
    while(!atr_vazio(&porto) || verifica_descarregou_navios(&porto));
}
