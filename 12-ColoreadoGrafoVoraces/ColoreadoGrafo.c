#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "imatriz2d.h"
#include "ivector.h"

#define TAM 6

/**
* Método auxiliar para mostrar la matriz.
*/
void mostrarMatriz(imatriz2d matriz)
{
    for (int i = 0; i < TAM; i++)
    {

        for (int j = 0; j < TAM; j++)
        {
            printf("%d ", matriz[i][j]);
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
        printf("%d ", vector[i]);
    }
    printf("\n");
}

/**
* Método auxiliar para rellenar la matriz.
*/
void rellenaMatriz(imatriz2d matriz)
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            int aux = rand() % 2;
            matriz[i][j] = aux;
            matriz[j][i] = aux;
        }
        matriz[i][i] = 0;
    }
}

/**
* Heuristica Voraz para el coloreado de un grafo. Intenta colorear un grafo usando el menor nº de colores posible. La solución estará contenida en el vector "coloreado" y tendrá el siguiente formato: ivector[nodo]=color
* return int. Devuelve el nº de coloraciones empleadas. En un caso ideal, este nº coincidirá con el nº cromático del grafo
*/
int heuristicaVoraz(imatriz2d matriz, ivector coloreado)
{
    int max = -1;
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if (matriz[i][j] == 1 && coloreado[j] == coloreado[i])
            {
                coloreado[j]++;
                if(coloreado[j]>max)
                    max = coloreado[j];
            }
        }
    }
    return max + 1;
}

int main()
{
    srand(6);
    imatriz2d matriz = icreamatriz2d(TAM, TAM);
    ivector coloreado = icreavector(TAM);
    for (int i = 0; i < TAM; i++)
    {
        coloreado[i] = 0;
    }
    rellenaMatriz(matriz);

    mostrarMatriz(matriz);
    int nColoreado = heuristicaVoraz(matriz, coloreado);
    printf("\nSolucion: ");
    mostrarVector(coloreado);
    printf("N coloracion: %d", nColoreado);

    ifreematriz2d(&matriz);
}