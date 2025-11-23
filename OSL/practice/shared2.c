#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 

// writer process
int main(){
    key_t tok = ftok(".", 1);
    int shmid = shmget(tok, 1024, 0666 | IPC_CREAT);

    char * str = (char *) shmat(shmid, (void *)0, 0);

    printf("\nWrite data : ");
    fgets(str,1024,stdin);

    shmdt(str);

    return 0;
}