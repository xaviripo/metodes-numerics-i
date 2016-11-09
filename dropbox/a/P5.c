/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Miquel
 *
 * Created on 8 de noviembre de 2016, 21:41
 */

#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<float.h>
#include "matrix_tools.h"

int permuta_vector(int i, int j, double *v);
int pivotatge_parcial(int k, int n, double **A);
int palu(int n, double **A, double *p, double tol);
int d3(int n, double *a, double *b, double *c, double *f, double tol);

int main() {
	double **A;
	int i, n;
	double *p;
	clock_t t;

	for (n = 1000; n < 10000; n *= 2) {
		p = vector_alloc(n);
		for (i = 0; i < n; i++) { p[i] = i;}
		A = random_matrix(n, n, -1, 1); /* devuelve una matriz con coef
						   entre -1 y 1.
						   Ver archivo matrix_tools.h */
		t = clock();
		palu(n, A, p, DBL_EPSILON);
		t = clock() - t;
		printf("Valor per a n = %d: %e\n", n, (double)t/(double)pow(n,3));
	}

	free(A);
	free(p);
}

/* Funcion de ayuda para permutar vectores, 
 * si la permutacion no se da devuelve 0,
 * si se da 1. */
int permuta_vector(int i, int j, double *v) {
    double temp;

    if (i == j) return 0;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    return 1;
}

/* Funcion para hacer el pivotatge_parcial de una
 * matriz nxn A */
int pivotatge_parcial(int k, int n, double **A) {
    /* 
     * Cerca el maxim i l'intercanvia per la k-essima fila
     * a mÃ©s, retorna l'index de la fila pivotada.
     */
    int i,j, max_idx;
    max_idx = k;
    for (i = k + 1; i < n; i++) {
        if (fabs(A[i][k]) > fabs(A[max_idx][k]) ) max_idx = i;
    }
    permuta_files(k, max_idx, A);
    return max_idx;
}

int palu(int n, double **A, double *p, double tol) {
    int i, j, k, idx_pivot, s_permutacions; // i apunta a la fila i j a la columna
    double m;

    /* cargar vector p */
    for (i = 0; i < n; i++) { p[i] = i; }

    s_permutacions = 1;
    for (k = 0; k < n-1; k++) {
        if (fabs(A[k][k]) < tol) return 0;

        idx_pivot = pivotatge_parcial(k, n, A);
        /* si fem pivotatge ho enregistrem al vector de permutacions i
         * ho guardem a la variable n_permutacions
         */
        if( permuta_vector(k, idx_pivot, p) ) s_permutacions *= -1;

        m = A[k+1][k]/A[k][k];
        for (i = k+1; i < n; i++) {
            suma_files(k,i,-m, n, A); /* suma la fila k multiplicada por -m  a la i */
            A[i][k] = m;
        }

    }
    return (s_permutacions);
}

int palu_d3(int n, double *a, double *b, double *c, double tol) {
	int k;
	double m;

	for (k = 0; k < n - 1; k++) {
		if (fabs(c[k+1] < tol)) return 1; /* si se intenta dividir
						    por 0 el programa acaba
						    con un 1 */
		m = b[k]/c[k+1];
		c[k+1] = m;
		b[k+1] -= m*a[k];
	}

	return 0;
}

void substitucio_endavant_d3(int n, double *l, double *b) {
	/* supongamos l la diagonal inferior (la diagonal central esta
	 * compuesta de 1s, y b el vector de los coeficientes.
	 *
	 * supongamos que l empieza en l[1] y acaba en l[-1] */
	int k, i;
	double temp;

	for (k = 1; k < n; k++) {
		temp = b[k] - l[k]*b[k-1];
	}
}
		
int substitucio_endarrere_d3(int n, double *a, double *b, double *y, double tol) {
	int k;

	y[n-1] = y[n-1]/b[n-1];
	for (k = n-2; k >= 0; k--) {
		if (fabs(b[k]) < tol) return 1;
		y[k] = (y[k] - a[k]*y[k-1])/b[k];
	}
	return 0;
}
	
int d3(int n, double *a, double *b, double *c, double *f, double tol) {
	/* 
	 * Suposem que a és la diagonal superior, b la central
	 * i c la inferior 
	 * Suposem que el vector c comenÃ§a en c[1] i que a
	 * acaba en a[n-1]
	 */
	
	if (palu_d3(n, a, b, c, tol)) return 1;
	substitucio_endavant_d3(n, c, f);
	if (substitucio_endarrere_d3(n, a, b, f, tol)) return 1;

	return 0;
}