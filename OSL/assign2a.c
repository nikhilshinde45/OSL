#include <stdio.h>  //for c I/O opertaions
#include <stdlib.h>  //for using calloc
#include <unistd.h>  //to use system calls like fork, exec, exit, sleep
#include <sys/wait.h>  //for using the wait
#include <sys/types.h>  //for using the type pid_t

void insertion_sort(int arr[], int n) {
    int i, j, temp;
    for(i=1; i<n; i++){
        temp = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > temp){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

void display_array(int arr[], int n){
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int choice;
    pid_t p, p1;
    printf("Select option\n1. Sort an Array\n2. Simulate Orphan State\n3. Simulate zombie State\nEnter choice : ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            printf("=== Starting the main process ===\n");
            printf("PID : %d\n", getpid());
            int n;
            printf("Enter the number of elements : ");
            scanf("%d", &n);
            printf("\n");
            int * arr = (int*) calloc(n, sizeof(int));

            printf("Enter array numbers : ");
            for(int i=0; i<n; i++){
                scanf("%d", &arr[i]);
            }
            printf("\n");

            printf("=== Forking ===\n");
            p = fork();
            if(p < 0){
                printf("Fork failed\n");
            }
            else if(p == 0){
                printf("\n=== In child process ===\n");
                printf("PID : %d, PPID : %d\n", getpid(), getppid());
                insertion_sort(arr, n);
                printf("Array sorted by Child process\n");
                display_array(arr, n);
                printf("=== Child process done ===\n");
                _exit(-1);
            }
            else{
                printf("=== In parent process ===\n");
                printf("PID : %d\n", getpid());
                insertion_sort(arr, n);
                printf("Array sorted by Parent process\n");
                display_array(arr, n);
                printf("Parent waits for child to sort array\n");
                printf("\n");
                wait(0);
                printf("Back in parent process\n");
                printf("=== Parent process done ===\n");
                _exit(0);
            }
            break;

        case 2:
            printf("=== Starting the main process ===\n");
            p1 = getpid();
            printf("PID : %d\n", p1);
            printf("=== Forking ===\n");
            p = fork();
            if(p < 0){
                printf("Fork failed\n");
            }
            else if(p == 0){
                wait(0);
                printf("In child process\n");
                printf("PID : %d\n", getpid());
                printf("Original process id of parent : %d\n", p1);
                printf("PPID now : %d\n", getppid());
                printf("PID of parent has changed. Child is in orphan state\n");
                printf("Child process done\n");
                _exit(0);
            }
            else{
                printf("In parent process\n");
                printf("PID : %d\n", getpid());
                printf("Parent process terminates\n");
                _exit(-1);
            }
            break;
        case 3:
            printf("=== Starting the main process ===\n");
            p1 = getpid();
            printf("PID : %d\n", p1);
            printf("=== Forking ===\n");
            p = fork();
            if(p < 0){
                printf("Fork failed\n");
            }
            else if(p == 0){
                printf("In child process\n");
                printf("PID : %d\n", getpid());
                printf("PPID : %d\n", getppid());
                printf("Child process done\n");
                _exit(-1);
            }
            else{
                printf("In parent process\n");
                printf("PID : %d\n", getpid());
                printf("Parent process going to sleep\n");
                sleep(10);
                printf("Parent wakes up\n");
                while(1);
                printf("Parent process done\n");
                _exit(0);
            }
            break;
        default:
            printf("Invalid input\n");
    }
    return 0;
}