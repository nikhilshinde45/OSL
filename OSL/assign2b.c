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

int main() {
    int n;
    printf("Enter the number of elements : ");
    scanf("%d", &n);
    int * p = (int *) calloc(n, sizeof(int));
    printf("=== Enter the elements of array ===\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    
    pid_t p2 = fork();
    if(p2 == 0) {
        char * arg[n + 1];
        char str[12];
        int i;

        printf("=== In the child process ===\n");
        printf("PID : %d, PPID : %d\n", getpid(), getppid());
        selectionSort(p, n);
        printf("Sorted array : \n");
        for(i = 0; i < n; i++) {
            printf("%d ", p[i]);
            sprintf(str, "%d", p[i]);
            arg[i] = malloc(strlen(str) + 1);
            strcpy(arg[i], str);
        }
        arg[n] = NULL;

        printf("\nExecuting execvp statement\n");
        execvp("./search_assign2b", arg);

        printf("Back to child\n");
        exit(-1);
    } 
    else{
        printf("=== In the parent process ===\n");
        printf("Parent waits for child\n");
        wait(0);
        printf("Back to parent\n");
        printf("Parent exits\n");
        exit(0);
    }

    return 0;
}
