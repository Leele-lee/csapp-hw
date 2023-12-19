#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/*
 * Copy integer into buffer if space is avaliable
 */
void copy_int(int val, void* buf, int maxbytes) {
  if (maxbytes - (int)sizeof(val) >= 0) {
    memcpy(buf, (void *) &val, sizeof(val));
  }
}

int main(int argc, char* argv[]) {
  int maxbytes = sizeof(int) * 10;
  void* buf = malloc(maxbytes);
  int val;

  val = 0x12345678;
  copy_int(val, buf, maxbytes);
  assert(*(int*)buf == val);

  val = 0xaabbccdd;
  copy_int(val, buf, 0);
  assert(*(int*)buf != val);
  return 0;
}
