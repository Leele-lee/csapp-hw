#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "float-negate.h"
#include <math.h>

float u2f(unsigned u) {
  return *(float *)&u;
}

/*
 * Compute (int)f.
 * If conversion causes overflow(it is out of range) or f is NaN, return 0x80000000
 * Your function should round to zero
 */
int float_f2i(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  unsigned bias = pow(2, 7) - 1;
  int E;
  int M;
  if (exp == 0xff && frac != 0) {
    return 0x80000000;
  }
  if (exp < bias) { // num < 1, return 0
    return 0;
  }
  /* INT_MIN = -2 ^ (n - 1) = - 2 ^ 31, INT_MAX = 2 ^ (n - 1) - 1 = 2 ^ 31 - 1*/
  if (exp >= 31 + bias) { // overflow
    return 0x80000000;
  } else {
    /* The value of E represents the number of significant digits of the floating point number. */
    E = exp - bias;
    M = frac | 0x800000; //fraction has leading 1
    /* If e is less than 23, we need to right shift to get the correct result, otherwise left shift */
    if (E < 23) {  // round to zero
      M >>= (23 - E);
    } else { // add zero to the end of M
      M <<= (E - 23);
    }
    return sign ? -M : M;
  }
}

int main(int argc, char * argv[]) {
  assert(float_f2i(0x98765432) == (int)u2f(0x98765432));
  assert(float_f2i(0x19802385) == (int)u2f(0x19802385));
  assert(float_f2i(0x78000087) == 0x80000000);
  assert(float_f2i(0x8F088888) == (int)u2f(0x8F088888));
  return 0;
}
