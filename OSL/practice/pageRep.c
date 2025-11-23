#include <stdio.h>
#define FRAME 3

void displayFrame(int frame[]){
    for(int i=0; i<FRAME; i++){
        if(frame[i] != -1){
            printf("%d ", frame[i]);
        }
    }
    printf("\n");
}

// FIFO Algorithm
void FIFO(int pages[], int n){
    int frame[FRAME] = {-1, -1, -1};
    int pf = 0, ph = 0;
    int k = 0;

    printf("\n=== FIFO ===\n");
    for(int i=0; i<n; i++){
        int flag = 0;
        for(int j=0; j<FRAME; j++){
            if(frame[j] == pages[i]){
                flag = 1;
                break;
            }
        }
        if(flag){
            ph++;
        } else {
            pf++;
            frame[k] = pages[i];
            k = (k+1) % FRAME;
        }
        displayFrame(frame);
    }
    printf("\nTotal Page Faults = %d", pf);
    printf("\nTotal Page Hits = %d\n", ph);
}

// LRU helper
int findLRU(int recent[]){
    int lru = 0;
    for(int i=1; i<FRAME; i++){
        if(recent[i] < recent[lru]){
            lru = i;
        }
    }
    return lru;
}

// LRU Algorithm
void LRU(int pages[], int n){
    int frame[FRAME] = {-1, -1, -1};
    int recent[FRAME] = {-1, -1, -1};
    int pf = 0, ph = 0;

    printf("\n=== LRU ===\n");
    for(int i=0; i<n; i++){
        int ind = -1;
        for(int j=0; j<FRAME; j++){
            if(frame[j] == pages[i]){
                ind = j;
                break;
            }
        }
        if(ind != -1){
            ph++;
            recent[ind] = i;
        } else {
            pf++;
            int k = findLRU(recent);
            frame[k] = pages[i];
            recent[k] = i;
        }
        displayFrame(frame);
    }
    printf("\nTotal Page Faults = %d", pf);
    printf("\nTotal Page Hits = %d\n", ph);
}

// Optimal helper
int findLastUpcoming(int pages[], int n, int frame[], int current){
    int upcoming[FRAME];
    for(int j=0; j<FRAME; j++){
        upcoming[j] = 99999; // initialize once per frame
        for(int i=current+1; i<n; i++){
            if(pages[i] == frame[j]){
                upcoming[j] = i;
                break;
            }
        }
    }
    int max = upcoming[0], ind = 0;
    for(int i=1; i<FRAME; i++){
        if(upcoming[i] > max){
            max = upcoming[i];
            ind = i;
        }
    }
    return ind;
}

// Optimal Algorithm
void Optimal(int pages[], int n){
    int frame[FRAME] = {-1, -1, -1};
    int pf = 0, ph = 0;

    printf("\n=== Optimal ===\n");
    for(int i=0; i<n; i++){
        int ind = -1;
        for(int j=0; j<FRAME; j++){
            if(frame[j] == pages[i]){
                ind = j;
                break;
            }
        }
        if(ind != -1){
            ph++;
        } else {
            pf++;
            int k = -1;
            // if there is an empty frame, use it
            for(int j=0; j<FRAME; j++){
                if(frame[j] == -1){
                    k = j;
                    break;
                }
            }
            if(k == -1)
                k = findLastUpcoming(pages, n, frame, i);
            frame[k] = pages[i];
        }
        displayFrame(frame);
    }
    printf("\nTotal Page Faults = %d", pf);
    printf("\nTotal Page Hits = %d\n", ph);
}

int main(){
    int n;
    printf("Enter number of pages in reference string : ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page sequence : ");
    for(int i=0; i<n; i++){
        scanf("%d", &pages[i]);
    }

    FIFO(pages, n);
    LRU(pages, n);
    Optimal(pages, n);

    return 0;
}
