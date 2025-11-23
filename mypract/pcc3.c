#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<time.h>

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg){
  int num;
  FILE *fp;
  for(int i=0;i<10;i++ ){
       sem_wait(&empty);
       pthread_mutex_lock(&mutex);//decrease the empty=0 signal that block by producer and writing the data
      num=rand()%10;
      fp=fopen("pc.txt","w");
      if(fp==NULL){
         perror("Error in opening file..\n");
         exit(1);
      }
      fprintf(fp,"%d",num);//writing to hte file
      fclose(fp);
      printf("\nProducer produced :%d\n",num);
      pthread_mutex_unlock(&mutex);
      sem_post(&full);
      usleep((rand()%101)*1000);//sleep for the 0-100 ms
     
  }
  return NULL;

}
void* consumer(void* arg){
  int num;
  FILE* fp;
  for(int i=0;i<10;i++){
     sem_wait(&full);
     pthread_mutex_lock(&mutex);
     fp=fopen("pc.txt","r");
     if(fp==NULL){
       perror("Error in opening file...\n");
       exit(1);
     }
     fscanf(fp,"%d",&num);
     printf("\nConsumer consumed :%d\n",num);
     pthread_mutex_unlock(&mutex);
     sem_post(&empty);

  }
  return NULL;

}

int main(){
    srand(time(NULL));
    pthread_t prod,cons;
    sem_init(&empty,0,1);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("\nAll numbers are produced and consumed succesfully\n");
    return 0;
}