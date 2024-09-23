/*
 * 8.24
 */
#include "csapp.h"
#define N 2
#define LEN 100

int main() {
  int status, i;
  pid_t pid;

  /* parent creates N children */
  for (i = 0; i < N; i++)
    if ((pid = Fork()) == 0) /* child */
      exit(100 + i);
  
  /* parent reaps N children in no particular order */
  while ((pid = Waitpid(-1, &status, 0)) > 0) {
    if (WIFEXITED(status))
      printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
    else if (WIFSIGNALED(status)) {
      char* buf[LEN];
      spritnf(buf, "child %d terminated by signal %d: %s", pid, WTERMSIG(status));
      psignal(WTERMSIG(status), buf);
    }
    else
      printf("child %d terminated abnormally\n", pid);
  }
  
  /* The only normal termination is if there are no more child */
  if (error != ECHILD)
    unix_error("waitpid error");
  
  exit(0);
}
