#include "ivector.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#ifdef WIN32

/* retorna "a - b" en segundos */
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

#define TIME_THIS(X)                                    \
    {                                                   \
        LARGE_INTEGER t_ini, t_fin;                     \
        double secs;                                    \
        QueryPerformanceCounter(&t_ini);                \
        X;                                              \
        QueryPerformanceCounter(&t_fin);                \
        secs = performancecounter_diff(&t_fin, &t_ini); \
        printf(#X " ha tardado %f segundos \n", secs);  \
    }
#else
#define TIME_THIS(X)                                                                                                 \
    {                                                                                                                \
        struct timespec ts1, ts2;                                                                                    \
        clock_gettime(CLOCK_REALTIME, &ts1);                                                                         \
        X;                                                                                                           \
        clock_gettime(CLOCK_REALTIME, &ts2);                                                                         \
        printf(#X " ha tardado %f segundos\n",                                                                       \
               (float)(1.0 * (1.0 * ts2.tv_nsec - ts1.tv_nsec * 1.0) * 1e-9 + 1.0 * ts2.tv_sec - 1.0 * ts1.tv_sec)); \
    }

#endif

#define TAM 10000000

/**
* Método auxiliar para comprobar si el algoritmo funciona correctamente.
*/
bool correcto(ivector v1, ivector v2)
{
    for (int i = 0; i < TAM; i++)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

/**
* Método auxiliar para mostrar el vector.
*/
void mostrarVector(ivector vector, int tam)
{

    for (int i = 0; i < tam; i++)
    {
        printf(" %d", vector[i]);
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
* Algoritmo clásico para resolver el problema. Escoge un tornillo y compara con las tuercas hasta que encuentre una coincidente. Después, repitirá lo mismo con el siguiente tornillo.
*/
void algClasico(ivector tuercas, ivector tornillos, int posInicio, int posFinal)
{
    for (int j = posInicio; j <= posFinal; j++)
    {
        for (int i = j; i <= posFinal; i++)
        {
            if (tuercas[i] == tornillos[j])
            {
                intercambia(tuercas, j, i);
                i = posFinal + 1;
            }
        }
    }
}

/**
* Reordena el vector dejando los valores menores que el pivote por debajo de *inicio y los mayores por encima de posFinal.
*/
int reordenar(ivector v, int posInicio, int posFinal, int pivote, int *inicio)
{
    *inicio = posInicio;
    while (posInicio <= posFinal)
    {
        if (v[posInicio] < pivote)
        {
            intercambia(v, *inicio, posInicio);
            posInicio++;
            (*inicio)++;
        }
        else if (v[posInicio] == pivote)
        {
            posInicio++;
        }
        else
        {
            intercambia(v, posInicio, posFinal);
            posFinal--;
        }
    }

    return posFinal;
}

/**
 * Algoritmo Divide y Vencerás que soluciona el problema. Reordena las tuercas utilizando el método de reordenado y mas tarde hace lo mismo con los tornillos. Después, realiza llamadas recursivas a esta función hasta que tam<=umbral
 */
void TornillosTuercas(ivector tuercas, ivector tornillos, int posInicio, int posFinal)
{
    int tam = posFinal - posInicio + 1;
    if (tam <= 32)
    {
        algClasico(tuercas, tornillos, posInicio, posFinal);
    }
    else
    {
        int posTuerca;
        int puntoCorte = reordenar(tuercas, posInicio, posFinal, tornillos[(posInicio + posFinal) / 2], &posTuerca);
        reordenar(tornillos, posInicio, posFinal, tuercas[posTuerca], &posTuerca);
        TornillosTuercas(tuercas, tornillos, posInicio, posTuerca - 1);
        TornillosTuercas(tuercas, tornillos, puntoCorte + 1, posFinal);
    }
}

int main()
{
    srand(88812318);
    const int limite = 200;
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

    for (int i = 0; i < TAM; i++)
    {
        int aux1 = rand() % TAM;
        intercambia(tuercas, i, aux1);
        intercambia(tuercas2, i, aux1);
    }
    /*
    printf("Tuercas:   ");
    mostrarVector(tuercas2, TAM);
    printf("Tornillos: ");
    mostrarVector(tornillos2, TAM);
    */

    TIME_THIS(TornillosTuercas(tuercas, tornillos, 0, TAM - 1));

    //TIME_THIS(algClasico(tuercas2, tornillos2, 0, TAM - 1));

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
    mostrarVector(tuercas2, TAM);
    printf("Tornillos: ");
    mostrarVector(tornillos2, TAM); 
    */
    ifreevector(&tuercas);
    ifreevector(&tuercas2);
    ifreevector(&tornillos);
    ifreevector(&tornillos2);
}