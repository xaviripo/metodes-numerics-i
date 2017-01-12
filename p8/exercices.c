#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int p8_e1() {

    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("\n");

    double *x = malloc((n+1) * sizeof(double));
    double *y = malloc((n+1) * sizeof(double));

    for(int i = 0; i <= n; i++) {

        printf("Enter x[%d]: ", i);
        scanf("%lf", &x[i]);

        printf("Enter y[%d]: ", i);
        scanf("%lf", &y[i]);
        printf("\n");

    }

    int m;
    printf("Enter m: ");
    scanf("%d", &m);
    printf("\n");

    natural_cubic_splines(n, m, x, y);

    return 0;

}