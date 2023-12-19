#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Perform a logical shift using an arithmatic right shift.*/
unsigned srl(unsigned x, int k) {
  /* Perform shift arithmaticlly */
  unsigned xsra = (int) x >> k;
  unsigned sum = sizeof(int) << 3;
  return ((!! (x & (1 << (sum - k - 1)))) << (sum - k)) + xsra;
}

/* Perform an arithmatic shift using a logical right shift.*/
int sra(int x, int k) {
  /* Perform shift logically */
  int xsrl = (unsigned) x >> k;
  unsigned sum = sizeof(int) << 3;
  return (((1 << k) - 1) << (sum - k)) + xsrl + (!(x & (1 << 31)) << (sum - k));
  //return (!(x & (1 << 31)) << (sum - k));
}

void test_srl() {
  unsigned x = 0xf0000003;
  unsigned ans = srl(x, 2);
  assert(ans = 0x3c000000);
  unsigned x2 = 0xf0000006;
  unsigned ans2 = srl(x2, 2);
  assert(ans2 = 0x3c000001);
  unsigned x3 = 0x000000ff;
  unsigned ans3 = srl(x3, 4);
  assert(ans3 == 0x0000000f);
}

void test_sra() {
  int x = 0xf0000003;
  unsigned ans = sra(x, 4);
  assert(ans == 0xff000000);
  unsigned x2 = 0x000000ff;
  unsigned ans2 = sra(x2, 4);
  assert(ans2 == 0x0000000f);
  // printf("%.2x", ans2);
}
int main(int argc, char *argv[]) {
  test_srl();
  test_sra();
  return 0;
}
