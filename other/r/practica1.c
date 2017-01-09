#include <stdio.h>
#include <math.h>
//Declaracions de les functions
int main();
int factorial(int i);
double factorialD(int i);
int powInt(int elem, int exponent);
void exercici1();
void exercici2();
void exercici3();
void exercici4();
//Implementacions
int main() {
  exercici1();
  exercici2();
  exercici3();
  exercici4();
  return 0;
}
void exercici1() {
  int varNumPart3, varNumPart31;
  printf("\nPart 1 Eexercici 1");
  for(int i = 0; i<12; i++)
    printf("\n Valor de 10^(%d) = %d", i, powInt(10, i+1));
  printf("\nPart 2 Exercici 1");
  for(int i = 0; i<32; i++)
    printf("\n Valor de 2^(%d) = %d", i, powInt(2, i+1));
  printf("\nPart 3 Exercici 1");
  varNumPart3 = 0;
  varNumPart31 = 1;
  while(varNumPart3 < varNumPart31) {
    varNumPart3++;
    varNumPart31++;
  }
  /*Ull que en ordinadors amb 64 bits aquest bucle no termina en un temps raonable */
  printf("\nEl valor per a què no augmenti més és %d", varNumPart3);
  varNumPart3 = 1;
  varNumPart31 = 0;
  printf("\nPart 4 Exercici 1");
  while(varNumPart3 > varNumPart31) {
    varNumPart3--;
    varNumPart31--;
  }
  printf("\nEl valor per a què no disminueixi més és %d", varNumPart3);
  printf("\nPart 5 Exercici 1");
  for(int i = 0; i < 35; i++)
    printf("%d!=%d", i, factorial(i));
}

void exercici2() {
  printf("\nPart 1 Eexercici 2 (Double)");
  for(int i = 0; i<12; i++)
    printf("\n Valor de 10^(%d) = %lf", i, pow(10.0, i+1));
  printf("\nPart 2 Exercici 2 (Double)");
  for(int i = 0; i<32; i++)
    printf("\n Valor de 10^(%d) = %lf", i, pow(2.0, i+1));
  printf("\nPart 5 Exercici 1 (Double)");
  for(int i = 0; i < 35; i++)
    printf("%d!=%lf", i, factorialD(i));
}

void exercici3() {
  double valorLlegit, errorRelatiu;
  float valorLlegitF;
  printf("\nEntra un valor real (analitzat amb double)");
  scanf("%lf", &valorLlegit);
  printf("\nEl nombre entrat és %lf", valorLlegit);
  printf("\nEntra un valor real (analitzat amb float)");
  scanf("%f", &valorLlegitF);
  printf("\nEl nombre entrat és %f", valorLlegitF);
  printf("\nPart 2 Exercici 3");
  errorRelatiu = 0.;
  for(double i = 0.1; i<= 1000.00; i+=0.1)  {
    valorLlegitF = valorLlegit = i;
    errorRelatiu = fmax(fabs(((valorLlegitF-valorLlegit)/valorLlegit)), errorRelatiu);
  }
  printf("\nLa fita pràctica de l'error absolut és: %lf", errorRelatiu);
}
void exercici4() {
    double u = 1.;
    double unitat = 1;
    float unitatF = 1;
    float uF = 1.;
    while(unitat+u != unitat)
      u -= 0.1;
    printf("\nLa unitat de la màquina per doubles (Epsilon) que és el valor de arrodoniment és  %lf", u);
    while(unitatF+uF != unitatF)
      uF -= 0.1;
    printf("\nLa unitat de la màquina per floats (Epsilon) que és el valor de arrodoniment és  %f", uF);
}

/*
 * Retorna el factorial de i = i!
 */
int factorial(int i) {
  if (i == 0) return 1;
  for(int j = i -1; j > 0; j--)
    i *= j;
  return i;
}
/*
 * Retorna el factorial de i = i! amb valor double
 */
double factorialD(int i) {
  if (i == 0) return 1;
  double result = i;
  for(int j = i -1; j > 0; j--)
    result *= j;
  return result;
}

int powInt(int elem, int exponent) {
  if(exponent==0) return 1;
  int toReturn = elem;
  exponent--;
  for(exponent; exponent > 0; exponent--)
    toReturn *= elem;
  return toReturn;
}
