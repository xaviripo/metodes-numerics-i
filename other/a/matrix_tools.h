/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   matrix_tools.h
 * Author: Albert
 *
 * Created on 8 de noviembre de 2016, 21:45
 */

#ifndef MATRIX_TOOLS_H
#define MATRIX_TOOLS_H

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

/* Devuelve un vector vacio de tamaño n */
double * vector_alloc(int n) {
    double *v;

    v = (double*) malloc(n * sizeof(double));
    if (v == NULL) { 
	    printf("Error allocating vector.\n"); 
            exit(1);
    }
    return v;
}

/* Devuelve una matriz de tamaño nxm */
double ** matrix_alloc(int n, int m) {
    int i;
    double **A;

    A = (double**) malloc(n*sizeof(double));
    if (A == NULL) { 
	    printf("Error allocating matrix.\n"); 
            exit(1);
    }
    for (i = 0; i < n; i++) {
        A[i] = vector_alloc(m);
    }
    return A;
}

/* Lee por consola los valores de un vector */
void vector_read(int n, double * v) {
    int i;

    for (i = 0; i < n; i++) {
        scanf("%lf", v+i);     
    }
}

/* Lo mismo pero para matrices */
void matrix_read(int m, int n, double **M) {
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            scanf("%lf", (M[i]) +j);
        }
    }
}

/* Imprime un vector de doubles */
void vector_write(int n, double *v) {
    int i;
    printf("[");
    for (i = 0; i<n; i++) {
        printf("%+lf ", v[i]);
    }
    printf("]");
    printf("\n");
}

/*Imprime una matriz de doubles*/
void matrix_write(int n, int m, double **M) {
    int i, j;

    for (i = 0; i < n; i++) {
        vector_write(m,M[i]);
        printf("\n");
    }
}

/* permuta las filas i, j de una matriz y 
 * devuelve 1 o 0 en funcion de si permuta
 * o no */
int permuta_files(int i, int j, double **A) {
    /* permuta les files i i j de la matriu A*/
    double *temp;

    if (i == j){
      return 0; /* retorna 0 si no cal permutar */  
    } 

    temp = A[i];
    A[i] = A[j];
    A[j] = temp;

    return 1;
}


/* Funcion de ayuda para permutar vectores, 
 * si la permutacion no se da devuelve 0,
 * si se da 1. */
int permuta_vector(int i, int j, double *v) {
    double temp;

    if (i == j){ 
        return 0;
    }
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    return 1;
}

/* suma la fila i multiplicada por m a la j */
void suma_files(int i, int j, double m, int n, double **A) {
    /* suma la fila i multiplicada per m  a la fila j.
     * n fa referencia a la llargada de les files
     */
    int k;
    double * fi;
    double * fj;

    fi = A[i];
    fj = A[j];
    for (k = 0; k < n; k++) {
        fj[k] += m * fi[k];
    }
}

/* crea una matriz con coeficientes aleatorios */
double** random_matrix(int n, int m, double min, double max) {
    int i, j;
    double **A;
    srand(time(NULL)); 
    A = matrix_alloc(n,m);

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
	    A[i][j] = (max - min)*((double)rand()/RAND_MAX) + min;
        }
    }
	
    return A;
}

/**
 * Mètodo para resolver sistemas triangulares Ax=B
 * @param n tamaño de A
 * @param A matriz
 * @param b matriz
 * @param tol tolerancia para no dividir entre 0
 * @return 1 si funciona correctamente, 0 si se tiene que dividir por 0 y no se pude hacer
 *          el sistema
 */
int resoltrisup(int n, double **A, double* b, double tol){
    double bucle;
    for(int i = n;i > 0;i--){
        if(fabs(A[i-1][i-1]) < tol){
            return 0;
        } else{
            bucle = 0;
            for(int j = i+1; j<=n;j++){
                bucle += A[i-1][j-1] * b[j-1];
            }
            b[i-1] = (b[i-1]-bucle)/A[i-1][i-1];
        }
    }
    return 1;
}

int resoltriinf(int n, double **A, double* b, double tol){
    double bucle;
    for(int i = 0; i < n; i++){
        if(fabs(A[i][i]) < tol){
            return 0;
        } else{
            bucle = 0;
            for(int j = i-1; j >= 0; j--){
                bucle += A[i][j] * b[j];
            }
            b[i] = (b[i]-bucle)/A[i][i];
        }
    }
    return 1;
}

/**
 * Mètode de gauss per a triangular una matriu
 * @param n grandaria n
 * @param A matriu
 * @param b matriu
 * @param tol tolerancia
 * @return 1 si es pot fer, 0 sino
 */
int gauss (int n, double **A, double *b, double tol){
    for(int i = 0; i < n; i++){
        if(fabs(A[i][i])<tol){
            return 0;
        } else{
            for(int j = i+1;j<n;j++){
                A[j][i] = A[j][i]/A[i][i];
                for(int k = j; k<n;k++){
                    A[j][k] = A[j][k]-A[j][i]*A[i][k];
                }
                b[j] = b[j] - b[j-1] * A[j][i];
            }
        }
    }
    return 1;
}

/**
 * Calculo del determinante haciendo gauss en la matriz
 * @param n tamaño matriz
 * @param A matriz
 * @return determinante
 */
double determinant(int n,double** A){
    double* b = vector_alloc(n);
    for(int i= 0; i <n; i++){
        b[i] = 0;
    }
    gauss(n,A,b,1e-10);
    double det = 1;
    for(int i = 0; i <n; i++){
        det *= A[i][i];
    }
    return det;
}

/* Funcion para hacer el pivotatge_parcial de una
 * matriz nxn A */
int pivotatge_parcial(int k, int n, double **A) {
    /* 
     * Cerca el maxim i l'intercanvia per la k-essima fila
     * a mÃ©s, retorna l'index de la fila pivotada.
     */
    int i, max_idx;
    max_idx = k;
    for (i = k + 1; i < n; i++) {
        if (fabs(A[i][k]) > fabs(A[max_idx][k]) ){
            max_idx = i;
        }
    }
    permuta_files(k, max_idx, A);
    return max_idx;
}

int palu(int n, double **A, double *p, double tol) {
    int i, k, idx_pivot, s_permutacions; // i apunta a la fila i j a la columna
    double m;

    /* cargar vector p */
    for (i = 0; i < n; i++) { p[i] = i; }

    s_permutacions = 1;
    for (k = 0; k < n-1; k++) {
        if (fabs(A[k][k]) < tol) {
            return 0;
        }

        idx_pivot = pivotatge_parcial(k, n, A);
        /* si fem pivotatge ho enregistrem al vector de permutacions i
         * ho guardem a la variable n_permutacions
         */
        if( permuta_vector(k, idx_pivot, p) ) {
            s_permutacions *= -1;
        }

        m = A[k+1][k]/A[k][k];
        for (i = k+1; i < n; i++) {
            suma_files(k,i,-m, n, A); /* suma la fila k multiplicada por -m  a la i */
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
double* resolve_alu(int n,double** A,double* b){
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
double* resolve_palu(int n, double** A,double* b, double* p){
    double* temp;
    temp = vector_alloc(n);
    
    for(int i = 0; i <n;i++){
        temp[i] = b[p[i]];
    }
    
    return resolve_alu(n,A,temp);
}  

#endif /* MATRIX_TOOLS_H */

