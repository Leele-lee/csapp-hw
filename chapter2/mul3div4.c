#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Computes the value of 3 * x / 4 
 * Your code should replicate the fact that the computation 3 * x can cause overflow
 */

int mul3div4(int x) {
  int num = sizeof(int) << 3;
  int mul3 = (x << 1) + x;
  int bias = (mul3 >> (num - 1)) & ((1 << 2) - 1);
  return (mul3 + bias) >> 2;
  //return bias;
}

int main(int argc, char * argv[]) {
  int x = 0x87654321;
  assert(mul3div4(x) == x * 3 / 4);
  assert(mul3div4(8) == 6);
  assert(mul3div4(-8) == -6);
  assert(mul3div4(9) == 6);
  assert(mul3div4(-9) == -6);
  //printf("%.2x\n", mul3div4(x));
  //printf("%.2x", x * 3 / 4);
  return 0;
}
