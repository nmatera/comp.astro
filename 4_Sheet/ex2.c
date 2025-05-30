#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

const int N_MAX = 30; // max number of interval halvings
const double epsilon = 0.00000001; // error tolerance    
int N = 1; // iteration step number at start (could be set higher to skip some computation)

// functions to be integrated

double sinc(double x){ // for SI integral
    if (fabs(x < 1e-10)){
        return 1;
    }
    
    return sin(x)/x;
}

double fresnel(double x){ // for fresnel integral
    return cos(PI/2.0*x*x);
}


double testfunction( double x){ // for testing (if that wasn't clear)
    return x*x;
}

// integration methods

double trapezoidal(double a, double b, double (*func)(double)){
    return (b-a)*(func(a)+func(b))/2.0;
}

double simpson(double a, double b, double (*func)(double)){
    return (b-a)/6.0*(func(a)+4.0*func((a+b)/2.0)+func(b));
}

// numerical integration
// N: number of steps,   a: interval start, b: interval end,   integration method,    func: function to be integrated
double integrate(int N, double a, double b, double (*method)(double, double, double (*)(double)), double (*func)(double)){
    
    if (N==1){
        return method(a, b, func);
    }
    double mid = (a+b)/2.0;
    
    return integrate(N-1, a, mid, method, func) + integrate(N-1, mid, b, method, func);

}

// adaptive procedure with error tolerance epsilon
void adaptive(int N, double a, double b, double (*method)(double, double, double (*)(double)), double (*func)(double), double epsilon){
    
    double res, nextres = integrate(N, a, b, method, func);

    do{
        res = nextres;
        nextres = integrate(++N, a, b, method, func);

    } while((fabs(res-nextres) > epsilon) && (N < N_MAX));
    printf("%e with %d iterations\n", res, N);
}

int main(){

    printf("using an adaptive approach with an error tolerance of epsilon = %e \n", epsilon);
    printf("Si integral:\na = 0 \nb = 1\n");
    printf("Simpson's method: ");

    adaptive(N, 0, 1, simpson, sinc, epsilon);
    printf("Trapezoidal rule: ");
    adaptive(N, 0, 1, trapezoidal, sinc, epsilon);

    printf("\n");

    printf("Fresnel integral:\na = 0 \nb = 5\n");
    printf("Simpson's method: ");
    adaptive(N, 0, 5, simpson, fresnel, epsilon);
    printf("Trapezoidal rule: ");
    adaptive(N, 0, 5, trapezoidal, fresnel, epsilon);

/* // small sanity check
    printf("test integral:\na = 0 \nb = 5\n");
    printf("Simpson's method: ");
    adaptive(N, 0, 1, simpson, testfunction, epsilon);
    printf("Trapezoidal rule: ");
    adaptive(N, 0, 1, trapezoidal, testfunction, epsilon);
*/
    return 0;
}