#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void selectionSort(int * p, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i] > p[j]) {
                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main(){
    int n;
    printf("Enter the number of elements : ");
    scanf("%d", &n);
    int * p = (int *) calloc(n, sizeof(int));
    printf("Enter the elements of array : ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    pid_t p1 = fork();
    if(p1 < 0){
        printf("Error creating process\n");
    }
    else if(p1 == 0){
        printf("\n");
        printf("=== In the child process ===\n");
        printf("PID : %d, PPID : %d\n", getpid(), getppid());
        selectionSort(p, n);
        printf("Sorted array : ");

        char * arg[n+1];
        char str[20];
        for(int i=0; i<n; i++){
            printf("%d ", p[i]);
            sprintf(str, "%d", p[i]);
            arg[i] = (char *) malloc(strlen(str) + 1);
            strcpy(arg[i], str);
        }
        arg[n] = NULL;

        printf("\nExecuting the exec system call\n");
        execvp("./assign2b2", arg);

        printf("Back to child\n");
        printf("=== Child process done ===\n");
        exit(-1);
    }
    else{
        printf("=== In the parent process ===\n");
        printf("PID = %d\n", getpid());
        printf("Parent waits for child\n");
        printf("\n");
        wait(0);
        printf("Back to parent\n");
        printf("Parent exits\n");
        exit(0);
    }

    return 0;
}