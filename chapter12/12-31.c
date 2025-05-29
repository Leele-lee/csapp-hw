/* $begin tfgetsmain */
#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream);
sigjmp_buf buf;

void sigchld_handler(int sig) {
    siglongjmp(buf, 1);
}
/*
 * tfgets should: 1. return NULL if 5 seconds not receive input line
 *                2. run fgets if not
 */
char *tfgets(char *s, int size, FILE *stream) {
    if (Fork() == 0) {
        Sleep(5);
        exit(0);
    }
    switch (sigsetjmp(buf, 1)) {
        case 0:
          // check
          Signal(SIGCHLD, sigchld_handler);
          return fgets(s, size, stream);
        case 1:
          return NULL;
    }
} 

int main() 
{
    char buf[MAXLINE];

    if (tfgets(buf, MAXLINE, stdin) == NULL)
	printf("BOOM!\n");
    else 
	printf("%s", buf);

    exit(0);
}
/* $end tfgetsmain */
