#include "ivector.h"
#include "imatriz2d.h"
#include <stdlib.h>
#include <stdio.h>

#define TAM 10

struct Conferencia
{
    int id;
    int comienzo;
    int fin;
};
typedef struct Conferencia Conferencia;

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
 * Función de comparación para los elementos del vector. Compara el campo comienzo del struct Conferencia.
 */
int compareToComienzo(const void *_a, const void *_b)
{

    Conferencia *a, *b;

    a = (Conferencia *)_a;
    b = (Conferencia *)_b;

    return ((*a).comienzo - (*b).comienzo);
}

/**
 * Función de comparación para los elementos del vector. Compara el campo fin del struct Conferencia.
 */
int compareToFin(const void *_a, const void *_b)
{

    Conferencia *a, *b;

    a = (Conferencia *)_a;
    b = (Conferencia *)_b;

    return ((*a).fin - (*b).fin);
}

/**
 * Función de comparación para los elementos del vector. Calcula y compara la duración y en caso de ser iguales compara el campo Comienzo.
 */
int compareToDuracion(const void *_a, const void *_b)
{

    Conferencia *a, *b;

    a = (Conferencia *)_a;
    b = (Conferencia *)_b;

    int duracionA, duracionB;
    duracionA = (*a).fin - (*a).comienzo;
    duracionB = (*b).fin - (*b).comienzo;

    if (duracionA != duracionB)
    {
        return duracionA - duracionB;
    }

    return ((*a).comienzo - (*b).comienzo);
}

/**
 * Heuristica voraz para la asignación de salas. Para ello, recorre el vector de conferencias y si la conferencia "actual" puede encuadrarse en alguna sala, se asignará, si no, se abrirá una nueva sala.
 * Antes de realizar la asignación, se reordena el vector de conferencias en base a la hora de comienzo
 */
void HeuristicaComienzo(Conferencia Conferencias[])
{
    qsort(Conferencias, TAM, sizeof(Conferencia), compareToComienzo);
    ivector salas = icreavector(TAM);
    salas[0] = Conferencias[0].fin;
    printf("\nSe abre la sala %d para la conferencia %d de %d a %d\n", 0, Conferencias[0].id, Conferencias[0].comienzo, Conferencias[0].fin);
    int salasOcupadas = 1;

    for (int i = 1; i < TAM; i++)
    {
        int j;
        for (j = 0; j < salasOcupadas; j++)
        {
            if (salas[j] <= Conferencias[i].comienzo)
            {
                salas[j] = Conferencias[i].fin;
                printf("Se apunta la conferencia %d de %d a %d a la sala %d\n", Conferencias[i].id, Conferencias[i].comienzo, Conferencias[i].fin, j);
                j = salasOcupadas;
            }
        }
        if (j - 1 != salasOcupadas)
        {
            salas[salasOcupadas] = Conferencias[i].fin;
            printf("Se abre la sala %d para la conferencia %d de %d a %d\n", salasOcupadas, Conferencias[i].id, Conferencias[i].comienzo, Conferencias[i].fin);
            salasOcupadas++;
        }
    }
    ifreevector(&salas);
}

/**
 * Heuristica voraz para la asignación de salas. Para ello, recorre el vector de conferencias y si la conferencia "actual" puede encuadrarse en alguna sala, se asignará, si no, se abrirá una nueva sala.
 * Antes de realizar la asignación, se reordena el vector de conferencias en base a la hora de finalizacion
 */
void HeuristicaFin(Conferencia Conferencias[])
{
    qsort(Conferencias, TAM, sizeof(Conferencia), compareToFin);
    ivector salas = icreavector(TAM);
    salas[0] = Conferencias[0].fin;
    printf("\nSe abre la sala %d para la conferencia %d de %d a %d\n", 0, Conferencias[0].id, Conferencias[0].comienzo, Conferencias[0].fin);
    int salasOcupadas = 1;

    for (int i = 1; i < TAM; i++)
    {
        int j;
        for (j = 0; j < salasOcupadas; j++)
        {
            if (salas[j] <= Conferencias[i].comienzo)
            {
                salas[j] = Conferencias[i].fin;
                printf("Se apunta la conferencia %d de %d a %d a la sala %d\n", Conferencias[i].id, Conferencias[i].comienzo, Conferencias[i].fin, j);
                j = salasOcupadas;
            }
        }
        if (j - 1 != salasOcupadas)
        {
            salas[salasOcupadas] = Conferencias[i].fin;
            printf("Se abre la sala %d para la conferencia %d de %d a %d\n", salasOcupadas, Conferencias[i].id, Conferencias[i].comienzo, Conferencias[i].fin);
            salasOcupadas++;
        }
    }
    ifreevector(&salas);
}

/**
 * Heuristica voraz para la asignación de salas. Para ello, recorre el vector de conferencias y si la conferencia "actual" puede encuadrarse en alguna sala, se asignará, si no, se abrirá una nueva sala.
 * Antes de realizar la asignación, se reordena el vector de conferencias en base a la hora de comienzo
 */
void HeuristicaDuracion(Conferencia Conferencias[])
{
    qsort(Conferencias, TAM, sizeof(Conferencia), compareToDuracion);
    imatriz2d salas = icreamatriz2d(2, TAM);
    salas[0][0] = Conferencias[0].comienzo;
    salas[1][0] = Conferencias[0].fin;
    printf("\nSe abre la sala %d para la conferencia %d de %d a %d\n", 0, Conferencias[0].id, Conferencias[0].comienzo, Conferencias[0].fin);
    int salasOcupadas = 1;

    for (int i = 1; i < TAM; i++)
    {
        int j;
        for (j = 0; j < salasOcupadas; j++)
        {
            if (salas[0][j] >= Conferencias[i].fin)
            {
                salas[0][j] = Conferencias[i].comienzo;
                printf("Se apunta la conferencia %d de %d a %d a la sala %d\n", Conferencias[i].id, Conferencias[i].comienzo, Conferencias[i].fin, j);
                j = salasOcupadas;
            }
            else if (salas[1][j] <= Conferencias[i].comienzo)
            {
                salas[1][j] = Conferencias[i].fin;
                printf("Se apunta la conferencia %d de %d a %d a la sala %d\n", Conferencias[i].id, Conferencias[i].comienzo, Conferencias[i].fin, j);
                j = salasOcupadas;
            }
        }
        if (j - 1 != salasOcupadas)
        {
            salas[0][salasOcupadas] = Conferencias[i].comienzo;
            salas[1][salasOcupadas] = Conferencias[i].fin;
            printf("Se abre la sala %d para la conferencia %d de %d a %d\n", salasOcupadas, Conferencias[i].id, Conferencias[i].comienzo, Conferencias[i].fin);
            salasOcupadas++;
        }
    }
    ifreematriz2d(&salas);
}

/**
 * "Heuristica" adaptada a la situación actual.
 */
void HeuristicaBroma()
{
    printf("Señor, Usted cree que es momento de planificar eventos culturales?");
}

int main()
{
    srand(1);
    Conferencia Conferencias[TAM] = {{0, 1000, 1100}, {1, 930, 1100}, {2, 1030, 1200}, {3, 1200, 1400}, {4, 1100, 1300}, {5, 900, 1030}, {6, 800, 930}, {7, 900, 1230}, {8, 1200, 1230}, {9, 1300, 1430}};
    printf("\n Heuristica Comienzo \n");
    HeuristicaComienzo(Conferencias);

    printf("\n Heuristica Fin \n");
    HeuristicaFin(Conferencias);

    printf("\n Heuristica Duracion \n");
    HeuristicaDuracion(Conferencias);
}