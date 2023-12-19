#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
 * Do rotating left shift. Assume 0 <= n < w
 * Example when x = 0x12345678 and w = 32:
 * n = 4 -> 0x23456781, n = 20 -> 0x67812345
 * Be care of the case n = 0.
 */

unsigned rotate_left(unsigned x, int n){
  unsigned left, right;
  unsigned num;
  num = sizeof(unsigned) << 3; 
  left = (x >> (num - n - 1)) >> 1;
  right = x << n;
  return left + right;
}

int main(int argc, char *argv[]) {
  unsigned x = 0x12345678;
  assert(rotate_left(x, 4) == 0x23456781);
  assert(rotate_left(x, 20) == 0x67812345);
  assert(rotate_left(x, 0) == x);
  return 0;
}
