#include <stdio.h>
#include <float.h>

int main() {
    float f = 1.0f;
    while ((float)(1.0 + f / 2.0) > 1.0) {
        f /= 2.0f;
    }

    double d = 1.0;
    while ((1.0 + d / 2.0) > 1.0) {
        d /= 2.0;
    }

    printf("Calculated machine epsilon:\n");
    printf("Single precision: %.10e\n", f);
    printf("Double precision: %.20e\n\n", d);

    printf("From limits.h:\n");
    printf("FLT_EPSILON: %.10e\n", FLT_EPSILON);
    printf("DBL_EPSILON: %.20e\n", DBL_EPSILON);

    return 0;
}
