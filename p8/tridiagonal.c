/*RESOL UNA MATRIU DIAGONAL BANDA*/
/*	(b	c	0	0	0)
	(a	b	c	0	0)
	(0	a	b	c	0)
	(0	0	a	b	c)
	(0	0	0	a	b)
n = dimensio, (a,b,c) bandes diagonals vectors de dimensio (n,n+1,n), f = vector solucio inicial del sistema (on es guardaran les noves solucions), tol = tolerancia pel 0*/
int d3(int n, double *a, double *b, double *c, double *f, double tol) {

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
