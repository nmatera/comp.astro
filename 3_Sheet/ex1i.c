#include <stdio.h>
#include <math.h>

// Constants
const double pi = 3.141592653589793;
const double eM = 0.205;
const double aM = 0.39;
const double eH = 0.967;
const double aH = 17.8;

// Fixed-point iteration
double fixed_point(char B, double M, double tol, int *iterations) {
    double e = (B == 'M') ? eM : eH;
    double E = (e < 0.8) ? M : pi;
    double delta;
    *iterations = 0;

    do {
        double E_next = M + e * sin(E);
        delta = fabs(E_next - E);
        E = E_next;
        (*iterations)++;
    } while (delta > tol);

    return E;
}

// Newton-Raphson method
double Newton(char B, double M, double tol, int *iterations) {
    double e = (B == 'M') ? eM : eH;
    double E = (e < 0.8) ? M : pi;
    double delta;
    *iterations = 0;

    do {
        double f = E - e * sin(E) - M;
        double fp = 1 - e * cos(E);
        double E_next = E - f / fp;
        delta = fabs(E_next - E);
        E = E_next;
        (*iterations)++;
    } while (delta > tol);

    return E;
}

// Convert eccentric anomaly to true anomaly
double true_anomaly(double E, double e) {
    return 2 * atan(sqrt((1 + e) / (1 - e)) * tan(E / 2));
}

// Compute distance from Sun
double radius(double a, double e, double f) {
    return a * (1 - e * e) / (1 + e * cos(f));
}

int main() {
    const double tol = 1e-9;
    int total_fp_mercury = 0, total_newton_mercury = 0;
    int total_fp_halley = 0, total_newton_halley = 0;

    FILE *fp = fopen("orbit.csv", "w");
    if (!fp) {
        perror("File opening failed");
        return 1;
    }

    fprintf(fp, "method,body,step,x,y,iterations\n");

    for (int i = 0; i < 256; i++) {
        double M = 2 * pi * i / 256.0;

        // Mercury
        int it_fp, it_newton;
        double E_fp = fixed_point('M', M, tol, &it_fp);
        double f_fp = true_anomaly(E_fp, eM);
        double r_fp = radius(aM, eM, f_fp);
        double x_fp = r_fp * cos(f_fp), y_fp = r_fp * sin(f_fp);
        total_fp_mercury += it_fp;
        fprintf(fp, "fixed,M,%d,%.12lf,%.12lf,%d\n", i, x_fp, y_fp, it_fp);

        double E_newton = Newton('M', M, tol, &it_newton);
        double f_newton = true_anomaly(E_newton, eM);
        double r_newton = radius(aM, eM, f_newton);
        double x_newton = r_newton * cos(f_newton), y_newton = r_newton * sin(f_newton);
        total_newton_mercury += it_newton;
        fprintf(fp, "newton,M,%d,%.12lf,%.12lf,%d\n", i, x_newton, y_newton, it_newton);

        // Halley's Comet
        E_fp = fixed_point('H', M, tol, &it_fp);
        f_fp = true_anomaly(E_fp, eH);
        r_fp = radius(aH, eH, f_fp);
        x_fp = r_fp * cos(f_fp), y_fp = r_fp * sin(f_fp);
        total_fp_halley += it_fp;
        fprintf(fp, "fixed,H,%d,%.12lf,%.12lf,%d\n", i, x_fp, y_fp, it_fp);

        E_newton = Newton('H', M, tol, &it_newton);
        f_newton = true_anomaly(E_newton, eH);
        r_newton = radius(aH, eH, f_newton);
        x_newton = r_newton * cos(f_newton), y_newton = r_newton * sin(f_newton);
        total_newton_halley += it_newton;
        fprintf(fp, "newton,H,%d,%.12lf,%.12lf,%d\n", i, x_newton, y_newton, it_newton);
    }

    fclose(fp);

    // Print summary
    printf("Total iterations for 256 steps:\n");
    printf("Mercury  - Fixed Point: %d, Newton: %d\n", total_fp_mercury, total_newton_mercury);
    printf("Halley   - Fixed Point: %d, Newton: %d\n", total_fp_halley, total_newton_halley);

    return 0;
}
