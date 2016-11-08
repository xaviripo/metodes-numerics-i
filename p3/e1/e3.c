#include <stdio.h>

void polynomialPrint(double* p, int n);
void polynomialRead(double* p, int n);

int main(void) {

	int n;


	scanf("%d", &n);
	/*double[n+1] c; (double*) malloc((n+1)*sizeof(double));*/
	/*double z[n], c[n];*/ /*(double*) malloc((n+1)*sizeof(double));*/
	double* z = (double*) malloc(n*sizeof(double));
	double* c = (double*) malloc(n*sizeof(double));
	int i, j;
/*
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lf", &z[i]);
	}*/
	polynomialRead(z, n);

	c[0] = 1;
	for(i = 0; i < n; i++) {

		printf("\nIteració número %d: ", i);

		for(j = i; j >= 0; j--) {

			c[j+1] = c[j];

		}

		c[0]=0;
/*
		for(j = 0; j <= i+1; j++) {
			c[j] -= c[j+1] * z[i];
			printf("%+8.8lf x^%d ", c[j], j);
		}

*/
		polynomialPrint(c, n);
	}

	double epsilon = 1e-6;
	printf("\nPer a epsilon = %lf:\n", epsilon);
	c[n-1] *= epsilon;

	polynomialPrint(c, n);

	printf("\n");

	return 0;
}

void polynomialPrint(double* p, int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("%+8.8lf x^%d ", p[i], i);
	}
}

void polynomialRead(double* p, int n) {
	int i;
	for(i = 0; i < n; i++) {
		scanf("%lf", &p[i]);
	}
}
