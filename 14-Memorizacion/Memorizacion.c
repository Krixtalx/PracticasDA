#include "ivector.h"
#include <stdio.h>
#include <stdlib.h>

int AlgoritmoPDin(int n)
{
    ivector memoria = icreavector(2);
    memoria[0] = 3;
    memoria[1] = 3;

    for (int i = 2; i < n; i++)
    {
        if (i % 2 == 1)
            memoria[i % 2] = memoria[(i - 1) % 2] - 3;
        else
            memoria[i % 2] = memoria[i % 2] + 3;

        //printf("El calculo para el termino %d es %d\n", i+1, memoria[i % 2]);
    }
    int resultado = memoria[(n - 1) % 2];
    ifreevector(&memoria);
    return resultado;
}

int main()
{
    int termino = 20;
    int resultado = AlgoritmoPDin(termino);
    printf("El calculo para el termino %d es %d\n", termino, resultado);
}