#ifndef P8_TRIDIAGONAL_H
#define P8_TRIDIAGONAL_H

int palu_d3(int n, double* a, double* b, double* c, double tol);
void substitucio_endavant_d3(int n, double *l, double *b);
int substitucio_endarrere_d3(int n, double *a, double *b, double *y, double tol);
int d3(int n, double *a, double *b, double *c, double *f, double tol);

#endif //P8_TRIDIAGONAL_H
