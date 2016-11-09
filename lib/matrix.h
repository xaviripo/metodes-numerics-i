#ifndef MATRIX_TOOLS_H
#define MATRIX_TOOLS_H

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>





/************ make ************/
/* Returns a vector of length n */
double* vector_alloc(int n) {
    return (double*) malloc(n * sizeof(double));
}

/* Returns a square matrix of size n */
double** matrix_alloc(int n) {
    int i;
    double** A;
    A = (double**) malloc(n * sizeof(double));
    for (i = 0; i < n; i++) {
        A[i] = vector_alloc(n);
    }
    return A;
}

/************ scan ************/
/* Reads through the console the values of a vector of length n */
void vector_scan(int n, double* v) {
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf", &v[i]);
    }
}

/* Reads through the console the values of a square matrix of size n */
void matrix_scan(int n, double** M) {
    int i;
    for (i = 0; i < n; i++) {
        vector_scan(n, M[i]);
        /*for (j = 0; j < m; j++) {
            scanf("%lf", (M[i])+j);
        }*/
    }
}

/* Prints a vector of ints */
void vector_print_int(int n, int* v) {
    printf("[ ");
    int i;
    for (i = 0; i<n; i++) {
        printf("%d ", v[i]);
    }
    printf("]\n");
}

/* Prints a vector of doubles */
void vector_print(int n, double* v) {
    printf("[ ");
    int i;
    for (i = 0; i < n; i++) {
        printf("%+8.4lf ", v[i]);
    }
    printf("]\n");
}

/* Prints a square matrix of doubles of size n */
void matrix_print(int n, double** M) {
    int i;
    for (i = 0; i < n; i++) {
        vector_print(n, M[i]);
    }
}

/* Permutes rows i and j */
/**
 * Returns:
 * 0 if no permutation is necessary,
 * 1 otherwise
 */
int permute_rows(int n, double** M, int i, int j) {
    if (i < 0 || i >= n) {
        fprintf(stderr, "Invalid index i: %d\n", i);
    } else if(j < 0 || j >= n) {
        fprintf(stderr, "Invalid index j: %d\n", j);
    }

    double *temp;
    if (i == j) return 0; /* retorna 0 si no cal permutar */

    temp = M[i];
    M[i] = M[j];
    M[j] = temp;

    return 1;
}

int permute_elements(int n, double* v, int i, int j) {
    if (i < 0 || i >= n) {
        fprintf(stderr, "Invalid index i: %d\n", i);
    } else if(j < 0 || j >= n) {
        fprintf(stderr, "Invalid index j: %d\n", j);
    }

    double temp;
    if (i == j) return 0; /* retorna 0 si no cal permutar */

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;

    return 1;
}

/* Adds row i times m to row j */
void add_rows(int n, double** A, int i, int j, double m) {
    int k;

    /*
    double* fi;
    double* fj;
    fi = A[i];
    fj = A[j];*/
    for (k = 0; k < n; k++) {
        A[j][k] += m * A[i][k];
    }
}

/* crea una matriz con coeficientes aleatorios */
double** random_matrix(int n, double min, double max) {
    int i, j;
    double** A;
    srand(time(NULL));
    A = matrix_alloc(n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = (max - min) * ((double) rand()/RAND_MAX) + min;
        }
    }

    return A;
}

/************ create ************/
double** matrix_create(int n) {
	double** M = matrix_alloc(n);
	printf("Enter matrix coefficients: ");
	matrix_scan(n, M);
	matrix_print(n, M);
	return M;
}

double* vector_create(int n) {
	double* v = vector_alloc(n);
	printf("Enter vector coefficients: ");
	vector_scan(n, v);
	vector_print(n, v);
	return v;
}

int resoltrisup(int n, double** A, double* b, double tol){
    double sum;
    int i, j;
    for(i = n-1; i >= 0; i--){

        if(fabs(A[i][i]) < tol) {
            return 0;
        }

        sum = 0;
        for(j = i + 1; j < n; j++) {
            sum += A[i][j] * b[j];
        }
        b[i] -= sum;
        b[i] /= A[i][i];

    }
    return 1;
}

int resoltriinf(int n, double** A, double* b, double tol){
    double sum;
    for(int i = 0; i < n; i++){
        if(fabs(A[i][i]) < tol){
            return 0;
        } else{
            sum = 0;
            for(int j = i-1; j >= 0; j--){
                sum += A[i][j] * b[j];
            }
            b[i] -= sum;
            b[i] /= A[i][i];
        }
    }
    return 1;
}

int gauss(int n, double** A, double* b, double tol){
    int i, j, k;
    for(i = 0; i < n; i++) {
        if(fabs(A[i][i])<tol) {
            return 0;
        }

        for(j = i+1;j<n;j++) {
            A[j][i] = A[j][i] / A[i][i];
            for(k = j; k < n; k++) {
                A[j][k] = A[j][k] - A[j][i] * A[i][k];
            }
            b[j] = b[j] - b[j-1] * A[j][i];
        }

    }
    return 1;
}

double det(int n, double** A, double tol){
    double* b = vector_alloc(n);
    int i;
    for(i = 0; i < n; i++) {
        b[i] = 0;
    }
    gauss(n, A, b, tol);
    double det = 1;
    for(i = 0; i < n; i++){
        det *= A[i][i];
    }
    return det;
}

int pivotatge_parcial(int k, int n, double** A) {
    /*
     * Cerca el maxim i l'intercanvia per la k-essima fila
     * a més, retorna l'index de la fila pivotada.
     */
    int i, max_idx;
    max_idx = k;
    for (i = k + 1; i < n; i++) {
        if (fabs(A[i][k]) > fabs(A[max_idx][k])){
            max_idx = i;
        }
    }
    permute_rows(n, A, k, max_idx);
    return max_idx;
}

int palu(int n, double **A, double *p, double tol) {
    int i, k, idx_pivot, s_permutacions; /* i apunta a la fila i j a la columna */
    double m;

    /* cargar vector p */
    for (i = 0; i < n; i++) { p[i] = i; }

    s_permutacions = 1;
    for(k = 0; k < n-1; k++) {
        if(fabs(A[k][k]) < tol) {
            return 0;
        }

        idx_pivot = pivotatge_parcial(k, n, A);
        /* si fem pivotatge ho enregistrem al vector de permutacions i
         * ho guardem a la variable n_permutacions
         */
        if( permute_elements(n, p, k, idx_pivot) ) {
            s_permutacions *= -1;
        }

        m = A[k+1][k]/A[k][k];
        for (i = k + 1; i < n; i++) {
            add_rows(n, A, k, i, -m); /* suma la fila k multiplicada por -m  a la i */
            A[i][k] = m;
        }

    }
    return s_permutacions;
}

/**
 * Resol Ax= b si A=LU
 * LUx = b -> Ly= b -> Ux=y
 * @param n tamany de A
 * @param A Conté L a la diagonal inferior i U a la superior
 * @param b
 * @return X
 */
double* /* NO TESTEJAT !!! */ resolve_alu(int n,double** A,double* b){
    resoltriinf(n,A,b,1e-10);
    resoltrisup(n,A,b,1e-10);
    return b;
}

/**
 * Resoldre Ax = b si PA= LU
 * PAx = Pb -> LUx = b -> Ly = b -> Ux = y
 * @param n
 * @param A
 * @param b
 * @param p
 * @return
 */
double* /* NO TESTEJAT !!! */ resolve_palu(int n, double** A,double* b, double* p){
    double* temp = vector_alloc(n);
    for(int i = 0; i <n;i++){
        temp[i] = b[p[i]];
    }
    return resolve_alu(n,A,temp);
}

#endif /* MATRIX_TOOLS_H */
