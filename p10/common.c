#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Function to integrate
 * @param x Point to evaluate at
 * @return Value of function at x
 */
double feval(double x) {
    // CHANGE THIS FOR DESIRED FUNCTION
    return 1./(1+x);
}

/**
 * Auxiliar function for duplicating the number of points at which the trapezoid method is applied
 * @param n NEW number of points (which must equal the old n times 2)
 * @param a Lower integral bound
 * @param b Upper integral bound
 * @param T_half Value of the approximation with n/2 points
 * @return New approximation of the integral
 */
double T2n(int n, double a, double b, double T_half) {
    double sum = 0, h = (b-a)/n;
    int i;
    for(i = 1; i < n; i += 2) {
        sum += feval(a + i*h);
    }
    return .5*(T_half) + h*sum;
}

/**
 * Gives an approximation of the integral from a to b (a > b) of function feval with maximum error prec
 * @param a Lower integral bound
 * @param b Upper integral bound
 * @param prec Error at which to stop
 * @return Approximation of integral
 */
double T(double a, double b, double prec, int max) {
    double T_old, T_new;
    int n;
    n = 1;
    T_old = 0;
    T_new = .5*(b-a)*(feval(a)+ feval(b));
    while(fabs(T_old - T_new) >= prec && n < max) {
        T_old = T_new;
        n *= 2;
        T_new = T2n(n, a, b, T_old);
        printf("{Integral with n = %d}\t= %25.16lf\n", n, T_new);
    }
    return T_new;
}

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
        printf("M[%d][0]\t= %25.16lf\n", i, M[i][0]);
        for (int j = 1; j <= i; j++) {
            M[i][j] = (pow(q, p(i,j))*M[i][j-1] - M[i-1][j-1]) / (pow(q, p(i,j)) - 1);
            printf("M[%d][%d]\t= %25.16lf\n", i, j, M[i][j]);
        }
        stop = (i > 0) ? (fabs(M[i][i] - M[i-1][i-1]) < prec) : 0;
    }

    return M[i-1][i-1];

}

void romberg() {
    double h_init = pow(2,12); // Not used, only needed because of richardson function implementation
    double q = 2;
    double prec = 1e-12;
    int k = 100;
    int p(int i, int j) {
        return 2*j;
    }
    double formula(double h) {
        return  T(0, 1, prec, (int)(h_init / h));
    }

    richardson(h_init, q, p, formula, prec, k);

}
