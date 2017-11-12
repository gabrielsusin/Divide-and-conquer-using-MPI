/*-----------------------------------------------------------------------------
PONTIFÍCIA UNIVERSIDADE CATÓLICA DO RIO GRANDE DO SUL
PROGRAMAÇÃO PARALELA E DISTRIBUIDA - ENGENHARIA DE COMPUTAÇÃO
Gabriel Fasoli Susin - gabriel.susin@acad.pucrs.br
Augusto Bergamin - augusto.bergamin@acad.pucrs.br
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

#define SEND 1

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

int *interleaving(int job1[],int tam1, int job2[], int tam2, int job3[], int tam3)
{
	int *vetor_auxiliar;
	vetor_auxiliar = (int *)malloc(sizeof(int) * (tam1+tam2+tam3));

    if((job1[tam1-1] < job2[0])&&(job1[tam1-1] < job3[0]))
    {
        memmove(vetor_auxiliar, job1, tam1*sizeof(int));
        if(job2[tam2-1] < job3[0])
        {
            memmove(&vetor_auxiliar[tam1], job2, tam2*sizeof(int));
            memmove(&vetor_auxiliar[tam1+tam2], job3, tam3*sizeof(int));
        }
        else
        {
            memmove(&vetor_auxiliar[tam1], job3, tam3*sizeof(int));
            memmove(&vetor_auxiliar[tam1+tam3], job2, tam2*sizeof(int));
        }
    }
    else if((job2[tam2-1] < job1[0])&&(job2[tam2-1] < job3[0]))
    {
        memmove(vetor_auxiliar, job2, tam2*sizeof(int));
        if(job1[tam1-1] < job3[0])
        {
            memmove(&vetor_auxiliar[tam2], job1, tam1*sizeof(int));
            memmove(&vetor_auxiliar[tam2+tam1], job3, tam3*sizeof(int));
        }
        else
        {
            memmove(&vetor_auxiliar[tam2], job3, tam3*sizeof(int));
            memmove(&vetor_auxiliar[tam2+tam3], job1, tam1*sizeof(int));
        }
    }
    else if((job3[tam3-1] < job1[0])&&(job3[tam3-1] < job2[0]))
    {
        memmove(vetor_auxiliar, job3, tam3*sizeof(int));
        if(job1[tam1-1] < job2[0])
        {
            memmove(&vetor_auxiliar[tam3], job1, tam1*sizeof(int));
            memmove(&vetor_auxiliar[tam3+tam1], job2, tam2*sizeof(int));
        }
        else
        {
            memmove(&vetor_auxiliar[tam3], job2, tam2*sizeof(int));
            memmove(&vetor_auxiliar[tam3+tam2], job1, tam1*sizeof(int));
        }
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
    int my_rank, proc_n, debug=0;
    int delta=25000 ,tam_vetor=100000;
    double t1,t2;
    int *vetor;
    MPI_Status status;
    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n);

    int i;
	for(i=0; i<argc; i++)
	{
		if(!strcmp(argv[i],"-delta"))
		{
			delta = atoi(argv[i+1]);
			i++;
		}
		if(!strcmp(argv[i],"-size"))
		{
			tam_vetor = atoi(argv[i+1]);
			i++;
		}
        if(!strcmp(argv[i],"-d"))
            debug = 1;
	}

    if ( my_rank != 0 )
    {
        MPI_Probe(my_father(my_rank), MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &tam_vetor);  //descubro o tamanho da mensagem a ser recebida
        vetor = malloc (tam_vetor*sizeof(int)); //aloco um vetor com este tamanho
        MPI_Recv (vetor, tam_vetor, MPI_INT, my_father(my_rank), MPI_ANY_TAG, MPI_COMM_WORLD, &status); // recebo o vetor
    }
    else
    {
        vetor = malloc (tam_vetor*sizeof(int)); //aloco este vetor
        Inicializa (vetor, tam_vetor );// preencho o vetor de fora decrescente
        t1 = MPI_Wtime();
    }

    // dividir ou conquistar?
    if ( tam_vetor <= delta )
        qsort(vetor,tam_vetor, sizeof(int), cmpfunc);//conquisto ordedando o vetor
    else
    {
        int *my_job, *job1, *job2;
        int my_job_sz, job1_sz, job2_sz;

        my_job_sz = tam_vetor/(((int)ceil((double)tam_vetor/delta)<<1)-1);
        job1_sz = (tam_vetor-my_job_sz)/2;
        job2_sz = tam_vetor - (my_job_sz+job1_sz);

        if(debug) printf("M %d J1 %d J2 %d\n", my_job_sz, job1_sz, job2_sz);

        my_job = malloc(my_job_sz*sizeof(int));
        job1 = malloc(job1_sz*sizeof(int));
        job2 = malloc(job2_sz*sizeof(int));

        my_job = vetor;
        job1 = &vetor[my_job_sz];
        job2 = &vetor[my_job_sz+job1_sz];

        MPI_Send (job1, job1_sz, MPI_INT, (my_rank*2)+1, SEND, MPI_COMM_WORLD );  // mando metade inicial do vetor
        MPI_Send (job2, job2_sz, MPI_INT, (my_rank*2)+2, SEND, MPI_COMM_WORLD);  // mando metade final

		qsort(my_job,my_job_sz, sizeof(int), cmpfunc);

        MPI_Recv (job1, job1_sz, MPI_INT,(my_rank*2)+1,MPI_ANY_TAG,MPI_COMM_WORLD, &status);//recebo metade do vetor
        MPI_Recv (job2, job2_sz, MPI_INT, (my_rank*2)+2,MPI_ANY_TAG,MPI_COMM_WORLD, &status);//recebo o resto

        vetor = interleaving(my_job, my_job_sz, job1, job1_sz, job2, job2_sz); //intercalo este

        free(my_job);
    }

    // mando para o pai
    if ( my_rank !=0 )
        MPI_Send (vetor,tam_vetor,MPI_INT,my_father(my_rank),SEND, MPI_COMM_WORLD);//mando meu vetor para o pai
    else
    {
        t2 = MPI_Wtime();
        if(debug) printfv(vetor,tam_vetor);
		printf("Run time: %lf\n", t2-t1);
    }

    free(vetor);
    MPI_Finalize();
    return 0;
}
