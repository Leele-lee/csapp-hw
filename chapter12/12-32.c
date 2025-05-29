/* $begin tfgetsmain */
#include <stdio.h>
#include "csapp.h"


char *tfgets(char *s, int size, FILE *stream);

/*
 * tfgets should: 1. return NULL if 5 seconds not receive input line
 *                2. run fgets if not
 */
char *tfgets(char *s, int size, FILE *stream) {
    struct timeval timeout;
    fd_set read_set;

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);

    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    if (Select(1, &read_set, NULL, NULL, &timeout) == 0) {
        return NULL;
    } else {
        return fgets(s, size, stream);
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
