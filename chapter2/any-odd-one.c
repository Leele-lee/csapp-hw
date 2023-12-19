#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Return 1 when any odd bit of x equals 1; 0 otherwise. Assume w = 32 */
int any_odd_one(unsigned x) {
  unsigned x1 = 0xc;
  unsigned x2 = (x1 << 4) + x1;
  unsigned right_half = (x2 << 8) + x2;
  unsigned total = (right_half << 16) + right_half;
  return (x & total) == total;
}

int main(int argc, char *argv[]) {
  assert(any_odd_one(0xffffffff));
  assert(!any_odd_one(0));
  assert(any_odd_one(0xcccccccc));
  return 0;
}
