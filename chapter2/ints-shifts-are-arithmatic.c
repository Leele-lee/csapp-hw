#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* Write a function that yields 1 when run on a machine that uses arithmatic right shifts for data type int
 and yields 0 otherwise. Your code should work on a machine with any word size. Test your code on several machines.*/

int ints_shifts_are_arithmatic() {
  int x;
  x = -1;
  unsigned num = sizeof(int) << 3;
  return (x >> (num - 1)) == x;
}

int main(int argc, char *argv[]) {
  int ans = ints_shifts_are_arithmatic();
  assert(ans);
  return 0;
}
