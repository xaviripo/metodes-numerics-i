#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
//Declarations
int main();
int palu(int n, double **A, int *p, double tol);
void exercici1();
void exercici2();
int* vector_alloc(int n);
int vector_dealloc(int* vector);
void print_matrix(int m, int n, double **M);
void print_vector(int n, int *vector);
void print_matrix_with_mPermutations(int m, int n, double **M, int *p);
double** matrix_write(int m, int n, double **M);
double** matrix_random_write(int m, int n, double **M);
double** matrix_alloc(int m, int n);
void matriuPCreator(int size, int *p);
int matrix_dealloc(int m, int n, double** M);
//Implementations
int main() {
  //exercici1();
  exercici2();
  return 0;
}
void exercici1() {
  //Primer obtenim les dades de la matriu
  double **matriuDelSistema;
  double **matriuDelSistemaOriginal;
  double *coeficientsB;
  double *coeficientsBOriginal;
  double *vectorResidus;
  int *matriuP;
  int midaMatriu;
  printf("Introdueixi la mida de la matriu quadrada:\n");
  scanf("%d", &midaMatriu);
  matriuP = vector_alloc(midaMatriu);
  matriuPCreator(midaMatriu, matriuP);
  printf("\nVector permutacions (Gauss)\n");
  print_vector(midaMatriu, matriuP);
  printf("\nIntrodueix els coeficients de la matriu: \n");
  matriuDelSistema = matrix_alloc(midaMatriu, midaMatriu);
  matriuDelSistemaOriginal = matrix_write(midaMatriu, midaMatriu, matriuDelSistema);
  printf("\nMatriu\n");
  print_matrix(midaMatriu, midaMatriu, matriuDelSistemaOriginal);
  printf("\nMatriu Reduida (Gauss)\n");
  palu(midaMatriu, matriuDelSistema, matriuP, 10e-16);
  print_matrix_with_mPermutations(midaMatriu, midaMatriu, matriuDelSistema, matriuP);
  printf("\nVector permutacions (Gauss)\n");
  print_vector(midaMatriu, matriuP);
}
void exercici2() {
  //Primer obtenim les dades de la matriu
  double **matriuDelSistema;
  double **matriuDelSistemaOriginal;
  double *coeficientsB;
  double *coeficientsBOriginal;
  double *vectorResidus;
  double coeficient;
  int *matriuP;
  int midaMatriu;
  printf("Introdueixi la mida de la matriu quadrada:\n");
  scanf("%d", &midaMatriu);
  matriuP = vector_alloc(midaMatriu);
  matriuPCreator(midaMatriu, matriuP);
  matriuDelSistema = matrix_alloc(midaMatriu, midaMatriu);
  matriuDelSistemaOriginal = matrix_random_write(midaMatriu, midaMatriu, matriuDelSistema);
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  palu(midaMatriu, matriuDelSistema, matriuP, 10e-16);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  coeficient = (double)cpu_time_used/((double)(midaMatriu*midaMatriu*midaMatriu));
  printf("Ha tardat %lf segons, amb k=%lf on k*n^3 = %lf", cpu_time_used, coeficient, cpu_time_used);
}
/*
*Crea una matriu de permutació
*/
void matriuPCreator(int size, int *p) {
  for (int i = 0; i<size; i++)
    p[i] = i;
}
/*Calcula la factorització PA= LU
n = dimensió de A
A = conté A a la entrada LU a la sortida
p = vector de permutacions
tol = tolerancia
*/
int palu(int n, double **A, int *p, double tol) {
  int columna = 0;
  int varAux;
  int numeroPermutacio = 1;
  int multiplicadorActual;
  int filaIndexPivot;
  bool toleranciaInferiorOrError = true;
  while(columna < n-1 && toleranciaInferiorOrError) {
    if(fabs(A[p[columna]][columna]) < tol) {
      toleranciaInferiorOrError = false;
      continue;
    }
    /**
    Hallamos el pivote
    */
    filaIndexPivot = p[columna];
    for(int fila = columna; fila <= n-1; fila++) {
      if(A[p[fila]][columna] > A[filaIndexPivot][columna])
          filaIndexPivot = p[fila];
    }
    //Ara tenim la columna a pivotar, llavors:
    varAux = p[columna];
    p[columna] = filaIndexPivot;
    p[filaIndexPivot] = varAux;
    if(p[columna] != varAux)
      numeroPermutacio *= (-1);
    //Ya hemos intercambiado las filas, continuamos con normalidad.
    if(A[p[columna]][p[columna]] == 0) {
      toleranciaInferiorOrError = false;
      continue;
    }
    for(int fila = columna+1; fila <= n-1; fila++) {
      A[p[fila]][columna] = A[p[fila]][columna]/A[p[columna]][columna]; //Multplicador
      for(int columnaSecundaria = columna + 1; columnaSecundaria <= n-1; columnaSecundaria++)
        A[p[fila]][columnaSecundaria] -= A[p[fila]][columna]*A[p[columna]][columnaSecundaria]; //Aquí l'atribut columna que està en fila és la fila original
    }
    columna++;
  }
  if(toleranciaInferiorOrError)
    return 0; //Tot ha sortit correcte.
  else //En cas que la tolerància no sigui inferior.
    return numeroPermutacio;
}
/*
* Permet guardar un vector a memòria
*/
int* vector_alloc(int n) {
	int *copia = malloc(n*sizeof(int));
	return copia;
}
int vector_dealloc(int* vector) {
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
void print_matrix_with_mPermutations(int m, int n, double **M, int *p) {
  for(int i = 0; i < m; i++) {
		printf("|    ");
		for(int j = 0; j<n; j++)
			printf("%lf    " , M[p[i]][j]);
		printf("|\n");
	}
}
void print_vector(int n, int *vector) {
	for(int i = 0; i< n; i++) {
		printf("|    %d    |\n", vector[i]);
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
/*
*Aquest mètode permet escriure una matriu de mida m, n coeficient a coeficient.
* de manera aleatòria.
* Retorna una còpia de la matriu M, opcional per guardar el sistema original.
*/
double** matrix_random_write(int m, int n, double **M) {
  double **copia = matrix_alloc(m, n);
	int i, j;
	for(i = 0; i<m; i++) {
		for(j = 0; j<n; j++) {
			M[i][j] = ((double)rand()/RAND_MAX);
			copia[i][j] = M[i][j];
		}
	}
	return copia;
}
