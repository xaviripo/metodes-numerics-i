#include <stdio.h>
#include <math.h>

#define E (exp(1))

void exercici1();
void exercici2();

int main(void){
    printf("%s\n", "Exerici 1");
  exercici1();
    printf("%s\n", "Exerici 2");
  exercici2();
  return 0;
}

void exercici1(){
   
    /*Calculem e^-x utilitzant taylor per a x= 1,...,25*/
  printf("Amb 1/Taylor de e^-x:\t\t Amb 1/e^x:\t\t Amb 1/Taylor de e^x:\n");
  for(int x = 1;x <= 25;x++){
     double act = 1;
     double suma = 1;
     double i = 1;
     double act1 = 1;
     double suma1 = 1;
     int fact = 1;
     int fact1 = 1;
     
     while (fabs((act * (-x))/(fact * (fact+1))) >= 1e-15){
       act *= ((-x) / i);
       suma += act;
       i++;
       fact *= i;
    } 
     i = 1;
     while (fabs((act1 * x)/(fact1 * (fact1+1))) >= 1e-15){
       act1 *= (x / i);
       suma1 += act1;
       i++;
       fact1 *= i;
    }
    
    printf("%25.16lf\t",suma);
    printf("%25.16lf\t",1/exp(x));   
    printf("%25.16lf\n",1/suma1);    
    
    
    }
}

void exercici2(){
    double y = E - 1;
    printf("Utilitzant la recurrència endevant:\n");
    for(int i= 1; i <= 25; i++){
        y = E-i*y;
    }
    printf("El resultat y_25 = %25.16lf\n",y);
    printf("Ara utilitzem la recurrència enrere:\n");
    int inicial = 25;
    y = (E+1.)/(2.*(inicial+1));
    for(int i = 2*inicial-1;i>=inicial;i--){
        y = (1./(inicial+1))*(E-y);
    }
    printf("El resultat y_25 = %5.16lf\n",y);

}