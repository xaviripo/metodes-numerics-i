#include <stdio.h>

/************ Exercici 1 ************/



void exercici1(int n, double* z) {

	int i,j;
	double c[n];
	c[0] = 1;
	for(i = 0; i < n; i++) {
		
		printf("\nIteració número %d: ", i);
		
		for(j = i; j >= 0; j--) {

			c[j+1] = c[j];

		}

		c[0]=0;
		
		for(j = 0; j <= i+1; j++) {
			
			c[j] -= c[j+1] * z[i];
			printf("%25.16lf x^%d ", c[j], j);
			
		}

	}
	
	printf("\n");
	
	


}

/************ main ************/

int main(void) {
	
	int n;
	double *c, *z;
	
	scanf("%d", &n);
	
	c = (double*) malloc((n+1)*sizeof(double));
	z = (double*) malloc((n+1)*sizeof(double));
	
	int i;
	for(i = 0; i < n; i++) {
		scanf("%lf", &z[i]);
	}
	
	exercici1(n, z);

	return 0;
	
}

