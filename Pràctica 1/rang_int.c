#include <stdio.h>

/************ (i) ************/

void power(int base, int lim) {
	
	int i, k = 1;
	
	for(i = 0; i <= lim; i++) {
		printf("%i\n", k);
		k *= base;
	}
	
}

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
	
	for(i = 0; i >= 0; i++) {
	}
	printf("%i\n", i-1);
	
}

/************ (iv) ************/

/************ (v) ************/

/************ main ************/

void exercici1(void) {
	printf("(i)\n");
	i();
	printf("\n(ii)\n");
	ii();
	printf("\n(iii)\n");
	iii();
}

int main(void) {
	
	exercici1();
	
	return 0;
	
}

