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

int main()
{
}