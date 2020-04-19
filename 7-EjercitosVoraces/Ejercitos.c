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
* Método auxiliar para intercambiar dos posiciones de un vector.
*/
void intercambia(ivector v, int pos1, int pos2)
{
    int aux = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = aux;
}

/**
 * Empareja cada aliado con el "menor" adversario de los que puede vencer. En el caso de que no haya ninguno, se empareja con el mayor ejercito enemigo.
 */
void heuristicaVoraz(ivector enemigos, ivector aliados)
{
    for (int i = 0; i < TAM; i++)
    {
        int posMejor = -1;
        int mejorActual = -1;
        int mayor = -1;
        int posMayor = -1;
        for (int j = i; j < TAM; j++)
        {
            if (enemigos[j] <= aliados[i] && enemigos[j] > mejorActual)
            {
                mejorActual = enemigos[j];
                posMejor = j;
            }
            if (enemigos[j] > mayor)
            {
                mayor = enemigos[j];
                posMayor = j;
            }
        }
        if (mejorActual != -1)
        {
            printf("El ejercito %d aliado combatira contra el ejercito %d enemigo\n", i, posMejor);
            intercambia(enemigos, posMejor, i);
        }
        else
        {
            printf("El ejercito %d aliado combatira contra el ejercito %d enemigo\n", i, posMayor);
            intercambia(enemigos, posMayor, i);
        }
    }
}

/**
 * Ordena ambos vectores de menor a mayor, de manera que el menor ejercito de los aliados combatiran contra el menor ejercito de los enemigos, el mayor de los aliados con el mayor de los enemigos...
 */
void heuristicaVoraz2(ivector enemigos, ivector aliados)
{
    qsort(enemigos, TAM, sizeof(int), compareTo);
    qsort(aliados, TAM, sizeof(int), compareTo);
}

int main()
{
    srand(1);
    ivector enemigos = icreavector(TAM);
    ivector aliados = icreavector(TAM);

    for (int i = 0; i < TAM; i++)
    {
        enemigos[i] = rand() % 9 + 1;
        aliados[i] = rand() % 9 + 1;
    }
    printf("\nEstado inicial\n");
    mostrarVector(enemigos);
    mostrarVector(aliados);

    //heuristicaVoraz(enemigos, aliados);
    heuristicaVoraz2(enemigos, aliados);

    printf("\nEstado final\n");
    mostrarVector(enemigos);
    mostrarVector(aliados);
}
