#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
 * Return 1 when x can be represented as an n-bit, 2's-complement number;
 * 0 otherwise. Assume 1 <= n <= w
 */

int fits_bits(int x, int n){
  /* when x > 0, x < 2 ^ (n - 1) //(1 << (n -1)), eg: x = 5, n = 4, 5 < 0000 ... 0000 1000(8)
   * when x < 0, x <= -2 ^ (n - 1), eg: x = -5, n = 4, -5 < 1111 ...  1111 1000(-8)
   * when x = 5 -> x > 0 -> signbit = 0; reduction = 0000 1000 - x 's signbit = 0 -> reduction ^ (x >> 31) == 0
   * when x = -5 -> x < 0 -> signbit = 1; reduction = 1111 1000 - x 's signbit = 1 / 0 -> reduction ^ (x >> 31) == 0 -> ((x >> 31) == 0) || (signbit == 1 && reduction == 0)
   */
  int reduction;
  int reduction_sign_bit;
  int signbit = !!(x >> 31);
  int num = sizeof(int) << 3;
  //return !(((1 << (n - 1)) + ((signbit << 31) >> (num - n - 1)) - x) >> 31 ^ (x >> 31));
  reduction = ((1 << (n - 1)) + ((signbit << 31) >> (num - n - 1)) - x);
  reduction_sign_bit = reduction >> 31;
  //argu = ((1 << (n - 1)) + ((signbit << 31) >> (num - n - 1)) - x) >> 31;
  return (!(reduction_sign_bit ^ (x >> 31))) | (signbit & (reduction == 0));
}

int main(int argc, char *argv[]) {
  assert(fits_bits(5, 4) == 1);
  //printf("%.2x", fits_bits(5, 4));
  assert(fits_bits(-5, 4) == 1);
  assert(fits_bits(16, 4) == 0);
  assert(fits_bits(-16, 5) == 1);
  return 0;
}
