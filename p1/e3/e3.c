#include <stdio.h>
#include <math.h>

/************ main ************/

int main(void) {

	double x, e, epsilon = -1.0;
	float a;

	for(x = 0.01; x <= 1000.00; x += 0.01) {
		a = x;
		e = fabs((a-x)/x);
		epsilon = fmax(e, epsilon);
		printf("x: %07.2lf, a: %011f, e: %.100lf\n", x, a, e);
	}

	printf("epsilon: %.100lf\n", epsilon);
	return 0;

}
