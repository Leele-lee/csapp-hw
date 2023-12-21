#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* To use only + - <<, and at most three operations per expression
 */
int cons_seventeeen(int x) {
  return (x << 4) + x;
}

int cons_neg_seven(int x) {
  return -((x << 3) - x);
}

int cons_sixty(int x) {
  return (x << 6) - (x << 2);
}

int cons_neg_onehuntwelve(int x) {
  return (x << 4) - (x << 7);
}

int main(int argc, char * argv[]) {
  int x = 0x87654321;
  assert(cons_seventeeen(x) == x * 17);
  assert(cons_neg_seven(x) == x * (-7));
  assert(cons_sixty(x) == x * 60);
  assert(cons_neg_onehuntwelve(x) == x * (-112));
  return 0;
}
