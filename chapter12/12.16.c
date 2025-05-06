/* 
 * hello.c - Pthreads "hello, world" program 
 */
/* $begin hello */
#include "csapp.h"
void *thread(void *vargp);                    //line:conc:hello:prototype

int main(int argc, char* argv[])                                    //line:conc:hello:main
{
    int n;  
    pthread_t tid;                            //line:conc:hello:tid

    if (argc != 2) {
      fprintf(stderr, "Usage: %s <number of threads>\n", argv[0]);
      exit(1);
    }

    n = atoi(argv[1]);
    for (int i = 0; i < n; i++) {
      Pthread_create(&tid, NULL, thread, NULL); //line:conc:hello:create
      Pthread_join(tid, NULL);                  //line:conc:hello:join  
    }  
    exit(0);                                  //line:conc:hello:exit
}

void *thread(void *vargp) /* thread routine */  //line:conc:hello:beginthread
{
    printf("Hello, world!\n");                 
    return NULL;                               //line:conc:hello:return
}                                              //line:conc:hello:endthread
/* $end hello */
