#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N_READERS 5 // Max number of readers
#define NUM_READERS 10
#define NUM_WRITERS 5

sem_t queue;       // Controls access order (fairness)
sem_t resource;    // Controls access to the shared resource
pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;

void *reader(void *arg) {
    int id = *(int *)arg;
    free(arg);

    sem_wait(&queue);             // Wait turn
        pthread_mutex_lock(&read_mutex);
            if (read_count == 0)
                sem_wait(&resource); // First reader locks resource
            read_count++;
        pthread_mutex_unlock(&read_mutex);
    sem_post(&queue);             // Allow next thread

    // Reading section
    printf("Reader %d is reading\n", id);
    sleep(1); // Simulate reading

    pthread_mutex_lock(&read_mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&resource); // Last reader releases resource
    pthread_mutex_unlock(&read_mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    free(arg);

    sem_wait(&queue);        // Wait turn
        sem_wait(&resource); // Lock resource
    sem_post(&queue);        // Allow next thread

    // Writing section
    printf("Writer %d is writing\n", id);
    sleep(1); // Simulate writing

    sem_post(&resource);     // Release resource

    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t r_threads[NUM_READERS], w_threads[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&queue, 0, 1);
    sem_init(&resource, 0, 1);

    // Create reader and writer threads
    for (int i = 0; i < NUM_READERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&r_threads[i], NULL, reader, id);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&w_threads[i], NULL, writer, id);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(r_threads[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(w_threads[i], NULL);
    }

    // Clean up
    sem_destroy(&queue);
    sem_destroy(&resource);
    pthread_mutex_destroy(&read_mutex);

    return 0;
}