#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#DEFINE N = 1000000
#DEFINE MIN = 1
#DEFINE MAX = 100

int[N] randVector()
{
    srand(time(NULL));
    int vector[N] = [];
    for (i = 0; i < N; i++)
    {
        vector[i] = random_number(MIN, MAX)
    }
    return vector;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void BubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

int main(int argc, char **argv)
{
    MPI_Init();
    my_rank = MPI_Comm_rank(); // pega o numero do processo atual (rank)
    int delta = 2;

    if (my_rank != 0)
    {                                                // recebo vetor
        MPI_Recv(vetor, pai);                        // não sou a raiz, tenho pai
        MPI_Get_count(&Status, MPI_INT, &tam_vetor); // descubro tamanho da mensagem recebida
    }
    else
    {
        tam_vetor = N;                // defino tamanho inicial do vetor
        int vector[N] = randVector(); // sou a raiz e portanto gero o vetor - ordem reversa
    }

    // dividir ou conquistar?
    if (tam_vetor <= delta)
    {
        int size = sizeof(vetor) / sizeof(vetor[0]);
        BubbleSort(vetor, size); // conquisto
    }

    else
    {
        // quebrar em duas partes e mandar para os filhos
        MPI_Send(&vetor[0], &vetor[0], tam_vetor / 2);             // mando metade inicial do vetor
        MPI_Send(&vetor[tam_vetor / 2], &vetor[0], tam_vetor / 2); // mando metade final

        // receber dos filhos
        MPI_Recv(&vetor[0], &vetor[0]);
        MPI_Recv(&vetor[tam_vetor / 2], &vetor[tam_vetor / 2]);

        // intercalo vetor inteiro
        Intercala(vetor);
    }

    MPI_Send(vetor, pai, tam_vetor); // tenho pai, retorno vetor ordenado pra ele
    else Mostra(vetor);              // sou o raiz, mostro vetor

    MPI_Finalize();
}
