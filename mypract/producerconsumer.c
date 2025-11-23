#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>

#define BUFFER_SIZE 5
int in=0;
int out=0;
int buffer[BUFFER_SIZE];

sem_t empty; //counting empty slots
sem_t full ;//counting full slots
pthread_mutex_t mutex; //mutex binary lock 

void *producer(void *args){

  int item;
  for(int i=1;i<=10;i++){
      item=i;
      sem_wait(&empty);//automatically deccremnts the value of empty
      pthread_mutex_lock(&mutex);//enters in crititcal section 
      buffer[in]=item;
      printf("Producer produced :%d\n",item);
      in=(in+1)%BUFFER_SIZE;
      pthread_mutex_unlock(&mutex);//leaves critical section as the produces produced item alloe further producers and consumers

      sem_post(&full);//incremetns the full value as producer produced value
       sleep(1);//for realistic delay
  }
  return NULL;

}

void *consumer(void *args){
  int item;
  for(int i=1;i<=10;i++){
      sem_wait(&full);
      //enters crittical section 
      pthread_mutex_lock(&mutex);
      item=buffer[out];
      printf("\nConsumer consumed :%d\n",item);
      out=(out+1)%BUFFER_SIZE;
      //leaves critical section
      pthread_mutex_unlock(&mutex);
      sem_post(&empty);//INcrease the value fo empty ad consumer consumed an item 

   sleep(2);
  }
  return NULL;

}

int main(){
     pthread_t prod,cons;

     //Initialization os semaphore and mutex
     sem_init(&empty,0,BUFFER_SIZE);
     sem_init(&full,0,0);
     pthread_mutex_init(&mutex,NULL);

     //creation of thread 
     pthread_create(&prod,NULL,producer,NULL);
     pthread_create(&cons,NULL,consumer,NULL);


     //wait for the thread completion 
     pthread_join(prod,NULL);
     pthread_join(cons,NULL);

     //Cleanup destroy semaphore and mutex
     sem_destroy(&empty);
     sem_destroy(&full);
     pthread_mutex_destroy(&mutex);

    printf("\nAll items are produced and consumed successfully\n");

    return 0;



}