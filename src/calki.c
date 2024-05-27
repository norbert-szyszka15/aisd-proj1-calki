#include "calki.h"

#define lp 10000000

double c_od, c_do;


    // FUNKCJE PODCALKOWE

double f3(double x) {
    return x * x;      
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
    double dx = (c_do - c_od) / lp;
    double min = compute(func, x);
    int count = 1;
    int funcValuesSize = fabs(c_do - c_od) * lp;
    double* funcValues = (double*)malloc(funcValuesSize * sizeof(double));

    do {
        funcValues[count - 1] = compute(func, x);
        if (min > funcValues[count - 1]) { min = funcValues[count - 1]; }
        x += dx;
        count ++;
    } while ((count < funcValuesSize) && (x < c_do));

    free(funcValues);
    return min;
}

double findMax(double(*func)(double)) {
    double x = c_od;
    double dx = (c_do - c_od) / lp;
    double max = compute(func, x);
    int count = 1;
    int funcValuesSize = fabs(c_do - c_od) * lp;
    double* funcValues = (double*)malloc(funcValuesSize * sizeof(double));

    do {
        funcValues[count - 1] = compute(func, x);
        if (max < funcValues[count - 1]) { max = funcValues[count - 1]; }
        x += dx;
        count ++;
    } while ((count < funcValuesSize) && (x < c_do));

    free(funcValues);
    return max;
}

double randRange(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;

    return min + (rand() / div);
}


    // FUNKCJE LICZACE CALKI

double prostokaty(double(*func)(double)) {
    double x = c_od;
    double dx = fabs(c_do - c_od) / lp;
    double result = 0;

    for (int i = 0; i < lp; i++) {
        double rectangle = dx * compute(func, x);
        result += rectangle;
        x += dx;
    }

    return result;
}

double trapezy(double(*func)(double)) {
    double a1 = c_od;
    double dx = fabs(c_do - c_od) / lp;
    double result = 0;
    
    for (int i = 0; i < lp; i++) {
        double b1 = a1 + dx;
        double trapeze = ((func(a1) + func(b1)) * dx) / 2;
        result += trapeze;
        a1 = b1;
    }

    return result;
}

double mc(double(*func)(double)) {
    double x, y;
    double max = findMax(func);
    double min = findMin(func);
    double aboveZero = 0.0;
    double belowZero = 0.0;

    srand(time(NULL));

    for (int i = 0; i < lp; i++) {
        x = randRange(c_od, c_do);
        y = randRange(min, max);

        if (y <= compute(func, x) && y >= 0) {
            aboveZero += 1;
        } else if (y >= compute(func, x) && y < 0) {
            belowZero += 1;
        }
    }

    double areaAboveZero = (aboveZero / lp) * (c_do - c_od) * max;
    double areaBelowZero = (belowZero / lp) * (c_do - c_od) * fabs(min);

    if (max >= 0 && min >= 0) {
        return areaAboveZero;
    } else if (max > 0 && min < 0) {
        return areaAboveZero - areaBelowZero;
    } else if (max < 0 && min < 0) {
        return - areaBelowZero;
    }

    return 0;
}
