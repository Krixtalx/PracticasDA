#include "ivector.h"
#include "imatriz2d.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 10

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

int maximo(int i, int j)
{
    if (i > j)
        return i;
    return j;
}

ivector botellon(imatriz2d matriz, ivector datos)
{
    for (int i = 0; i < TAM - 1; i++)
    {
        matriz[i][i + 1] = maximo(datos[i], datos[i + 1]);
    }

    for (int i = 3; i < TAM; i += 2)
    {
        for (int fila = 0; i + fila < TAM; fila++)
        {
            int columna = i + fila;
            int camino1 = 0;
            int camino2 = 0;
            if (datos[columna] > datos[fila + 1])
                camino1 = matriz[fila + 1][columna - 1];
            else if (datos[columna] < datos[fila + 1])
                camino1 = matriz[fila + 2][columna];

            if (datos[fila] > datos[columna - 1])
                camino2 = matriz[fila + 1][columna - 1];
            else if (datos[fila] < datos[columna - 1])
                camino2 = matriz[fila][columna - 2];

            matriz[fila][columna] = maximo(datos[fila] + camino1, datos[columna] + camino2);
        }
    }

    ivector solucion = icreavector(TAM);
    int fila = 0;
    int columna = TAM - 1;
    while (fila < columna)
    {
        //Listillo

        if (matriz[fila][columna] == datos[fila] + matriz[fila + 2][columna])
        {
            solucion[fila++] = 1;
        }
        else if (matriz[fila][columna] == datos[fila] + matriz[fila + 1][columna - 1])
        {
            solucion[fila++] = 1;
        }

        else if (matriz[fila][columna] == datos[columna] + matriz[fila + 1][columna - 1])
        {
            solucion[columna--] = 1;
        }
        else if (matriz[fila][columna] == datos[columna] + matriz[fila][columna + 2])
        {
            solucion[columna--] = 1;
        }

        //Agonioso

        if (datos[fila] > datos[columna])
            solucion[fila++] = 0;
        else
            solucion[columna--] = 0;
    }

    return solucion;
}

int main()
{
    ivector problema = icreavector(TAM);
    imatriz2d matriz = icreamatriz2d(TAM, TAM);
    int aux[] = {3, 15, 20, 45, 1, 2, 11, 10, 3, 1};
    for (int i = 0; i < TAM; i++)
    {
        problema[i] = aux[i];
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
    for (int i = 0; i < TAM; i++)
    {
        if (solucion[i] == 1)
        {
            valor += problema[i];
        }
    }

    printf("\nVasos: ");
    mostrarVector(problema);
    printf("\nMatriz de memorizacion: \n");
    mostrarMatriz(matriz);

    printf("\nSolucion:\n1->Listillo      0->Agonioso\n");
    mostrarVector(solucion);
    printf("Valor: %d", valor);

    ifreevector(&problema);
    ifreevector(&solucion);
    ifreematriz2d(&matriz);
}