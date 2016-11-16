#ifndef MATRIX_H
#define MATRIX_H

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



#endif /* MATRIX_H */
