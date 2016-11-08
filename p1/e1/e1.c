#include <stdio.h>

/************ main ************/

void i(), ii(), iii(), iv(), v();

int main(void) {

	printf("Exercici 1\n\n");
	printf("(i)\n");
	i();
	printf("\n(ii)\n");
	ii();
	printf("\n(iii)\n");
	iii();
	printf("\n(iv)\n");
	iv();
	printf("\n(v)\n");
	v();

	return 0;

}



void power(int base, int lim) {

	int i, k = 1;

	for(i = 0; i <= lim; i++) {
		printf("%d\n", k);
		k *= base;
	}

}

/************ (i) ************/

void i(void) {

	power(10, 12);

}

/************ (ii) ************/

void ii(void) {

	power(2, 32);

}

/************ (iii) ************/

void iii(void) {

	int i;

	for(i = 0; i >= 0; i++);

	printf("%d\n", i-1);

}

/************ (iv) ************/

void iv(void) {

	int i;

	for(i = 0; i <= 0; i--);

	printf("%d\n", i+1);

}

/************ (v) ************/

void v(void) {

	int i, n = 1;

	for(i = 1; i <= 35; i++) {
		n *= i;
		printf("%d\n", n);
	}

}

/************ main ************/
