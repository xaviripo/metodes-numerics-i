#include <stdio.h>
#include <stdlib.h>



int main2() {

    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("\n");

    int M;
    printf("Enter M: ");
    scanf("%d", &M);
    printf("\n");

    double *x = malloc((n+1) * sizeof(double));
    double *f = malloc((n+1) * sizeof(double));

    for(int i = 0; i <= n; i++) {

        printf("Enter x[%d]: ", i);
        scanf("%lf", &x[i]);

        printf("Enter f[%d]: ", i);
        scanf("%lf", &f[i]);
        printf("\n");

    }

    difdiv(n, x, f);

    double k = (x[n] - x[0])/M;
    for(double z = x[0]; z <= x[n]; z += k) {
        printf("p(%f) = %f\n", z, horner(z, n, x, f));
    }

    return 0;

}