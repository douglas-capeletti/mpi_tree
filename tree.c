#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

int merge(int a[], int b[], int n)
{
    int c[n * 2];
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        if (a[j] <= b[k])
        {
            c[i] = a[j];
            j++;
        }
        else
        {
            c[i] = b[k];
            k++;
        }
    }
}

int main(int argc, char **argv)
{
    int my_rank;  // Identificador do processo
    int tag = 50; // Tag para as mensagens

    int vetor[SIZE]; // Buffer para as mensagens
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // pega o numero do processo atual (rank)

    int actual_size;
    int delta = 500000;

    // recebo vetor
    if (my_rank != 0)
    {
        MPI_Recv(vetor, actual_size, MPI_INT, (my_rank - 1) / 2, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Get_count(MPI_STATUS_IGNORE, MPI_INT, &actual_size);
    }
    else
    {
        int i;
        actual_size = SIZE;
        for (i = 0; i < SIZE; i++)
            vetor[i] = SIZE - i;
    }

    // dividir ou conquistar?
    if (actual_size <= delta)
    {
        bubbleSort(vetor, actual_size);
    }
    else
    {
        // dividir - quebrar em duas partes e mandar para os filhos
        // printf("RANK: %d \n", my_rank);
        MPI_Send(&vetor[0], actual_size / 2, MPI_INT, (my_rank * 2) + 1, tag, MPI_COMM_WORLD);
        MPI_Send(&vetor[actual_size / 2], actual_size / 2, MPI_INT, (my_rank * 2) + 2, tag, MPI_COMM_WORLD);

        // receber dos filhos
        MPI_Recv(&vetor[0], actual_size / 2, MPI_INT, (my_rank * 2) + 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&vetor[actual_size / 2], actual_size / 2, MPI_INT, (my_rank * 2) + 2, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // intercalo vetor inteiro
        merge(&vetor[0], &vetor[actual_size / 2], actual_size);
    }

    if (my_rank != 0)
    {
        // printf("RANK: %d \n", my_rank);
        MPI_Send(vetor, actual_size, MPI_INT, (my_rank - 1) / 2, tag, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
            printf("%2d  ", vetor[i]);
        printf("\n");
    }

    MPI_Finalize();
}