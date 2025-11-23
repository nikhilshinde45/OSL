#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // size of buffer

int buffer[BUFFER_SIZE];  // shared buffer
int in = 0, out = 0;      // buffer indexes

sem_t empty;                // counts empty slots
sem_t full;                 // counts filled slots
pthread_mutex_t mutex;      // mutex for critical section

void *producer(void *arg) {
    int item;
    for (int i = 1; i <= 10; i++) {
        item = i;  // produce an item (just a number)

        sem_wait(&empty); // wait if buffer is full . sem_wait atomically decrements empty.
        pthread_mutex_lock(&mutex);   // enter critical section

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // leave critical section
        sem_post(&full);              // signal that buffer has a new item

        sleep(1); // simulate production time
    }
    return NULL;
}

void *consumer(void *arg){
    int item;
    for (int i = 1; i <= 10; i++){
        sem_wait(&full);                // wait if buffer is empty  sem_wait(&full) decrements full or blocks if full == 0
        pthread_mutex_lock(&mutex);   // enter critical section

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // leave critical section
        sem_post(&empty);             // signal that buffer has space

        sleep(2); // simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);  // initially all slots empty
    sem_init(&full, 0, 0);             // initially no full slots
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("\nAll items produced and consumed successfully.\n");
    return 0;
}