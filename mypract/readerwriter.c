#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex,wr;
int a=10;
int readcount=0;

void *reader(void* arg){

     long int num = (long int)arg;
     pthread_mutex_lock(&mutex);
     readcount++;
     pthread_mutex_unlock(&mutex);

     if(readcount==1){ 
      pthread_mutex_lock(&wr);
     }
     printf("\n=====Reader %1ld in critical section=====\n",num);
     printf("\nReader %1ld reading the data %d\n",num,a);
     sleep(1);
     
     pthread_mutex_lock(&mutex);
     readcount--;
     pthread_mutex_unlock(&mutex);
     if(readcount==0){
         pthread_mutex_unlock(&wr);
     }
     printf("\n Reader %1ld left from the crititcal section\n",num);

   
}

void *writer(void* arg){
  long int num =(long int)arg;

  pthread_mutex_lock(&wr);
  printf("\n=====Writer in critical section=====\n");
  printf("\nWriter %1ld wrting the data %d\n",num,a++);
  sleep(1);
  pthread_mutex_unlock(&wr);

  printf("Writer %1ld left from the critical section\n",num);



}

int main(){
     int nr,nw;
     long int i,j;
     printf("Enter the no of readers and the no of writer:");
     scanf("%d %d",&nr,&nw);

     pthread_t r[10],wa[10];// array to stare reader writer Id woth the pthread_t is datatype that handles the thread 
     

     //Initialize the mutex locks before using it so that they become 
     //easy to lock and unlock 
       pthread_mutex_init(&mutex,NULL);
       pthread_mutex_init(&wr,NULL);

       //creation of threads 
       for( i=0;i<nr;i++){
         pthread_create(&r[i],NULL,reader,(void *)i);
       }

       for(j=0;j<nw;j++){
         pthread_create(&wa[j],NULL,writer,(void *)j);
       }


       //join makes tje programs to stop for complete excution of the thread because
       //program may end and before execution of thread

       for(i=0;i<nr;i++){
        pthread_join(r[i],NULL);
       }
       for( j=0;j<nw;j++){
         pthread_join(wa[j],NULL);
       }
}