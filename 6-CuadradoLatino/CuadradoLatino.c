#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "imatriz2d.h"

#define TAM 16384

/* retorna "a - b" en segundos */
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

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
            if (usados[matriz[j][i] - 1])
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
            if (usados[matriz[i][j] - 1])
            {
                printf("Falla en la fila %d, columna %d\n", i, j);
                return;
            }
            else
                usados[matriz[i][j] - 1] = true;
        }
    }
    printf("Funciona correctamente");
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
    int tam = posFinalFila - posInicialFila + 1;
    if (tam <= 4)
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

    LARGE_INTEGER t_ini, t_fin;
    double secs;
    QueryPerformanceCounter(&t_ini);
    cuadradoLatino(matriz, 0, TAM - 1, 0, TAM - 1);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    printf("Ha tardado %f segundos el algoritmo DyV\n", secs);

    QueryPerformanceCounter(&t_ini);
    algClasico(matriz, 0, TAM - 1, 0, TAM - 1);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    printf("Ha tardado %f segundos el algoritmo clasico\n", secs);
    ifreematriz2d(&matriz);
}