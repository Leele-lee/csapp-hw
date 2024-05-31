#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

void* basic_memset(void *s, int c, size_t n) {
  size_t cnt = 0;
  unsigned char *schar = s;
  while (cnt < n) {
    *schar++ = (unsigned char)c;
    cnt++;
  }
  return s;
}

/*
 * K = sizeof(unsigned long)
 * cs store K chars for memset
 */
void* effective_memset(void *s, unsigned long cs, size_t n) {
  size_t K = sizeof(unsigned long);
  size_t cnt = 0;
  unsigned char *schar = s;
  /* align to K */
  while (cnt < n) {
    if ((size_t)schar % K == 0) {
      break;
    }
    *schar++ = (unsigned char)cs;
    cnt++;
  }

  /* Set K chars one time */
  unsigned long *slong = (unsigned long *)schar;
  size_t rst = n - cnt;
  size_t num = rst / K;
  size_t tail = rst % K;
  for (size_t i = 0; i < num; i++) {
    *slong++ = cs;
  }

  schar = (unsigned char *)slong;
  for (size_t i = 0; i < tail; i++) {
    *schar++ = (unsigned char)cs;
  }
  return s;
}

int main(int argc, char* argv[]) {
  size_t space = sizeof(char) * 65537;
  void* basic_space = malloc(space);
  void* effective_space = malloc(space);
  
  int basic_fill = 0xFF;
  unsigned long effective_fill = ~0;

  basic_memset(basic_space, basic_fill, space);
  effective_memset(effective_space, effective_fill, space);

  assert(memcmp(basic_space, effective_space, space) == 0);

  free(basic_space);
  free(effective_space);
  return 0;
}
