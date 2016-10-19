#include <stdio.h>
#include <math.h>

/************ Exercici 1 ************/



int gauss (int n, double **A, double *b, double tol) {
	
	int i, j, k;
	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {
			
			if(fabs(A[k][k]) < tol) return 1;
			
			A[i][k] /= A[k][k];
			
			for(k=i+1; k<n; k++) {
				A[j][k] -= A[i][k]*A[j][i];
			}
			
			b[j]=A[j][i]*b[i];
			
		}
	}
	
	return 0;
	
}



int resoltrisup(int n, double **A, double *b, double tol) {
	
	double acc;
	int i, j;
	for(i=n-1; i>=0; i--) {
		
		acc = 0;
		for(j=n-1; j>i; j--) {
			
			if(fabs(A[i][j]) < tol) return 1;
			
			acc += b[j]*A[i][j];
			
		}
		
		b[i] = -acc/A[i][j];
		
	}
	
	return 0;
	
}



void vector_read(int n, double *v) {
	
	int i;
	for(i=0; i<n; i++) {
		
		printf("Posició %d: ", i);
		scanf("%lf\n", &(v[i]));
		
	}
	
}



void matrix_read(int n, double **M) {
	
	int i, j;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			printf("Fila %d, columna %d: ", i, j);
			scanf("%lf\n", &(M[i][j]));
		}
	}
	
}



void vector_print(int n, double *v) {
	
	int i;
	for(i=0; i<n; i++) {
		
		printf("Posició %d: %lf\n", i, v[i]);
		
	}
	
}



/************ main ************/

int main(void) {
	
	int n;
	double **A, *b, tol = 1e-15;
	
	printf("Mida del sistema: ");
	scanf("%d", &n);
	
	matrix_read(n, A);
	vector_read(n, b);
	
	gauss(n, A, b, tol);
	resoltrisup(n, A, b, tol);
	
	vector_print(n, b);
	
	return 0;
	
}


