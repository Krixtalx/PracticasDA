#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "imatriz2d.h"

#define TAM 1024

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

void validarMatriz(imatriz2d matriz)
{
    for (int i = 0; i < TAM; i++)
    {
        bool usados[TAM];
        for (int j = 0; j < TAM; j++)
        {
            usados[j] = false;
        }
        for (int j = 0; j < TAM; j++)
        {
            if (usados[matriz[j][i] - 1] || matriz[i][j] > TAM)
            {
                printf("Falla en la fila %d, columna %d\n", j, i);
                return;
            }
            else
                usados[matriz[j][i] - 1] = true;
        }
    }
    for (int i = 0; i < TAM; i++)
    {
        bool usados[TAM];
        for (int j = 0; j < TAM; j++)
        {
            usados[j] = false;
        }
        for (int j = 0; j < TAM; j++)
        {
            if (usados[matriz[i][j] - 1] || matriz[i][j] > TAM)
            {
                printf("Falla en la fila %d, columna %d\n", i, j);
                return;
            }
            else
                usados[matriz[i][j] - 1] = true;
        }
    }
    printf("Funciona correctamente\n");
}

void algClasico(imatriz2d matriz, int posInicialFila, int posFinalFila, int posInicialColumna, int posFinalColumna)
{

    for (int i = posInicialFila; i <= posFinalFila; i++)
    {
        for (int j = posInicialColumna; j <= posFinalColumna; j++)
        {
            matriz[i][j] = (i + j) % (TAM) + 1;
        }
    }
}

void cuadradoLatino(imatriz2d matriz, int posInicialFila, int posFinalFila, int posInicialColumna, int posFinalColumna)
{
    int tamFila = posFinalFila - posInicialFila + 1;
    if (tamFila <= 4)
    {
        algClasico(matriz, posInicialFila, posFinalFila, posInicialColumna, posFinalColumna);
    }
    else
    {
        int mitadFila = (posFinalFila + posInicialFila) / 2;
        int mitadColumna = (posFinalColumna + posInicialColumna) / 2;
        cuadradoLatino(matriz, posInicialFila, mitadFila, posInicialColumna, mitadColumna);
        cuadradoLatino(matriz, mitadFila + 1, posFinalFila, posInicialColumna, mitadColumna);
        cuadradoLatino(matriz, posInicialFila, mitadFila, mitadColumna + 1, posFinalColumna);
        cuadradoLatino(matriz, mitadFila + 1, posFinalFila, mitadColumna + 1, posFinalColumna);
    }
}

int main()
{
    imatriz2d matriz = icreamatriz2d(TAM, TAM);

    cuadradoLatino(matriz, 0, TAM - 1, 0, TAM - 1, 1);
    //mostrarMatriz(matriz);
    validarMatriz(matriz);

    ifreematriz2d(&matriz);
}