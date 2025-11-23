#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    printf("Child process replaced by this process\n");
    printf("PID : %d\n", getpid());

    int * q = (int *) calloc(argc, sizeof(int));
    for(int i=0; i<argc; i++){
        q[i] = atoi(argv[i]);
        printf("%d ", q[i]);
    }

    int key, high = argc - 1, low = 0, mid, found = 0;
    printf("\n=== Search a number in this array ===\n");
    printf("Enter number to search : ");
    scanf("%d", &key);

    while(low <= high){
        mid = (low + high) / 2;
        if(q[mid] == key){
            found = 1;
            break;
        }
        else if(q[mid] > key){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    if(found){
        printf("Number found at index %d\n", mid);
    }
    else{
        printf("Number not found\n");
    }
    printf("=== Returning to child process ===\n");

    return 0;
}

// compile as gcc assign2b2.c -o assign2b2