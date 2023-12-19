#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
 * Mask with least significant n bits set to 1
 * Example: n = 6 -> 0x3f, n = 17 -> 0x1fff
 * Assume 1 <= n <= w
 * Be care of the case n = w;
 */

int low_one_mask(int n) {
  int num = sizeof(int) << 3;
  int x;
  //return ~(1 << (num - 1)) >> (num - n -1);
  x = 1 << (n - 1);
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  return x;
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  int x = atoi(argv[1]);
  int ans = low_one_mask(x);
  printf("%.2x", ans);
  return 0;
}
