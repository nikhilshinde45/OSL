#include <stdio.h>
#include <stdlib.h>

int binary_search(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] == key)
            return mid;
        else if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <sorted_array>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int arr[n];
    for(int i = 0; i < n; i++)
        arr[i] = atoi(argv[i+1]);

    int key;
    printf("Enter the number to search: ");
    scanf("%d", &key);

    int idx = binary_search(arr, n, key);
    if(idx != -1)
        printf("%d found at position %d (0-indexed)\n", key, idx);
    else
        printf("%d not found in the array.\n", key);

    return 0;
}
