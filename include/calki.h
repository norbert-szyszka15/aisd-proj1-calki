#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

extern double c_od, c_do;

    // FUNKCJE PODCALKOWE
double f3(double x); 
double f4(double x);


    // FUNKCJE POMOCNICZE
double compute(double(*func)(double), double x);

double findMin(double(*func)(double));

double findMax(double(*func)(double));


    // FUNKCJE OBLICZAJACE CALKI
double prostokaty(double(*func)(double));

double trapezy(double(*func)(double));
       
double mc(double(*func)(double));