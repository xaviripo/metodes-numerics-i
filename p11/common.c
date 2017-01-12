#include <stdlib.h>
#include <math.h>

double legendre(int i, double x) {

    if(i == 0) return 1.;
    if(i == 1) return x;

    double temp,
            p_i1 = x, // P_(i-1)
            p_i2 = 1.; // P_(i-2)

    for(int j = 2; j <= i; j++) {
        temp = (2*j - 1)/((double) j)*x*p_i1 - (j-1)/((double) j)*p_i2;
        p_i2 = p_i1;
        p_i1 = temp;
    }
    return temp;
}

int secant(int i, double *x0, double *x1, double prec, int nmax) {

    double **M;
    M = (double **) malloc(i*sizeof(double *));
    for(int j = 0; j < i; j++) M[j] = (double *) malloc((j+1)*sizeof(double));

    int j;
    for(j = 0; j < nmax; j++) {
        M[i][j] = (M[i]*f_1 - x_1*f_2)/(f_1 - f_2);
    }

    // As asked for, return 1 if max number of loops exceeded
    return (j > nmax);
}