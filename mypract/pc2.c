#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define Chairs 3

sem_t students; //wating stundent
sem_t ta ;  //teacher assistant track 
pthread_mutex_t mutex;
int waiting=0;

void *student(void* arg){
   int id =*(int *)arg;
  pthread_mutex_lock(&mutex);


   if(waiting<Chairs){
      
       waiting++;
       printf("Student waiting %dwaiting students :%d",id,waiting);
       sem_post(&students);
       pthread_mutex_unlock(&mutex);

       sem_wait(&ta);
       printf("Student %d getting help from TA\n",id);
       sleep(2);
       printf("Student %d leaves TA s office\n",id);

   }else{ 
     printf("Student %d does not found chair\n",id);
     pthread_mutex_unlock(&mutex);
   }
  return NULL;
}
void *taa(void* arg){
  while(1){
      sem_wait(&students);
      pthread_mutex_lock(&mutex);
      waiting--;
      printf("TA helping the student.waiting :%d\n",waiting);
      pthread_mutex_unlock(&mutex);
      sem_post(&ta);
      
      sleep(3);
      printf("TA has finished helping a student\n");

  }

}

int main(){
  pthread_t tathread;
  pthread_t studentsa[10];
  int studentids[10];

  sem_init(&students,0,0);
  sem_init(&ta,0,0);
  pthread_mutex_init(&mutex,NULL);

  pthread_create(&tathread,NULL,taa,NULL);
  for(int i=0;i<10;i++){
     studentids[i]=i+1;
     pthread_create(&studentsa[i],NULL,student,&studentids[i]);
     sleep(rand()%3);


  }
  for(int i=0;i<10;i++){
     pthread_join(studentsa[i],NULL);
  }

  pthread_cancel(tathread);
  sem_destroy(&students);
  sem_destroy(&ta);
  pthread_mutex_destroy(&mutex);
 
  return 0;

}