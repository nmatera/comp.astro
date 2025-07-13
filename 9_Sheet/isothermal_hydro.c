#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 500
#define XMAX 100.0
#define DX (XMAX / N)
#define CS 1.0
#define COURANT 0.5
#define TMAX 100.0

double max(double a, double b) { return (a > b) ? a : b; }

void initialize(double rho[], double u[]) {
    for (int i = 0; i < N; i++) {
        double x = i * DX;
        rho[i] = 1.0 + 0.3 * exp(-(x - 50.0) * (x - 50.0) / 10.0);
        u[i] = 0.0;
    }
}

void apply_reflective_boundaries(double rho[], double u[]) {
    rho[0] = rho[1];
    rho[N-1] = rho[N-2];
    u[0] = -u[1];
    u[N-1] = -u[N-2];
}

void compute_fluxes(double rho[], double u[], double flux_rho[], double flux_mom[]) {
    for (int i = 0; i < N - 1; i++) {
        double rho_avg = 0.5 * (rho[i] + rho[i+1]);
        double u_avg = 0.5 * (u[i] + u[i+1]);
        flux_rho[i] = rho_avg * u_avg;
        flux_mom[i] = rho_avg * u_avg * u_avg;
    }
}

void apply_advection(double rho[], double u[], double dt) {
    double flux_rho[N-1], flux_mom[N-1];
    compute_fluxes(rho, u, flux_rho, flux_mom);

    for (int i = 1; i < N - 1; i++) {
        double drho = -dt / DX * (flux_rho[i] - flux_rho[i-1]);
        double dmom = -dt / DX * (flux_mom[i] - flux_mom[i-1]);
        double momentum = rho[i] * u[i] + dmom;
        rho[i] += drho;
        u[i] = momentum / rho[i];
    }
}

void apply_pressure_source(double rho[], double u[], double dt) {
    double dp[N];
    for (int i = 1; i < N - 1; i++) {
        dp[i] = -CS * CS * (rho[i+1] - rho[i-1]) / (2.0 * DX);
        u[i] += dt * dp[i] / rho[i];
    }
}

void write_output(int step, double rho[]) {
    char filename[64];
    sprintf(filename, "output/step_%04d.dat", step);
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < N; i++) {
        double x = i * DX;
        fprintf(f, "%f %f\n", x, rho[i]);
    }
    fclose(f);
}

int main() {
    double rho[N], u[N];
    double t = 0.0;
    int step = 0;

    initialize(rho, u);
    system("mkdir -p output");

    while (t < TMAX) {
        double max_u = 0.0;
        for (int i = 0; i < N; i++) max_u = max(max_u, fabs(u[i]));
        double dt = COURANT * DX / (CS + max_u);
        if (t + dt > TMAX) dt = TMAX - t;

        apply_reflective_boundaries(rho, u);
        apply_advection(rho, u, dt);
        apply_reflective_boundaries(rho, u);
        apply_pressure_source(rho, u, dt);
        apply_reflective_boundaries(rho, u);

        if (step % 10 == 0)
            write_output(step, rho);

        t += dt;
        step++;
    }

    return 0;
}
