/*
* Pràctica 2: Mètodes Numérics
*/
#include <stdio.h>
#include <math.h>

//Declarations of functions
double function_e_x(double exponent, int numberOfSeries);
int factorial(int i);
double exponenciacion(double elem, int exponent);
double function_e_minus_x(double exponent, int numberOfSeries);
void exercici1();
void exercici2();
double recurrenciaEndavant(int nInteracions);
double recurrenciaEndarrera(int nInteracions);


//Implementations
int main() {
  exercici1();
  exercici2();
  return 0;
}
void exercici1() {
  int numeroSeries = 15;
  double valorReal, valorAproximat;
  printf("Exercici 1: \n\n");
  for(int exponente = -1; exponente > -4; exponente--) {
    valorAproximat = function_e_x(exponente, numeroSeries);
    valorReal = pow(M_E, exponente);
    printf("Valores para exponente = %d en %d series \n", exponente, numeroSeries);
    printf("-----------Valores aplicando e^(x):-----------\n");
    printf("Valor aproximado con Taylor: %lf \n", valorAproximat);
    printf("Valor real con la función exponente: %lf \n", valorReal);
    printf("Error relatiu: %lf%% - Error absolut: %lf \n",fabs((valorAproximat-valorReal)/valorReal)*100 , (valorAproximat-valorReal));
    printf("-----------Valores aplicando e^(-x)-----------:\n");
    valorAproximat = function_e_minus_x((-exponente), numeroSeries);
    printf("Valor aproximado con Taylor: %lf \n", valorAproximat);
    printf("Valor real con la función exponente: %lf \n", valorReal);
    printf("Error relatiu: %lf%% - Error absolut: %lf \n\n",fabs((valorAproximat-valorReal)/valorReal)*100 , (valorAproximat-valorReal));
  }
}

void exercici2() {
  printf("Exercici 2: \n\n");
  /*
  * Segons Wolfram Alpha el resultat correcte és : 0.10081
  */
  double valorRecEndavant = recurrenciaEndavant(25);
  double valorRecEndarrera = recurrenciaEndarrera(25);
  /*
  * El resultat de la recurrència endavant no és correcte.
  * Aquest exemple presenta molt bé la inestabilitat numèrica
  *que hi presenta el càlcul d'aquesta recurrència per a la integral.
  *Com petits errors arrossegats es tornen molt grans
  * (especialment quan fem la multiplicació)
  */
  printf("Valor recurrència endavant: %lf \n", valorRecEndavant);
  /*
  * Aquest resultat és molt millor.
  */
  printf("Valor recurrència endarrera: %lf \n", valorRecEndarrera);
}
/*
 * Aproxima per Taylor per a x = exponent amb n = number of series
  * e^(x)
 */
double function_e_x(double exponent, int numberOfSeries) {
  double sumaParcial = 1.;
  double valorSumaNi = 1.;
  for(int i = 1; i < numberOfSeries; i++) {
    valorSumaNi *=(double)exponent/(double)i;
    sumaParcial += valorSumaNi;
  }
  return sumaParcial;
}
/*
 * Aproxima per Taylor per a x = exponent amb n = number of series
  * e^(-x)
 */
double function_e_minus_x(double exponent, int numberOfSeries) {
  double sumaParcial = 1.;
  double valorSumaNi = 1.;
  for(int i = 1; i < numberOfSeries; i++) {
    //En la serie de Taylor de e^(-x) si es par suma y si no resta
    valorSumaNi *=(double)exponent/(double)i;
    sumaParcial += (i%2 == 0)? valorSumaNi : (-valorSumaNi);
  }
  return sumaParcial;
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
 * Retorna elem^exponent
 */
double exponenciacion(double elem, int exponent) {
  if (exponent == 0) return 1.;
  double powAux = elem;
  for(exponent; exponent > 1; exponent--)
    powAux *= elem;
  return powAux;
}
double recurrenciaEndavant(int nInteracions) {
  double recurrenciaActual = M_E - 1;
  for (int i = 1; i<= nInteracions; i++) {
    recurrenciaActual = M_E - i*recurrenciaActual;
  }
  return recurrenciaActual;
}
double recurrenciaEndarrera(int nIteracions) {
  double recurrenciaActual = (M_E + 1.)/(2.*(nIteracions + 1));
  for (int i = 2*nIteracions -1; i>=nIteracions; i--)
    recurrenciaActual = (1./(nIteracions+1))*(M_E-recurrenciaActual);
  return recurrenciaActual;
}
