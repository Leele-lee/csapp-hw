#include <stdio.h>
#include "csapp.h"
#include "12-34.h"

int A[N][M];
int B[M][P];
int C[N][P];
int CT[N][P];

void initalize_matrix() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = rand() % 10;
        }
    }
}

// sequential matrix multiplication
void sequen_multil() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            for (int k = 0; k < M; k++) {
                C[i][j] = A[i][k] * B[k][j];
            }
        }
    }
}

void * thread_mutil(void *arg) {
    int row = *(int *)arg;
    for (int j = 0; j < P; j++) {
        for (int k = 0; k < M; k++) {
            CT[row][k] += A[row][k] * B[k][j];
        }
    }
    free(arg);
    return NULL;
}

// concurrent matrx multiplication
// take one thread per row
void concurrent_mutil() {
    pthread_t tid[N];

    for (int i = 0; i < N; i++) {
        int *arg = Malloc(sizeof(* arg));
        *arg = i;
         // the last argument cannot direct use &args as the web, because it could cause race condition P992
        pthread_create(&tid[i], NULL, thread_mutil, arg); 

    }
    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }
}

// test the result 
int test_result() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            if (C[i][j] != CT[i][j]);
                return 0;
        }
    }
    return 1;
}

int main() {
    struct timeval start, end;
    double time_seq, time_multi, speed_up;

    initalize_matrix();

    // test sequential timing
    gettimeofday(&start, NULL);
    sequen_multil();
    gettimeofday(&end, NULL);
    time_seq = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_usec - start.tv_usec) / 1e3;

    // test concurrent thread timing
    gettimeofday(&start, NULL);
    concurrent_mutil();
    gettimeofday(&end, NULL);
    time_multi = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_usec - start.tv_usec) / 1e3;

    // test
    if (!test_result()) {
        printf("Your concurrent mutiply is right\n");
    } else {
        printf("Uh, there is something wrong in your code\n");
    }

    speed_up = time_seq/time_multi;
    printf("speedup: %.2fx\n", speed_up);
    return 0;
}