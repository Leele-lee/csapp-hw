#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Return 1 when x contains an odd number of ls; 0 otherwise. Assume w = 32
 * Your code should contain a total of at most 12 arithmatic, bitwise, and logical operations.
 */
int odd_ones(unsigned x) {
  /* You can split x into two parts, each part containing 16 bits.
   * Then you can use the XOR operation to merge these two parts.
   * Each bit in the result represents whether the origin two bits have an odd number of 1s.
   * when have two 1s or zero 1s, XOR operation result the bit is 0, otherwise 1.
   * Then we just need split the half, until there is only one bit to compare.
   * The last bit is the answer, 1 represent has odd numbers of 1s.
   * eg: 0000 1110 1010 1010 1010 1010 1010 1010
   * 0000 1110 1010 1010
   * ^
   * 1010 1010 1010 1010
   * =
   * 1010 1100 0000 0000
   *
   * 1010 1100
   * ^
   * 0000 0000
   * =
   * 1010 1100
   *
   * 1010
   * ^
   * 1100
   * =
   * 0110
   *
   * 01 ^ 10 = 11
   * 1 ^ 1 = 0
   *
   */
  x = (x >> 16) ^ x;
  x = (x >> 8) ^ x;
  x = (x >> 4) ^ x;
  x = (x >> 2) ^ x;
  x = (x >> 1) ^ x;
  return x & 0x1;
}

int main(int argc, char *argv[]) {
  assert(odd_ones(0x00000001));
  assert(!odd_ones(0));
  assert(odd_ones(0xefffffff));
  assert(!odd_ones(0xffffffff));
  return 0;
}
