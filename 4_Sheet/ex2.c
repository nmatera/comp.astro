#include <stdio.h>
#include <math.h>

double func(double x){
    return x;
}

double simpson(double a, double b, double (*func)(double)){
    return (b-a)/6*(func(a)+4*func((a+b)/2)+func(b));
}
// N: number of steps,     a: interval start, b: interval end,   integration method,    func: function to be integrated
double integrate(int N, double a, double b, double (*method)(double, double, double (*)(double)), double (*func)(double)){
    
    if (N==1){
        return method(a, b, func);
    }
    double mid = (a+b)/2;
    
    return integrate(N-1, a, mid, method, func) + integrate(N-1, mid, b, method, func);

}

double testfunction( double x){
    return x;
}

int main(){

    double epsilon = 0.00000001;
    const int N_MAX = 100;
    int N = 1;
    double a = 0;
    double b = 1;
    double res, nextres = integrate(N, a, b, simpson, testfunction);


    do{
        res = nextres;
        nextres = integrate(++N, a, b, simpson, testfunction);

    } while((fabs(res-nextres) > epsilon) && (N < N_MAX));
    printf("Integral = %e\n",res);

    return 0;
}