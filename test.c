#include "matrix.h"


void e1(int n, double tol) {
	double** A = matrix_create(n);
	printf("\n");
	double* b = vector_create(n);
	printf("\n");
	palu(n, A, b, tol);

	vector_print(n, b);
	printf("\n");
	matrix_print(n, A);
}

void e2(int n, double tol) {
	double* a = vector_create(n-1); printf("\n");
	double* b = vector_create(n); printf("\n");
	double* c = vector_create(n-1); printf("\n");
	palu_d3(n, a, b, c, tol);

	vector_print(n-1, a);
	vector_print(n, b);
	vector_print(n-1, c);
}

int main() {
	double tol = 1e-10;
	int n;
	printf("Enter matrix/vector size: ");
	scanf("%d", &n);
	e1(n, tol);

	return 0;
}
