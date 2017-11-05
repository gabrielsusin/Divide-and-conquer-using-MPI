/*-----------------------------------------------------------------------------
PONTIFÍCIA UNIVERSIDADE CATÓLICA DO RIO GRANDE DO SUL
PROGRAMAÇÃO PARALELA E DISTRIBUIDA - ENGENHARIA DE COMPUTAÇÃO
Gabriel Fasoli Susin - gabriel.susin@acad.pucrs.br
Augusto Bergamin - augusto.bergamin@acad.pucrs.br
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

#define SEND 1

#define VETOR_SIZE 100000
#define DELTA 60000

void bs(int n, int * vetor)
{
    int c=0, d, troca, trocou =1;

    while (c < (n-1) & trocou )
        {
        trocou = 0;
        for (d = 0 ; d < n - c - 1; d++)
            if (vetor[d] > vetor[d+1])
                {
                troca      = vetor[d];
                vetor[d]   = vetor[d+1];
                vetor[d+1] = troca;
                trocou = 1;
                }
        c++;
        }
}

int *interleaving(int vetor[], int tam)
{
	int *vetor_auxiliar;
	int i1, i2, i_aux;

	vetor_auxiliar = (int *)malloc(sizeof(int) * tam);

	i1 = 0;
	i2 = tam / 2;

	for (i_aux = 0; i_aux < tam; i_aux++) {
		if (((vetor[i1] <= vetor[i2]) && (i1 < (tam / 2)))
		    || (i2 == tam))
			vetor_auxiliar[i_aux] = vetor[i1++];
		else
			vetor_auxiliar[i_aux] = vetor[i2++];
	}

	return vetor_auxiliar;
}

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

int my_father(int my_rank){
    if(my_rank%2==0) return ((my_rank-2)/2);
    else return ((my_rank-1)/2); 
}

int main(int argc, char** argv){
    int tam_vetor, my_rank, probe;
    int *vetor_aux; 
    int *vetor;
    MPI_Status status;
    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if ( my_rank != 0 )
    {
    MPI_Probe(my_father(my_rank), MPI_ANY_TAG, MPI_COMM_WORLD, &status); 
    MPI_Get_count(&status, MPI_INT, &tam_vetor);  //descubro o tamanho da mensagem a ser recebida
    vetor = malloc (tam_vetor*sizeof(int)); //aloco um vetor com este tamanho
    MPI_Recv (vetor, tam_vetor, MPI_INT, my_father(my_rank), MPI_ANY_TAG, MPI_COMM_WORLD, &status); // recebo o vetor
    }
    else
    {
    tam_vetor = VETOR_SIZE; // defino tamanho inicial do vetor
    vetor = malloc (tam_vetor*sizeof(int)); //aloco este vetor
    Inicializa (vetor, tam_vetor );// preencho o vetor de fora decrescente
    }

    // dividir ou conquistar?

    if ( tam_vetor <= DELTA )bs(tam_vetor,vetor);//conquisto ordedando o vetor
    else
        {
        MPI_Send (&vetor[0], tam_vetor/2,MPI_INT ,(my_rank*2)+1, SEND, MPI_COMM_WORLD );  // mando metade inicial do vetor
        MPI_Send (&vetor[tam_vetor/2], tam_vetor/2, MPI_INT, (my_rank*2)+2, SEND, MPI_COMM_WORLD);  // mando metade final 

        MPI_Recv (&vetor[0],tam_vetor/2 ,MPI_INT,(my_rank*2)+1,MPI_ANY_TAG,MPI_COMM_WORLD, &status);//recebo metade do vetor          
        MPI_Recv (&vetor[tam_vetor/2],tam_vetor/2,MPI_INT, (my_rank*2)+2,MPI_ANY_TAG,MPI_COMM_WORLD, &status);//recebo o resto
       
        vetor_aux = malloc(tam_vetor*sizeof(int)); //aloco um vetor auxiliar
        vetor_aux = interleaving(vetor, tam_vetor); //intercalo este
        vetor = vetor_aux;
        }

    // mando para o pai
    if ( my_rank !=0 )MPI_Send (vetor,tam_vetor,MPI_INT,my_father(my_rank),SEND, MPI_COMM_WORLD);//mando meu vetor para o pai
    else{
        printfv(vetor,100000); // pai imprime o vetor
        printf("DONE");}
    
    free(vetor_aux);
    MPI_Finalize();
    return 0;
    }