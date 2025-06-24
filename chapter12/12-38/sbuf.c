#include "../csapp.h"
#include "sbuf.h"
#include "tiny.h"
#include "semaphore.h"

/* Create an empty, bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n) {
    sp->buf = Calloc(n, sizeof(int));
    sp->n = n;
    sp->front = sp->rear = 0;
    Sem_m_init(&sp->mutex, 0, 1);
    Sem_m_init(&sp->slots, 0, n);
    Sem_m_init(&sp->items, 0, 0);
}

/* Clean up buffer sp */
void sbuf_deinit(sbuf_t *sp) {
    Free(sp->buf);
}

/* Insert item onto the rear of shared buffer sp */
void sbuf_insert(sbuf_t *sp, int item) {
    P_m(&sp->slots);         // wait for avaliable slot, use a slot
    //printf("Inserting into buffer: %d\n", item); fflush(stdout);
    P_m(&sp->mutex);         // lock the buf
    //printf("Inserting into buffer: %d\n", item); fflush(stdout);
    sp->buf[(++sp->rear) % (sp->n)] = item;
    V_m(&sp->mutex);         // unlock the buf
    V_m(&sp->items);         // announce avaliable item, add a item
}

/* Remove and return the first item from buffer sp */
int sbuf_remove(sbuf_t *sp) {
    int item;
    P_m(&sp->items);
    P_m(&sp->mutex);
    item = sp->buf[(++sp->front) % (sp->n)];
    //printf("Remove from buffer: %d\n", item); fflush(stdout);
    V_m(&sp->mutex);
    V_m(&sp->slots);
    return item;
}

/* When rear == front ⇒ buffer is empty */
int sbuf_empty(sbuf_t *sp) {
    int f;
    P_m(&sp->mutex);
    f = (sp->front == sp->rear);
    V_m(&sp->mutex);
    return f;
}

/* When rear + 1 % n == front ⇒ buffer is full */
int sbuf_full(sbuf_t *sp) {
    int f;
    P_m(&sp->mutex);
    f = (sp->rear - sp->front) == sp->n;
    V_m(&sp->mutex);
    return f; 
}