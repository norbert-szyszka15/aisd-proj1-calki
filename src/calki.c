#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "calki.h"

#define lp 1000

double c_od, c_do;


    // FUNKCJE PODCALKOWE

double f3(double x) {
    return -1;      
}

double f4(double x) {
    return 1;
}


    // FUNKCJE POMOCNICZE

double compute(double(*func)(double), double x) {
    return func(x);
}

double findMin(double(*func)(double)) {
    double x = c_od;
    double dx = abs(c_do - c_od) / lp;
    double min = 0;
    int count = 0;
    int funcValuesSize = abs(c_do - c_od) * lp;
    double* funcValues = (double*)malloc(funcValuesSize * sizeof(double));

    do {
        funcValues[count] = compute(func, x);
        if (min > funcValues[count]) { min = funcValues[count]; }
        x += dx;
        count ++;
    } while ((count <= funcValuesSize) && (x <= c_do));

    free(funcValues);
    return min;
}

double findMax(double(*func)(double)) {
    double x = c_od;
    double dx = abs(c_do - c_od) / lp;
    double max = 0;
    int count = 0;
    int funcValuesSize = abs(c_do - c_od) * lp;
    double* funcValues = (double*)malloc(funcValuesSize * sizeof(double));

    do {
        funcValues[count] = compute(func, x);
        if (max < funcValues[count]) { max = funcValues[count]; }
        x += dx;
        count ++;
    } while ((count <= funcValuesSize) && (x <= c_do));

    free(funcValues);
    return max;
}


    // FUNKCJE LICZACE CALKI

double prostokaty(double(*func)(double)) {
    double rectangle;
    double x = c_od;
    double dx = abs(c_do - c_od) / lp;
    double result = 0;

    do {
        rectangle = dx * compute(func, x);
        result += rectangle;
        x += dx;
    } while (x <= c_do);

    return result;
}

double trapezy(double(*func)(double)) {
    double trapeze;
    double a1 = c_od;
    double dx = (c_do - c_od) / lp;
    double b1 = dx;
    double result = 0;

    do {
        trapeze = ((compute(func, a1) + compute(func, b1)) * dx) / 2;
        result += trapeze;
        a1 += dx;
        b1 += dx;
    } while (b1 <= c_do);

    return result;
}

double mc(double(*func)(double)) {
    srand(time(NULL));
    double sum = 0.0;
    double x, y;
    double min = findMin(func);
    double max = findMax(func);
    double range1 = max - min;
    double range2 = c_do - c_od;
    double div1 = RAND_MAX / range1;
    double div2 = RAND_MAX / range2;
    double result;


    for (int i = 0; i < lp; i++) {
        x = c_od + ((double)rand() / div2);
        y = min + ((double)rand() / div1);
        if (y <= func(x)) { sum += 1.0 ;}
    }

    double rectangleArea = (max - min) * (c_do - c_od);
    result = rectangleArea * sum / lp;
    return result;
}
