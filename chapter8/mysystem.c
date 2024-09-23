/*
 * 8.22
 */
#include <stdio.h>
#include "csapp.h"

int mysystem(char* command) {
  int status;
  int pid;
  if ((pid = Fork()) == 0) {
    char* argv[4] = {"", "-c", command, NULL};
    execve("/bin/sh", argv, environ);
  }

  printf("child pid: %d\n", pid); //in case to kill
  
  if (Waitpid(pid, &status, 0) > 0) {
    /* terminate normally */
    if (WIFEXITED(status)) {
      return WEXITSTATUS(status);
    }
    /* terminate abnormally*/
    if (WIFSIGNALED(status)) {
      return WTERMSIG(status);
    }
  }
}

int main(int argc, char* argv[], char* env[]) {
  int code;
  code = mysystem("./nomalexit");
  printf("normally exit test'status: %d\n", code); fflush(stdout);

  code = mysystem("./abnormalexit");
  printf("abnormally exit test's status: %d\n", code); fflush(stdout);
  
  exit(0);
}
