#include <stdio.h>  //for c I/O opertaions
#include <stdlib.h>  //for using calloc
#include <unistd.h>  //to use system calls like fork, exec, exit, sleep
#include <sys/wait.h>  //for using the wait
#include <sys/types.h>  //for using the type pid_t

// ascending sort
void insertionSort(int * arr, int n) {
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

// descending sort
void SelectionSort(int * arr, int n){
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i] < arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void display_array(int * arr, int n){
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int choice;
    printf("Select option\n1. Simulate Child process (Array sorting)\n2. Simulate Orphan State\n3. Simulate zombie State\n");
    scanf("%d", &choice);
    pid_t p;

    switch(choice){
        case 1:
            printf("=== Starting the main process ===\n");
            printf("PID = %d\n", getpid());
            int n;
            printf("Enter the number of elements in the array: ");
            scanf("%d",&n);
            int * arr = (int *) calloc(n, sizeof(int));
            printf("Enter array elements : ");
            for(int i=0; i<n; i++){
                scanf("%d", &arr[i]);
            }
            p = fork();
            if(p < 0){
                printf("Error creating child process\n");
            }
            else if(p == 0){
                printf("=== In Child process ===\n");
                printf("Child PID = %d\n", getpid());
                printf("Parent PID = %d\n", getppid());
                printf("Child process Sorting array using Selection Sort...\n");
                SelectionSort(arr, n);
                display_array(arr, n);
                printf("=== Child process done ===\n");
                _exit(-1);
            }
            else{
                printf("=== In Parent process ===\n");
                printf("PID = %d\n", getpid());
                printf("Parent  waits for child to sort array\n");
                printf("\n");
                wait(0);
                printf("Parent process sorting the array\n");
                insertionSort(arr, n);
                display_array(arr, n);
                printf("=== Parent process done ===\n");
                _exit(0);
            }
            break;

        case 2:
            printf("=== Starting the main process ===\n");
            printf("PID = %d\n", getpid());
            p = fork();
            if(p < 0){
                printf("Error creating child process\n");
            }
            else if(p == 0){
                // printf("=== In Child process ===\n");
                // printf("Child PID = %d\n", getpid());
                // printf("Parent PID = %d\n", getppid());
                // printf("Child waits for parent to complete\n");
                // printf("\n");
                wait(0);
                printf("Back to child process\n");
                printf("Child PID = %d\n", getpid());
                printf("Parent PID = %d\n", getppid());
                printf("PID of parent has changed. Child is in orphan state\n");
                printf("=== Child process done ===\n");
                _exit(-1);
            }
            else{
                printf("=== In Parent process ===\n");
                printf("PID = %d\n", getpid());
                printf("=== Parent process done ===\n");
                _exit(0);
            }
            break;

        case 3:
            printf("=== Starting the main process ===\n");
            printf("PID = %d\n", getpid());
            p = fork();
            if(p < 0){
                printf("Error creating child process\n");
            }
            else if(p == 0){
                printf("=== In Child process ===\n");
                printf("Child PID = %d\n", getpid());
                printf("Parent PID = %d\n", getppid());
                sleep(2);
                printf("Child process completes while parent is in sleep\n");
                printf("=== Child process done ===\n");
                _exit(-1);
            }
            else{
                printf("=== In Parent process ===\n");
                printf("PID = %d\n", getpid());
                printf("Parent going to sleep\n");
                sleep(5);
                printf("Parent wakes up\n");
                printf("Parent (Current) PID = %d", getpid());
                printf("Child PID = %d", p);
                while(1);
                printf("=== Parent process done ===\n");
                _exit(0);
            }
            break;

        default:
            printf("\nHug diye! Ab Firse karo");
    }
    return 0;
}