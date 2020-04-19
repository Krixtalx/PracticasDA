#include "ivector.h"
#include <stdlib.h>
#include <stdio.h>

#define TAM 10

/**
* Método auxiliar para mostrar el vector.
*/
void mostrarVector(ivector vector)
{

    for (int i = 0; i < TAM; i++)
    {
        printf(" %d", vector[i]);
    }
    printf("\n");
}

/**
 * Función de comparación para los elementos del vector
 */
int compareTo(const void *_a, const void *_b)
{

    int *a, *b;

    a = (int *)_a;
    b = (int *)_b;

    return ((*a) - (*b));
}

int main()
{
    srand(1);
    ivector inicio = icreavector(TAM);
    ivector duracion = icreavector(TAM);
}