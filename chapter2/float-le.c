#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Tests whether the first argument is less than or equal to its second
 * Assume the function f2u returns an unsigned 32-bit number having the same representation
 * as its floating point argument
 */
unsigned f2u(float x) {
  return *(unsigned *)&x;
}

int float_le(float x, float y) {
  unsigned ux = f2u(x);
  unsigned uy = f2u(y);
  unsigned sx = ux >> 31;
  unsigned sy = uy >> 31;

  /* Give an expression using only ux, uy, sx and sy */
  return ((sx == sy) && (sx == 1) && (ux >= uy)) || (ux > uy) || ((sx == sy) && (sx == 0) && (ux <= uy));
  //return sy;
}


int main(int argc, char* argv[]) {
  assert(float_le(-0, +0));
  assert(float_le(+0, -0));
  assert(float_le(0, 3));
  assert(float_le(-4, -0));
  assert(float_le(-4, 4));
  //printf("%.2x", float_le(-4, -0));
  assert(float_le(-3, 1));
  return 0;
}
