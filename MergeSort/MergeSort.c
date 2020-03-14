#include "ivector.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void mostrarVector(ivector vector, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf(" %d", vector[i]);
    }
    printf("\n");
}

void insercion(ivector vector, int posInicial, int posFinal)
{
    int i, j, temp;
    for (i = posInicial; i <= posFinal; i++)
    {
        temp = vector[i];
        j = i - 1;
        while (j >= 0 && vector[j] > temp)
        {
            vector[j + 1] = vector[j];
            j--;
        }

        vector[j + 1] = temp;
    }
}

void MergeSort(ivector vector, int posInicial, int posFinal){
    int tam = posFinal-posInicial+1;
    if(tam<=4){
        insercion(vector, posInicial, posFinal);
    }
    else{
        MergeSort(vector, posInicial, (posFinal+posInicial+1)/2-1);
        mostrarVector(vector, tam);
        MergeSort(vector, (posFinal+posInicial+1)/2, posFinal);
        mostrarVector(vector, tam);
    }
}

int main()
{
    int size = 16;
    ivector vector = icreavector(size);
    srand(3000);
    for (int i = 0; i < size; i++)
    {
        vector[i] = rand() % 100;
    }
    mostrarVector(vector, size);
    MergeSort(vector, 0, size - 1);
    mostrarVector(vector, size);
}