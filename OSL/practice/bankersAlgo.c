// Banker's Algorithm  
#include<stdio.h>

void readMatrix(int mat[20][20], int np, int nr){
    for(int i=0; i<np; i++){
        for(int j=0; j<nr; j++){
            scanf("%d", &mat[i][j]);
        }
    }
}

void displayMatrix(int mat[20][20], int np, int nr){
    for(int i=0; i<np; i++){
        for(int j=0; j<nr; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int np, nr;
    printf("Enter number of resources : ");
    scanf("%d", &nr);
    printf("Enter number of processes : ");
    scanf("%d", &np);

    // each row for one process and each column for one resource in matrix
    int max[20][20], allocation[20][20], need[20][20], available[20];

    printf("Enter the max matrix ::\n");
    readMatrix(max, np, nr);
    printf("Enter the allocation matrix ::\n");
    readMatrix(allocation, np, nr);

    printf("Enter the available resources : ");
    for(int i=0; i<nr; i++){
        scanf("%d", &available[i]);
    }

    // calculate the need matrix
    for(int i=0; i<np; i++){
        for(int j=0; j<nr; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    printf("\nNeed matrix :: \n");
    displayMatrix(need, np, nr);

    // array to track the finished processes and safe state sequence
    int finish[20] = {0};
    int safeState[20];
    int k = 0;

    int completed = 0;
    while(completed < np){
        int progress = 0;
        for(int i=0; i<np; i++){
            if(finish[i] == 0){
                int flag = 1;
                for(int j=0; j<nr; j++){
                    if(need[i][j] > available[j]){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    safeState[k] = i;
                    k++;
                    finish[i] = 1;
                    completed++;
                    progress = 1;
                    for(int j=0; j<nr; j++){
                        available[j] += allocation[i][j];
                    }
                }
            }
        }
        if(progress == 0){
            printf("\nNo safe sequence exists\n");
            return 0;
        }
    }

    if(completed == np){
        printf("System is in safe state.\n");
        printf("Sequence of processes : ");
        for(int i=0; i<np; i++){
            printf("%d ", safeState[i]);
        }
        printf("\n");
    }

    return 0;
}