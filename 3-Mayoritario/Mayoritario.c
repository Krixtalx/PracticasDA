#include "ivector.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/**
 * Función auxiliar para mostrar el vector
 */
void mostrarVector(ivector vector, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf(" %d", vector[i]);
    }
    printf("\n");
}

struct mayoritario
{
    int num, veces;
};

struct mayoritario buscaMayoritarioClasico(ivector vector, int posInicio, int posFinal)
{
    struct mayoritario resultado;
    resultado.num = 0;
    resultado.veces = -1;
    for (int i = posInicio; i <= posFinal; i++)
    {
        int numAux = vector[i];
        int vecesAux = 0;
        for (int j = posInicio; j <= posFinal; j++)
        {
            if (vector[j] == numAux)
            {
                vecesAux++;
            }
        }
        if (vecesAux > resultado.veces)
        {
            resultado.num = numAux;
            resultado.veces = vecesAux;
        }
    }
    return resultado;
}

struct mayoritario buscaMayoritario(ivector vector, int posInicio, int posFinal)
{
    struct mayoritario resultado;
    resultado.num = -1;
    resultado.veces = -1;

    int tam = posFinal - posInicio + 1;
    if (tam / 2 <= 3)
    {
        return buscaMayoritarioClasico(vector, posInicio, posFinal);
    }
    else
    {
        int mitad = (posFinal + posInicio + 1) / 2;
        struct mayoritario res1 = buscaMayoritario(vector, posInicio, mitad);
        struct mayoritario res2 = buscaMayoritario(vector, mitad + 1, posFinal);
        if (res1.veces > res2.veces)
        {
            for (int i = mitad + 1; i <= posFinal; i++)
            {
                if (vector[i] == res1.num)
                {
                    res1.veces++;
                }
            }
            if (res1.veces > tam / 2)
                return res1;
            return resultado;
        }
        else
        {
            for (int i = posInicio; i <= mitad; i++)
            {
                if (vector[i] == res2.num)
                {
                    res2.veces++;
                }
            }
            if (res2.veces > tam / 2)
                return res2;
            return resultado;
        }
    }
}

int main()
{
    int size = 16;
    srand(3040);
    ivector vector = icreavector(size);
    for (int i = 0; i < size; i++)
    {
        vector[i] = rand() % 3;
    }

    mostrarVector(vector, size);
    struct mayoritario resultado = buscaMayoritario(vector, 0, size - 1);
    printf("El mayoritario es %d repitiendose %d veces", resultado.num, resultado.veces);
    ifreevector(&vector);
}