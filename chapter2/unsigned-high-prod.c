#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <inttypes.h>

int signed_high_prod_test(int x, int y) {
  int64_t mul = (int64_t) x * y;
  return mul >> 32;
}

/* Computes the high-order w bits if x * y for unsigned variables
 * We have signed_high_prod to computes the high-order w bits of x * y for signed variables
 */
int signed_high_prod(int x, int y) {
  int t_num = sizeof(int) << 3;
  long res = (long)x * (long)y;
  return res >> t_num;
}
/* Firstly, we need to know x' = x + sign_bit_x * (2 ^ w), y' = y + sign_bit_y * (2 ^ w)
 * x'y'(the value before truanting) = xy(before truanting) + x * sigh_bit_y * (2 ^ w) + y * sign_bit_x * (2 ^ w) + sign_bit_x * sign_bit_y * (2 ^ 2w);
 * If we only want to get the most w signifancant bits, x * sign_bit_y and y * sign_bit_x actually are added to the x'y'' most signifancant bits,
 * sign_bit_x * sign_bit_y is negelect because it shift left 2w bit, is beyond the range we need to consider.
 */
unsigned unsigned_high_prod(unsigned x, unsigned y) {
  int t_num = sizeof(int) << 3;
  int tx = (signed)x;
  int ty = (signed)y;
  int sign_bit_x = x >> 31;
  int sign_bit_y = y >> 31;
  return signed_high_prod(tx, ty) + tx * sign_bit_y + ty * sign_bit_x;
}

unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
  unsigned t_num = sizeof(unsigned) << 3;
  unsigned long res = (unsigned long)x * (unsigned long)y;
  return res >> t_num;
}

unsigned another_unsigned_high_prod2(unsigned x, unsigned y) {
  uint64_t mul = (uint64_t) x * y;
  return mul >> 32;
}

int main(int argc, char* argv[]) {
  assert(unsigned_high_prod(1234567890, 987654321) == another_unsigned_high_prod(1234567890, 987654321));
  assert(unsigned_high_prod(4294967295, 4294967295) == another_unsigned_high_prod(4294967295, 4294967295));
  assert(unsigned_high_prod(0, 4294967295) == another_unsigned_high_prod(0, 4294967295));
  unsigned x = 0x12345678;
  unsigned y = 0xFFFFFFFF;

  assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
  //assert(another_unsigned_high_prod2(x, y) == another_unsigned_high_prod(x, y));
  //assert(another_unsigned_high_prod2(1234567890, 987654321) == another_unsigned_high_prod(1234567890, 987654321));
  //assert(another_unsigned_high_prod2(4294967295, 4294967295) == another_unsigned_high_prod(4294967295, 4294967295));
  //assert(another_unsigned_high_prod2(0, 4294967295) == another_unsigned_high_prod(0, 4294967295));
  printf("%.2x\n", unsigned_high_prod(x, y));
  printf("%.2x\n", another_unsigned_high_prod(x, y));
  printf("%.2x\n", x * y);
  return 0;
}
