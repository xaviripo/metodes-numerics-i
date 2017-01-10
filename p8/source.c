#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tridiagonal.h"

/**
 * Computes a natural cubic spline from the given (x, y) points and prints m+1 equidistant points of the spline in the
 * x[0] to x[n] interval.
 * @param n Number of intervals of the spline
 * @param m Number (minus 1) of points to evaluate at
 * @param x Array with n+1 abscissas
 * @param y Array with n+1 ordinates
 */
void natural_cubic_splines(int n, int m, double* x, double* y) {

    // Tridiagonal diagonals
    double *a = malloc((n-1) * sizeof(double)); // Has elements a[1] through a[n-2] inclusive
    double *b = malloc((n-1) * sizeof(double)); // Has elements b[0] through b[n-2] inclusive
    double *c = malloc((n-2) * sizeof(double)); // Has elements c[0] through c[n-3] inclusive
    // Moments
    double *M = malloc((n-1) * sizeof(double));
    // Interval lengths
    double *h = malloc((n+1) * sizeof(double));
    // Auxiliar vectors
    double* A = malloc((n) * sizeof(double));
    double* B = malloc((n) * sizeof(double));

    // Calculate h
    for(int i = 0; i < n; i++) {
        h[i+1] = x[i+1] - x[i];
    }

    // Calculate the a, b and c diagonals, and the constants, for the tridiagonal system that gives the moments
    M[0] = 0.; // Natural constrains
    M[n] = 0.;
    for(int i = 1; i < n; i++) {
        // The indexes of a, b, c and M are off by 1 as the d3 function takes vectors starting at 0
        a[i-1] = h[i] / 6.;
        b[i-1] = (h[i] + h[i+1]) / 3.;
        c[i-1] = h[i+1] / 6.;
        M[i-1] = (y[i+1] - y[i])/h[i+1] - (y[i] - y[i-1])/h[i];
    }

    // CHECK HERE IS VALUES M[0] AND M[n] ARE STILL 0
    printf("M[0] = %25.16lf\n", M[0]);
    printf("M[n] = %25.16lf\n", M[n]);

    // Solve the tridiagonal system, the solutions are stored in M
    d3(n-1, a, b, c, M, 1e-10);

    // Calculate A and B
    for(int i = 0; i < n; i++) {
        B[i] = y[i] - M[i]*pow(h[i-1],2)/6.;
        A[i] = (y[i+1] - y[i])/h[i] - h[i]*(M[i+1] - M[i])/6.;
    }


    /* Old gerard code semiadapted; needs indexes of M reduced
    B[0] = y[0];
    A[0] = ((y[1] - y[0]) / h[0]) - (h[0] * M[0] / 6.);
    for(int i = 1; i < n-1; i++) {
        B[i] = y[i] - M[i-1]*h[i]*h[i]/6.;
        A[i] = (y[i+1] - y[i])/h[i] - h[i]*(M[i] - M[i-1])/6.;
    }
    B[n-1] = y[n-1] - (M[n-2]*h[n-1]*h[n-1]/6.);
    A[n-1] = (y[n] - y[n-1])/h[n-1] + h[n-1]*M[n-2]/6.;
     */

    // Evaluation
    double z, eval;

    /**
     * Evaluates S at z
     * @param z Point to evaluate at; must be x[0] <= z <= z[n]
     * @return Value of S ar z
     */
    double S(double z) {
        for(int i = 0; i < n; i++) {
            if(x[i] <= z || z <= x[i+1]) {
                return M[i]*pow(x[i+1] - z, 3)/(6.*h[i+1]) + M[i+1]*pow(z - x[i], 3) + A[i]*(z - x[i]) + B[i];
            }
        }
        return 0.; // z outside interpolation domain
    }

    double heval = (x[n] - x[0])/m;
    double xeval = x[0];
    for(int i = 0; i <= m; i++) {
        printf("S(%25.16lf) = %25.16lf\n", xeval, S(xeval));
        xeval += heval;
    }

    /* Gerard
    // Primer punt
    z = x[0];
    eval = (M[0] * pow(z - x[0], 3)) / (6.0 * h[0]) + (A[0] * (z - x[0])) + B[0];
    printf("%25.16lf %25.16lf\n", z, eval);

    // Primer spline
    for(int i = 0; i < m; i++) {
        z = x[0] + ((x[1] - x[0]) * (i+1) / (m + 0.0));
        eval = (M[0] * pow(z - x[0], 3)) / (6.0 * h[0]) + (A[0] * (z - x[0])) + B[0];
        printf("%25.16lf %25.16lf\n", z, eval);
    }

    // Segon a penultim spline
    for(int j = 1; j < n-1; j++) {
        for(int i = 0; i < m; i++) {
            z = x[j] + ((x[j+1] - x[j]) * (i+1) / (m + 0.0));
            eval = (((M[j-1] * pow(x[j+1] - z, 3)) + (M[j] * pow(z - x[j], 3))) / (6.0 * h[j])) + (A[j] * (z - x[j])) + B[j];

            printf("%25.16lf %25.16lf\n", z, eval);
        }
    }

    // Ultim spline
    for(int i = 0; i < m; i++) {
        z = x[n-1] + ((x[n] - x[n-1]) * (i+1) / (m + 0.0));
        eval = (M[n-2] * pow(x[n] - z, 3)) / (6.0 * h[n-1]) + (A[n-1] * (z - x[n-1])) + B[n-1];
        printf("%25.16lf %25.16lf\n", z, eval);
    }
    */

}