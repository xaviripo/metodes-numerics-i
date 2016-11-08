#include <stdio.h>
#include <math.h>

/************ main ************/

int main(void) {

	double u = 1;
	int i, stop = 0;

	for(i = -1; !stop; i--) {
		u /= 2.;
		stop = (1.+u == 1.);
		printf("1 + u: %.50lf, u: %.50f\n", 1+u, u);
	}

	printf("u: %.100lf\n", u);
	return 0;

}
