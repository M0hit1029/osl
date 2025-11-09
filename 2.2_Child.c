#include <stdio.h>
#include <stdlib.h>

// Binary search function
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int n = argc - 1; // Number of array elements passed
    int arr[n], i;

    if (argc < 2) {
        printf("No array data received!\n");
        return 1;
    }

    // Convert command-line arguments to integers
    for (i = 1; i < argc; i++)
        arr[i - 1] = atoi(argv[i]);

    printf("\n[Child] Received sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int key;
    printf("[Child] Enter element to search: ");
    scanf("%d", &key);

    int pos = binarySearch(arr, n, key);

    if (pos != -1)
        printf("[Child] Element %d found at position %d (0-based index)\n", key, pos);
    else
        printf("[Child] Element %d not found in the array\n", key);

    return 0;
}

