#include <stdio.h>
#include <math.h>

void calculate_a(double a, double b, double c, double *x1, double *x2) {
    if (a==0 && b!=0){
        *x1 = -c/b;
        *x2 = -c/b;
    }
    else {
        *x1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
    *x2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
    }
    return;
}
void calculate_c(double a, double b, double c, double *x1, double *x2) {
    if (a==0 && b!=0){
        *x1 = -c/b;
        *x2 = -c/b;
    }
    else if (c > 0) {
        *x1 = (double)(-b + sqrt(c)*sqrt(b*b/c - 4*a)) / (2*a);
        *x2 = (double)(-b - sqrt(c)*sqrt(b*b/c - 4*a)) / (2*a);
    } 
    else {
        *x1 = (double)(-b + sqrt(-c)*sqrt(-b*b/c + 4*a)) / (2*a);
        *x2 = (double)(-b - sqrt(-c)*sqrt(-b*b/c + 4*a)) / (2*a);
    }   
    return;
}

int main() {
    printf("Which exercise do you want to run?\n a, b, c or d?\n");
    double a;
    double b;
    double c;
    double x1;
    double x2;
    char exercise;
    scanf(" %c", &exercise);
    switch (exercise) {
        case 'a':
            printf("Running exercise a\n");
            printf("please enter a: \n");
            scanf("%lf", &a);
            printf("please enter b: \n");
            scanf("%lf", &b);
            printf("please enter c: \n");
            scanf("%lf", &c);
            calculate_a(a, b, c, &x1, &x2);
            printf("x1 = %f\n", x1);
            printf("x2 = %f\n", x2);    
            return 0;
            break;
        case 'b':
            printf("Running exercise b\n");
            printf("Notice that any input larger than 6 will result in a x1 being 0 and x2 being -1\n");
            printf("This is because the machine precision reaches its limit at around 10^7.\nThe square root will just be equal to b.\n");
            a = 1;
            b = 1;
            int n;
            printf("please enter your desired exponent: \n");
            scanf("%d", &n);

            c = pow(10, -n);
            x1 = (double)(-b + sqrt(b*b - 4*a*c)) / (2*a);
            x2 = (double)(-b - sqrt(b*b - 4*a*c)) / (2*a);
            printf("x1 = %f\n", x1);
            printf("x2 = %f\n", x2);    
            return 0;
            break;
        case 'c':
            printf("Running exercise c\n");
            printf("please enter a: \n");
            scanf("%lf", &a);
            printf("please enter b: \n");
            scanf("%lf", &b);
            printf("please enter c: \n");
            scanf("%lf", &c);
            calculate_c(a, b, c, &x1, &x2);         
            printf("x1 = %f\n", x1);
            printf("x2 = %f\n", x2);    
            return 0;
            break;
        case 'd':
            printf("Running exercise d\n");
            printf("please enter a: \n");
            scanf("%lf", &a);
            printf("please enter b: \n");
            scanf("%lf", &b);
            printf("please enter c: \n");
            scanf("%lf", &c);
            if (fabs(4*a*c/b*b) > 0.0000001){
                calculate_a(a, b, c, &x1, &x2);
                printf("x1 = %f\n", x1);
                printf("x2 = %f\n", x2); 
                printf("method a was used\n");
                return 0;
            }
            else{
                calculate_c(a, b, c, &x1, &x2);
                printf("x1 = %f\n", x1);
                printf("x2 = %f\n", x2); 
                printf("method c was used\n");
            }
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }
    
}