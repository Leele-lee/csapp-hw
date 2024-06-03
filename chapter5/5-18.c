#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Caculate a0 + a1*x + a2*x^2 + ... + an*x^n */
double poly(double a[], double x, long degree) {
  long i;
  double xexp = x;
  double result = a[0];
  for (i = 1; i <= degree; i++) {
    result += a[i] * xexp; 
    xexp *= x;
  }
  return result;
}

/* Caculate a0+x(a1+x(a2+…+x(an-1+xan)…) */
double polyh(double a[], double x, long degree) {
  long i;
  double result = a[degree];
  for (i = degree - 1; i >= 0; i--) {
    result = x * result + a[i]; 
  }
  return result;
}

/* Version 6*3a */
double poly6_3a(double a[], double x, long degree) {
  long i;
  double x6 = x * x * x * x * x * x;
  double result0 = a[0];
  double result1 = 0;
  double result2 = 0;
  double xexp0 = x;
  double xexp1 = x*x*x;
  double xexp2 = x*x*x*x*x;
  for (i = 1; i <= degree-5; i+=6) {
    result0 = result0 + (a[i] * xexp0 + a[i+1] * xexp0 * x);
    result1 = result1 + (a[i+2] * xexp1 + a[i+3] * xexp1 * x);
    result2 = result2 + (a[i+4] * xexp2 + a[i+5] * xexp2 * x);
    xexp0 *= x6;
    xexp1 *= x6;
    xexp2 *= x6;
  }

  for (; i <= degree; i++) {
    result0 += a[i] * xexp0;
    xexp0 *= x;
  }
  return result0 + result1 + result2;
}

int main(int argc, char* argv[]) {
  double a[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  double x = 2;
  long degree = 10;

  assert(poly(a, x, degree) == 2+4+8+16+32+(2+4+8+16+32)*32);
  assert(polyh(a, x, degree) == poly(a, x, degree));
  assert(poly6_3a(a, x, degree) == 2+4+8+16+32+(2+4+8+16+32)*32);
}
