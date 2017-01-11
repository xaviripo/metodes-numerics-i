#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*f0)(double, double);

double feval(double x) {
    // WRITE YOUR FUNCTION CODE HERE
    return cos(x);
}

/**
 * Approximates a given formula through Richardson extrapolation
 * @param a Initial point
 * @param hinit Initial step
 * @param q Step change factor
 * @param prec Precision
 * @param k Maximum iterations
 */
void derivative_common(double a, double hinit, int q, double prec, int k, f0 formula) {
    // To store previous results in in order to avoid recursion
    double **M;

    // Allocating M
    M = (double **) malloc(k*sizeof(double *));
    for(int i = 0; i < k; i++) M[i] = (double *) malloc((i+1)*sizeof(double));

    // Matrix filling
    int stop = 0;
    for(int i = 0; i < k && !stop; i++) {
        M[i][0] = formula(a, hinit/pow(q,i));
        for(int j = 1; j <= i; j++) {
            M[i][j] = (pow(q, 2*i)*M[i][j-1] - M[i-1][j-1]) / (pow(q, 2*i) - 1);
            printf("M[%d][%d] = %25.16lf\n", i, j, M[i][j]);
        }
        stop = (i > 0) ? (fabs(M[i][i] - M[i-1][i-1]) < prec) : 0;
    }
}

/**
 * Approximates the first derivative of feval with the F0 and Fi formulas
 * @param a Initial point
 * @param hinit Initial step
 * @param q Step change factor
 * @param prec Precision
 * @param k Maximum iterations
 */
void derivative_1(double a, double hinit, int q, double prec, int k) {
    // Formula for 1st derivative
    double F0_1(double a, double h) {
        return (feval(a + h) - feval(a - h)) / (2 * h);
    }
    derivative_common(a, hinit, q, prec, k, F0_1);
}

/**
 * Approximates the second derivative of feval with the F0 and Fi formulas
 * @param a Initial point
 * @param hinit Initial step
 * @param q Step change factor
 * @param prec Precision
 * @param k Maximum iterations
 */
void derivative_2(double a, double hinit, int q, double prec, int k) {
    // Formula for 2nd derivative
    double F0_2(double a, double h) {
        return (feval(a + h) - 2*feval(a) + feval(a - h)) / pow(h,2);
    }
    derivative_common(a, hinit, q, prec, k, F0_2);
}

void derivatives_table(double a, double hinit, double prec) {
    double table(double x) {
        switch((int)(x*10)) {
            case 4:
                return 0.7891;
            case 12:
                return 1.9827;
            case 16:
                return 2.5176;
            case 18:
                return 2.7633;
            case 20:
                return 2.9923;
            case 22:
                return 3.2048;
            case 24:
                return 3.4027;
            case 28:
                return 3.7636;
            case 36:
                return 4.4051;
            default:
                return 0.;
        }
    }
    // Formula for 1st derivative
    double F0_1(double a, double h) {
        return (feval(a + h) - feval(a - h)) / (2 * h);
    }
    // Formula for 2nd derivative
    double F0_2(double a, double h) {
        return (feval(a + h) - 2 * feval(a) + feval(a - h)) / pow(h, 2);
    }
    derivative_common(a, hinit, 2, prec, 3, F0_1);
    printf("\n");
    derivative_common(a, hinit, 2, prec, 3, F0_2);
}