#ifndef P9_SOURCE_H
#define P9_SOURCE_H

double richardson(double h, double q, double (*formula)(double), double prec, int k);
double derivative_1(double a, double h, int q, double (*f)(double), double prec, int k);
double derivative_2(double a, double h, int q, double (*f)(double), double prec, int k);
double derivatives_table(double a, double h, double prec);

#endif //P9_SOURCE_H
