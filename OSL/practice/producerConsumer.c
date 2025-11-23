#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NP 4
#define NC 4
#define ITEMS 10

// shared data
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int IN = 0;
int OUT = 0;
int BUFFER[BUFFER_SIZE];

void * Producer(void * arg){
    // for(int i=0; i<ITEMS; i++){
        int item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // critical section
        BUFFER[IN] = item;
        IN = (IN + 1) % BUFFER_SIZE;
        printf("\nItem produced by %ld producer : %d", (long) arg, item);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(rand() % 2);
    // }
}

void * Consumer(void * arg){
    for(int i=0; i<ITEMS; i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = BUFFER[OUT];
        OUT = (OUT + 1) % BUFFER_SIZE;
        printf("\nItem consumed by %ld consumer : %d", (long) arg, item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(rand() % 3);
    }
}

int main(){
    pthread_t producer[NP], consumer[NC];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for(long i=0; i<NP; i++){
        pthread_create(&producer[i], NULL, Producer, (void *) i);
    }
    for(long i=0; i<NC; i++){
        pthread_create(&consumer[i], NULL, Consumer, (void *) i);
    }

    for(long i=0; i<NP; i++){
        pthread_join(producer[i], NULL);
    }
    for(long i=0; i<NC; i++){
        pthread_join(consumer[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}