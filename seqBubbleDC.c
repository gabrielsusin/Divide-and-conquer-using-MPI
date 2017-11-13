/*-----------------------------------------------------------------------------
PONTIFÍCIA UNIVERSIDADE CATÓLICA DO RIO GRANDE DO SUL
PROGRAMAÇÃO PARALELA E DISTRIBUIDA - ENGENHARIA DE COMPUTAÇÃO
Gabriel Fasoli Susin - gabriel.susin@acad.pucrs.br
Augusto Bergamin - augusto.bergamin@acad.pucrs.br
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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


int main(int argc, char** argv){
    int tam_vetor;
    int *vetor;
    clock_t t1, t2;

    int i;
	for(i=0; i<argc; i++)
	{
		if(!strcmp(argv[i],"-size"))
		{
			tam_vetor = atoi(argv[i+1]);
			i++;
		}
	}

    vetor = malloc (tam_vetor*sizeof(int)); //aloco um vetor com este tamanho
    Inicializa(vetor,tam_vetor);

    t1 = clock();
    bs(tam_vetor,vetor);
    t2 = clock();

    printf("Run time: %lf\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    return 0;
    }
