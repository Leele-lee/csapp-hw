#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Divide by power of 2 with correct rounding.
 * Assume  0 <= k <= w-1
 */
int divide_power2(int x, int k) {
  int num = sizeof(int) << 3;
  int bias = (x >> (num - 1)) & ((1 << k) - 1);
  return (x + bias) >> k;
}

int main(int argc, char * argv[]) {
  int x = 0x80000007;
  assert(divide_power2(x, 1) == x / 2);
  assert(divide_power2(x, 2) == x / 4);
  return 0;
}
