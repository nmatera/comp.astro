#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

int main() {
    int nmax;
    printf("number of iterations: \n");
    scanf("%d", &nmax);
    int n;
    double An, R, Z;
    
    
    double A = 2.0 * sqrt(2.0); // A for n=2

    printf("Iteration\tApproximation of pi\n");
    for (n = 2; n <= nmax; ++n) {
        double pow2n = pow(2.0, n);
        double a_scaled = A / pow2n;

        // Compute Z using the reformulated expression
        Z = (a_scaled * a_scaled/2.0) / (1.0 + sqrt(1.0 - a_scaled * a_scaled));
        An = pow2n * sqrt(4.0 * Z);

        // printf("%d\t\t%.15f\n", n, An);

        // Update A for next iteration
        A = An;
    }
    printf("A%d = %.15f\n", nmax, An);
    printf("error = %.15f\n", An-PI);
    return 0;
}
