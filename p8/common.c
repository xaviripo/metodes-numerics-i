#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Solves for f in the tridiagonal system Mf = c
 * @param n Size of the tridiagonal matrix A, i.e. size of arrays a, b, c and f
 * @param a Sudiagonal of M, taken elements a[1] through a[n-1] inclusive
 * @param b Main diagonal of M, taken elements a[0] through a[n-1] inclusive
 * @param c Superdiagonal of M, taken elements a[0] through a[n-2] inclusive
 * @param f Initially contains the constants c, replaced with the solution x
 * @param tol Tolerance for 0 (currently unused, kept for function header backwards compatibility)
 */
void d3(int n, double *a, double *b, double *c, double *f, double tol) {

    c[0] /= b[0];
    f[0] /= b[0];

    printf("Before d3\n");
    for(int i = 0; i < n; i++) {
        printf("f[%d] = %25.16lf\n", i, f[i]);
    }

    double aux;
    for (int i = 1; i < n; i++) {
        aux = 1.0/(b[i] - a[i]*c[i-1]);
        c[i] *= aux;
        f[i] = (f[i] - a[i]*f[i-1])*aux;
    }

    for (int i = n-2; i >= 0; i--) {
        f[i] -= c[i]*f[i + 1];
    }

}

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

    // Solve the tridiagonal system, the solutions are stored in M
    d3(n-1, a, b, c, M, 1e-10);

    for(int i = 0; i <= n; i++) {
        printf("M[%d] = %25.16lf\n", i, M[i]);
    }

    // Calculate A and B
    for(int i = 0; i < n; i++) {
        B[i] = y[i] - M[i]*pow(h[i-1],2)/6.;
        A[i] = (y[i+1] - y[i])/h[i] - h[i]*(M[i+1] - M[i])/6.;
    }

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

}