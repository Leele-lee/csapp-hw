/* $begin tfgetsmain */
#include <stdio.h>
#include "csapp.h"

struct tfgets_args {
    char *s;
    int size;
    FILE *stream;
};

static int done;  // 0: not done, 1: read done, 2: timeout
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static char* result;

/*
 * receive input then call fgets
 * change condition variable done
 * call pthread_cond_signal to wake up pthread wake up function
 */
void *read_thread(void *vargp) {
    struct tfgets_args *args = (struct tfgets_args *)vargp;
    char *res = fgets(args->s, args->size, args->stream);

    pthread_mutex_lock(&mutex);    // protect shared varibale done
    if (!done) {
        done = 1; // notice tfgets read is done
        result = res;
        pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&mutex);
}

char *tfgets(char *s, int size, FILE *stream);
/*
 * tfgets should: 
 */
char *tfgets(char *s, int size, FILE *stream) {
    pthread_t tid;
    struct tfgets_args args = {s, size, stream};
    done = 0;
    pthread_create(&tid, NULL, read_thread, &args);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 5;      // timeout after 5 secs

    pthread_mutex_lock(&mutex);
    while (!done) {
        if (pthread_cond_timedwait(&cond, &mutex, &ts) == ETIMEDOUT) {
            done = 2;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    // if read done 
    if (done == 2) {
        pthread_cancel(tid);
        pthread_detach(tid);
        return NULL;
    } else {
        pthread_join(tid, NULL);
        return result;
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
