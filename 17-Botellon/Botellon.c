#include "ivector.h"
#include "imatriz2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 20

/**
* Método auxiliar para mostrar la matriz.
*/
void mostrarMatriz(imatriz2d matriz)
{
    for (int i = 0; i < TAM; i++)
    {

        for (int j = 0; j < TAM; j++)
        {
            printf("%*d", 5, matriz[i][j]);
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
        printf("%*d", 5, vector[i]);
    }
    printf("\n");
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
* Método auxiliar que devuelve el máximo de dos números.
*/
int maximo(int i, int j)
{
    if (i > j)
        return i;
    return j;
}

/**
 * Función que resuelve el problema del Botellon.
 * pre: Es necesario que no hayan datos repetidos. En caso de que haya datos repetidos, puede llegar a funcionar para valores pequeños.
 * Es recomendable pasar la matriz inicializada a 0, pero no es indispensable
 */
ivector botellon(imatriz2d matriz, ivector datos)
{
    //Inicializamos la matriz con los casos triviales
    for (int i = 0; i < TAM - 1; i++)
    {
        matriz[i][i + 1] = maximo(datos[i], datos[i + 1]);
    }

    //Completamos la matriz con el resto de resultados
    for (int i = 3; i < TAM; i += 2)
    {
        for (int fila = 0; i + fila < TAM; fila++)
        {
            int columna = i + fila;
            int camino1 = 0;
            int camino2 = 0;
            if (datos[columna] > datos[fila + 1])
                camino1 = matriz[fila + 1][columna - 1];
            else
                camino1 = matriz[fila + 2][columna];

            if (datos[fila] > datos[columna - 1])
                camino2 = matriz[fila + 1][columna - 1];
            else
                camino2 = matriz[fila][columna - 2];

            matriz[fila][columna] = maximo(datos[fila] + camino1, datos[columna] + camino2);
        }
    }

    //Construimos la solución al problema
    ivector solucion = icreavector(TAM);
    int fila = 0;
    int columna = TAM - 1;

    while (fila < columna)
    {
        bool camino1 = false;
        bool camino2 = false;
        int valorCam1, valorCam2;

        if (datos[fila + 1] > datos[columna])
            valorCam1 = datos[fila] + matriz[fila + 2][columna];
        else
        {
            valorCam1 = datos[fila] + matriz[fila + 1][columna - 1];
            camino1 = true;
        }

        if (datos[fila] > datos[columna - 1])
        {
            valorCam2 = datos[columna] + matriz[fila + 1][columna - 1];
        }
        else
        {
            valorCam2 = datos[columna] + matriz[fila][columna - 2];
            camino2 = true;
        }

        if (valorCam1 > valorCam2)
        {
            if (!camino1)
            {
                solucion[fila++] = 1;
                solucion[fila++] = 0;
            }
            else
            {
                solucion[fila++] = 1;
                solucion[columna--] = 0;
            }
        }
        else
        {
            if (!camino2)
            {
                solucion[columna--] = 1;
                solucion[fila++] = 0;
            }
            else
            {
                solucion[columna--] = 1;
                solucion[columna--] = 0;
            }
        }
    }

    return solucion;
}

int main()
{
    ivector problema = icreavector(TAM);
    imatriz2d matriz = icreamatriz2d(TAM, TAM);
    srand(1);
    for (int i = 0; i < TAM; i++)
    {
        problema[i] = i;
    }

    for (int i = 0; i < TAM; i++)
    {
        intercambia(problema, rand() % TAM, rand() % TAM);
    }

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            matriz[i][j] = 0;
        }
    }

    ivector solucion = botellon(matriz, problema);
    int valor = 0;
    int contador = 0;
    
    //Calculamos la cantidad de liquido y vasos que bebe Listillo según la solución
    for (int i = 0; i < TAM; i++)
    {
        if (solucion[i] == 1)
        {
            valor += problema[i];
            contador++;
        }
    }

    printf("\nVasos: ");
    mostrarVector(problema);
    printf("\nMatriz de memorizacion: %d\n", matriz[0][TAM - 1]);
    mostrarMatriz(matriz);

    printf("\nSolucion:\n1->Listillo      0->Agonioso\n");
    mostrarVector(solucion);
    printf("Valor: %d, %d", valor, contador);

    ifreevector(&problema);
    ifreevector(&solucion);
    ifreematriz2d(&matriz);
}