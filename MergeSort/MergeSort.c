#include "ivector.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void intercambia(int *n1, int *n2)
{
    int aux = *n1;
    *n1 = *n2;
    *n2 = aux;
}

void mostrarVector(ivector vector, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf(" %d", vector[i]);
    }
    printf("\n");
}

ivector MergeSort(ivector vector, int posInicial, int posFinal)
{
    int tam = posFinal - posInicial+1;
    if (tam == 2)
    {
        if (vector[0] > vector[1])
        {
            intercambia(&vector[0], &vector[1]);
        }
        return vector;
    }
    else if (tam == 1)
        return vector;
    else
    {
        ivector izq = MergeSort(vector, posInicial, posFinal / 2);
        ivector der = MergeSort(vector, posFinal / 2 + 1, posFinal);
        int i = posInicial;
        int j = posFinal / 2;
        int k = 0;
        ivector aux = icreavector(tam);
        while (i < posFinal / 2 && j < posFinal)
        {
            if (izq[i] < der[j])
            {
                aux[k] = izq[i];
                i = i + 1;
            }
            else
            {
                aux[k] = der[j];
                j = j + 1;
            }
            k = k + 1;
        }
        return aux;
    }
}

int main()
{
    int size = 10;
    ivector vector = icreavector(size);
    srand(5000);
    for (int i = 0; i < size; i++)
    {
        vector[i] = rand() % 100;
    }
    mostrarVector(vector, size);
    ivector vectorOrdenado = MergeSort(vector, 0, size);
    mostrarVector(vectorOrdenado, size);
}