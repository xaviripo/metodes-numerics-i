void difdiv(int n, double *x, double *f) {
    for(int i = 1; i <= n; i++) { // Left to right, 1 ... n; we can skip 0 because it's the initial state
        for(int j = n; j >= i; j--) { // Bottom to top, n ... i
            f[j] = (f[j] - f[j-1])/(x[j]- x[j-i]);
        }
    }
}

double horner(double z, int n, double *x, double *c) {
    double p = c[n];
    for(int i = n-1; i >= 0; i--) {
        p = p*(z - x[i]) + c[i];
    }
    return p;
}