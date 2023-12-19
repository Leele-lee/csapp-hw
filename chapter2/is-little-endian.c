#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

int is_little_endian(byte_pointer start) {
  
  if (start[0] == 0x78) {
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char *argv[]) {
  int val = 0x12345678;
  byte_pointer valp = (byte_pointer) &val;
  int ans = is_little_endian(valp);
  printf("%d\n", ans);
  return 0;
}
