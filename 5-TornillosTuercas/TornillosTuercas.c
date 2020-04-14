#include "ivector.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define TAM 10000000

/* retorna "a - b" en segundos */
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

bool correcto(ivector v1, ivector v2)
{
    for (int i = 0; i < TAM; i++)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

void mostrarVector(ivector vector, int tam)
{

    for (int i = 0; i < tam; i++)
    {
        printf(" %d", vector[i]);
    }
    printf("\n");
}

void intercambia(ivector v, int pos1, int pos2)
{
    int aux = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = aux;
}

void algClasico(ivector tuercas, ivector tornillos, int posInicio, int posFinal)
{
    for (int j = posInicio; j <= posFinal; j++)
    {
        bool aux = false;
        for (int i = posInicio; i <= posFinal && !aux; i++)
        {
            if (tuercas[i] == tornillos[j])
            {
                intercambia(tuercas, posInicio, i);
                aux = true;
            }
        }
        posInicio++;
    }
}

int reordenar(ivector v, int posInicio, int posFinal, int pivote, int *inicio)
{
    *inicio = posInicio;
    do
    {
        intercambia(v, posInicio, posFinal);
        while (v[posInicio] < pivote)
            posInicio++;
        while (v[posFinal] > pivote)
            posFinal--;
        if (v[posInicio] == pivote)
        {
            intercambia(v, posInicio, *inicio);
            (*inicio)++;
            posInicio++;
        }
        if (v[posFinal] == pivote)
        {
            intercambia(v, posFinal, *inicio);
            (*inicio)++;
            if (posInicio <= *inicio)
                posInicio = *inicio;
        }

    } while (posInicio <= posFinal);

    return posFinal;
}

void TornillosTuercas(ivector tuercas, ivector tornillos, int posInicio, int posFinal)
{
    int tamTornillos = posFinal - posInicio + 1;
    if (tamTornillos <= 4194304 * 2)
    {
        algClasico(tuercas, tornillos, posInicio, posFinal);
    }
    else
    {
        int *posTuerca = malloc(sizeof(int));
        int puntoCorte = reordenar(tuercas, posInicio, posFinal, tornillos[(posInicio + posFinal) / 2], posTuerca);
        reordenar(tornillos, posInicio, posFinal, tuercas[*posTuerca - 1], posTuerca);
        TornillosTuercas(tuercas, tornillos, *posTuerca, puntoCorte);
        TornillosTuercas(tuercas, tornillos, puntoCorte + 1, posFinal);
        free(posTuerca);
    }
}

int main()
{
    srand(88812318);
    const int limite = 20;
    ivector tuercas = icreavector(TAM);
    ivector tuercas2 = icreavector(TAM);
    ivector tornillos = icreavector(TAM);
    ivector tornillos2 = icreavector(TAM);

    for (int i = 0; i < TAM; i++)
    {
        int aux = rand() % limite;

        tornillos[i] = aux;
        tornillos2[i] = aux;
        tuercas[i] = aux;
        tuercas2[i] = aux;
    }

    for (int i = 0; i < TAM * 2; i++)
    {
        int aux1 = rand() % limite;
        int aux2 = rand() % limite;
        intercambia(tuercas, aux1, aux2);
        intercambia(tuercas2, aux1, aux2);
    }
    /*
    printf("Tuercas:   ");
    mostrarVector(tuercas, TAM);
    printf("Tornillos: ");
    mostrarVector(tornillos, TAM);
    */

    LARGE_INTEGER t_ini, t_fin;
    double secs;
    QueryPerformanceCounter(&t_ini);

    TornillosTuercas(tuercas, tornillos, 0, TAM - 1);

    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    printf("Ha tardado %f segundos el algoritmo DyV\n", secs);

    QueryPerformanceCounter(&t_ini);

    algClasico(tuercas2, tornillos2, 0, TAM - 1);

    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    printf("Ha tardado %f segundos el algoritmo clasico\n", secs);

        if (correcto(tornillos, tuercas))
    {
        printf("Funciona correctamente\n");
    }
    else
    {
        printf("No funciona correctamente\n");
    }

    if (correcto(tornillos2, tuercas2))
    {
        printf("Funciona correctamente\n");
    }
    else
    {
        printf("No funciona correctamente\n");
    }

    /*
    printf("\n");
    printf("Tuercas:   ");
    mostrarVector(tuercas, TAM);
    printf("Tornillos: ");
    mostrarVector(tornillos, TAM);
    */
    ifreevector(&tuercas);
    ifreevector(&tuercas2);
    ifreevector(&tornillos);
    ifreevector(&tornillos2);
}