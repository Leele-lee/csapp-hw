#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/* Returns a floating point value having an identical bit representation as its unsigned urgument*/
float u2f(unsigned u) {
  return *(float *)&u;
}

float fpwr2(int x) {
  /* Result exponent and fraction */
  unsigned exp, frac;
  unsigned u;
  if (x < -129) { // 1 - bias -23 0 000...0 00000...001 
    /* Too small, return 0.0 */
    exp = 0;
    frac = 0;
  } else if (x < -126) { // 0 00000001 0000..0 1-bias
    /* Denormalized result */
    exp = 1;
    frac = (1 << 23) >> (-126 - x);
  } else if (x < 128) { // < 0 11111111 000...0 2^8 - 1 -bias = 255 - 127
    /* Normalized result */
    exp = x + 127; // x + bias
    frac = 0;
  } else {
    /* Too big. Return +oo */
    exp = 255;
    frac = 0;
  }
  /* Pack exp and frac into 32 bits */
  u = exp << 23 | frac;
  /* Return as float */
  return u2f(u);
}

int main(int argc, char* argv[]) {
  assert(fpwr2(0) == powf(2,0));
  assert(fpwr2(100) == powf(2,100));
  assert(fpwr2(-100) == powf(2,-100));
  assert(fpwr2(10000) == powf(2,10000));
  assert(fpwr2(-10000) == powf(2,-10000));
  return 0;
}
