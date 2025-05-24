#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

int main() {
    
    int nmax;
    printf("number of iterations: \n");
    scanf("%d", &nmax);

    //int nmax = 10; 
    double A2 =2*sqrt(2);
    double An = pow(2,2)*sqrt(2*(1 - sqrt(1 - 8.0 / pow(2,4)))); // initializing with n=3
    double p = 8.0;
    for (int i = 3; i < nmax; i++) { 
        An = p*sqrt(2*(1-sqrt(1-pow(An,2)/pow(2,2*i))));
        p = p*2.0;
    }
    printf("A%d = %f\n", nmax, An);
    printf("error = %f\n", An-PI);
    return 0;
}

// 2: Since each iteration involves some kind of exponential, pow(2,15) already exceeds memory. 
// An/2^n will be aproximately 0