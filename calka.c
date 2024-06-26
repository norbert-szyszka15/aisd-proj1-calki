#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "calki.h"

double f1(double x) {
    return -4.4 * x * x * x * x + 13.5 * x * x - 17;          
}

double f2(double x) {
    double y;
    return 2 * sin(3 * x) * sin(x - 3) + cos(5 * x) + 5;       
}

int main(int argc, char *argv[]) {
    printf("od = ");
    scanf("%lf",&c_od);
    printf("do = ");
    scanf("%lf",&c_do);

    {   // FUNKCJA 1
    printf("\n\nFunkcja 1 \n");
    printf("wynik prostokaty -  %lf\n" ,prostokaty(f1));
    printf("wynik trapezy    -  %lf\n" ,trapezy(f1));
    printf("wynik MC         -  %lf\n", mc(f1));
    }

    {   // FUNKCJA 2
    printf("\n\nFunkcja 2 \n");
    printf("wynik prostokaty -  %lf\n" ,prostokaty(f2));
    printf("wynik trapezy    -  %lf\n" ,trapezy(f2));
    printf("wynik MC         -  %lf\n", mc(f2));
    }

    {   // FUNKCJA 3
    printf("\n\nFunkcja 3 \n");
	printf("wynik prostokaty -  %lf\n" ,prostokaty(f3));
    printf("wynik trapezy    -  %lf\n" ,trapezy(f3));
    printf("wynik MC         -  %lf\n", mc(f3));
    }

    {   // FUNKCJA 4
    printf("\n\nFunkcja 4 \n");
	printf("wynik prostokaty -  %lf\n" ,prostokaty(f4));
    printf("wynik trapezy    -  %lf\n" ,trapezy(f4));
    printf("wynik MC         -  %lf\n", mc(f4));
    }

    return 0;
}