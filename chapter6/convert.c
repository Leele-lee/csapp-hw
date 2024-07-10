/*
 * convert.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define MATRIX_N 9973
#define MEM_SIZE (sizeof(int) * MATRIX_N * MATRIX_N)
#define LOOP 1000
#define BLOCK 16

void randomize(int *arr, int N) {
  srand(time(0));
  int i, j;
  for (i = 0; i <= N - 1; i++ )
    for (j = 0; j <= N - 1; j++)
      arr[i * N + j] = rand() % 2;      
}

void convert(int *src, int N) {
  int i, j;
  for (i = 0; i <= N - 1; i++)
    for (j = 0; j <= N - 1; j++)
      src[j * N + i] = src[i * N + j] || src[j * N + i];
}

void effective_convert(int *src, int N) {
  int i, j, a, b, tmp;

  for (i = 0; i <= N - BLOCK; i += BLOCK)
    for (j = i; j <= N - BLOCK; j += BLOCK)
      for (a = i; a < i + BLOCK; a++)
	for (b = j; b < j + BLOCK; b++) {
	  tmp = src[b * N + a] || src[a * N + b];
	  src[b * N + a] = tmp;
	  src[a * N + b] = tmp;
	}

  int offset = i;

  for (i = offset; i <= N - 1; i++)
    for (j = 0; j < offset; j++) {
      tmp = src[j * N + i] || src[i * N + j];
      src[j * N + i] = tmp;
      src[i * N + j] = tmp;
    }

  for (i = offset; i <= N - 1; i++)
    for (j = 0; j < offset; j += BLOCK)
      for (b = j; b < j + BLOCK; b++) {
        tmp = src[b * N + i] || src[i * N + b];
        src[b * N + i] = tmp;
        src[i * N + b] = tmp;
      }

  for (i = offset; i <= N - 1; i++)
    for (j = i; j <= N - 1; j++) {
      tmp = src[j * N + i] || src[i * N + j];
      src[j * N + i] = tmp;
      src[i * N + j] = tmp;
    }
}

void test(void) {
  int *s = (int *)malloc(MEM_SIZE);
  int *e = (int *)malloc(MEM_SIZE);

  randomize(s, MATRIX_N);
  memcpy(e, s, MEM_SIZE);

  convert(s, MATRIX_N);
  effective_convert(e, MATRIX_N);

  for (int i = 0; i < MATRIX_N; i++)
    for (int j = 0; j < MATRIX_N; j++)
      assert(s[i * MATRIX_N + j] == e[i * MATRIX_N + j]);

  free(e);
  free(s);
}

void pro(void) {
  int *s = (int *)malloc(MEM_SIZE);
  clock_t start, end;
  start = clock();
  convert(s, MATRIX_N);
  end = clock();

  printf("origin convert run time: %lf\n", difftime(end, start)/CLOCKS_PER_SEC);

  free(s);
}

void pro_effect(void) {
  int *s = (int *)malloc(MEM_SIZE);
  clock_t start, end;
  start = clock();
  effective_convert(s, MATRIX_N);
  end = clock();

  printf("effective transpose run time: %lf\n", difftime(end, start)/CLOCKS_PER_SEC);

  free(s);
}

int main(int argc, char *argv[]) {
  //test();
  pro();
  pro_effect();
  return 0;
}
