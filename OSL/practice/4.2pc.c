#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


#define NUM_CHAIRS 3

sem_t students;   // counts waiting students (TA sleeps if 0)
sem_t ta;         // ensures TA is ready for a student
pthread_mutex_t mutex; // to protect shared state
int waiting = 0;  // number of students waiting


void *student(void *num) {
    int id = *(int *)num;

    pthread_mutex_lock(&mutex);
    if (waiting < NUM_CHAIRS) {
        waiting++;
        printf("Student %d waiting. Waiting students = %d\n", id, waiting);
        sem_post(&students); // notify TA that a student is waiting
        pthread_mutex_unlock(&mutex);

        sem_wait(&ta); // wait for TA to help
        printf("Student %d getting help from TA.\n", id);
        sleep(2); // getting help
        printf("Student %d leaves TA’s office.\n", id);
    } else {
        printf("Student %d found no chair, will come later.\n", id);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}



void *teachingAssistant(void *arg) {
    while (1) {
        sem_wait(&students); // sleep until a student arrives

        pthread_mutex_lock(&mutex);
        waiting--;
        printf("TA starts helping a student. Waiting = %d\n", waiting);
        pthread_mutex_unlock(&mutex);

        sem_post(&ta); // signal that TA is ready for a student
        sleep(3); // simulate helping time
        printf("TA finished helping a student.\n");
    }
}


int main() {
    pthread_t taThread;
    pthread_t studentThreads[10];
    int studentIds[10];

    sem_init(&students, 0, 0);
    sem_init(&ta, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&taThread, NULL, teachingAssistant, NULL);

    for (int i = 0; i < 10; i++) {
        studentIds[i] = i + 1;
        pthread_create(&studentThreads[i], NULL, student, &studentIds[i]);
        sleep(rand() % 3); // students arrive at random intervals
    }

    for (int i = 0; i < 10; i++)
        pthread_join(studentThreads[i], NULL);

    pthread_cancel(taThread);
    sem_destroy(&students);
    sem_destroy(&ta);
    pthread_mutex_destroy(&mutex);
    return 0;
}