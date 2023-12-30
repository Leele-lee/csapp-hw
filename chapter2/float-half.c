#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "float-negate.h"

/* Compute 0.5*f. If f is NaN, then return f. */
float_bits float_half(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  unsigned rest = f & 0x7fffffff;
  /*
   * Round to even, we focus on the last 2 bits of fraction
   * 00 => 0, just frac >> 1
   * 01 => 0, round to even, also is 0, just frac >> 1
   * 10 => 1, just frac >> 1
   * 11 => 10, (frac >> 1) + 1
   */
  unsigned addition = (frac & 0x3) == 0x3;
  if (exp == 0xff && frac != 0) {
    return f;
  } else if (exp == 0){
    /* Denormalized */
    frac = frac >> 1;
    frac += addition;
  } else if (exp == 1){
    /* Normalized to denormalized */
    rest >>= 1;
    rest += addition;
    frac = rest & 0x7fffff;
    exp = (rest >> 23) & 0xff;
  } else {
    exp -= 1;
  }
  return (sign << 31) | (exp << 23) | frac;
}
