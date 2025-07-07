#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define METHOD_UPWIND 1
#define METHOD_CENTRAL 2
#define METHOD_LAXWENDROFF 3
#define N 400  // Number of grid points

const double XMIN = -1.0;
const double XMAX = 1.0;
const double A = 1.0 ;     // Advection speed
const double SIGMA = 0.8;
const double T_FINAL = 4.0;

double u[N+2];         // includes ghost cells
double u_next[N+2];
double x[N+2];

void initialize() {
    double dx = (XMAX - XMIN)/N;
    for (int i = 0; i <= N; ++i){
        x[i] = XMIN + i * dx;
        if (fabs(x[i]) < 1.0/3.0)    // initial condition
            u[i] = 1.0;
        else
            u[i] = 0.0;
    }
}

void apply_periodic_bc() {
    u[0] = u[N-1];
    u[N+1] = u[1];
}

void step_upwind(double sigma) {
    for (int i = 1; i <= N; ++i)
        u_next[i] = u[i] - sigma * (u[i] - u[i-1]);
}

void step_centered(double sigma) {
    for (int i = 1; i <= N; ++i)
        u_next[i] = u[i] - 0.5 * sigma * (u[i+1] - u[i-1]);
}

void step_lax_wendroff(double sigma) {
    for (int i = 1; i <= N; ++i)
        u_next[i] = u[i] - 0.5 * sigma * (u[i+1] - u[i-1]) + 0.5*sigma*sigma*(u[i+1] - 2*u[i] + u[i-1]);
}

void write_to_file(const char* filename) {
    FILE* fp = fopen(filename, "w");
    double dx = (XMAX - XMIN) / N;

    for (int i = 1; i <= N; ++i) fprintf(fp, "%lf,%lf\n", x[i], u[i]);

        fclose(fp);
}

void solve(int method, const char* output_file) {
    double dx = (XMAX - XMIN) / N;
    double dt = SIGMA * dx;
    int steps = (int)(T_FINAL / dt);

    initialize();
    for (int n = 0; n < steps; ++n) {
        apply_periodic_bc();

        switch(method) {
            case METHOD_UPWIND:
                step_upwind(SIGMA);
                break;
            case METHOD_CENTRAL:
                step_centered(SIGMA);
                break;
            case METHOD_LAXWENDROFF:
                step_lax_wendroff(SIGMA);
                break;
        }

        // swap pointers
        for (int i = 0; i <= N+1; ++i)
            u[i] = u_next[i];
    }

    write_to_file(output_file);
}

void write_analytical(const char* filename) {
    FILE* fp = fopen(filename, "w");
    double dx = (XMAX - XMIN) / N;
    initialize();
    // u(x,t) = u(x-A*t,0)
    // periodic boundary: -A*t => (-A*t)%(XMAX-XMIN) //  i.e. 4 % 2 which happens to be zero

    for (int i = 1; i <= N; ++i) {
        // double x_shifted = x[i] + (A*T_FINAL)%(XMAX-XMIN); // time reversal t -> -t, such that it corresponds with past x
        // double val = (fabs(x_shifted) < 1.0/3.0) ? 1.0 : 0.0; // if x_shifted complies with bc, "current" x needs to be 1
        fprintf(fp, "%lf,%lf\n", x[i], u[i]);
    }

    fclose(fp);
}

int main() {
    solve(METHOD_UPWIND, "upwind.csv");
    solve(METHOD_CENTRAL, "central.csv");
    solve(METHOD_LAXWENDROFF, "laxwendroff.csv");
    write_analytical("analytical.csv");

    printf("Done. Output files generated.\n");
    return 0;
}
