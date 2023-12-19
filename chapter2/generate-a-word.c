#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Write a C expression that will yield a word consisting of
  the least significant byte of × and the remaining bytes of .
  For operands × = 0x89ABCDEF and y = 0×76543210, this would give
  0x765432EF.*/
unsigned generate_a_word(unsigned x, unsigned y) {
  unsigned ans;
  ans = ((x << 24) >> 24) + (y & ((y >> 8) << 8));
  return ans;
}

int main(int argc, char *argv[]) {
  unsigned res = generate_a_word(0x89abcdef, 0x76543210);
  assert(res == 0x765432ef);
  return 0;
}
