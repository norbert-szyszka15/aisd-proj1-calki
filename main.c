#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "calki.h"

typedef double (*MathFunction)(double);

struct INTEGRAL {
    double resultRectangle;
    double resultTrapeze;
    double resultMonteCarlo;
};

double square(double x);

double compute(MathFunction func, double x);

struct INTEGRAL integrateRectangle(MathFunction func, double a, double b, double dx);

struct INTEGRAL integrateTrapeze(MathFunction func, double a, double b, double dx);

struct INTEGRAL integrateMonteCarlo(MathFunction func, double a, double b, double dx);

double findMin(MathFunction func, double a, double b, double dx);

double findMax(MathFunction func, double a, double b, double dx);

int main() {
    struct INTEGRAL integral;

    integral = integrateRectangle(square, 0, 4, 0.00000001);
    integral = integrateTrapeze(square, 0, 4, 0.00000001);
    integral = integrateMonteCarlo(square, 0, 4, 0.00000001);
    double min = findMin(square, 0, 4, 0.001);
    double max = findMax(square, 0, 4, 0.001);

    printf("%lf, %lf\n", min, max);
    printf("%lf\n%lf\n", integral.resultRectangle, integral.resultTrapeze);
    printf("%lf\n", integral.resultMonteCarlo);

    return 0;
}

double square(double x) {
    return -3 * x * x + 7 * exp(x);
}

double compute(MathFunction func, double x) {
    return func(x);
}

double findMin(MathFunction func, double a, double b, double dx) {
    double numOfSteps = 1 / dx;
    double x = a;
    double min = 0;
    int count = 0;
    double* funcValues = (double*)malloc(abs(b - a) * numOfSteps * sizeof(double));

    do {
        funcValues[count] = compute(func, x);
        if (min > funcValues[count]) { min = funcValues[count]; }
        x += dx;
        count ++;
    } while ((count <= abs(b - a) * numOfSteps) && (x <= b));

    free(funcValues);
    return min;
}

double findMax(MathFunction func, double a, double b, double dx) {
    double numOfSteps = 1 / dx;
    double x = a;
    double max = 0;
    int count = 0;
    double* funcValues = (double*)malloc(abs(b - a) * numOfSteps * sizeof(double));

    do {
        funcValues[count] = compute(func, x);
        if (max < funcValues[count]) { max = funcValues[count]; }
        x += dx;
        count ++;
    } while ((count <= abs(b - a) * numOfSteps) && (x <= b));

    free(funcValues);
    return max;
}

struct INTEGRAL integrateRectangle(MathFunction func, double a, double b, double dx) {
    struct INTEGRAL integralResult;
    double rectangle;
    double x = a;
    integralResult.resultRectangle = 0;

    do {
        rectangle = dx * compute(func, x);
        integralResult.resultRectangle += rectangle;
        x += dx;
    } while (x <= b);

    return integralResult;
}

struct INTEGRAL integrateTrapeze(MathFunction func, double a, double b, double dx) {
    struct INTEGRAL integralResult;
    double trapeze;
    double a1 = a;
    double b1 = dx;
    integralResult.resultTrapeze = 0;

    do {
        trapeze = ((compute(func, a1) + compute(func, b1)) * dx) / 2;
        integralResult.resultTrapeze += trapeze;
        a1 += dx;
        b1 += dx;
    } while (b1 <= b);

    return integralResult;
}

struct INTEGRAL integrateMonteCarlo(MathFunction func, double a, double b, double dx) {
    srand(time(NULL));
    struct INTEGRAL integralResult;
    double sum = 0.0;
    double x, y;
    int steps = 1 / dx;
    double min = findMin(func, a, b, dx);
    double max = findMax(func, a, b, dx);
    double range1 = max - min;
    double range2 = b - a;
    double div1 = RAND_MAX / range1;
    double div2 = RAND_MAX / range2;


    for (int i = 0; i < steps; i++) {
        x = a + ((double)rand() / div2);
        y = min + ((double)rand() / div1);
        if (y <= func(x)) { sum += 1.0 ;}
    }

    double rectangleArea = (max - min) * (b - a);
    integralResult.resultMonteCarlo = rectangleArea * sum / steps;
    return integralResult;
}