#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

//reader process
int main(){
    key_t tok =ftok(".",1);
    int shmid = shmget(tok,1024,0666|IPC_CREAT);

    char *str=(char *)shmat(shmid,(void *)0,0);

    printf("\nReads data: %s",str);
    shmdt(str);
    shmctl(shmid,IPC_RMID,NULL);

}