#include <stdio.h>
#include <math.h>
#include "common.h"

int p10_e1() {

    double a;
    printf("Enter a: ");
    scanf("%lf", &a);

    double b;
    printf("Enter b: ");
    scanf("%lf", &b);

    printf("Final integral value: %25.16lf", T(a, b, 1e-12, pow(2,20)));

    return 0;

}

int p10_e2() {

    double a;
    printf("Enter a: ");
    scanf("%lf", &a);

    double b;
    printf("Enter b: ");
    scanf("%lf", &b);

    romberg();

    return 0;

}