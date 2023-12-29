#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "float-negate.h"

/* Compute 2*f. If f is NaN, then return f. */
float_bits float_twice(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  if (exp == 0xff) { // if f == NaN,return f(NaN), if f == +oo, return f(+oo)
    return f;
  } else if (exp == 0) {
    frac = frac << 1;
  } else if (exp == 0xfe){
    exp = 0xff;
    frac = 0;
  } else {
    exp = exp + 1; 
  }
  return (sign << 31) | (exp << 23) | frac;
}
