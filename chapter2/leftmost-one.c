#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Generate mask indicating leftmost 1 in x. Assume w = 32.
 * For example, 0xff00 -> 0x8000, and 0x6600 -> 0x4000.
 * If x = 0, return 0
 * limit of 15 operations.
 */

int leftmost_one(unsigned x) {
  /* Set all bits to the right of the leftmost 1 to 1.
     You can then reset these bits to 0 by adding 1's and bitwise operations,
     leaving only the leftmost 1.*/
  x = (x >> 1) | x;
  x = (x >> 2) | x;
  x = (x >> 4) | x;
  x = (x >> 8) | x;
  x = (x >> 16) | x;
  return (x + 1) >> 1;
}

int main(int argc, char *argv[]) {
  //assert(leftmost_one(0xff00) == 0x8000);
  //assert(leftmost_one(0x6600) == 0x4000);
  unsigned a = leftmost_one(0xff00);
  unsigned b = leftmost_one(0x4000);
  //printf("%.2x", a);
  assert(a == 0x8000);
  assert(b == 0x4000);
  return 0;
}
