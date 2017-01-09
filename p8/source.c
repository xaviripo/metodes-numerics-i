#include <stdio.h>
#include <stdlib.h>
#include "tridiagonal.h"

int natural_cubic_splines(int n, int m, double* x, double* y) {

    // Tridiagonal diagonals
    double *a = malloc((n-2) * sizeof(double));
    double *b = malloc((n-1) * sizeof(double));
    double *c = malloc((n-2) * sizeof(double));
    // Moments
    double *M = malloc((n-1) * sizeof(double));
    // Interval lengths
    double *h = malloc((n+1) * sizeof(double));
    // Auxiliar vectors
    double* A = malloc((n) * sizeof(double));
    double* B = malloc((n) * sizeof(double));

    for(int i = 0; i < n; i++) {
        h[i+1] = x[i+1] - x[i];
    }

    for(int i = 0; i < n-2; i++) {
        a[i] = h[i+1] / 6.0;
        b[i] = (h[i] + h[i+1]) / 3.0;
        c[i] = h[i+1] / 6.0;
        M[i] = ((y[i+2] - y[i+1]) / h[i+1]) - ((y[i+1] - y[i]) / h[i]);
    }

    b[n-2] = (h[n-2] + h[n-1]) / 3.0;
    M[n-2] = ((y[n] - y[n-1]) / h[n-1]) - ((y[n-1] - y[n-2]) / h[n-2]);

    d3(n-2, a, b, c, M, 1e-10);

    B[0] = y[0];
    A[0] = ((y[1] - y[0]) / h[0]) - (h[0] * M[0] / 6.0);

    for(int i = 1; i < n-1; i++) {
        A[i] = ((y[i+1] - y[i])/h[i]) - (h[i]*(M[i] - M[i-1])/6.0);
        B[i] = y[i] - (M[i-1]*h[i]*h[i]/6.0);
    }

    A[n-1] = ((y[n] - y[n-1])/h[n-1]) + (h[n-1] * M[n-2]/6.0);
    B[n-1] = y[n-1] - (M[n-2]*h[n-1]*h[n-1]/6.0);

}