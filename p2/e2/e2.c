#include <stdio.h>
#include <math.h>

/************ main ************/

int main(void) {

	int N, n; double e, temp;

	e = exp(1.0);
	temp = e - 1;
	scanf("%d", &N);
	for(n = 0; n <= N; n++) {
		temp = e - n*temp;
		printf("n: %d, y_n: %25.15f\n", n, temp);
	}

	printf("\n");

	temp = (e+1)/(2*(N+1));
	for(n = 2*N; n >= N; n--) {
		temp = (e-temp)/(n+1);
		printf("n: %d, y_n: %25.15f\n", n, temp);
	}

	return 0;
}
