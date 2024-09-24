/*
 * 8.25
 */
#include <stdio.h>
#include "csapp.h"
#define LEN 100

sigjmp_buf buf;

void handler(int sig) {
  siglongjmp(buf, 1);
}

char* tfgets(char* str, int size, FILE* stream) {
  char* read;
  if (!sigsetjmp(buf, 1)) {
    Signal(SIGALRM, handler);
    alarm(5);
    read = fgets(str, size, stream); // if user input nothing, fgets is wating until call SIGALARM
    alarm(0); // alarm must be cancelled only after waiting time is less than 5 secs and user input sth
    return read;
  }
  else
    return NULL;
}

int main(int argc, char* argv[]) {
  char buf[LEN];
  char* input = tfgets(buf, LEN, stdin);
  if (input == NULL)
    printf("nothing input: NULL\n");
  else
    printf("%s", input);
  return 0;  
}
