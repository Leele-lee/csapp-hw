#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void psum1a(float a[], float p[], long n) {
  long i;
  /* last_val holds p[i-1], val holds p[i] */
  float last_val, val;
  last_val = p[0] = a[0];
  for (i = 1; i < n; i++) {
    val = last_val + a[i];
    p[i] = val;
    last_val = val;
  }
}

void psum_4_1a(float a[], float p[], long n) {
  long i;
  float last_val, val;
  float tmp, tmp1, tmp2, tmp3;
  val = p[0] = a[0];
  for (i = 1; i < n - 3; i += 4) {
    val = last_val + a[i];
    tmp = val;
    tmp1 = tmp + a[i+1];
    tmp2 = tmp1 + a[i+2];
    tmp3 = tmp2 + a[i+3];

    p[i]= tmp;
    p[i+1] = tmp1;
    p[i+2] = tmp2;
    p[i+3] = tmp3;

    /* Must spilt it and reassociation */
    last_val = last_val + (a[i] + a[i+1] + a[i+2] + a[i+3]);
  }

  for (; i < n; i++) {
    last_val += a[i];
    p[i] = last_val;
  }
}

int main(int argc, char* argv[]) {
  float a[5] = {1, 2, 3, 4, 5};
  float p[5];
  psum1a(a, p, 5);
  assert(p[4] == 15);

  float q[5];
  psum_4_1a(a, q, 5);
  assert(q[4] == 15);
  return 0;
}
