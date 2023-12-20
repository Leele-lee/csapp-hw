#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void * another_calloc(size_t nmemb, size_t size) {
  if (nmemb == 0 || size == 0) {
    return NULL;
  }
  size_t t_num = sizeof(size_t) << 3;
  size_t total_byte = nmemb * size;
  if (total_byte / nmemb != size) {
    return NULL;
  } else {
  void * new_space = malloc(total_byte);
  memset(new_space, 0, total_byte);
  return new_space;
  }
}


int main() {
  void * p;
  p = another_calloc(0x1234, 1);
  assert(p != NULL);
  free(p);

  p = another_calloc(SIZE_MAX, 2);
  assert(p == NULL);
  return 0;
}
