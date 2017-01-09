/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Albert
 *
 * Created on 2 de octubre de 2016, 12:30
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-6;
#define TOLERANCE 1e-10;

/*
 * 
 */

void exercici1();
int newton(int n,double* c,double* x, double* listaZEpsilon, int iteracions, double tolerancia);
void horner(int n, double* c, double z, double p[2]);

int main(int argc, char** argv) {
    exercici1();
    return (EXIT_SUCCESS);
}

void exercici1(){
    
/*PART 1 CREEM EL POLINOMI*/
    int n;
    double z;
    
    /*AGAFEM EL GRAU DEL POLINOMI*/
    do{
        printf("Escrigui un valor enter n > 0:\n ");
        scanf("%d", &n);
    } while(n<=0);
    
    /*GUARDEM LA MEMORIA PER AL POLINOMI*/
    double polinomi[n+1];
    double listaZ[n];
    double listaZEpsilon[n];
    polinomi[0] = 1;
    
    /*FEM EL PRODUCTORI DE LES ARRELS INTRODUIDES PER L'USUARI*/
    for(int i = 0; i < n;i++){
        
        printf("Escrigui el valor de Z%d\n",i);
        scanf("%lf", &z);

        listaZ[i] = z;
        
        for(int j = i; j >= 0 ;j--){
            polinomi[j+1] = polinomi[j];
        }
        
        polinomi[0] = 0;        
        for(int k = 0; k <= i ; k++){
            polinomi[k] +=  polinomi[k+1] * (-z);
        }
            
    }
    
    for(int l = 0; l <= n;l++){
        printf("%25.16lf x^%d",polinomi[l],l);
    }
        
    printf("%s\n","");
    
    /*EL MODIFIQUEM PER A AFEGIR-HI L'ERR0R EN EL GRAU N-1*/
    
    polinomi[n-1] += polinomi[n-1] * EPSILON;
    
    for(int l = 0; l <= n;l++){
        printf("%25.16lf x^%d",polinomi[l],l);
    }
        
    printf("%s\n","");
    
    /*MÈTODE DE NEWTON-RAPHSON*/
    
    if (newton(n, polinomi, listaZ, listaZEpsilon, 8, 1e-16)){
        for(int l = 0; l < n;l++){
            printf("\nUna arrel és: %25.16lf\nLa variació de l'arrel és %lf",listaZEpsilon[l], (listaZEpsilon[l] - listaZ[l])/listaZ[l]);
        }
        
    } else{
        printf("No s'han trobat les arrels");
    }
}

/**
 * Calcula les arrels de un polinomi utilitzant el mètode de Newton-Raphson i modifica la llistaZ amb les noves arrels aproximades
 * @param n grau polinomi
 * @param c array coeficients polinomi
 * @param x array zk
 * @return 0 si no converge, 1 si converge
 */
int newton(int n,double* polinomi,double* listaZ, double* listaZEpsilon, int iteracions, double tolerancia){
    int iterations_counter;
    double p[2], x0, x_ant, x_next;
    for(int k = 0;k<n;k++){
        x0 = listaZ[k];
        iterations_counter = 0;
        x_ant = x0;
        x_next = x_ant;
        while(iterations_counter < iteracions && (fabs(x_ant - x_next) > tolerancia) || iterations_counter == 0) {
            //We update the variable data
            horner(n,polinomi,x_ant,p);
            x_ant = x_next;
            x_next = x_ant - (p[0]/p[1]); 
            iterations_counter++;
        }
        if(abs(x_ant - x_next) < tolerancia) listaZEpsilon[k] =  x_next;
        else return 0;
    }
    return 1;
}

/**
 * Calcula els valors del polinomi i la seva derivada en x_i mitjançant el mètode de horner
 * @param n grau polinomi
 * @param polinomi array coeficients
 * @param x_i valor on volem evaluar
 * @param p array amb p[0] = polinomi evaluat en xi i p[1] = derivada del polinomi evaluat en xi
 */
void horner(int n, double* polinomi, double x_i, double p[2]){
    p[0] = polinomi[n];
    p[1] = 0;
    for(int j = n -1; j >= 0; j--) {
        p[0] = polinomi[j] + x_i*p[0];
        p[1] = p[0] + x_i*p[1];
    }
}
void exercici2() {
    for(int i = 6; i >= 0; i--) {
        //Executar l'algorisme per 1e -i
    }
}