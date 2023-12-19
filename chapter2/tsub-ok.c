#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

/*
 * Determine whether arguments can be subtracted withour overflow
 * Should return 1 when x-y does not overflow
 */

int tsub_ok(int x, int y) {
  int neg_y = (~y) + 1;

  int pos_over = !((x >> 31) | (neg_y >> 31)) & !(~((x + neg_y) >> 31));
  int neg_over = !~((x >> 31) & (y >> 31)) & !((x + neg_y) >> 31);
  // special case, when x >= 0, but y = INT_MIN, x - y must result positive overflow
  // because INT_MIN = - INT_MAX - 1, - INT_MIN = INT_MAX + 1 > INT_MAX, result in overflow
  int special_over = (!(x >> 31)) & (!(y ^ INT_MIN));
  return !(pos_over | neg_over | special_over);
}

int main(int argc, char* argv[]) {
  assert(!tsub_ok(0x0, INT_MIN));
  assert(tsub_ok(0x0, 0x0));
  return 0;
}
