#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*Write C expressions that evaluate to 1 when the following conditions are true and to 0 when they are false.
  Assume × is of type int.
  A. Any bit of × equals 1.
  B. Any bit of × equals 0.
  C. Any bit in the least significant byte of × equals 1.
  D. Any bit in the most significant byte of × equals 0.
  Your code should follow the bit-level integer coding rules (page
  128), with the additional restriction that you may not use equality ==) or inequality (!=) tests.*/

int testA(int x) {
  //size_t num = sizeof(int) << 3;
  return !!x;
}

int testB(int x) {
  size_t num = sizeof(int) << 3;
  return !!(x ^ (~0x0));
}

int testC(int x) {
  size_t num = (sizeof(int) - 1) << 3;
  return !!(((x << num) >> num) ^ 0x0);
}


int testD(int x) {
  size_t num = (sizeof(int) - 1) << 3;
  return !!((((x >> num) & 0xff) + (~0xff)) ^ (~0));
}

int main(int argc, char *argv[]) {
  int x = atoi(argv[1]);
  printf("Any bit of × equals1  is: %d\n", testA(x));
  printf("Any bit of × equals0.is: %d\n", testB(x));
  printf("Any bit in the least significant byte of × equa 1 is: %d\n", testA(x));
  printf("Any bit in the most significant byte of × equals 0is: %d\n", testD(x));
}
