#include "ivector.h"
#include "imatriz2d.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 10

/**
* Método auxiliar para mostrar la matriz.
*/
void mostrarMatriz(imatriz2d matriz)
{
    for (int i = 0; i < TAM; i++)
    {

        for (int j = 0; j < TAM; j++)
        {
            printf("%*d", 5, matriz[i][j]);
        }
        printf("\n");
    }
}

/**
* Método auxiliar para mostrar el vector.
*/
void mostrarVector(ivector vector)
{

    for (int i = 0; i < TAM; i++)
    {
        printf("%*d", 5, vector[i]);
    }
    printf("\n");
}

int maximo(int i, int j)
{
    if (i > j)
        return i;
    return j;
}

ivector botellon(imatriz2d matriz, ivector datos)
{
    ivector solucion = icreavector(TAM);
    solucion[TAM - 1] = 0;
    for (int i = 0; i < TAM - 1; i++)
    {
        solucion[i] = 0;
        matriz[i][i + 1] = maximo(datos[i], datos[i + 1]);
    }

    for (int i = 3; i < TAM; i += 2)
    {
        for (int j = 0; i + j < TAM; j++)
        {
            int k = i + j;
            int camino1 = maximo(matriz[j + 1][k - 1], matriz[j + 2][k]);
            int camino2 = maximo(matriz[j + 1][k - 1], matriz[j][k - 2]);
            matriz[j][k] = maximo(datos[j] + camino1, datos[k] + camino2);
        }
    }

    return solucion;
}

int main()
{
    ivector problema = icreavector(TAM);
    imatriz2d matriz = icreamatriz2d(TAM, TAM);
    int aux[] = {6, 4, 7, 9, 10, 2, 3, 3, 4, 8};
    for (int i = 0; i < TAM; i++)
    {
        problema[i] = aux[i];
    }
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            matriz[i][j] = 0;
        }
    }

    ivector solucion = botellon(matriz, problema);
    printf("\nVasos: ");
    mostrarVector(problema);
    printf("\nMatriz de memorizacion: \n");
    mostrarMatriz(matriz);

    printf("\nSolucion: \n");
    mostrarVector(solucion);

    ifreevector(&problema);
    ifreevector(&solucion);
    ifreematriz2d(&matriz);
}