/// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>

// #define RC 3
// #define WC 3

// int data = 10;
// int read_count = 0;
// pthread_mutex_t wr_mutex;
// pthread_mutex_t rc_mutex;

// void * Reader(void * arg){
//     long rno = (long) arg;

//     pthread_mutex_lock(&rc_mutex);
//     read_count++;
//     if(read_count == 1){
//         pthread_mutex_lock(&wr_mutex);
//     }
//     pthread_mutex_unlock(&rc_mutex);

//     printf("\nReader no %ld entered the critical section", rno);
//     printf("\nRead data = %d", data);
//     sleep(2);

//     pthread_mutex_lock(&rc_mutex);
//     read_count--;
//     if(read_count == 0){
//         pthread_mutex_unlock(&wr_mutex);
//     }
//     pthread_mutex_unlock(&rc_mutex);

//     printf("\nReader %ld has left", rno);
//     return NULL;
// }

// void * Writer(void * arg){
//     long wno = (long) arg;
//     pthread_mutex_lock(&wr_mutex);

//     printf("\nWriter no %ld entered the critical section", wno);
//     data++;
//     printf("\nData modified by writer to %d", data);
//     sleep(1);

//     pthread_mutex_unlock(&wr_mutex);
//     printf("\nWriter %ld has left", wno);
//     return NULL;
// }

// int main(){
//     pthread_t reader[RC], writer[WC];
//     pthread_mutex_init(&wr_mutex, NULL);
//     pthread_mutex_init(&rc_mutex, NULL);

//     for(long i=0; i<RC; i++){
//         pthread_create(&reader[i], NULL, Reader, (void *) i);
//     }
//     for(long i=0; i<WC; i++){
//         pthread_create(&writer[i], NULL, Writer, (void *) i);
//     }

//     for(long i=0; i<RC; i++){
//         pthread_join(reader[i], NULL);
//     }
//     for(long i=0; i<WC; i++){
//         pthread_join(writer[i], NULL);
//     }

//     pthread_mutex_destroy(&rc_mutex);
//     pthread_mutex_destroy(&wr_mutex);
//     printf("\n");

//     return 0;
// }

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t wr,mutex; //declaration of thread_local
int a=10,readcount=0;

void * reader (void *arg)
{
    long int num=(long int)arg;
    pthread_mutex_lock(&mutex);
        readcount++;
    pthread_mutex_unlock(&mutex);
    
    if(readcount==1)
    {
        pthread_mutex_lock(&wr);
    }
    
    printf("\n reader %ld in critical section",num);
    printf("\n reader %ld reading data %d",num,a);
    sleep(1);
         
    pthread_mutex_lock(&mutex);
        readcount--;
    pthread_mutex_unlock(&mutex);
    
    if(readcount==0)
    {
        pthread_mutex_unlock(&wr);
    }
    printf("\nreader %ld left from critical section",num);
    
    
}

void * writer (void *arg)
{
    long int num=(long int)arg;
    
    pthread_mutex_lock(&wr);
    
    printf("\n writer %ld in critical section",num);
    printf("\n writer %ld have written data as %d",num,a++);
    sleep(1);
    
    pthread_mutex_unlock(&wr);
    printf("\nwriter %ld left from critical section",num);
    
}


int main()
{
    int nor,now;
    long int i,j;
    
    pthread_t r[10],w[10];
    
    printf("Enter the no of reader and writer:");
    scanf("%d %d",&nor,&now);
    
    //thread initialation
    pthread_mutex_init(&wr,NULL);
    pthread_mutex_init(&mutex,NULL);
    
    //creating thread for reader
    for(i=0;i<nor;i++)
    {
        pthread_create(&r[i],NULL,reader,(void *)i);
    }
    
     //creating thread for writer
    for(j=0;j<now;j++)
    {
        pthread_create(&w[j],NULL,writer,(void *)j);
    }
    
    //Main program waits for all reader threads and writer threads to finish.

// Without this, the program could end before threads complete.
    for(i=0;i<nor;i++)
    {
        pthread_join(r[i],NULL);
    }
    
    for(j=0;j<now;j++)
    {
        pthread_join(w[j],NULL);
    }
    
    return 0;
    
}