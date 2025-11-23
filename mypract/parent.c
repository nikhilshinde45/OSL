#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void sort_array(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    sort_array(arr, n);
    printf("Sorted array: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = fork();

    if(pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if(pid == 0) {
        // Child process → execute binary_search program
        char *args[n + 2]; // program name + n elements + NULL
        args[0] = "./binary_search"; // name of child executable
        for(int i = 0; i < n; i++) {
            char *num_str = (char*)malloc(12 * sizeof(char));
            sprintf(num_str, "%d", arr[i]);
            args[i+1] = num_str;
        }
        args[n+1] = NULL;

        execve(args[0], args, NULL); // execute binary_search
        perror("execve failed"); // if execve fails
        exit(1);
    } else {
        // Parent waits for child
        printf("==========In Parent==========\n");
        wait(NULL);
        printf("Parent process done.\n");
    }

    return 0;
}
