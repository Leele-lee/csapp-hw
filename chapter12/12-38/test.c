/* 
 * badcnt.c - An improperly synchronized counter program 
 */
/* $begin badcnt */
/* WARNING: This code is buggy! */
#include "../csapp.h"
#include "semaphore.h"

void *thread(void *vargp);  /* Thread routine prototype */

/* Global shared variable */
volatile long cnt = 0; /* Counter */
mysem_t mutex;

int main(int argc, char **argv) 
{
    long niters;
    pthread_t tid1, tid2;
    Sem_m_init(&mutex, 0, 1);

    /* Check input argument */
    if (argc != 2) { 
	    printf("usage: %s <niters>\n", argv[0]);
	    exit(0);
    }
    niters = atoi(argv[1]);

    /* Create threads and wait for them to finish */
    Pthread_create(&tid1, NULL, thread, &niters);
    Pthread_create(&tid2, NULL, thread, &niters);
    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    /* Check result */
    if (cnt != (2 * niters))
	    printf("BOOM! cnt=%ld\n", cnt);
    else
	    printf("OK cnt=%ld\n", cnt);
    exit(0);
}

/* Thread routine */
void *thread(void *vargp) 
{
    long i, niters = *((long *)vargp);

    for (i = 0; i < niters; i++) {//line:conc:badcnt:beginloop
        P_m(&mutex);
	    cnt++;                   //line:conc:badcnt:endloop
        V_m(&mutex);
    }
    return NULL;
}
/* $end badcnt */

