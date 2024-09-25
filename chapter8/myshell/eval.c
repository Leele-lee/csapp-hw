/* eval - evaluate a command line */
#include <stdlib.h>
#include <stdio.h>
#include "csapp.h"
#include "eval.h"

void eval(char *cmdline) {
  char *argv[MAXARGS]; /* Argument list execve() */
  char buf[MAXLINE];   /* Holds modified command line*/
  int bg;              /* Should the job run in bg or fg*/
  pid_t pid;           /* Process id*/

  strcpy(buf, cmdline);
  bg = parseline(buf, argv);
  if (argv[0] = NULL)
    return; /* Igonre empty lines */

  if (!builtin_command(argv)) {
    if ((pid = Fork()) == 0) { /* child runs user job */
      if () {
      }
    }
  }
  
}
