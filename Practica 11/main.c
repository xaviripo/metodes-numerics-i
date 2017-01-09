#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double legendre(int i, double x) {
    switch(i) {
        case 0:
            return 1.;
        case 1:
            return x;
        default: {
            double p_i, // P_i
                    p_i1 = 1, // P_(i-1)
                    p_i2 = x; // P_(i-2)
            for(int j = 2; j <= i; j++) {
                p_i = (2*j-1)/((double) j)*x*p_i1 - (j-1)/((double) j)*p_i2;
                p_i =
            }
            return p_i;
        }
    }
}

int secant(int i, double *x0, double *x1, double prec, int nmax) {
    double x;
    for(int j = 0; j < nmax; j++) {

    }
    return 1;
}


int main(int argc, char* argv) {

    return 0;
}