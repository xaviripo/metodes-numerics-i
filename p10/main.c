#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double f(double x) {
	return 1./(1+x);
}

double T2n(int n, double a, double b, double T_half) {
	double sum = 0, h = (b-a)/n;
	int i;
	for(i = 1; i < n; i += 2) {
		sum += f(a+i*h);
	}
	return .5*(T_half) + h*sum;
}


double T(double a, double b, double prec) {
	double T_old, T_new; int n, max;
	max = pow(2, 20);
	n = 1;
	T_old = 0;
	T_new = .5*(b-a)*(f(a)+f(b));
	while(fabs(T_old - T_new) >= prec && n < max) {
		T_old = T_new;
		n *= 2;
		T_new = T2n(n, a, b, T_old);
		printf("Resultat amb n=%d:\t%25.16lf\n", n, T_new);
	}
	return T_new;
}



int main(void) {
	T(0., 1., 1e-12);
	return 0;
}
