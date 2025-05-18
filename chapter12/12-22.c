/* $begin select */
#include "csapp.h"
void echo(int connfd);
void command(void);
int echo_line(int connfd);

//#define MAXFD FD_SETSIZE
//static rio_t client_buf[MAXFD];

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        listenfd = Open_listenfd("5000");
    } else {
        listenfd = Open_listenfd(argv[1]); // line:conc:select:openlistenfd
    }

    FD_ZERO(&read_set); /* Clear read set */                     // line:conc:select:clearreadset
    FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */ // line:conc:select:addstdin
    FD_SET(listenfd, &read_set); /* Add listenfd to read set */  // line:conc:select:addlistenfd

    int n = listenfd + 1;  // max fd

    while (1)
    {
        ready_set = read_set;
        Select(n, &ready_set, NULL, NULL, NULL); // line:conc:select:select
        if (FD_ISSET(STDIN_FILENO, &ready_set))             // line:conc:select:stdinready
            command();                                      /* Read command line from stdin */
        if (FD_ISSET(listenfd, &ready_set))
        { // line:conc:select:listenfdready
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            //echo(connfd); /* Echo client input until EOF */
            //Close(connfd);

            // if too many clients
            if (connfd + 1 > FD_SETSIZE) {
                fprintf(stderr, "too many clients\n");
                close(connfd);
            }
            n = n > connfd + 1 ? n : connfd + 1;
            FD_SET(connfd, &read_set);
            ready_set = read_set;

            //Rio_readinitb(&client_buf[connfd], connfd);
        }
        int fd;
        for (fd = listenfd + 1; fd < n; fd++) {
            if (FD_ISSET(fd, &ready_set)) {
                if (echo_line(fd) == -1) {
                    close(fd);
                    FD_CLR(fd, &read_set);
                    break;
                }
                break;
            }
        }
    }
}

int echo_line(int connfd) 
{
    ssize_t n;
    char buf[1];
    while ((n = Rio_readn(connfd, buf, 1)) > 0) {
        Rio_writen(connfd, buf, n);
        if (buf[0] == '\n') {
            //printf("Read %zd bytes: %s", n, buf); //debug
            return 0;
        }
    }
    return -1;
    /*static rio_t rio;
    static int current_fd = -1;
    char buf[MAXLINE];

    if (connfd != current_fd) {
        Rio_readinitb(&rio, connfd);
        current_fd = connfd;
    }

    ssize_t n = Rio_readlineb(&rio, buf, MAXLINE);
    if (n <= 0)
        return -1;

    Rio_writen(connfd, buf, n);
    return 0;*/
    /*char buf[MAXLINE];
    ssize_t n = Rio_readlineb(&client_buf[connfd], buf, MAXLINE);
    printf("Read %zd bytes: %s", n, buf); //debug

    if (n <= 0) {
        printf("Client closed connection or error\n");
        return -1;
    }

    Rio_writen(connfd, buf, n);
    return 0;*/
}

void command(void)
{
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
        exit(0);       /* EOF */
    printf("%s", buf); /* Process the input command */
}
/* $end select */
