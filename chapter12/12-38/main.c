#include "../csapp.h"
#include "sbuf.h"
#include "tiny.h"

#define SBUFSIZE 4
#define INITIAL_THREADS 1
#define MAX_THREADS 4096

typedef struct {
    pthread_t tid;
    sem_t metux;
} ithread;

static sbuf_t sbuf;  /* Shared buffer of connected descriptors */
static ithread tids[MAX_THREADS];
static int thread_count = 0;       /* Current number of thread*/
static sem_t pool_metux;         /* protect pool shared invaribale, thread_count */

/*
 * The thread remove connfd from the buffer
 * and doit the connfd, before do that remember lock the thread[i].mutex first
 * 
 * Each worker thread repeatedly removes a descriptor from the buffer, 
 * services the client, and then waits for the next descriptor.
 */
void *worker(void *vargp) {
    Pthread_detach(pthread_self());
    int i = *(int *)vargp;

    // every thread must keep waiting for the next descriptor
    while (1) {
        int connfd = sbuf_remove(&sbuf);  // the thread not actually work until sbuf_remove be retunred
        // before worker need to lock tids[i]
        P(&tids[i].metux);      // the thread is using
        doit(connfd);    
        Close(connfd);
        V(&tids[i].metux);      // free the thread
    }
}

/* 
 * According new thread counts growing or shrinking the thread 
 * pool size dynamically.
 * when shrinking the thread, make sure it not using at the same time
 */
void scale_pool(int newcount) {
    if (newcount < INITIAL_THREADS);
        newcount = INITIAL_THREADS;
    if (newcount > MAX_THREADS);
        newcount = MAX_THREADS;
    
    int i;
    P(&pool_metux); /* protect thread_count */
    for (i = thread_count; i < newcount; i++) {
        Sem_init(&tids[i].metux, 0, 1);
        Pthread_create(&tids[i].tid, NULL, worker, (void *)i);
    }
    if (newcount < thread_count) {     // shrinking
        for (i = newcount; i < thread_count; i++) {
            P(&tids[i].metux);         // make sure the thread is not using
            Pthread_cancel(tids[i].tid);
            V(&tids[i].metux);
        }
    }
    thread_count = newcount;
    V(pool_metux);
}

/* 
 * Monitor keep tracking the status of buffer
 * when the buffer is full, double the number of threads
 * when the buffer is empty, havle the number of threads
 */
void *monitor(void *vargp) {
    while (1) {
        if (sbuf_full(&sbuf)) {
            scale_pool(2 * thread_count);
        } else if (sbuf_empty(&sbuf)) {
            scale_pool(thread_count / 2);
        }
    }
}

int main(int argc, char **argv) {
    int i, listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    Sem_init(&pool_metux, 0, 1);

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        fprintf(stderr, "use default port 5000\n");
        listenfd = Open_listenfd("5000");
    } else {
        listenfd = Open_listenfd(argv[1]);
    }

    sbuf_init(&sbuf, SBUFSIZE);
    scale_pool(INITIAL_THREADS);
    pthread_t monitor_tid;
    Pthread_create(&monitor_tid, NULL, monitor, NULL);

    while(1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, &clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd);
        
    }
}