#include "../csapp.h"
#include "sbuf.h"
#include "tiny.h"
#include "semaphore.h"

void Sem_m_init(mysem_t *s, int pshared, int value) {
    s->value = value;
    pthread_mutex_init(&s->mutex, NULL);
    pthread_cond_init(&s->cond, NULL);
}

void P_m(mysem_t *s) {
    pthread_mutex_lock(&s->mutex);
    while (s->value <= 0)
        pthread_cond_wait(&s->cond, &s->mutex);
    s->value--;
    pthread_mutex_unlock(&s->mutex);
}

void V_m(mysem_t *s) {
    pthread_mutex_lock(&s->mutex);
    s->value++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->mutex);
}
