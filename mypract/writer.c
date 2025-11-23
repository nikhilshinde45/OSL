#include<stdio.h>
#include<sys/ipc.h>//for the ftok key creation 
#include<sys/shm.h>//used for the creation of shared memory segment

//writer process
int main(){
    key_t tok=ftok(".",1);//generate unique key 
    int shmid=shmget(tok,1024,0666|IPC_CREAT);//It creates the shared memory segemnt 
    //with 1024 limited space and 0666 for the permission so anyone can read or write it 
    //if memory segmemnt does not exit the creat

    char *str=(char *)shmat(shmid,(void*)0,0);// it return pointer for the shared memory segement 
    //(void *)0 for the let os choose to attach memory space

    printf("\nWrite data :");
    fgets(str,1024,stdin);

    shmdt(str);//detach memory segement from the server 



}
