#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t empty;  // indicates file is empty → producer can write
sem_t full;   // indicates file has data → consumer can read
pthread_mutex_t mutex;  // protects file access

// Producer thread function
void *producer(void *arg) {
    FILE *fp;
    int num;

    for (int i = 0; i < 10; i++) {
        sem_wait(&empty);              // wait until file is empty
        pthread_mutex_lock(&mutex);    // lock file access

        num = rand() % 10;             // generate random number
        fp = fopen("shared.txt", "w"); // open file for writing
        if (fp == NULL) {
            perror("Error opening file");
            exit(1);
        }
        fprintf(fp, "%d", num);
        fclose(fp);

        printf("Producer produced: %d\n", num);

        pthread_mutex_unlock(&mutex);  // unlock file
        sem_post(&full);               // signal consumer that data is ready

        // Sleep random 0–100 ms (0–0.1 seconds)
        usleep((rand() % 101) * 1000);
    }
    return NULL;
}

// Consumer thread function
void *consumer(void *arg) {
    FILE *fp;
    int num;

    for (int i = 0; i < 10; i++) {
        sem_wait(&full);               // wait until file has data
        pthread_mutex_lock(&mutex);    // lock file access

        fp = fopen("shared.txt", "r"); // open file for reading
        if (fp == NULL) {
            perror("Error opening file");
            exit(1);
        }
        fscanf(fp, "%d", &num);
        fclose(fp);

        printf("Consumer consumed: %d\n", num);

        pthread_mutex_unlock(&mutex);  // unlock file
        sem_post(&empty);              // signal producer that file is empty
    }
    return NULL;
}

int main() {
    srand(time(NULL));  // seed random numbers Start the random number generator with the current time so that each run gives new random numbers.

    pthread_t prodThread, consThread;

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 1);  // file starts empty
    sem_init(&full, 0, 0);   // no data yet

    // Create producer and consumer threads
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("\nAll numbers produced and consumed successfully.\n");
    return 0;
}
