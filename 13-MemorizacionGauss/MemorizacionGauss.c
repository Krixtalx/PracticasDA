#include "ivector.h"
#include <stdio.h>
#include <stdlib.h>

int funcion(int n)
{
    ivector memoria = icreavector(4);
    memoria[0] = 0;
    memoria[1] = 3;
    memoria[2] = 13;
    memoria[3] = 34;

    for (int i = 4; i < n; i++)
    {
        memoria[i % 4] = 4 * memoria[(i - 1) % 4] - 6 * memoria[(i - 2) % 4] + 4 * memoria[(i - 3) % 4] - memoria[(i - 4) % 4];
        //printf("La cantidad maxima de operaciones que usa el algoritmo de Gauss para triangular una matriz de dimension %d es %d\n", i + 1, memoria[i % 4]);
    }
    int resultado = memoria[(n - 1) % 4];
    ifreevector(&memoria);
    return resultado;
}

int main()
{
    int dimension = 25;
    int resultado = funcion(dimension);
    printf("La cantidad maxima de operaciones que usa el algoritmo de Gauss para triangular una matriz de dimension %d es %d\n", dimension, resultado);
}