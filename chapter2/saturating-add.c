#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y) {
  /* when x < 0, y < 0, and x + y > 0, it satisfiled negative overflow, should return TMin = 0x80000000
   * when x > 0, y > 0, and x + y < 0, it satisfiled positive overflow, should return TMax = 0x7fffffff 
   */
  int add_sign_bit = !!((x + y) >> 31); // positive is 0, negative is 1
  int pos_over = (!((x >> 31) | (y >> 31))) & add_sign_bit;
  int neg_over = (!~((x >> 31) & (y >> 31))) & (!add_sign_bit);
  int either_over = (pos_over | neg_over);
  // when either = 0x1, ~either + 2*either = 0x0, 0x0 & x = 0
  // when either = 0x0, ~either + 2*either = 0xffffffff, 0xffffffff & x = x
  return (((pos_over << 31) - pos_over) | (neg_over << 31))  + (((~either_over) + (either_over << 1)) & (x + y));
  //return (((pos_over << 31) - pos_over) | (neg_over << 31));
}

int main(int argc, char* argv[]) {
  assert(saturating_add(INT_MAX - 1, 2) == INT_MAX);
  //printf("%.2x", saturating_add(INT_MIN + 1, -2));
  assert(saturating_add(INT_MIN + 1, -2) == INT_MIN);
  assert(0x11 + 0x22 == saturating_add(0x11, 0x22));
  return 0;
}
