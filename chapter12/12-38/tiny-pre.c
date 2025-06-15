#include "csapp.h"
#include "sbuf.h"

#define SBUFSIZE 4
#define INITIAL_THREADS 1
#define MAX_THREADS 4096

sbuf_t sbuf;  /* Shared buffer of connected descriptors */

int main(int argc, char **argv) {
    int i, listenfd, connfd;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        fprintf(stderr, "use default port 5000\n");
        listenfd = Open_listenfd("5000");
    } else {
        listenfd = Open_listenfd(argv[1]);
    }

    subf_init(&sbuf, SBUFSIZE);

    while(1) {
        
    }
}