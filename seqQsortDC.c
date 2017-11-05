/*-----------------------------------------------------------------------------
PONTIFÍCIA UNIVERSIDADE CATÓLICA DO RIO GRANDE DO SUL
PROGRAMAÇÃO PARALELA E DISTRIBUIDA - ENGENHARIA DE COMPUTAÇÃO
Gabriel Fasoli Susin - gabriel.susin@acad.pucrs.br
Augusto Bergamin - augusto.bergamin@acad.pucrs.br
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VETOR_SIZE 100
#define DELTA 30


void printfv(int *vetor, int tam_vetor){
    int i;
    for(i = 0; i<tam_vetor;i++){
        printf("%d: %d\n",i,vetor[i]);
    }

}

void Inicializa( int *vetor,int tam_vetor){
    int i;
    for(i = 0; i<tam_vetor;i++){
        vetor[i] = tam_vetor - i;
    }
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
 }


int main(int argc, char** argv){
    int tam_vetor;
    int *vetor;

    tam_vetor = VETOR_SIZE; // defino tamanho inicial do vetor
    vetor = malloc (tam_vetor*sizeof(int)); //aloco um vetor com este tamanho
    Inicializa(vetor,tam_vetor);

    qsort(vetor,tam_vetor, sizeof(int), cmpfunc);//conquisto ordedando o vetor   

    printfv(vetor,100); // pai imprime o vetor
    printf("DONE");

    return 0;
    }