 /* snippet.c, calculate square root of binary32 */
 #include <stdio.h>
 #include <math.h>

 int main (int argc, char **argv)
 {
 float a;
 float b;
 double res = 0.0;
 
 a = 1e30;
 b = 1.0;
 
 res = sqrt(a + b*b/a)*sqrt(a);
 fprintf(stdout, "standard method res: %e \n", res);
 
 return 0;
 }