#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned packet_t;

int xbyte(packet_t word, int bytenum){
  return (int)(word >> (bytenum << 3) << 24) >> 24;
}

int main(int argc, char *argv[]){
  assert(xbyte(0x12345678, 1) == 0x00000056);
  assert(xbyte(0x12345678, 2) == 0x00000034);
  assert(xbyte(0x12345678, 3) == 0x00000012);
  assert(xbyte(0x123456FF, 0) == 0xFFFFFFFF);
  assert(xbyte(0x00112233, 0) == 0x33);
  assert(xbyte(0x00112233, 1) == 0x22);
  assert(xbyte(0x00112233, 2) == 0x11);
  assert(xbyte(0x00112233, 3) == 0x00);

  assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
  assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
  assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
  assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);
  return 0;
}
