#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <float.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*NORMA D'UN VECTOR*/
/* n = dimensio, b = vector */
double infnorm(int n, double* b) {
	double norm = 0;
	int i;
	for(i = 0; i < n; i++) {
		if(fabs(b[i]) > norm) {
			norm = fabs(b[i]);
		}
	}
	return norm;
}

/*RESOL UNA MATRIU DIAGONAL INFERIOR*/
/* n = dimensio, A = array de la matriu, b = coeficients del sistema (on es guardara la solucio), tol = tolerancia pel 0*/
int resoltriinf(int n, double** A, double* b, double tol) {
	int i;
	double sum;
	for(i = 0; i < n; i++) {
		sum = 0;
		if(fabs(A[i][i]) < fabs(tol)) {
			goto stop;
		}
		int j;
		for(j = 0; j < i; j++) {
			sum = sum + (A[i][j] * b[j]);
		}
		b[i] = (b[i] - sum) / A[i][i];
	}
	return 0;
	stop : return -1;
}

/*RESOL UNA MATRIU DIAGONAL SUPERIOR*/
/* n = dimensio, A = array de la matriu, b = coeficients del sistema (on es guardara la solucio), tol = tolerancia pel 0*/
int resoltrisup(int n, double** A, double* b, double tol) {
	int i;
	double sum;
	for(i = n-1; i > -1; i--) {
		sum = 0;
		if(fabs(A[i][i]) < fabs(tol)) {
			goto stop;
		}
		int j;
		for(j = n; j > i; j--) {
			sum = sum + (A[i][j] * b[j]);
		}
		b[i] = (b[i] - sum) / A[i][i];
	}
	return 0;
	stop : return -1;
}

/*RESOL UNA MATRIU DIAGONAL BANDA*/
/*	(b	c	0	0	0)
	(a	b	c	0	0)
	(0	a	b	c	0)
	(0	0	a	b	c)
	(0	0	0	a	b)
n = dimensio, (a,b,c) bandes diagonals vectors de dimensio (n,n+1,n), f = vector solucio inicial del sistema (on es guardaran les noves solucions), tol = tolerancia pel 0*/
int d3(int n, double *a, double *b, double *c, double *f, double tol) {
	/*
	int i;
	for(i = 0; i < n-1; i++) {
		if(fabs(b[i]) < tol) {
			goto stop;
		}
		a[i] = a[i] / b[i];
		b[i+1] = b[i+1] - (a[i] * c[i]);
	}

	double** L = malloc(n * sizeof(double*));
	for(i = 0; i < n; i++) {
		L[i] = malloc(n * sizeof(double));
	}
	double** U = malloc(n * sizeof(double*));
	for(i = 0; i < n; i++) {
		U[i] = malloc(n * sizeof(double));
	}
	for(i = 0; i < n-1; i++) {
		L[i+1][i] = a[i];
		L[i][i] = 1;
		U[i][i] = b[i];
		U[i][i+1] = c[i]; 
	}
	U[n-1][n-1] = b[n-1];
	L[n-1][n-1] = 1;
	resoltriinf(n, L, f, tol);
	resoltrisup(n, U, f, tol);
	return 0;
	stop: return -1;
	*/

	int i;

	c[0] = c[0] / b[0];
	for(i = 1; i < n-1; i++) {
		c[i] = c[i] / (b[i] - (c[i-1] * a[i-1]));
	}

	f[0] = f[0] / b[0];
	for(i = 1; i < n; i++) {
		f[i] = (f[i] - (f[i-1] * a[i-1])) / (b[i] - (c[i-1] * a[i-1]));
	}

	for(i = n-2; i > -1; i--) {
		f[i] = f[i] - (c[i] * f[i+1]);
	}

	return 0;
}

/*///P6 : APROXIMACIO D'UNA FUNCIO PER NEWTON (PUNTS)///*/

/*APROXIMACIO D'UNA FUNCIO PER LA RESOLUCIO D'UN SISTEMA D'EQUACIONS DIFERENCIALS*/
/*///ATRIBUTS :
	- (a,b) : Interval d'interpolacio
	- alfa : f(a)
	- beta : f(b)
	- n : Nombre de punts (100)
	- prec : Precisio dels calculs (1e-10)
	- kmax : Iteracions maximes (10)
*/
void p6(double a, double b, double alfa, double beta, int n, double prec, int kmax) {

	/*Definir funcions d'avaluacions*/
	/*Cal substituir per funcions correctes :
		- feval : funcio de la forma y''(x, y, y')
		- d2feval : dy''/dy
		- d3feval : dy''/dy'
	*/
	double feval(double x, double y, double z) {
		return (pow(x*z,2) - (9*pow(y,2)) + (4*pow(x,6))) / pow(x,5);
	}

	double d2feval(double x, double y, double z) {
		return (-18*y)/pow(x,5);
	}

	double d3feval(double x, double y, double z) {
		return (2*z)/pow(x,3);
	}

	/*Iteradors*/
	int i;

	/*Realitzem el pas de discretitzacio h i els nodes*/
	double h = (b-a)/(n+1);
	double* x = malloc((n+2) * sizeof(double));
	for(i = 0; i < n+2; i++) {
		x[i] = a + (i*h);
	}

	/*Trobar el vector y 0 aproximat*/
	double* y = malloc((n+2) * sizeof(double));
	for(i = 0; i < n+2; i++) {
		y[i] = alfa + ((beta-alfa)*(x[i]-a)/(b-a));
	}

	/*Guardar memoria per vectors*/
	double* e = malloc(n * sizeof(double));
	double* diaginf = malloc((n-1) * sizeof(double));
	double* diagmit = malloc(n * sizeof(double));
	double* diagsup = malloc((n-1) * sizeof(double));

	/*Repetir iteracions fins acabar*/
	int it = 0;
	while(1) {
		/*Calcular i preparar vectors*/
		for(i = 0; i < n-1; i++) {
			diagsup[i] = -1 + ((h/2) * d3feval(x[i+1], y[i+1], (y[i+2]-y[i])/(2*h)));
			diagmit[i] = 2 + (pow(h,2) * d2feval(x[i+1], y[i+1], (y[i+2]-y[i])/(2*h)));
			diaginf[i] = -1 - ((h/2) * d3feval(x[i+2], y[i+2], (y[i+3]-y[i+1])/(2*h)));
			e[i] = y[i] - (2*y[i+1]) + y[i+2] - (pow(h,2) * feval(x[i+1], y[i+1], (y[i+2]-y[i])/(2*h)));
		}
		diagmit[n-1] = 2 + (pow(h,2) * d2feval(x[n], y[n], (y[n+1]-y[n-1])/(2*h)));
		e[n-1] = y[n-1] - (2*y[n]) + y[n+1] - (pow(h,2) * feval(x[n], y[n], (y[n+1]-y[n-1])/(2*h)));

		/*Resoldre sistema per trobar e k*/
		d3(n, diaginf, diagmit, diagsup, e, prec);

		/*Comprovacions per acabar iteracions*/
		if(it == kmax) {
			goto stop;
		}
		double norma = infnorm(n, e);
		printf("Iteracio : %d // Norma : %25.16lf\n", it + 1, norma);
		if(norma < prec) {
			goto stop;
		}

		/*Si no sortim, preparem per seguent iteracio*/
		for(i = 0; i < n; i++) {
			y[i+1] = y[i+1] + e[i];
		}

		it = it + 1;
	}

	stop: printf("Hem acabat el proces\n");
	/*
	printf("Resultat final : punts (x,y) i error\n");
	double error;
	for(i = 0; i < n+2; i++) {
		error = fabs(y[i]-log(x[i])); 
		printf("%25.16lf %25.16lf %25.16lf\n", x[i], y[i], error);
	}
	*/
	printf("Resultat final : punts (x,y)\n");
	for(i = 0; i < n+2; i++) {
		printf("%25.16lf %25.16lf\n", x[i], y[i]);
	}
	/*
	printf("Resultat final : punts (x, error)\n");
	for(i = 0; i < n+2; i++) {
		error = fabs(y[i]-log(x[i])); 
		printf("%25.16lf %25.16lf\n", x[i], error);
	}
	printf("Resultat final : punts (x, arrel error)\n");
	for(i = 0; i < n+2; i++) {
		error = sqrt(fabs(y[i]-log(x[i]))); 
		printf("%25.16lf %25.16lf\n", x[i], error);
	}
	*/

	/*EXEMPLES*/
	/*Primer exercici
	double feval(double x, double y, double z) {
		return - pow(z,2) - y + log(x);
	}

	double d2feval(double x, double y, double z) {
		return -1;
	}

	double d3feval(double x, double y, double z) {
		return - 2*z;
	}

	double beta = log(2);
	ex1(1, 2, 0, beta, 100, 1e-10, 10);
	*/

	/*Segon exercici
	double feval(double x, double y, double z) {
		return pow(y,3) - (y*z);
	}

	double d2feval(double x, double y, double z) {
		return (3*pow(y,2)) - z;
	}

	double d3feval(double x, double y, double z) {
		return - y;
	}

	double alfa = 1.0/2.0;
	double beta = 1.0/3.0;
	ex1(1, 2, alfa, beta, 100, 1e-10, 10);
	*/

	/*Tercer exercici
	double feval(double x, double y, double z) {
		return z + (2*pow(y-log(x),3)) - pow(x,-1);
	}

	double d2feval(double x, double y, double z) {
		return (6*pow(y-log(x),2));
	}

	double d3feval(double x, double y, double z) {
		return 1;
	}

	double alfa = 1;
	double beta = (1.0/2.0) + log(2);
	ex1(1, 2, alfa, beta, 100, 1e-10, 10);
	*/

	/*Quart exercici
	double feval(double x, double y, double z) {
		return (pow(x*z,2) - (9*pow(y,2)) + (4*pow(x,6))) / pow(x,5);
	}

	double d2feval(double x, double y, double z) {
		return (-18*y)/pow(x,5);
	}

	double d3feval(double x, double y, double z) {
		return (2*z)/pow(x,3);
	}

	double alfa = 0;
	double beta = log(256);
	ex1(1, 2, alfa, beta, 100, 1e-10, 10);
	*/
}

/*///P7 : APROXIMACIO D'UNA FUNCIO PER NEWTON (DIFERENCIES DIVIDIDES)///*/

/* n = largada dels vectors x, f; x, f = vectors amb els punts a interpolar */
void difdiv(int n, double* x, double* f) {
	int i, j;
	for(i = 1; i < n; i++) {
		for(j = n-1; j > i-1; j--) {
			f[j] = (f[j] - f[j-1]) / (x[j] - x[j-i]);
		}
	}
}

/* z = valor en que avaluar el polinomi; n = llargada del vector de coeficients; x, c = vectors amb els coeficients i els valors de les x */
/* Forma del polinomi : c0 + c1(x-x0) + c2(x-x0)(x-x1) + ... */
double horner(double z, int n, double* x, double* c) {
	int i;
	double r = c[n-1];
	for(i = n-2; i > -1; i--) {
		r = r * (z - x[i]);
		r = r + c[i];
	}
	return r;
}

/*INTERPOLACIO D'UN SEGUIT DE NODES UTILITZANT DIFERENCIES DIVIDIDES*/
/*///ATRIBUTS :
	- n : Nombre de nodes
	- m : Nombre de punts (100)
	- x : Vector x dels nodes
	- f : Vector y dels nodes
*/
void p7_1(int n, int m, double* x, double* f) {
	int i;

	difdiv(n, x, f);

	double* xp = malloc((n-1) * sizeof(double));
	for(i = 0; i < n-1; i++) {
		xp[i] = x[i];
	}

	printf("Punts del polinomi : \n");
	for(i = 0; i < m; i++) {
		double xi = x[0] + ((x[n-1] - x[0])*(i/(m - 1.0))); 
		double eval = horner(xi, n, xp, f);
		printf("%25.16lf %25.16lf\n", xi, eval);
	}
}

/*INTERPOLACIO D'UNA FUNCIO PER ABCISSES NORMALS UTILITZANT DIFERENCIES DIVIDIDES*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // INTERPOLA DE -1 A 1 // DEFECTE RUNGE)
	- n : Nombre de nodes (30)
	- m : Nombre de punts (120)
*/

void p7_2equi(int n, int m) {
	int i;

	double feval(double x) {
		return 1.0 / (1 + (25 * pow(x, 2)));
	}

	double* x = malloc(n * sizeof(double));
	double* y = malloc(n * sizeof(double));
	for(i = 0; i < n; i++) {
		x[i] = -1 + (2.0*i/(n-1.0));
		y[i] = feval(x[i]);
	}

	difdiv(n, x, y);

	double* xp = malloc((n-1) * sizeof(double));
	for(i = 0; i < n-1; i++) {
		xp[i] = x[i];
	}

	printf("Punts del polinomi : \n");
	for(i = 0; i < m; i++) {
		double xi = x[0] + ((x[n-1] - x[0])*(i/(m - 1.0))); 
		double eval = horner(xi, n, xp, y);
		printf("%25.16lf %25.16lf\n", xi, eval);
	}
}

/*INTERPOLACIO D'UNA FUNCIO PER ABCISSES DE CHEBISHEV UTILITZANT DIFERENCIES DIVIDIDES*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // INTERPOLA DE -1 A 1 // DEFECTE RUNGE)
	- n : Nombre de nodes (30)
	- m : Nombre de punts (120)
*/

void p7_2cheb(int n, int m) {
	int i;

	double feval(double x) {
		return 1.0 / (1 + (25 * pow(x, 2)));
	}

	double* x = malloc(n * sizeof(double));
	double* y = malloc(n * sizeof(double));
	for(i = 0; i < n; i++) {
		x[i] = -1 + (1 + (cos(M_PI * ((2*i)+1) / (2*n))));
		y[i] = feval(x[i]);
	}

	difdiv(n, x, y);

	double* xp = malloc((n-1) * sizeof(double));
	for(i = 0; i < n-1; i++) {
		xp[i] = x[i];
	}

	printf("Punts del polinomi : \n");
	for(i = 0; i < m; i++) {
		double xi = x[0] + ((x[n-1] - x[0])*(i/(m - 1.0))); 
		double eval = horner(xi, n, xp, y);
		printf("%25.16lf %25.16lf\n", xi, eval);
	}
}

/*///P8 : APROXIMACIO D'UNA FUNCIO PER SPLINES CUBICS///*/

/*INTERPOLACIO D'UN SEGUIT DE NODES UTILITZANT SPLINES CUBICS*/
/*///ATRIBUTS :
	- n : Nombre de nodes
	- p : Nombre de punts per spline (20) // Punts totals = np + 1
	- delta : Vector x dels nodes
	- y : Vector y dels nodes
*/
void p8_1(int n, int p, double* delta, double* y) {
	int i, j;

	/*Ajustament pel codi*/
	n = n - 1;

	/*Vector d'intervals*/
	double* h = malloc((n) * sizeof(double));
	for(i = 0; i < n; i++) {
		h[i] = delta[i+1] - delta[i];
	}

	/*Vectors pel sistema tridiagonal, m tindra els moments M1 -> Mn-1*/
	double* a = malloc((n-2) * sizeof(double));
	double* b = malloc((n-1) * sizeof(double));
	double* c = malloc((n-2) * sizeof(double));
	double* m = malloc((n-1) * sizeof(double));
	for(i = 0; i < n-2; i++) {
		a[i] = h[i+1] / 6.0;
		b[i] = (h[i] + h[i+1]) / 3.0;
		c[i] = h[i+1] / 6.0;
		m[i] = ((y[i+2] - y[i+1]) / h[i+1]) - ((y[i+1] - y[i]) / h[i]);
	}
	b[n-2] = (h[n-2] + h[n-1]) / 3.0;
	m[n-2] = ((y[n] - y[n-1]) / h[n-1]) - ((y[n-1] - y[n-2]) / h[n-2]);
	d3(n-2, a, b, c, m, 1e-10);

	/*Quan tenim els moments, calculem els Ai i els Bi*/
	double* B = malloc((n) * sizeof(double));
	double* A = malloc((n) * sizeof(double));
	B[0] = y[0];
	A[0] = ((y[1] - y[0]) / h[0]) - (h[0] * m[0] / 6.0);
	for(i = 1; i < n-1; i++) {
		B[i] = y[i] - (m[i-1] * h[i] * h[i] / 6);
		A[i] = ((y[i+1] - y[i]) / h[i]) - (h[i] * (m[i] - m[i-1]) / 6.0);
	}
	B[n-1] = y[n-1] - (m[n-2] * h[n-1] * h[n-1] / 6);
	A[n-1] = ((y[n] - y[n-1]) / h[n-1]) + (h[n-1] * m[n-2] / 6.0);

	/*Passem a l'avaluacio del spline cubic*/
	/*Agafem un nombre de punts i avaluem. El nombre m indica punts per spline cubic*/
	
	double x, eval;
	/*Primer punt*/
	x = delta[0];
	eval = (m[0] * pow(x - delta[0], 3)) / (6.0 * h[0]) + (A[0] * (x - delta[0])) + B[0];
	printf("%25.16lf %25.16lf\n", x, eval);

	/*Primer spline*/
	for(i = 0; i < p; i++) {
		x = delta[0] + ((delta[1] - delta[0]) * (i+1) / (p + 0.0));
		eval = (m[0] * pow(x - delta[0], 3)) / (6.0 * h[0]) + (A[0] * (x - delta[0])) + B[0];
		printf("%25.16lf %25.16lf\n", x, eval);
	}

	/*Segon a penultim spline*/
	for(j = 1; j < n-1; j++) {
		for(i = 0; i < p; i++) {
			x = delta[j] + ((delta[j+1] - delta[j]) * (i+1) / (p + 0.0));
			eval = (((m[j-1] * pow(delta[j+1] - x, 3)) + (m[j] * pow(x - delta[j], 3))) / (6.0 * h[j])) + (A[j] * (x - delta[j])) + B[j];
			
			printf("%25.16lf %25.16lf\n", x, eval);
		}
	}

	/*Ultim spline*/
	for(i = 0; i < p; i++) {
		x = delta[n-1] + ((delta[n] - delta[n-1]) * (i+1) / (p + 0.0));
		eval = (m[n-2] * pow(delta[n] - x, 3)) / (6.0 * h[n-1]) + (A[n-1] * (x - delta[n-1])) + B[n-1];
		printf("%25.16lf %25.16lf\n", x, eval);
	}
}

/*INTERPOLACIO D'UNA FUNCIO EN [a,b] UTILITZANT SPLINES CUBICS*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // DEFECTE FABS)
	- n : Nombre de nodes
	- p : Nombre de punts per spline (20) // Punts totals = np + 1
	- (a,b) : Interval d'interpolacio
*/
void p8_2(int n, int p, double a, double b) {
	int i;

	double feval(double x) {
		return fabs(x);
	}

	/*Creem els nodes a interpolar*/
	double* delta = malloc(n * sizeof(double));
	double* y = malloc(n * sizeof(double));
	for(i = 0; i < n; i++) {
		delta[i] = a + ((b-a)*i/(n-1.0));
		y[i] = feval(delta[i]); /*Part de la funcio a interpolar*/
	}

	p8_1(n, p, delta, y);
}

/*///P9 : APROXIMACIO DE LA PRIMERA I SEGONA DERIVADA PER EXTRAPOLACIO///*/
/*///ATENCIO : ELS PARAMETRES kmax i q son per defecte 10 i 2///*/

/*EXTRAPOLACIO DE LA PRIMERA DERIVADA EN UN PUNT a*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // DEFECTE COS(X))
	- a : Punt on aproximar la 1a derivada
	- h : Pas inicial (0.1)
	- prec : Precisio maxima (1e-10)
*/
void p9_11(double a, double h, double prec) {
	
	/*Parametres i iteradors*/

	int i, j;
	int max = 10;
	double q = 2.0;

	double** F = malloc(max * sizeof(double*));
	for(i = 0; i < max; i++) {
		F[i] = malloc((max-i) * sizeof(double));
	}

	/*Funcions d'avaluació*/

	double feval(double x) {
		return cos(x);
	}

	double f0eval(double h) {
		return (feval(a+h) - feval(a-h)) / (2*h);
	}

	double extrap(int i, int j, double** F) {
		return (((pow(q, i+j) * F[i+1][j-1]) - F[i][j-1]) / (pow(q, i+j) - 1));
	}

	/*Codi base*/

	F[0][0] = f0eval(h);
	i = 1;
	while(i < max) {
		F[i][0] = f0eval(h / pow(q, i));
		for(j = 0; j < i; j++) {
			F[i-1-j][j+1] = extrap(i-1-j, j+1, F);
		} 
		if(fabs(F[0][i] - F[1][i-1]) < prec) {
			break;
		}
		i = i + 1;
	}

	/*Prints i final del metode*/

	printf("Valor aproximat de la primera derivada : %25.16lf\n", F[0][i]);
}

/*EXTRAPOLACIO DE LA SEGONA DERIVADA EN UN PUNT a*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // DEFECTE COS(X))
	- a : Punt on aproximar la 2a derivada
	- h : Pas inicial (0.1)
	- prec : Precisio maxima (1e-10)
*/
void p9_12(double a, double h, double prec) {
	
	/*Parametres i iteradors*/

	int i, j;
	int max = 10;
	double q = 2.0;

	double** F = malloc(max * sizeof(double*));
	for(i = 0; i < max; i++) {
		F[i] = malloc((max-i) * sizeof(double));
	}

	/*Funcions d'avaluació*/

	double feval(double x) {
		return cos(x);
	}

	double f0eval(double h) {
		return (feval(a+h) - (2*feval(a)) + feval(a-h)) / pow(h, 2);
	}

	double extrap(int i, int j, double** F) {
		return (((pow(q, i+j) * F[i+1][j-1]) - F[i][j-1]) / (pow(q, i+j) - 1));
	}

	/*Codi base*/

	F[0][0] = f0eval(h);
	i = 1;
	while(i < max) {
		F[i][0] = f0eval(h / pow(q, i));
		for(j = 0; j < i; j++) {
			F[i-1-j][j+1] = extrap(i-1-j, j+1, F);
		} 
		if(fabs(F[0][i] - F[1][i-1]) < prec) {
			break;
		}
		i = i + 1;
	}

	/*Prints i final del metode*/

	printf("Valor aproximat de la segona derivada : %25.16lf\n", F[0][i]);
}

/*EXTRAPOLACIO DE LA PRIMERA I SEGONA DERIVADA EN UN PUNT 2.0 FENT SERVIR UNA TAULA*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // DEFECTE COS(X) // POC MODULARITZAT : NO CANVIAR VALORS IMPORTANTS)
	- a : Punt on aproximar la 1a i 2a derivada (2.0)
	- h : Pas inicial (0.2)
	- valors : Vector y dels nodes
*/
void p9_2(double a, double h, double* valors) {

	/*Parametres i iteradors*/

	int i, j;
	double q = 0.5;

	double** F1 = malloc(4 * sizeof(double*));
	for(i = 0; i < 4; i++) {
		F1[i] = malloc((4-i) * sizeof(double));
	}
	double** F2 = malloc(4 * sizeof(double*));
	for(i = 0; i < 4; i++) {
		F2[i] = malloc((4-i) * sizeof(double));
	}

	/*Funcions d'avaluacio*/

	double extrap(int i, int j, double** F) {
		return (((pow(q, i+j) * F[i+1][j-1]) - F[i][j-1]) / (pow(q, i+j) - 1));
	}

	/*Codi base*/

	for(i = 0; i < 4; i++) {
		F1[i][0] = (valors[5+i] - valors[3-i]) / (2*h);
		F2[i][0] = (valors[5+i] - (2*valors[4]) + valors[3-i]) / pow(h, 2);
	}

	for(i = 1; i < 4; i++) {
		for(j = 0; j < 4-i; j++) {
			F1[j][i] = extrap(j, i, F1);
			F2[j][i] = extrap(j, i, F2);
		}
	}

	/*Prints i final del metode*/

	printf("Valor aproximat de la primera derivada : %25.16lf\n", F1[0][3]);
	printf("Valor aproximat de la segona derivada : %25.16lf\n", F2[0][3]);
}

/*///P10 : INTEGRACIO NUMERICA : TRAPEZIS I ROIMBERG///*/

/*APROXIMACIO DE LA INTEGRAL D'UNA FUNCIO EN [a,b] PER TRAPEZIS*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // DEFECTE 1/1+x)
	- (a,b) : Interval d'integracio
	- prec : Precisio maxima (1e-10)
	- max : Iteracions maximes (12)
*/
void p10_1(double a, double b, double prec, int max) {

	/*Parametres i iteradors*/

	int i;
	double* T = malloc((max+1) * sizeof(double));

	/*Funcions d'evaluacio*/
	
	double feval(double x) {
		return (1.0) / (1.0 + x);
	}

	double nextT(double T, double n) {
		int i;
		double sum = 0;
		for(i = 0; i < n; i++) {
			sum = sum + feval(a + ((1.0+(2.0*i))*(b-a)/(2.0*n)));
		}
		return (T / 2.0) + ((b-a) * sum / (2.0*n));
	}

	/*Codi*/

	T[0] = (b - a) * (feval(a) + feval(b)) / 2.0;
	i = 0;
	while(i < max) {
		T[i+1] = nextT(T[i], pow(2, i));
		if(fabs(T[i+1] - T[i]) < prec) {
			break;
		}
		i++;
	}

	/*Prints finals*/

	printf("Valor de la integral entre %10.6lf i %10.6lf : %25.16lf\n", a, b, T[i]);
}

/*APROXIMACIO DE LA INTEGRAL D'UNA FUNCIO EN [a,b] PER ROIMBERG*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // DEFECTE 1/1+x)
	- (a,b) : Interval d'integracio
	- prec : Precisio maxima (1e-10)
	- max : Iteracions maximes (12)
*/
void p10_2(double a, double b, double prec, int max) {

	/*Parametres i iteradors*/

	int i, j;

	double** T = malloc(max * sizeof(double*));
	for(i = 0; i < max; i++) {
		T[i] = malloc((i+1) * sizeof(double));
	}

	/*Funcions d'evaluacio*/
	
	double feval(double x) {
		return (1.0) / (1.0 + x);
	}

	double nextT(double T, double n) {
		int i;
		double sum = 0;
		for(i = 0; i < n; i++) {
			sum = sum + feval(a + ((1.0+(2.0*i))*(b-a)/(2.0*n)));
		}
		return (T / 2.0) + ((b-a) * sum / (2.0*n));
	}

	double extrap(int i, int j, double** T) {
		return ((pow(4, i) * T[i][j-1]) - T[i-1][j-1]) / (pow(4, i) - 1);
	}

	/*Codi*/

	T[0][0] = (b - a) * (feval(a) + feval(b)) / 2.0;
	i = 1;
	while(i < max) {
		T[i][0] = nextT(T[i-1][0], pow(2, i-1));
		for(j = 0; j < i; j++) {
			T[i][j+1] = extrap(i, j+1, T);
		}
		if(fabs(T[i][i] - T[i][i-1]) < prec) {
			break;
		}
		i++;
	}

	/*Prints finals*/

	printf("Valor de la integral entre %10.6lf i %10.6lf : %25.16lf\n", a, b, T[i][i]);
}

/*///P11 : ZEROS DE FUNCIONS : POLINOMIS DE LEGEANDRE I METODE DE LA SECANT///*/

double legeandre(int i, double x) {
	if(i == 0) {
		return 1;
	}
	else if(i == 1) {
		return x;
	}
	else {
		double p0 = 1;
		double p1 = x;
		double p2;
		int j;
		for(j = 2; j < i+1; j++) {
			p2 = ((((2.0*(j+0.0))-1.0)/(j+0.0))*x*p1) - (((j-1.0)/(j+0.0))*p0);
			p0 = p1;
			p1 = p2;
		}
		return p2;
	}
}

double secantaux1(int i, double x0, double x1, double prec, int nmax) {

	double feval(double x) {
		return legeandre(i, x);
	}

	double segiter(double x0, double x1) {
		return ((x0 * feval(x1)) - (x1 * feval(x0))) / (feval(x1) - feval(x0));
	}

	if(i == 1) {
		return 0;
	} 

	int k = 0;
	double x2;
	while(k < nmax) {
		x2 = segiter(x0, x1);
		x0 = x1;
		x1 = x2;
		if(fabs(feval(x2)) < prec || fabs(x1 - x0) < prec) {
			break;
		}
		k++;
	}

	if(k == nmax) {
		return -2.0;
	}

	return x2;
}

double secantaux2(double x0, double x1, double prec, int nmax) {

	double feval(double x) {
		return (x-(2.0/5.0)) * (x+(3.0/7.0)) * (x-(19.0/6.0));
	}

	double segiter(double x0, double x1) {
		return ((x0 * feval(x1)) - (x1 * feval(x0))) / (feval(x1) - feval(x0));
	}

	int k = 0;
	double x2;
	while(k < nmax) {
		x2 = segiter(x0, x1);
		x0 = x1;
		x1 = x2;
		if(fabs(feval(x2)) < prec || fabs(x1 - x0) < prec) {
			break;
		}
		k++;
	}

	if(k == nmax) {
		return x0 - 1.0;
	}

	return x2;
}

/*ZEROS DEL POLINOMI DE LEGEANDRE DE GRAU i*/
/*///ATRIBUTS : (NO MODULARITZAT : NOMES POLINOMI DE LEGEANDRE // LES ALTRES ARRELS ES GUARDEN EN UNA MATRIU)
	- i : Grau del polinomi de Legeandre
	- prec : Precisio maxima (1e-14)
	- nmax : Iteracions maximes (15)
*/
int p11_1(int i, double prec, int nmax) {

	double** zeros = malloc(i * sizeof(double*));
	int j;
	for(j = 0; j < i; j++) {
		zeros[j] = malloc((j+1) * sizeof(double));
	}

	zeros[0][0] = 0;

	int f = 0;

	for(j = 2; j < i+1; j++) {
		int k;
		double x0, x1;
		for(k = 0; k < j; k++) {
			if(k == 0) {
				x0 = -1;
				x1 = zeros[j-2][0];
			}
			else if(k == j-1) {
				x0 = zeros[j-2][j-2];
				x1 = 1;
			}
			else{
				x0 = zeros[j-2][k-1];
				x1 = zeros[j-2][k];
			}
			zeros[j-1][k] = secantaux1(j, x0, x1, prec, nmax);
			if(zeros[j-1][k] == -2) {
				f = 1;
			}
		}
	}

	printf("Arrels : \n");
	for(j = 0; j < i; j++) {
		printf("%25.16lf\n", zeros[i-1][j]);
	}

	return f;
}

/*ZEROS D'UNA FUNCIO QUALSEVOL*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL EN secantaux2 // DEFECTE POLINOMI GENERIC)
	- n : Nombre d'arrels a trobar
	- (x0,x1) : Vectors d'intervals on es troben les arrels
	- prec : Precisio maxima (1e-14)
	- nmax : Iteracions maximes (15)
*/
int p11_2(int n, double* x0, double* x1, double prec, int nmax) {

	int f = 0;

	double* roots = malloc(n * sizeof(double));

	int i;
	for(i = 0; i < n; i++) {
		roots[i] = secantaux2(x0[i], x1[i], prec, nmax);
		if(roots[i] == x0[i] - 1.0) {
			f = 1;
			printf("Arrel (%d) entre %lf i %lf no trobada\n", i, x0[i], x1[i]);
		}
	}

	printf("Arrels : \n");
	for(i = 0; i < n; i++) {
		printf("%25.16lf\n", roots[i]);
	}

	return f;
}

int main(void) {
	/*EXEMPLES*/

	/*
	double alfa = 0;
	double beta = log(256);
	p6(1, 2, alfa, beta, 100, 1e-10, 10);
	*/

	/*
	double* x = malloc(6 * sizeof(double));
	double* f = malloc(6 * sizeof(double));
	x[0] = -1;
	x[1] = 0;
	x[2] = 1;
	x[3] = 2;
	x[4] = 2.5;
	x[5] = 5;
	f[0] = -10;
	f[1] = 2.5;
	f[2] = 4;
	f[3] = 0.5;
	f[4] = -1.25;
	f[5] = 17;
	p7_1(6, 100, x, f);
	*/

	/*
	p7_2equi(30, 120);
	p7_2cheb(30, 120);
	*/

	/*	
	double* delta = malloc(6 * sizeof(double));
	double* y = malloc(6 * sizeof(double));
	delta[0] = -1;
	delta[1] = 0;
	delta[2] = 1;
	delta[3] = 2;
	delta[4] = 2.5;
	delta[5] = 5;
	y[0] = -10;
	y[1] = 2.5;
	y[2] = 4;
	y[3] = 0.5;
	y[4] = -1.25;
	y[5] = 17;
	p8_1(6, 20, delta, y);
	*/

	/*
	p8_2(11, 20, -5.0, 5.0);
	*/

	/*
	p9_11(1.0, 0.1, 1e-10);
	p9_12(1.0, 0.1, 1e-10);
	*/

	/*
	double* valors = malloc(9 * sizeof(double));
	valors[0] = 0.7891;
	valors[1] = 1.9827;
	valors[2] = 2.5176;
	valors[3] = 2.7633;
	valors[4] = 2.9923;
	valors[5] = 3.2048;
	valors[6] = 3.4027;
	valors[7] = 3.7636;
	valors[8] = 4.4051;
	p9_2(2, 0.2, valors);
	*/

	/*
	p10_1(0, 1, 1e-10, 12);
	p10_2(0, 1, 1e-10, 12);
	*/

	/*	
	p11_1(6, 1e-14, 15);
	*/

	/*
	double* x0 = malloc(3 * sizeof(double));
	double* x1 = malloc(3 * sizeof(double));
	x0[0] = -1;
	x0[1] = 0;
	x0[2] = 3;
	x1[0] = 0;
	x1[1] = 1;
	x1[2] = 4;
	p11_2(3, x0, x1, 1e-14, 15);
	*/

	return 0;
}

/*INDEX*/

/*APROXIMACIO D'UNA FUNCIO PER LA RESOLUCIO D'UN SISTEMA D'EQUACIONS DIFERENCIALS*/

/*INTERPOLACIO D'UN SEGUIT DE NODES UTILITZANT DIFERENCIES DIVIDIDES*/
/*INTERPOLACIO D'UNA FUNCIO PER ABCISSES NORMALS UTILITZANT DIFERENCIES DIVIDIDES*/
/*INTERPOLACIO D'UNA FUNCIO PER ABCISSES DE CHEBISHEV UTILITZANT DIFERENCIES DIVIDIDES*/

/*INTERPOLACIO D'UN SEGUIT DE NODES UTILITZANT SPLINES CUBICS*/
/*INTERPOLACIO D'UNA FUNCIO EN [a,b] UTILITZANT SPLINES CUBICS*/

/*EXTRAPOLACIO DE LA PRIMERA DERIVADA EN UN PUNT a*/
/*EXTRAPOLACIO DE LA SEGONA DERIVADA EN UN PUNT a*/
/*EXTRAPOLACIO DE LA PRIMERA I SEGONA DERIVADA EN UN PUNT 2.0 FENT SERVIR UNA TAULA*/

/*APROXIMACIO DE LA INTEGRAL D'UNA FUNCIO EN [a,b] PER TRAPEZIS*/
/*APROXIMACIO DE LA INTEGRAL D'UNA FUNCIO EN [a,b] PER ROIMBERG*/

/*ZEROS DEL POLINOMI DE LEGEANDRE DE GRAU i*/
/*ZEROS D'UNA FUNCIO QUALSEVOL*/

