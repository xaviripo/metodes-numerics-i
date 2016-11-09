/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Miquel
 *
 * Created on 17 de octubre de 2016, 18:40
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_tools.h"

/*
 * 
 */

int resoltrisup (int n, double **A, double *b, double tol);
int gauss (int n, double **A, double *b, double tol);
double determinant(int n,double **A);
void exercici1();
void exercici2();

int main(int argc, char** argv){
    exercici1();
    exercici2();
    return (EXIT_SUCCESS);
}

void exercici1() {
    
    int n;
    do{
        printf("Escrigui la dimensió de la matriu\n");
        scanf("%d",&n);
    }while(n<=0);
    
    double **A = matrix_alloc(n,n);
    double *b = vector_alloc(n);
    
    double** U = matrix_alloc(n,n);
    double* y = vector_alloc(n);
    
    matrix_read(n,n,A);
    vector_read(n,b);
    
    for(int i = 0; i<n;i++){
        for(int j=0;j<n;j++){
            U[i][j] = A[i][j];
        }
        y[i] = b[i];
    }
    
    if(gauss(n,A,b,1e-10)){
        printf("Error en l'aplicació del mètode de Gauss perquè un valor de la diagonal val 0");
    } else{
        for(int i = 0; i<n;i++){
            for(int j = 0; j< n; j++){
                printf("%lf  ",A[i][j]);
            }
            printf("%lf\n",b[i]);
        }
    }
    
    if(resoltrisup(n,A,b,1e-10)){
        printf("Error en el mètode de substitució enrere perquè un valor de la diagonal val 0");
    } else{
        for(int i = 0; i<n;i++){
            printf("x_%d val %lf\n",i,b[i]);
        }
    }
    
    printf("El determinant de A és %lf",determinant(n,A));
    
    free(A);
    free(b);
}

void exercici2(){
    int n;
    do{
        printf("Escrigui la dimensió de la matriu\n");
        scanf("%d",&n);
    }while(n<=0);
    
    double **A = matrix_alloc(n,n);
    
    for(int i = 1; i <=n;i++){
        for(int j = 1;j<=n;j++){
            A[i-1][j-1] = 1.0/(i+j-1);
        }
    }
    
    double *b = vector_alloc(n);
    for(int i = 0; i<n;i++){
        double suma= 0 ;
        for(int j = 0;j<n;j++){
            suma += A[i][j];
        }
        b[i] = suma;
    }
    
    double** U = matrix_alloc(n,n);
    double* y = vector_alloc(n);
    
    for(int i = 0; i<n;i++){
        for(int j=0;j<n;j++){
            U[i][j] = A[i][j];
        }
        y[i] = b[i];
    }
    
    for(int i = 0; i<n;i++){
        for(int j = 0; j< n; j++){
            printf("%lf  ",A[i][j]);
        }
        printf("%lf\n",b[i]);
    }
    
    double *vectorErrors = vector_alloc(n);
    for(int i = 0; i< n; i++){
        double suma = 0;
        for(int j = 0; j<n;j++){
            suma+=U[i][j]*y[i];
        }
        vectorErrors[i] = b[i] - suma;
    }
    
    printf("El vector d'errors és:\n");
    for(int i = 0;i<n;i++){
        printf("  %lf",vectorErrors[i]);
    }
    
    
}

int resoltrisup(int n, double **A, double* b, double tol){
    double bucle = 0;
    for(int i = n;i > 0;i--){
        if(fabs(A[i-1][i-1]) < tol){
            return 1;
        } else{
            for(int j = i+1; j<=n;j++){
                bucle += A[i-1][j-1] * b[j-1];
            }
            b[i-1] = (b[i-1]-bucle)/A[i-1][i-1];
        }
    }
    return 0;
}

int gauss (int n, double **A, double *b, double tol){
    for(int i = 0; i < n; i++){
        if(fabs(A[i][i])<tol){
            return 1;
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
    return 0;
}

double determinant(int n,double** A){
/*FER GAUSS I DESPRES MULTIPLICAR ELS ELEMENTS DE LA DIAGONAL*/
}

