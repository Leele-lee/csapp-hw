#include "csapp.h"
#include "sbuf.h"

/* Create an empty, bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n) {
    sp->buf = calloc(n, sizeof(int));
    sp->n = n;
    sp->front = sp->rear = 0;
    Sem_init(&sp->mutex, 0, 1);
    Sem_init(&sp->slots, 0, n);
    Sem_init(&sp->items, 0, 0);
}

/* Clean up buffer sp */
void sbuf_deinit(sbuf_t *sp) {
    Free(sp->buf);
}

/* Insert item onto the rear of shared buffer sp */
void sbuf_insert(sbuf_t *sp, int item) {
    P(&sp->slots);         // wait for avaliable slot, use a slot
    P(&sp->mutex);         // lock the buf
    sp->buf[(++sp->rear) % (sp->n)] = item;
    V(&sp->mutex);         // unlock the buf
    V(&sp->items);         // announce avaliable item, add a item
}

/* Remove and return the first item from buffer sp */
int sbuf_remove(sbuf_t *sp) {
    int item;
    P(&sp->items);
    P(&sp->mutex);
    item = sp->buf[(++sp->front) % (sp->n)];
    P(&sp->mutex);
    V(&sp->slots);
    return item;
}

/* When rear == front ⇒ buffer is empty */
int sbuf_empty(sbuf_t *sp) {
    if (sp->front == sp->rear)
        return 1;
}

/* When rear + 1 % n == front ⇒ buffer is full */
int sbuf_full(sbuf_t *sp) {
    if (((sp->rear+1) % (sp->n)) == sp->front)
        return 1;
}