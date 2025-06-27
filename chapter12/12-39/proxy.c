/*
 * proxy.c
 *
 * visited url log to file log.list
 * block url base on entry from file block.list
 */
#include <stdio.h>
#include "../csapp.h"

/*
 * 1. Read request line using Rio_readlineb
 * and extract method, uri, and version from it.
 * 2. block uri if it in the filter list
 * 3. sent relative path format request line and headers to the server
 * 4. logging the uri toa proxy.log file
 */
void handle_request(int fd) {
    rio_t rio;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];

    Rio_readinitb(&rio, fd);
    // read request line and header
    if (!Rio_readlineb(&rio, buf, MAXLINE)) {
        Close(fd);
        return;
    }
    sscanf(buf, "%s %s %s", method, uri, version);
    // check block list
    if (is_blocked(uri)) {

    }


}

int mian(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        fprintf(stderr, "use default port 5050\n");
        listenfd = Open_listenfd("5050");
    } else {
        listenfd = Open_listenfd(argv[1]);
    }

    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
        handle_request(connfd);
    }
}