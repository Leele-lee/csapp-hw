#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*Suppose we number the bytes in a w-bit word from O (least significant)
  to w/8 - 1 (most significant).Write code for the following C function,
  which will return an unsigned value in which byte i of argument × has beenreplaced by byte b:
  unsigned replace_ byte (unsigned x, int i, unsigned char b);
  replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
  replace_byte(0x12345678, 0, 0xAB) --> 0×123456AB*/

typedef unsigned char * byte_pointer;

unsigned replace_byte(unsigned x, int i, unsigned char b) {
  byte_pointer xf = (byte_pointer) &x;
  assert(i < sizeof(unsigned));
  //memcpy(ans, xf, sizeof(byte_pointer));
  
  xf[i] = b;
  return x;
}

int main(int argc, char *argv[]) {
  unsigned ans;
  ans = 0x12345678;
  ans = replace_byte(ans, 0, 0xab);
  printf("%.2x", ans);
  return 0;
}
