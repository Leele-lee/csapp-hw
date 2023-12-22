#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* computes the value of 3/4 * x, rounded towards zero
 * It should not overflow which means we need divide 4 first, then multiply 3
 *
 */
int threefourth(int x) {
  int sign = x >> 31;
  int num = sizeof(int) << 3;
  int bias = (x >> (num - 1)) & ((1 << 2) - 1); // change the value of negative number division rounded to zero
  int divided4 = (x + bias) >> 2;
  int module = ((x ^ sign) - sign) & 0x3; // x % 4, for x^sign-sign, when sign = 0xffffffff, return -x ,when sign = 0, return x
  int addition_bias = (((module-1) ^ sign) - sign) & (((module >> 1) << 31) >> 31); // if module < 1, addtion_bias = 0
  return (divided4 << 1) + divided4 + (addition_bias);
  //return addition_bias;
}

int main(int argc, char * argv[]) {
  //printf("%.2x", threefourth(-10));
  assert(threefourth(8) == 6);
  assert(threefourth(9) == 6);
  assert(threefourth(10) == 7);
  assert(threefourth(11) == 8);
  assert(threefourth(12) == 9);

  assert(threefourth(-8) == -6);
  assert(threefourth(-9) == -6);
  assert(threefourth(-10) == -7);
  assert(threefourth(-11) == -8);
  assert(threefourth(-12) == -9);
  return 0;
}
