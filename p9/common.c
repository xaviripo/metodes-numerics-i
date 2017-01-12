#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Accelerates a given sequence through Richardson extrapolation
 * @param h Initial step
 * @param q Step change factor
 * @param p Exponents of h in the approximation error in function of i and j
 * @param formula Sequence to accelerate; must take h as only parameter
 * @param prec Precision
 * @param k Maximum number of iterations
 */
double richardson(double h, double q, int (*p)(int,int), double (*formula)(double), double prec, int k) {
    // To store previous results in in order to avoid recursion
    double **M;

    // Allocating M; it's a triangular matrix
    M = (double **) malloc(k*sizeof(double *));
    for(int i = 0; i < k; i++) M[i] = (double *) malloc((i+1)*sizeof(double));

    // Matrix filling
    int i, stop = 0;
    for(i = 0; i < k && !stop; i++) {
        M[i][0] = formula(h / pow(q, i));
        printf("M[%d][0] = %25.16lf\n", i, M[i][0]);
        for (int j = 1; j <= i; j++) {
            M[i][j] = (pow(q, p(i,j))*M[i][j-1] - M[i-1][j-1]) / (pow(q, p(i,j)) - 1);
            printf("M[%d][%d] = %25.16lf\n", i, j, M[i][j]);
        }
        stop = (i > 0) ? (fabs(M[i][i] - M[i-1][i-1]) < prec) : 0;
    }

    return M[i-1][i-1];

}

/**
 * Approximates the first derivative of f through Richardson extrapolation
 * @param a Initial point
 * @param h Initial step
 * @param q Step change factor
 * @param prec Precision
 * @param k Maximum number of iterations
 * @return Approximation of the first derivative
 */
double derivative_1(double a, double h, int q, double (*f)(double), double prec, int k) {
    // Formula for 1st derivative
    double formula(double h) {
        return (f(a+h) - f(a-h))/(2*h);
    }

    int p(int i, int j) {
        return 2*i;
    }

    return richardson(h, q, p, formula, prec, k);

}

/**
 * Approximates the second derivative of f through Richardson extrapolation
 * @param a Initial point
 * @param h Initial step
 * @param q Step change factor
 * @param prec Precision
 * @param k Maximum number of iterations
 * @return Approximation of the second derivative
 */
double derivative_2(double a, double h, int q, double (*f)(double), double prec, int k) {
    // Formula for 2nd derivative
    double formula(double h) {
        return (f(a+h) - 2*f(a) + f(a-h)) / pow(h,2);
    }

    int p(int i, int j) {
        return 2*i;
    }

    return richardson(h, q, p, formula, prec, k);

}