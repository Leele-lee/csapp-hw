/*
 * 8.20
 */
#include <stdio.h>
#include "csapp.h"

int main(int argc, char* argv[], char* env[]) {
  if (execve("/bin/ls", argv, env) < 0) {
    fprintf(stderr, "execve error: %s\n", strerror(errno));
    exit(1);
  }
}
