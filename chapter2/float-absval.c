#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "float-negate.h"

/* Compute |f|. If f is NaN, the return f. */
float_bits float_absval(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  if ((exp == 0xff) && (frac != 0)) {
    return f;
  } else {
    return (0 << 31) | (exp << 23) | frac;
  }
}
