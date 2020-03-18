#include "ivector.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

/* retorna "a - b" en segundos */
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

void mostrarPolinomio(ivector vector, int posInicial, int posFinal)
{
    for (int i = posFinal - 1; i > posInicial; i--)
    {
        printf("%d x^%d + ", vector[i], i);
    }
    printf("%d", vector[posInicial]);
    printf("\n");
}

void rellenaVector(ivector vector, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        vector[i] = rand() % 5;
    }
}

ivector suma(ivector pol1, ivector pol2, int posInicial1, int posFinal1, int posInicial2, int posFinal2)
{
    int tam = (posFinal1 - posInicial1 + 1);
    ivector res = icreavector(tam);

    for (int i = 0; i < tam; i++)
    {

        res[i] = pol1[i + posInicial1] + pol2[i + posInicial2];
    }

    /*printf("Suma entre: ");
    printf("\n");
    mostrarPolinomio(pol1, posInicial1, posFinal1 + 1);
    mostrarPolinomio(pol2, posInicial2, posFinal2 + 1);
    mostrarPolinomio(res, 0, tam);
    printf("\n");*/

    return res;
}

ivector resta(ivector pol1, ivector pol2, int posInicial1, int posFinal1, int posInicial2, int posFinal2)
{
    int tam = (posFinal1 - posInicial1 + 1);
    ivector res = icreavector(tam);

    for (int i = 0; i < tam; i++)
    {

        res[i] = pol1[i + posInicial1] - pol2[i + posInicial2];
    }
    /*printf("Resta entre: ");
    printf("\n");
    mostrarPolinomio(pol1, posInicial1, posFinal1 + 1);
    mostrarPolinomio(pol2, posInicial2, posFinal2 + 1);
    mostrarPolinomio(res, 0, tam);
    printf("\n");*/
    return res;
}

ivector multClasico(ivector pol1, ivector pol2, int posInicial1, int posFinal1, int posInicial2, int posFinal2)
{
    int tam = (posFinal1 - posInicial1 + 1) * 2 - 1;

    ivector res = icreavector(tam);
    for (int i = 0; i < tam; i++)
    {
        res[i] = 0;
    }

    for (int i = 0; i <= posFinal1 - posInicial1; i++)
    {
        for (int j = 0; j <= posFinal2 - posInicial2; j++)
        {
            res[i + j] += pol2[i + posInicial2] * pol1[j + posInicial1];
        }
    }
    return res;
}

ivector multDyV(ivector pol1, ivector pol2, int posInicial1, int posFinal1, int posInicial2, int posFinal2)
{
    int tam = posFinal1 - posInicial1 + 1;

    if (tam <= 64)
    {
        return multClasico(pol1, pol2, posInicial1, posFinal1, posInicial2, posFinal2);
    }
    else
    {
        int mitad1 = (posFinal1 + posInicial1) / 2;
        int mitad2 = (posFinal2 + posInicial2) / 2;
        ivector res1 = icreavector(tam - 1);
        ivector res2 = icreavector(tam - 1);
        ivector res3 = icreavector(tam - 1);
        ivector resFinal = icreavector(tam * 2 - 1);
        res1 = multDyV(pol1, pol2, mitad1 + 1, posFinal1, mitad2 + 1, posFinal2);
        res2 = multDyV(pol1, pol2, posInicial1, mitad1, posInicial2, mitad2);
        res3 = multDyV(suma(pol1, pol1, posInicial1, mitad1, mitad1 + 1, posFinal1), suma(pol2, pol2, posInicial2, mitad2, mitad2 + 1, posFinal2), 0, mitad1 - posInicial1, 0, mitad2 - posInicial2);
        res3 = resta(resta(res3, res1, 0, tam - 2, 0, tam - 2), res2, 0, tam - 2, 0, tam - 2);

        for (int i = 0; i < tam * 2 - 1; i++)
        {
            resFinal[i] = 0;
        }
        for (int i = 0; i <= tam - 2; i++)
        {
            resFinal[i] += res2[i];
            resFinal[i + tam / 2] += res3[i];
            resFinal[i + tam] += res1[i];
        }
        ifreevector(&res1);
        ifreevector(&res2);
        ifreevector(&res3);
        return resFinal;
    }
}

int main()
{
    const int size = 25000;
    srand(1682);
    ivector vector1 = icreavector(size);
    ivector vector2 = icreavector(size);
    ivector vectorRes = icreavector(2 * size - 1);

    rellenaVector(vector1, size);
    rellenaVector(vector2, size);

    LARGE_INTEGER t_ini, t_fin;
    double secs;
    QueryPerformanceCounter(&t_ini);
    vectorRes = multDyV(vector1, vector2, 0, size - 1, 0, size - 1);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    printf("Ha tardado %f segundos el algoritmo DyV", secs);
    QueryPerformanceCounter(&t_ini);
    vectorRes = multClasico(vector1, vector2, 0, size - 1, 0, size - 1);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    printf("\nHa tardado %f segundos el algoritmo clasico", secs);
}