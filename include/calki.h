#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double f3(double x); 
double f4(double x);


double prostokaty(double( *f)(double));

double trapezy(double (*f)(double));
       
double mc(double(*f)(double));