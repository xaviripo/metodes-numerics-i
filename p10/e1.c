#include <stdio.h>
#include <math.h>
#include "source.h"

void e1() {

    double a;
    printf("Enter a: ");
    scanf("%lf", &a);

    double b;
    printf("Enter b: ");
    scanf("%lf", &b);

    printf("Final integral value: %25.16lf", T(a, b, 1e-12, pow(2,20)));

}