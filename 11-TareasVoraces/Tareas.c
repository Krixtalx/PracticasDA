#include "ivector.h"
#include "imatriz2d.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TAM 4

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
* Método auxiliar para rellenar la matriz.
*/
void rellenaMatriz(imatriz2d matriz)
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            int aux = rand() % 8 + 1;
            matriz[i][j] = aux;
        }
    }
}
/**
 * Heuristica voraz para la matriz de Tiempos. Intenta devolver la solución que minimiza el tiempo empleado. Para ello, elige la tarea mas rápida disponible para cada alumno.
 * return ivector La solución al problema. Su formato es el siguiente: ivector[alumno]=tarea
 */
ivector HeuristicaTiempos(imatriz2d tiempo)
{
    ivector solucion = icreavector(TAM);
    bool usados[TAM];
    for (int i = 0; i < TAM; i++)
    {
        usados[i] = false;
    }

    for (int i = 0; i < TAM; i++)
    {
        int menor = 999999;
        int posMenor = -1;
        for (int j = 0; j < TAM; j++)
        {
            if (tiempo[i][j] < menor && !usados[j])
            {
                menor = tiempo[i][j];
                posMenor = j;
            }
        }
        usados[posMenor] = true;
        solucion[i] = posMenor;
    }
    return solucion;
}

/**
 * Heuristica voraz para la matriz de Eficiencia. Intenta devolver la solución que maximiza la eficiencia. Para ello, elige la tarea mas eficiente disponible para cada alumno.
 * return ivector La solución al problema. Su formato es el siguiente: ivector[alumno]=tarea
 */
ivector HeuristicaEficiencia(imatriz2d eficiencia)
{
    ivector solucion = icreavector(TAM);
    bool usados[TAM];
    for (int i = 0; i < TAM; i++)
    {
        usados[i] = false;
    }

    for (int i = 0; i < TAM; i++)
    {
        int mayor = -1;
        int posMayor = -1;
        for (int j = 0; j < TAM; j++)
        {
            if (eficiencia[i][j] > mayor && !usados[j])
            {
                mayor = eficiencia[i][j];
                posMayor = j;
            }
        }
        usados[posMayor] = true;
        solucion[i] = posMayor;
    }
    return solucion;
}

int main()
{
    srand(2);
    imatriz2d tiempo = icreamatriz2d(TAM, TAM);
    imatriz2d eficiencia = icreamatriz2d(TAM, TAM);

    rellenaMatriz(tiempo);
    rellenaMatriz(eficiencia);

    //mostrarMatriz(tiempo);
    mostrarMatriz(eficiencia);

    //ivector solucion = HeuristicaTiempos(tiempo);
    ivector solucion = HeuristicaEficiencia(eficiencia);

    printf("\nSolucion: ");
    mostrarVector(solucion);

    ifreematriz2d(&tiempo);
    ifreematriz2d(&eficiencia);
    ifreevector(&solucion);
}