#include <stdio.h>
#include <math.h>

// Function prototypes
double f1(double xi, double w, double z);
double f2(double xi, double w, double z, double n);

int main() {
    // Polytropic index
    double n = 1.5;

    // Initial conditions
    double xi = 1e-6; // small value to avoid division by zero
    double w = 1.0;
    double z = 0.0;

    // Step size
    double h = 0.01;

    // Temporary variables for predictor step
    double w_pred, z_pred;

    printf("# xi\tw\tz\n");

    while (w > 0.0) {
        printf("%lf\t%lf\t%lf\n", xi, w, z);

        // Predictor step
        w_pred = w + h * f1(xi, w, z);
        z_pred = z + h * f2(xi, w, z, n);

        // Corrector step
        w += (h/2.0) * (f1(xi, w, z) + f1(xi + h, w_pred, z_pred));
        z += (h/2.0) * (f2(xi, w, z, n) + f2(xi + h, w_pred, z_pred, n));

        // Update xi
        xi += h;
    }

    printf("# First root found at xi ≈ %lf\n", xi);

    return 0;
}

// Derivative of w: dw/dxi = z
double f1(double xi, double w, double z) {
    return z;
}

// Derivative of z: dz/dxi = -(2/xi)*z - w^n
double f2(double xi, double w, double z, double n) {
    if (xi == 0.0) {
        return 0.0; // avoid division by zero
    }
    return -(2.0/xi)*z - pow(w, n);
}
