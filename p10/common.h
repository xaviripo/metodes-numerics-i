#ifndef P10_SOURCE_H
#define P10_SOURCE_H

double feval(double x);
double T2n(int n, double a, double b, double T_half);
double T(double a, double b, double prec, int max);
double richardson(double h, double q, int (*p)(int,int), double (*formula)(double), double prec, int k);
void romberg();

#endif //P10_SOURCE_H
