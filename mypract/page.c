#include <stdio.h>

void displayFrame(int frame[], int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (frame[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frame[i]);
        }
    }
    printf("\n");
}

void FIFO(int pages[], int n, int frameSize) {
    int frame[frameSize];
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
    }

    int pf = 0, ph = 0;
    int k = 0;

    printf("\n--- FIFO (Frame Size: %d) ---\n", frameSize);
    printf("Page\tFrames\n");
    printf("---------------------\n");
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        printf("%d\t: ", pages[i]);
        if (flag) {
            ph++;
        } else {
            pf++;
            frame[k] = pages[i];
            k = (k + 1) % frameSize;
        }
        displayFrame(frame, frameSize);
    }
    printf("---------------------\n");
    printf("Total Page Faults: %d\n", pf);
    printf("Total Page Hits: %d\n", ph);
}

int findLRU(int recent[], int frameSize) {
    int lru_index = 0;
    for (int i = 1; i < frameSize; i++) {
        if (recent[i] < recent[lru_index]) {
            lru_index = i;
        }
    }
    return lru_index;
}

void LRU(int pages[], int n, int frameSize) {
    int frame[frameSize];
    int recent[frameSize];
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
        recent[i] = -1;
    }

    int pf = 0, ph = 0;

    printf("\n--- LRU (Frame Size: %d) ---\n", frameSize);
    printf("Page\tFrames\n");
    printf("---------------------\n");
    for (int i = 0; i < n; i++) {
        int ind = -1;
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == pages[i]) {
                ind = j;
                break;
            }
        }

        printf("%d\t: ", pages[i]);
        if (ind != -1) {
            ph++;
            recent[ind] = i;
        } else {
            pf++;
            int k = findLRU(recent, frameSize);
            frame[k] = pages[i];
            recent[k] = i;
        }
        displayFrame(frame, frameSize);
    }
    printf("---------------------\n");
    printf("Total Page Faults: %d\n", pf);
    printf("Total Page Hits: %d\n", ph);
}

int findOptimal(int pages[], int n, int frame[], int current, int frameSize) {
    int replace_index = -1;
    int farthest = current;

    for (int j = 0; j < frameSize; j++) {
        if (frame[j] == -1) {
            return j;
        }

        int k;
        for (k = current + 1; k < n; k++) {
            if (frame[j] == pages[k]) {
                if (k > farthest) {
                    farthest = k;
                    replace_index = j;
                }
                break;
            }
        }

        if (k == n) {
            return j;
        }
    }

    return (replace_index == -1) ? 0 : replace_index;
}

void Optimal(int pages[], int n, int frameSize) {
    int frame[frameSize];
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
    }

    int pf = 0, ph = 0;

    printf("\n--- Optimal (Frame Size: %d) ---\n", frameSize);
    printf("Page\tFrames\n");
    printf("---------------------\n");
    for (int i = 0; i < n; i++) {
        int ind = -1;
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == pages[i]) {
                ind = j;
                break;
            }
        }

        printf("%d\t: ", pages[i]);
        if (ind != -1) {
            ph++;
        } else {
            pf++;
            int k = findOptimal(pages, n, frame, i, frameSize);
            frame[k] = pages[i];
        }
        displayFrame(frame, frameSize);
    }
    printf("---------------------\n");
    printf("Total Page Faults: %d\n", pf);
    printf("Total Page Hits: %d\n", ph);
}

int main() {
    int n;
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    if (n <= 0) {
         printf("Number of pages must be > 0.\n");
         return 1;
    }
    int pages[n];

    printf("Enter the page sequence (e.g., 1 2 3 4 ...): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    int frameSize;
    printf("Enter number of page frames: ");
    scanf("%d", &frameSize);

    if (frameSize <= 0) {
        printf("Number of frames must be > 0.\n");
        return 1;
    }
    
    FIFO(pages, n, frameSize);
    LRU(pages, n, frameSize);
    Optimal(pages, n, frameSize);

    return 0;
}