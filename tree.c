
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000
#define DELTA 31250 // 32 nodos folha

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int tam, int *arr)
{
    int i, j;
    for (i = 0; i < tam - 1; i++)
        for (j = 0; j < tam - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

int *merge(int tam, int vetor[])
{
    int *vetor_auxiliar;
    int i1, i2, i_aux;

    vetor_auxiliar = (int *)malloc(sizeof(int) * tam);

    i1 = 0;
    i2 = tam / 2;

    for (i_aux = 0; i_aux < tam; i_aux++)
    {
        if (((vetor[i1] <= vetor[i2]) && (i1 < (tam / 2))) || (i2 == tam))
            vetor_auxiliar[i_aux] = vetor[i1++];
        else
            vetor_auxiliar[i_aux] = vetor[i2++];
    }

    return vetor_auxiliar;
}

int main(int argc, char **argv)
{
    MPI_Status status, upperStatus;

    MPI_Init(&argc, &argv);

    int my_rank, proc_n;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n);

    double initial_time = MPI_Wtime();

    int vetor[ARRAY_SIZE];
    int *new_vector;
    int i, current_size;

    int left_node = 2 * my_rank + 1;
    int right_node = 2 * my_rank + 2;

    if (my_rank != 0)
    {
        MPI_Recv(vetor, ARRAY_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &upperStatus);
        MPI_Get_count(&upperStatus, MPI_INT, &current_size);
    }
    else
    {
        for (i = 0; i < ARRAY_SIZE; i++)
            vetor[i] = ARRAY_SIZE - i;
        current_size = ARRAY_SIZE;
    }
    if (current_size > DELTA)
    {
        MPI_Send(&vetor[0], current_size / 2, MPI_INT, left_node, 1, MPI_COMM_WORLD);
        MPI_Send(&vetor[current_size / 2], current_size / 2, MPI_INT, right_node, 1, MPI_COMM_WORLD);

        MPI_Recv(&vetor[0], current_size / 2, MPI_INT, left_node, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&vetor[current_size / 2], current_size / 2, MPI_INT, right_node, 1, MPI_COMM_WORLD, &status);

        new_vector = merge(current_size, vetor);
    }
    else
    {
        bubbleSort(current_size, vetor);
        new_vector = vetor;
    }

    if (my_rank != 0)
    {
        MPI_Send(new_vector, current_size, MPI_INT, upperStatus.MPI_SOURCE, 1, MPI_COMM_WORLD);
    }
    else
    {
        printf("\nTempo de execucao: %.4f s\n", MPI_Wtime() - initial_time);
    }
    MPI_Finalize();
    return 0;
}