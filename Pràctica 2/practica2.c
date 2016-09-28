#include <stdio.h>
#include <math.h>

/************ Exercici 1 ************/

double taylor(double x, double tolerance) {
	
	double result = 0;
	double term = 1;
	int i = 0;

	while(fabs(term) >= tolerance) {
		result += term;
		term *= x/++i;
	}

	return result;

}

void exercici1(double tolerance) {
	int i;
	for(i = -1; i >= -25; i--) {
		printf("x: %25d, tolerance: %25.15f, result: %25.15f\n", i, tolerance, taylor(i, tolerance));
	}
}

/************ main ************/

int main(void) {
	
	exercici1(1e-15);	

	return 0;
	
}

