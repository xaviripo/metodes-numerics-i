#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "source.h"

int e2() {

    double feval(double x) {
        return 1./(1 + 25*pow(x,2));
    }

    int chebyshev;
    printf("Equidistant (0) or chebyshev (1): ");
    scanf("%d", &chebyshev);

    double a;
    printf("Enter a: ");
    scanf("%lf", &a);

    double b;
    printf("Enter b: ");
    scanf("%lf", &b);

    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int M;
    printf("Enter M: ");
    scanf("%d", &M);
    printf("\n");

    double *x = malloc((n+1) * sizeof(double));
    double *f = malloc((n+1) * sizeof(double));


    double h;

    if(chebyshev == 0) { // Equidistant

        h = (b - a)/n;

        x[0] = a;
        for(int i = 1; i <= n; i++) {
            x[i] = x[i-1] + h;
            f[i] = feval(x[i]);
        }

    } else { // Chebyshev

        h = (b - a)/2;

        for(int i = 0; i <= n; i++) {
            x[n-i] = a + h*(1 + cos(M_PI*(2*i + 1)/(2.*(n + 1))));
            f[n-i] = feval(x[n-i]);
        }

    }

    difdiv(n, x, f);

    // Print the polynomial for copying and pasting in gnuplot
    for(int i = 0; i <= n; i++) {
        printf("%+lf", f[i]);
        for(int j = 0; j < i; j++) {
            printf("*(x-%lf)", x[j]);
        }
    }
    printf("\n");

    double k = (x[n] - x[0])/M;
    double z = x[0];

    double pv, fv;
    for(int i = 0; i <= M; i++) {
        pv = horner(z, n, x, f);
        fv = feval(z);
        printf("p(%+25.16lf) = %+25.16lf\n", z, pv);
        printf("f(%+25.16lf) = %+25.16lf\n", z, fv);
        printf("f error = %+.8lf\n", fv - pv);
        printf("x error = %d\n", z==x[i]);
        printf("\n");
        z += k;
    }

    for(int i = 0; i <= n; i++) {
        pv = horner(x[i], n, x, f);
        fv = feval(x[i]);
        printf("p(%+25.16lf) = %+25.16lf\n", x[i], pv);
        printf("f(%+25.16lf) = %+25.16lf\n", x[i], fv);
        printf("f error = %+.8lf\n", fv - pv);
        printf("\n");
    }

    return 0;

}