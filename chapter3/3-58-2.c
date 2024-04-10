#include <stdio.h>
#include <stdlib.h>

long decode2(long x, long y, long z) {
  y -= z;
  x *= y;
  return (y << 63 >> 63) ^ x;
}
