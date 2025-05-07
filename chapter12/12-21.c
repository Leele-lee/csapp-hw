ude <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

int read_count = 0;
int write_wait = 0;

sem_t mutex;      // Protects read_count and write_wait
sem_t rw_mutex;   // Resource access
sem_t queue;      // Fair access (blocks readers if writer is waiting)

void* reader(void* arg) {
  int id = *(int*)arg;
  free(arg);

  // Entry Section
  sem_wait(&queue);            // Wait to enter the queue (writer priority)
  sem_wait(&mutex);
  if (read_count == 0)
    sem_wait(&rw_mutex);     // First reader locks the resource
  read_count++;
  sem_post(&mutex);
  sem_post(&queue);            // Allow others to line up

  // Critical Section
  printf("Reader %d is reading\n", id);
  sleep(1); // Simulate reading

  // Exit Section
  sem_wait(&mutex);
  read_count--;
  if (read_count == 0)
    sem_post(&rw_mutex);     // Last reader releases the resource
  sem_post(&mutex);

  printf("Reader %d is done reading\n", id);
  return NULL;
}

void* writer(void* arg) {
  int id = *(int*)arg;
  free(arg);

  // Entry Section
  sem_wait(&mutex);
  write_wait++;               // Writer announces intention to write
  sem_post(&mutex);

  sem_wait(&queue);           // Wait in line (blocks future readers)
  sem_wait(&rw_mutex);        // Exclusive access to resource

  // Critical Section
  printf("Writer %d is writing\n", id);
  sleep(2); // Simulate writing

  // Exit Section
  sem_post(&rw_mutex);        // Release resource
  sem_post(&queue);           // Allow next in line

  sem_wait(&mutex);
  write_wait--;               // Writer done
  sem_post(&mutex);

  printf("Writer %d is done writing\n", id);
  return NULL;
}

int main(int argc, char* argv[]) {
  pthread_t r_threads[NUM_READERS], w_threads[NUM_WRITERS];

  // Initialize semaphores
  sem_init(&mutex, 0, 1);
  sem_init(&rw_mutex, 0, 1);
  sem_init(&queue, 0, 1);

  // Create writer threads
  for (int i = 0; i < NUM_WRITERS; i++) {
    int* id = malloc(sizeof(int));
    *id = i + 1;
    pthread_create(&w_threads[i], NULL, writer, id);
  }

  // Create reader threads
  for (int i = 0; i < NUM_READERS; i++) {
    int* id = malloc(sizeof(int));
    *id = i + 1;
    pthread_create(&r_threads[i], NULL, reader, id);
  }

  // Join threads
  for (int i = 0; i < NUM_WRITERS; i++) {
    pthread_join(w_threads[i], NULL);
  }

  for (int i = 0; i < NUM_READERS; i++) {
    pthread_join(r_threads[i], NULL);
  }

  // Destroy semaphores
  sem_destroy(&mutex);
  sem_destroy(&rw_mutex);
  sem_destroy(&queue);

  return 0;
}
~
