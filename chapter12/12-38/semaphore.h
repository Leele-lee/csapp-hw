#ifndef __SEMA_H__
#define __SEMA_H__

#include "../csapp.h"

// Replace csapp.h or add this:
/* $begin mysem_t */
typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} mysem_t;
/* $end mysem_t */

void Sem_m_init(mysem_t *s, int pshared, int value);
void P_m(mysem_t *s);
void V_m(mysem_t *s);

#endif /* __SEMA_H__ */