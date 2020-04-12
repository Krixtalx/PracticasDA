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
        while (j >= posInicial && vector[j] > temp)
        {
            vector[j + 1] = vector[j];
            j--;
        }

        vector[j + 1] = temp;
    }
}

void Merge(ivector vector, int posInicial, int posFinal)
{
    int tam = posFinal - posInicial + 1;
    int mitad = (posFinal + posInicial + 1) / 2;
    int i = posInicial;
    int j = mitad;
    int k = 0;
    ivector aux = icreavector(tam);
    while (i < mitad && j <= posFinal && k < tam)
    {
        if (vector[i] < vector[j])
        {
            aux[k] = vector[i];
            i++;
        }
        else
        {
            aux[k] = vector[j];
            j++;
        }
        k++;
    }
    if (k < tam)
    {
        while (i < mitad)
        {
            aux[k] = vector[i];
            i++;
            k++;
        }
        while (j <= posFinal)
        {
            aux[k] = vector[j];
            j++;
            k++;
        }
    }
    int k2 = 0;
    for (int i = posInicial; i <= posFinal; i++)
    {
        vector[i] = aux[k2];
        k2++;
    }
    ifreevector(&aux);
}

void MergeSort(ivector vector, int posInicial, int posFinal)
{
    int tam = posFinal - posInicial + 1;
    if (tam <= 4)
    {
        insercion(vector, posInicial, posFinal);
    }
    else
    {
        MergeSort(vector, posInicial, (posFinal + posInicial + 1) / 2 - 1);
        MergeSort(vector, (posFinal + posInicial + 1) / 2, posFinal);
        Merge(vector, posInicial, posFinal);
    }
}
/**
 * Algoritmo de busqueda binaria. Devuelve la pos donde se encuentra el dato. Si no se encuentra, devuelve -1
 * @pre: Es necesario que el vector que se pasa como parámetro se encuentre ordenado
 */
int BBin(int buscado, ivector vector, int posInicial, int posFinal)
{
    int mitad = (posInicial + posFinal+1) / 2;
    if (buscado < vector[mitad])
    {
        return BBin(buscado, vector, posInicial, mitad-1);
    }
    else if (buscado > vector[mitad])
    {
        return BBin(buscado, vector, mitad, posFinal);
    }
    else
    {
        if (buscado == vector[mitad])
            return mitad;
        else
        {
            return -1;
        }
    }
}

int main()
{
    const int size = 10;
    const int buscado = 7;
    ivector vector = icreavector(size);
    srand(6810);
    for (int i = 0; i < size; i++)
    {
        vector[i] = rand() % (buscado + 5);
    }

    mostrarVector(vector, size);
    MergeSort(vector, 0, size - 1);
    mostrarVector(vector, size);
    int resultado = BBin(buscado, vector, 0, size - 1);
    printf("Encontrado en pos %d", resultado);
    ifreevector(&vector);
}