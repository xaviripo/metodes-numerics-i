#include <stdio.h>

/************ Exercici 1 ************/



void exercici1(int n, double z[]) {
	
	(x-a)=x+(-a) | -a,1
	(x-a)(x-b)=x^2+(-a-b)x+ab | ab,-a-b,1
	(x-a)(x-b)(x-c)=(x^2+(-a-b)x+ab)(x-c)=x^3+(-a-b-c)x^2+(ab+c(a+b))x-abc | -abc,ab+ac+bc,-a-b-c,1

	(c_[k-1]*x^(k-1)+...+c_0)(x-z_k)=c_[k-1]*x^(k)+...+c_0*x+(-c_[k-1]*z_k)*x^(k-1)+...+(-c_[0]*z_k)=c_[k-1]*x^(k)+(c_[k-2]-c_[k-1]*z_k)*x^(k-1)


	int i,j;
	double c[n];
	for(i = 0; i < n; i++) {

		for(j = i; j > 0; j--) {

			c[j] = c[j-1]

		}

		c[0]=//Special case...

	}


}

/************ main ************/

int main(void) {
	
	// Read z as a list of reals from keyboard

	exercici1(n, z);	

	return 0;
	
}

