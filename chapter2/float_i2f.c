#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include "float-negate.h"

int bits_length(int i) {
    if ((i & INT_MIN) != 0) {
        return 32;
    }
    int length = 0;
    unsigned u = (unsigned)i;
    while(u >= (1 << length)) {
        length++;
    }
    return length;
}

/* Generage mask for length len. e.g. 3->0x7 */
unsigned mask_length(int length) {
  return (unsigned)-1 >> (32 - length);
}

/* Compute (float)i */
float_bits float_i2f(int i) {
  //unsigend frac = ((i << 1) >> (32 - 24 + 1)) + addition;
  unsigned bias = pow(2, 7) - 1;
  unsigned sign, frac, exp;
  if (i == 0) {
    sign = 0;
    exp = 0;
    frac = 0;
    return (sign << 31) | (exp << 23) | frac;
  }
  if (i == INT_MIN) {
    sign = 1;
    exp = 31 + bias;
    frac = 0;
    return sign << 31 | exp << 23 | frac;
  }
  
  sign = 0;
  if (i < 0) {
    sign = 1;
    i = -i;
  }
  
  int length = bits_length(i);
  int flength = length - 1;
  exp = flength + bias;
  unsigned mask = mask_length(flength);
  unsigned f = i & mask;
  unsigned exp_frac;
  if (flength <= 23) {
    frac = f << (23 - flength);
    exp_frac = exp << 23 | frac;
  } else {
    frac = f >> (flength - 23);
    exp_frac = exp << 23 | frac;
    /* Check round */
    unsigned bit_mid = 1 << (flength - 23 - 1);
    unsigned bit_left = f & mask_length(flength - 23);
    if (bit_left < bit_mid) { // not round, direct cut
    } else if (bit_left > bit_mid) {
      exp_frac += 1;
    } else {
      /* If bit_left == bit_mid, round to even */
      if ((exp_frac & 0x1) == 0x1) {
	exp_frac += 1;
      }
    }
    
  }
  return sign << 31 | exp_frac;
}

int main(int argc, char * argv[]) {
  /* Test bit_length */
  assert(bits_length(0x3) == 2);
  assert(bits_length(0xf0000000) == 32);
  assert(bits_length(-1) == 32);
  assert(bits_length(INT_MIN) == 32);
  assert(bits_length(0) == 0);
  assert(bits_length(3) == 2);
  assert(bits_length(23) == 5);
  assert(bits_length(8388608) == 24);

  /* Test generate_mask */
  assert(mask_length(3) == 0x7);
  assert(mask_length(9) == 0x1FF);
  assert(mask_length(31) == 0x7FFFFFFF);

  /* Test float_i2f */
  assert(float_i2f(0) == 0x0);
  assert(float_i2f(INT_MIN) == 0xCF000000);
  assert(float_i2f(0x00359141) == 0x4A564504);
  assert(float_i2f(-98765) == 0xC7C0E680);
  assert(float_i2f(8388608) == 0x4b000000);
  //printf("%.2x", float_i2f(8388608));
  return 0;
}

