#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/* The following function does not run properly on some machine */
/*
int bad_int_size_is_32() {
  int set_msb = 1 << 31;
  int beyond_msb = 1 << 32;

  return set_msb && !beyond_msb;
}
*/

/* Set_msb is nonzero when word size >= 32
   beyond_msb is zero when word size <= 32
 */
int int_size_is_32() {
  //return (1 << 31) < 0;
  int msb = (1 << 31);
  int beyond = msb << 1;
  return msb && (!beyond);
}

int int_size_is_32_for_16() {
  int msb = ((1 << 15) << 15) << 1;
  int beyond = msb << 1;
  return msb && (! beyond);  
}

int main(int argc, char *argv[]) {
  assert(int_size_is_32());
  assert(int_size_is_32_for_16());
  return 0;
}


