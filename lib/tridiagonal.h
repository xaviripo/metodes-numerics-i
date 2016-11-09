int palu_d3(int n, double* a, double* b, double* c, double tol) {
	int k;
	double m;

	for (k = 0; k < n - 1; k++) {
		if (fabs(c[k+1]) < tol) {
            return 1;
        }
		m = b[k]/c[k+1];
		c[k+1] = m;
		b[k+1] -= m*a[k];
	}

	return 0;
}

void substitucio_endavant_d3(int n, double *l, double *b) {
	/* supongamos l la diagonal inferior (la diagonal central esta
	 * compuesta de 1s, y b el vector de los coeficientes.
	 *
	 * supongamos que l empieza en l[1] y acaba en l[-1] */
	int k, i;

	for (k = 1; k < n; k++) {
		b[k] = b[k] - l[k]*b[k-1];
	}
}

int substitucio_endarrere_d3(int n, double *a, double *b, double *y, double tol) {
	int k;

	y[n-1] = y[n-1]/b[n-1];
	for (k = n-2; k >= 0; k--) {
		if (fabs(b[k]) < tol){
            return 1;
        }
		y[k] = (y[k] - a[k]*y[k-1])/b[k];
	}
	return 0;
}

int d3(int n, double *a, double *b, double *c, double *f, double tol) {
	/*
	 * Suposem que a és la diagonal superior, b la central
	 * i c la inferior
	 * Suposem que el vector c comenÃ§a en c[1] i que a
	 * acaba en a[n-1]
	 */

	if (palu_d3(n, a, b, c, tol)) {
        return 1;
    }
	substitucio_endavant_d3(n, c, f);
	if (substitucio_endarrere_d3(n, a, b, f, tol)) {
        return 1;
    }

	return 0;
}
