#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int p11_e1() {

    int nmax;
    printf("Enter nmax: ");
    scanf("%d", &nmax);

    int imax;
    printf("Enter imax: ");
    scanf("%d", &imax);

    double prec;
    printf("Enter prec: ");
    scanf("%lf", &prec);

    // To store the zeros in
    // M[i] holds the zeros for P_{i+1} as P_0 doesn't have any
    double **M;
    M = (double **) malloc(imax*sizeof(double *));

    double x0_ = -1, x1_ = 1;
    double *x0 = &x0_,
            *x1 = &x1_;

    // Iterate over the polynomials
    for(int i = 0; i < imax; i++) {

        // As many slots as the polynomial has roots
        M[i] = (double *) malloc(i*sizeof(double));

        // Iterate over the solutions
        for(int j = 0; j <= i; j++) {

            // Far left
            if(j == 0) {
                *x0 = -1;
            } else {
                *x0 = M[i-1][j-1];
            }

            // Far right
            if(j == i) { // Watch out! For imax = 1, this is not mutually exclusive with previous if
                *x1 = 1;
            } else {
                *x1 = M[i-1][j];
            }

            // Calculate and check for failure
            if(secant(i+1, x0, x1, prec, nmax)) {
                printf("Convergence failed at polynomial %d in root number %d between %lf and %lf", i+1, j, *x0, *x1);
                return 1; // Oops
            }

            // Latest value is assigned
            M[i][j] = *x1;

        }
    }

    // Done
    return 0;

}