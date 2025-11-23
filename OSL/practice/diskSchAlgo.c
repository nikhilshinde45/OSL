#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void sort(int requests[], int reqCount){
    for(int i=0; i<reqCount; i++){
        for(int j=i+1; j<reqCount; j++){
            if(requests[i] > requests[j]){
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
}

void SSTF(int tracks, int reqCount, int requests[], int head){
    printf("\n=== Shortest Seek Time First ===");
    int finish[100] = {0};
    int distance = 0;
    int completed = 0;
    printf("\nHead");
    printf("\n=> %d", head);
    while(completed < reqCount){
        int seekTime = 1000000;
        int ind = -1;
        for(int i=0; i<reqCount; i++){
            if(abs(requests[i] - head) < seekTime && finish[i] == 0){
                seekTime = abs(requests[i] - head);
                ind = i;
            }
        }
        if(ind != -1){
            head = requests[ind];
            printf("\n=> %d", head);
            distance += seekTime;
            finish[ind] = 1;
            completed++;
        }
    }
    printf("\nTotal distance traversed : %d\n", distance);
}

void SCAN(int tracks, int reqCount, int requests[], int head){
    printf("\n=== Elevator / SCAN ===");
    int finish[100] = {0};
    int distance = 0;
    int completed = 0;
    printf("\nHead");
    printf("\n=> %d", head);

    int ind; // ind will hold the index of request pointed by head or just to the right of head
    for(int i=0; i<reqCount; i++){
        if(requests[i] >= head){
            ind = i;
            break;
        }
    }

    int closestEnd = (abs(head - 0) > abs(tracks - head)) ? tracks : 0;
    if(closestEnd == 0){
        ind--;
        distance += head;
        while(completed < reqCount && ind >= 0){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind--;
        }
        while(completed < reqCount && ind < reqCount){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind++;
        }
        distance += head;
    }
    else{
        distance += tracks - head;
        while(completed < reqCount && ind < reqCount){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind++;
        }
        while(completed < reqCount && ind >= 0){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind--;
        }
        distance += tracks - head;
    }
    printf("\nTotal distance traversed : %d\n", distance);
}

void CSCAN(int tracks, int reqCount, int requests[], int head){
    printf("\n=== C-SCAN ===");
    int finish[100] = {0};
    int distance = 0;
    int completed = 0;
    printf("\nHead");
    printf("\n=> %d", head);

    int ind; // ind will hold the index of request pointed by head or just to the right of head
    for(int i=0; i<reqCount; i++){
        if(requests[i] >= head){
            ind = i;
            break;
        }
    }

    int closestEnd = (abs(head - 0) > abs(tracks - head)) ? tracks : 0;
    if(closestEnd == 0){
        ind--;
        distance += head;
        while(completed < reqCount && ind > 0){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind--;
        }
        printf("\n=> 0");
        ind = reqCount - 1;
        head = tracks;
        printf("\n=> %d (Head Jumped)", head);
        while(completed < reqCount && ind > 0){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind--;
        }
        distance += tracks - head;
    }
    else{
        distance += tracks - head;
        while(completed < reqCount && ind < reqCount){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind++;
        }
        head = 0;
        printf("\n=> %d (Head Jumped)", head);
        ind = 0;
        while(completed < reqCount && ind < reqCount){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind++;
        }
        distance += head;
    }
    printf("\nTotal distance traversed : %d\n", distance);
}

void CLOOK(int tracks, int reqCount, int requests[], int head){
    printf("\n=== C-LOOK ===");
    int finish[100] = {0};
    int distance = 0;
    int completed = 0;
    printf("\nHead");
    printf("\n=> %d", head);

    int ind; // ind will hold the index of request pointed by head or just to the right of head
    for(int i=0; i<reqCount; i++){
        if(requests[i] >= head){
            ind = i;
            break;
        }
    }

    int closestEnd = (abs(head - 0) > abs(tracks - head)) ? tracks : 0;
    if(closestEnd == 0){
        ind--;
        distance += head - requests[0];
        while(completed < reqCount && ind >= 0){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind--;
        }
        ind = reqCount - 1;
        head = requests[ind];
        printf("\n=> %d (Head Jumped)", head);
        while(completed < reqCount && ind >= 0){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind--;
        }
        distance += requests[reqCount - 1] - head;
    }
    else{
        distance += requests[reqCount - 1] - head;
        while(completed < reqCount && ind < reqCount){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind++;
        }
        head = requests[0];
        printf("\n=> %d (Head Jumped)", head);
        ind = 0;
        while(completed < reqCount && ind < reqCount){
            if(finish[ind] == 0){
                head = requests[ind];
                printf("\n=> %d", head);
                finish[ind] = 1;
                completed++;
            }
            ind++;
        }
        distance += head - requests[0];
    }
    printf("\nTotal distance traversed : %d\n", distance);
}

int main(){
    int tracks, reqCount, requests[100], head;
    printf("Enter total number of tracks : ");
    scanf("%d", &tracks);
    printf("Enter number of requests : ");
    scanf("%d", &reqCount);
    printf("Enter requests in order they are arrived : ");
    for(int i=0; i<reqCount; i++){
        scanf("%d", &requests[i]);
    }
    printf("Enter initial head position : ");
    scanf("%d", &head);

    int choice;
    while(1){
        printf("\nEnter choice\n1. SSTF\n2. SCAN\n3. S-SCAN\n4. C-LOOK\n5. Exit\n:: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                SSTF(tracks, reqCount, requests, head);
                break;
            case 2:
                sort(requests, reqCount);
                SCAN(tracks, reqCount, requests, head);
                break;
            case 3:
                sort(requests, reqCount);
                CSCAN(tracks, reqCount, requests, head);
                break;
            case 4:
                sort(requests, reqCount);
                CLOOK(tracks, reqCount, requests, head);
                break;
            case 5:
                _exit(0);
                break;
            default:
                printf("\nAhh na na, Go again...");
        }
    }

    return 0;
}