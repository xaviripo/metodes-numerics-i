#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
//Declaracions:
int main();
void exercici1();
void print_matrix(int m, int n, double **M);
void print_vector(int n, double *vector);
double** matrix_write(int m, int n, double **M);
double** matrix_alloc(int m, int n);
int matrix_dealloc(int m, int n, double** M);
double* vector_alloc(int n);
int vector_dealloc(double* vector);
double* vector_write(int n, double *vector);
int resoltrisup(int n, double **A, double *b, double tol);
int gauss (int n, double **A, double *b, double tol);
int gauss2 (int n, double **A, double tol);
double determinant(int n, double **matriu, double tol);
void vectorResidu(int mida, double *coeficientsOriginals, double **matrixN, double *solucions, double *vectorResidu);
double determinantTriangularSuperior(int n, double **matriu);
double** matrix_write_Hilbert(int n, double **M);
double* vector_write_Hilbert(int n, double *vector, double **matrix);
void producte_de_matrius_nxn_nx1(int n, double **matrixN, double *vectorN, double *vectorTotal);
void exercici2();
//Implementacions
int main() {
	exercici1();
	exercici2();
}

void exercici1() {
	//Primer obtenim les dades de la matriu
	double **matriuDelSistema;
	double **matriuDelSistemaOriginal;
	double *coeficientsB;
	double *coeficientsBOriginal;
	double *vectorResidus;
	int midaMatriu;
	printf("Introdueixi la mida de la matriu quadrada:\n");
	scanf("%d", &midaMatriu);
	printf("\nIntrodueix els coeficients de la matriu: \n");
	matriuDelSistema = matrix_alloc(midaMatriu, midaMatriu);
	matriuDelSistemaOriginal = matrix_write(midaMatriu, midaMatriu, matriuDelSistema);
	printf("\nIntrodueix els coeficients de B: \n");
	coeficientsB = vector_alloc(midaMatriu);
	coeficientsBOriginal = vector_write(midaMatriu, coeficientsB);
	printf("\nMatriu\n");
	print_matrix(midaMatriu, midaMatriu, matriuDelSistemaOriginal);
	printf("\nVector de coeficients\n");
	print_vector(midaMatriu, coeficientsBOriginal);
	printf("\nMatriu Reduida (Gauss)\n");
	gauss(midaMatriu, matriuDelSistema, coeficientsB, 10e-16);
	print_matrix(midaMatriu, midaMatriu, matriuDelSistema);
	printf("\nVector coeficients reduits (Gauss)\n");
	print_vector(midaMatriu, coeficientsB);
	resoltrisup(midaMatriu, matriuDelSistema, coeficientsB, 10e-16);
	printf("\nSolució del sistema\n");
	print_vector(midaMatriu, coeficientsB);
	printf("\nDeterminant (A)\n %lf", determinantTriangularSuperior(midaMatriu, matriuDelSistema));
	vectorResidus = vector_alloc(midaMatriu);
	vectorResidu(midaMatriu, coeficientsBOriginal, matriuDelSistemaOriginal, coeficientsB, vectorResidus);
	printf("\nVector de residus\n");
	print_vector(midaMatriu, vectorResidus);
}
/*
* El que passa és que la matriu de Hilbert està mal condicionada. Com més augmentem
* la mida de la matriu més petits són els seus coeficients i per tant més prop de
* l'error de l'arrodoniment. La divisió creix exponencialment quan més t'apropis a 0
*/
void exercici2() {
	double **matriuDelSistema;
	double **matriuDelSistemaOriginal;
	double *coeficientsB;
	double *coeficientsBOriginal;
	double *vectorResidus;
	int midaMatriu;
	printf("Introdueixi la mida de la matriu quadrada:\n");
	scanf("%d", &midaMatriu);
	matriuDelSistema = matrix_alloc(midaMatriu, midaMatriu);
	matriuDelSistemaOriginal = matrix_write_Hilbert(midaMatriu, matriuDelSistema);
	coeficientsB = vector_alloc(midaMatriu);
	coeficientsBOriginal = vector_write_Hilbert(midaMatriu, coeficientsB, matriuDelSistemaOriginal);
	printf("\nMatriu\n");
	print_matrix(midaMatriu, midaMatriu, matriuDelSistemaOriginal);
	printf("\nVector de coeficients\n");
	print_vector(midaMatriu, coeficientsBOriginal);
	printf("\nMatriu Reduida (Gauss)\n");
	gauss(midaMatriu, matriuDelSistema, coeficientsB, 10e-16);
	print_matrix(midaMatriu, midaMatriu, matriuDelSistema);
	printf("\nVector coeficients reduits (Gauss)\n");
	print_vector(midaMatriu, coeficientsB);
	resoltrisup(midaMatriu, matriuDelSistema, coeficientsB, 10e-16);
	printf("\nSolució del sistema\n");
	print_vector(midaMatriu, coeficientsB);
	printf("\nDeterminant (A)\n %lf", determinantTriangularSuperior(midaMatriu, matriuDelSistema));
	vectorResidus = vector_alloc(midaMatriu);
	vectorResidu(midaMatriu, coeficientsBOriginal, matriuDelSistemaOriginal, coeficientsB, vectorResidus);
	printf("\nVector de residus\n");
	print_vector(midaMatriu, vectorResidus);
}
/*
* Crea la matriu de coeficients tal que la solució del sistema sigui
(1, ..., 1)
*/
double* vector_write_Hilbert(int n, double *vector, double **matrix) {
	double suma;
	double *copia = vector_alloc(n);
	for(int i= 0; i<n; i++) {
		suma = 0;
		for(int j= 0; j<n; j++)
			suma += matrix[i][j];
		copia[i] = vector[i] = suma;
	}
	return copia;
}
/*
*Fa el producte de la matriu i el vector i ho guarda al vector residus
*/
void producte_de_matrius_nxn_nx1(int n, double **matrixN, double *vectorN, double *vectorTotal) {
	double total;
	for(int i=0; i<n;i++) {
		total = 0;
		for(int j=0; j<n;j++) {
			total += matrixN[i][j]*vectorN[j];
		}
		vectorTotal[i] = total;
	}
}
//Resol un sistema lineal Ax=b
int resoltrisup(int n, double **A, double *b, double tol) {
	double suma;
	bool toleranciaInferior = true;
	int fila = n-1;
	//Recorrem totes les files comprobant si la tolerància és menor a la font d'error.
	while (fila >= 0 && toleranciaInferior) {
		//Comprobem si la tolerancia és inferior al element de la diagonal.
		if(fabs(A[fila][fila]) < tol) {
			toleranciaInferior = false;
			continue;
		}
		//La tolerància és inferior al element de la diagonal si arribem aquí
		suma = b[fila];
		for(int columna = fila + 1; columna <= n-1; columna++)
				suma -= A[fila][columna]*b[columna];
		b[fila] = suma/A[fila][fila]; //Element de la diagonal
	fila--;
	}
	if(toleranciaInferior)
		return 0; //Tot ha sortit correcte.
	else //En cas que la tolerància no sigui inferior.
		return -1;
}
//Realitza eliminació Gaussiana de una matriu sense pivotatge.
int gauss (int n, double **A, double *b, double tol) {
		int columna = 0;
		int multiplicadorActual;
		bool toleranciaInferior = true;
		while(columna < n-1 && toleranciaInferior) {
			if(fabs(A[columna][columna]) < tol) {
				toleranciaInferior = false;
				continue;
			}
			for(int fila = columna+1; fila <= n-1; fila++) {
				A[fila][columna] = A[fila][columna]/A[columna][columna]; //Multplicador
				for(int columnaSecundaria = columna + 1; columnaSecundaria <= n-1; columnaSecundaria++)
					A[fila][columnaSecundaria] -= A[fila][columna]*A[columna][columnaSecundaria]; //Aquí l'atribut columna que està en fila és la fila original
				b[fila] -= A[fila][columna]*b[columna];
			}
			columna++;
		}
		if(toleranciaInferior)
			return 0; //Tot ha sortit correcte.
		else //En cas que la tolerància no sigui inferior.
			return -1;
}
//Realitza eliminació Gaussiana de una matriu sense pivotatge.
int gauss2 (int n, double **A, double tol) {
		int columna = 0;
		int multiplicadorActual;
		bool toleranciaInferior = true;
		while(columna < n-1 && toleranciaInferior) {
			if(fabs(A[columna][columna]) < tol) {
				toleranciaInferior = false;
				continue;
			}
			for(int fila = columna+1; fila <= n-1; fila++) {
				A[fila][columna] = A[fila][columna]/A[columna][columna]; //Multplicador
				for(int columnaSecundaria = columna + 1; columnaSecundaria <= n-1; columnaSecundaria++)
					A[fila][columnaSecundaria] -= A[fila][columna]*A[columna][columnaSecundaria]; //Aquí l'atribut columna que està en fila és la fila original
			}
			columna++;
		}
		if(toleranciaInferior)
			return 0; //Tot ha sortit correcte.
		else //En cas que la tolerància no sigui inferior.
			return -1;
}
/*
*Aquest mètode permet escriure una matriu de mida m, n coeficient a coeficient.
*Retorna una còpia de la matriu M, opcional per guardar el sistema original.
*/
double** matrix_write(int m, int n, double **M) {
	double **copia = matrix_alloc(m, n);
	int i, j;
	for(i = 0; i<m; i++) {
		for(j = 0; j<n; j++) {
			printf("\nIntrodueixi el element %d, %d:\n", i, j);
			scanf("%lf", &(M[i][j]));
			copia[i][j] = M[i][j];
		}
	}
	return copia;
}
double** matrix_write_Hilbert(int n, double **M) {
	double **copia = matrix_alloc(n, n);
	int i, j;
	for(i = 0; i<n; i++) {
		for(j = 0; j<n; j++) {
			M[i][j] = 1./(i+j-1.+2.); //Sumem dos perque sempre estem una fila i columna anteriors.
			copia[i][j] = M[i][j];
		}
	}
	return copia;
}
/*
*Permet introduir les dades de un vector
*/
double* vector_write(int n, double *vector) {
	double *copia = vector_alloc(n);
	for(int i = 0; i < n; i++) {
		printf("\nIntrodueixi el element %d:\n", i);
		scanf("%lf", &(vector[i]));
		copia[i] =vector[i];
	}
	return copia;
}
/*
* Permet guardar un vector a memòria
*/
double* vector_alloc(int n) {
	double *copia = malloc(n*sizeof(double));
	return copia;
}
int vector_dealloc(double* vector) {
	free(vector);
	return 1;
}
/*
*Permet eliminar un vector a memoria
*/
/*
* Imprimeix la matriu en forma matricial
*/
void print_matrix(int m, int n, double **M) {
	for(int i = 0; i < m; i++) {
		printf("|    ");
		for(int j = 0; j<n; j++)
			printf("%lf    " , M[i][j]);
		printf("|\n");
	}
}
void print_vector(int n, double *vector) {
	for(int i = 0; i< n; i++) {
		printf("|    %lf    |\n", vector[i]);
	}
}
double** matrix_alloc(int m, int n) {
	double **matrix_elem;
	matrix_elem = malloc(m*sizeof(double));
	for(int i = 0; i < m; i++)
		*(matrix_elem+i) = malloc(n*sizeof(double));
	return matrix_elem;
}
//Retorna 1 si la matriu s'ha desfet correctament
int matrix_dealloc(int m, int n, double** M) {
	//Liberem l'espai per a totes les columnes
	for(int i = 0; i < m; i++)
		free(M[i]);
	//Liberem l'espai de totes les files
	free(M);
	return 1;
}
/*
* Calcula el determinant d'una matriu nxn passada per paràmetre.
*A més dóna la matriu triangulada (triangular superior).
* Es defineix una tolerància per fer l'eliminació Gaussiana
*/
double determinant(int n, double **matriu, double tol) {
	gauss2(n, matriu, tol);
	double determinant = 1;
	for(int i= 0; i<n; i++)
		determinant *= matriu[i][i];
	return determinant;
}
/*
* Retorna el determinant de una matriuTriangular superior
*/
double determinantTriangularSuperior(int n, double **matriu) {
	double determinant = 1;
	for(int i= 0; i<n; i++)
		determinant *= matriu[i][i];
	return determinant;
}
/*
* Determina el vector residu r = b-Ax on Ax = b', què és b després d'aplicar
* transformacions. El vector residus ha de tenir mida n
*/
void vectorResidu(int mida, double *coeficientsOriginals, double **matrixN, double *solucions, double *vectorResidu) {
	producte_de_matrius_nxn_nx1(mida, matrixN, solucions, vectorResidu);
	for(int i = 0; i<mida; i++)
		vectorResidu[i] = coeficientsOriginals[i] - vectorResidu[i];
}
