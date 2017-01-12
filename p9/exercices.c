#include <stdio.h>
#include <math.h>
#include "common.h"

int p9_e1() {
    double f(double x) {
        return cos(x);
    }
    printf("First derivative = %25.16f\n", derivative_1(1, 0.1, 2, f, 1e-10, 10));
    return 0;
}

int p9_e2() {
    double f(double x) {
        return cos(x);
    }
    printf("Second derivative = %25.16f\n", derivative_2(1, 0.1, 2, f, 1e-10, 10));
    return 0;
}

int p9_e3() {

    // Function for points table
    int table_size = 9;
    double x[9] = {.4, 1.2, 1.6, 1.8, 2., 2.2, 2.4, 2.8, 3.6};
    double y[9] = {0.7891, 1.9827, 2.5176, 2.7633, 2.9923, 3.2048, 3.4027, 3.7636, 4.4051};
    double table(double x_eval) {
        for(int i = 0; i < table_size; i++) {
            if(x_eval == x[i]) {
                return y[i];
            }
        }
        // x not in the table
        return 1;
    }

    // Approximations of first and second derivatives
    printf("First derivative = %25.16f\n", derivative_1(2., 1.6, 2, table, 1e-10, 3));
    printf("\n");
    printf("Second derivative = %25.16f\n", derivative_2(2., 1.6, 2, table, 1e-10, 3));

    return 0;

}