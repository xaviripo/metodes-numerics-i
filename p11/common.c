#include <stdlib.h>
#include <math.h>
#include <stdio.h>

double legendre(int i, double x) {

    if(i == 0) return 1.;
    if(i == 1) return x;

    double p, // P_i
            p1 = x, // P_{i-1}
            p2 = 1.; // P_{i-2}

    for(int j = 2; j <= i; j++) {
        p = (2*j-1)*x*p1/j - (j-1)*p2/j;
        p2 = p1;
        p1 = p;
    }
    return p;
}

int secant(int i, double *x0, double *x1, double prec, int nmax) {
    int k, stop = 0;
    double x,
            f0 = legendre(i, *x0),
            f1 = legendre(i, *x1);
    for(k = 0; k < nmax && !stop; k++) {
        x = ((*x0)*f1 - (*x1)*f0)/(f1 - f0);
        *x0 = *x1;
        f0 = f1;
        *x1 = x;
        f1 = legendre(i, *x1);
        stop = fabs(f1) < prec || fabs(x1 - x0) < prec;
    }
    printf("P_%d, x = %lf\n", i, x);

    // As asked for, return 1 iff max number of loops exceeded
    return (k >= nmax);

}