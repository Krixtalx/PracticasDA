#include "ivector.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define TAM 200

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

void intercambia(ivector v1, int pos1, int pos2)
{
    int aux = v1[pos1];
    v1[pos1] = v1[pos2];
    v1[pos2] = aux;
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

int reordenar(ivector v, int posInicio, int posFinal, int pivote)
{
    do
    {
        intercambia(v, posInicio, posFinal);
        while (v[posInicio] < pivote)
            posInicio++;
        while (v[posFinal] >= pivote)
            posFinal--;

    } while (posInicio <= posFinal);

    return posInicio;
}

int reordenar2(ivector v, int posInicio, int posFinal, int pivote, int* posEncontrado)
{
    do
    {
        intercambia(v, posInicio, posFinal);
        if(posFinal==*posEncontrado){
            *posEncontrado=posInicio;
        }
        while (v[posInicio] < pivote)
            posInicio++;
        while (v[posFinal] >= pivote && posInicio <= posFinal){
            if(v[posFinal]==pivote){
                *posEncontrado=posFinal;
            }
            posFinal--;
        }

    } while (posInicio <= posFinal);

    return posInicio;
}

void TornillosTuercas(ivector tuercas, ivector tornillos, int posInicio, int posFinal)
{
    int tamTornillos = posFinal - posInicio + 1;
    if (tamTornillos <= 64)
    {
        algClasico(tuercas, tornillos, posInicio, posFinal);
    }
    else
    {
        int posTuerca=0;
        int puntoCorteTuercas = reordenar2(tuercas, posInicio, posFinal, tornillos[posInicio], &posTuerca);
        int puntoCorteTornillos = reordenar(tornillos, posInicio, posFinal, tuercas[posTuerca]);
        TornillosTuercas(tuercas, tornillos, posInicio, puntoCorteTornillos - 1);
        TornillosTuercas(tuercas, tornillos, puntoCorteTornillos, posFinal);
    }
}

int main()
{
    srand(1602);
    const int limite = 10;
    ivector tuercas = icreavector(TAM);
    ivector tuercas2 = icreavector(TAM);
    ivector distintos = icreavector(limite);
    ivector tornillos = icreavector(TAM);
    ivector tornillos2 = icreavector(TAM);

    for (int i = 0; i < limite; i++)
    {
        distintos[i] = 0;
    }

    for (int i = 0; i < TAM; i++)
    {
        int aux = rand() % limite;
        distintos[aux]++;

        tornillos[i] = aux;
        tornillos2[i] = aux;
    }

    for (int i = 0; i < TAM; i++)
    {
        int aux = rand() % limite;
        while (distintos[aux] == 0)
            aux = rand() % limite;
        tuercas[i] = aux;
        tuercas2[i] = aux;
        distintos[aux]--;
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

    TornillosTuercas(tuercas, tornillos,  0, TAM - 1);

    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    printf("Ha tardado %f segundos el algoritmo DyV\n", secs);

    QueryPerformanceCounter(&t_ini);

    algClasico(tuercas, tornillos, 0, TAM - 1);

    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    printf("Ha tardado %f segundos el algoritmo clasico\n", secs);
    

    /*
    if (correcto(tornillos, tuercas))
    {
        printf("Funciona correctamente");
    }
    else
    {
        printf("No funciona correctamente");
    }
    */
   /*
    printf("\n");
    printf("Tuercas:   ");
    mostrarVector(tuercas, TAM);
    printf("Tornillos: ");
    mostrarVector(tornillos, TAM);
    */
    ifreevector(&tuercas);
    ifreevector(&tuercas2);
    ifreevector(&distintos);
    ifreevector(&tornillos);
    ifreevector(&tornillos2);
}