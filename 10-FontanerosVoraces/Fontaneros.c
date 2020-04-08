#include "ivector.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 10

struct trabajo
{
    int cliente;
    int tiempo;
};
typedef struct trabajo trabajos;

int compare(const void *_a, const void *_b)
{

    struct trabajo *a, *b;

    a = (struct trabajo *)_a;
    b = (struct trabajo *)_b;

    return ((*a).tiempo - (*b).tiempo);
}

void mostrarVector(trabajos *vTrabajos, int tam)
{
    printf("Clientes: ");
    for (int i = 0; i < tam; i++)
    {
        printf(" %d", vTrabajos[i].cliente);
    }
    printf("\n");

    printf("Tiempos:  ");
    for (int i = 0; i < tam; i++)
    {
        printf(" %d", vTrabajos[i].tiempo);
    }
    printf("\n");
}

int main()
{

    trabajos vTrabajos[TAM];
    srand(6810);
    for (int i = 0; i < TAM; i++)
    {
        vTrabajos[i].cliente = i;
        vTrabajos[i].tiempo = rand() % 19 + 1;
    }

    mostrarVector(vTrabajos, TAM);
    qsort(vTrabajos, TAM, sizeof(trabajos), &compare);
    mostrarVector(vTrabajos, TAM);
}