/*RESOL UNA MATRIU DIAGONAL BANDA*/
#include <stdio.h>

/*	(b	c	0	0	0)
	(a	b	c	0	0)
	(0	a	b	c	0)
	(0	0	a	b	c)
	(0	0	0	a	b)
n = dimensio, (a,b,c) bandes diagonals vectors de dimensio (n,n+1,n), f = vector solucio inicial del sistema (on es guardaran les noves solucions), tol = tolerancia pel 0*/
int d3_GERARD(int n, double *a, double *b, double *c, double *f, double tol) {

    c[0] = c[0] / b[0];

    for(int i = 1; i < n-1; i++) {
        c[i] = c[i] / (b[i] - (c[i-1] * a[i-1]));
    }

    f[0] = f[0] / b[0];
    for(int i = 1; i < n; i++) {
        f[i] = (f[i] - (f[i-1] * a[i-1])) / (b[i] - (c[i-1] * a[i-1]));
    }

    for(int i = n-2; i > -1; i--) {
        f[i] = f[i] - (c[i] * f[i+1]);
    }

    return 0;
}


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

    printf("After d3\n");
    for(int i = 0; i < n; i++) {
        printf("f[%d] = %25.16lf\n", i, f[i]);
    }

}
