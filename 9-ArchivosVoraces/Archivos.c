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

/**
 * Heuristica que intenta maximizar el numero de archivo que se almacenan
 */
void heuristicaArchivos(ivector archivos, int tamAlmacenamiento)
{
    qsort(archivos, TAM, sizeof(int), &compareTo);
    int posActual = 0;
    while (tamAlmacenamiento > 0)
    {
        if (archivos[posActual] <= tamAlmacenamiento)
        {
            tamAlmacenamiento -= archivos[posActual];
            printf("Se ha introducido un archivo con tamano %d. Tamano restante: %d\n", archivos[posActual], tamAlmacenamiento);
            posActual++;
        }
        else
        {
            tamAlmacenamiento = -1;
        }
    }
}

/**
 * Heuristica que intenta maximizar el tamaño de los archivos que se almacenan
 */
void heuristicaArchivos2(ivector archivos, int tamAlmacenamiento)
{
    qsort(archivos, TAM, sizeof(int), &compareTo);
    int posActual = TAM - 1;
    while (tamAlmacenamiento > 0)
    {
        if (archivos[posActual] <= tamAlmacenamiento)
        {
            tamAlmacenamiento -= archivos[posActual];
            printf("Se ha introducido un archivo con tamano %d. Tamano restante: %d\n", archivos[posActual], tamAlmacenamiento);
            posActual--;
        }
        else
        {
            tamAlmacenamiento = -1;
        }
    }
}

int main()
{
    srand(1);
    int limite = 20;
    int tamAlmacenamiento = 75;
    ivector archivos = icreavector(TAM);

    for (int i = 0; i < TAM; i++)
    {
        archivos[i] = rand() % limite + 1;
    }
    printf("\nHeuristica 1\n");
    heuristicaArchivos(archivos, tamAlmacenamiento);
    printf("\nHeuristica 2\n");
    heuristicaArchivos2(archivos, tamAlmacenamiento);

    ifreevector(&archivos);
}