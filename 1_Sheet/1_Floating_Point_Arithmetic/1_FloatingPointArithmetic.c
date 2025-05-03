#include <stdio.h>
#include <math.h>
#include <time.h>

#define PI 3.141592653589793
#define TRUE_SUM (PI * PI / 6.0)

float sum_forward(int k) {
    double sum = 0.0;
    for (int n = 1; n <= k; n++) {
        sum += 1.0 / n / n;
    }
    return sum;
}

float sum_backward(int k) {
    double sum = 0.0;
    for (int n = k; n >= 1; n--) {
        sum += 1.0 / n / n;
    }
    return sum;
}

void compute_and_report(int k, FILE *fp) {
    clock_t start, end;
    
    printf("\n--- k = %d ---\n", k);

    // Forward sum
    start = clock();
    double forward = sum_forward(k);
    end = clock();
    double forward_time = (double)(end - start) / CLOCKS_PER_SEC; // converts ticks into seconds

    // Backward sum
    start = clock();
    double backward = sum_backward(k);
    end = clock();
    double backward_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Relative errors
    double err_forward = fabs(forward - TRUE_SUM) / TRUE_SUM;
    double err_backward = fabs(backward - TRUE_SUM) / TRUE_SUM;

    // Write to csv
    double rel_err = fabs(backward - TRUE_SUM) / TRUE_SUM;
    fprintf(fp, "%d,%.10e\n", k, rel_err);
    

    // print to terminal
    printf("Forward sum    = %.7f (err = %.3e), time = %.4fs\n", forward, err_forward, forward_time);
    printf("Backward sum   = %.7f (err = %.3e), time = %.4fs\n", backward, err_backward, backward_time);
}   // floats only have about 7 digits of accuracy

int main() {
    FILE *fp = fopen("rel_err_double.csv", "w");
    if (!fp) {
        perror("File opening failed");
        return 1;
    }
    fprintf(fp, "k,relative_error\n");
    printf("double precision");
    int ks[] = {100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

    for (int i = 0; i < 8; i++) {
        compute_and_report(ks[i],fp);
    }
    fclose(fp);
    return 0;
}
// use the following code for single precision instead
/*
#include <stdio.h>
#include <math.h>
#include <time.h>

#define PI 3.141592653589793
#define TRUE_SUM (PI * PI / 6.0)

float sum_forward(int k) {
    float sum = 0.0;
    for (int n = 1; n <= k; n++) {
        sum += 1.0 / n / n;
    }
    return sum;
}

float sum_backward(int k) {
    float sum = 0.0;
    for (int n = k; n >= 1; n--) {
        sum += 1.0 / n / n;
    }
    return sum;
}

void compute_and_report(int k, FILE *fp) {
    clock_t start, end;
    
    printf("\n--- k = %d ---\n", k);

    // Forward sum
    start = clock();
    float forward = sum_forward(k);
    end = clock();
    double forward_time = (double)(end - start) / CLOCKS_PER_SEC; // converts ticks into seconds

    // Backward sum
    start = clock();
    float backward = sum_backward(k);
    end = clock();
    double backward_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Relative errors
    double err_forward = fabs(forward - TRUE_SUM) / TRUE_SUM;
    double err_backward = fabs(backward - TRUE_SUM) / TRUE_SUM;

    // Write to csv
    double rel_err = fabs(backward - TRUE_SUM) / TRUE_SUM;
    fprintf(fp, "%d,%.10e\n", k, rel_err);
    

    // print to terminal
    printf("Forward sum    = %.7f (err = %.3e), time = %.4fs\n", forward, err_forward, forward_time);
    printf("Backward sum   = %.7f (err = %.3e), time = %.4fs\n", backward, err_backward, backward_time);
}   // floats only have about 7 digits of accuracy

int main() {
    FILE *fp = fopen("rel_err_float.csv", "w");
    if (!fp) {
        perror("File opening failed");
        return 1;
    }
    fprintf(fp, "k,relative_error\n");
    printf("single precision");
    int ks[] = {1000, 1000000, 10000000, 100000000};

    for (int i = 0; i < 4; i++) {
        compute_and_report(ks[i],fp);
    }
    fclose(fp);
    return 0;
}*/
