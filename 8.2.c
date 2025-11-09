#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
}

void scan(int req[], int n, int head) {
    int total = 0, i, pos;
    int arr[100];
    for (i = 0; i < n; i++) arr[i] = req[i];
    sort(arr, n);
    for (i = 0; i < n; i++) if (arr[i] > head) break;
    printf("\nSCAN order: %d ", head);
    for (pos = i; pos < n; pos++) {
        total += abs(arr[pos] - head);
        head = arr[pos];
        printf("-> %d ", head);
    }
    if (head != 499) {
        total += abs(499 - head);
        head = 499;
        printf("-> %d ", head);
    }
    for (pos = i - 1; pos >= 0; pos--) {
        total += abs(arr[pos] - head);
        head = arr[pos];
        printf("-> %d ", head);
    }
    printf("\nTotal head movement (SCAN): %d", total);
    printf("\nAverage seek distance: %.2f\n", (float)total / n);
}

void look(int req[], int n, int head) {
    int total = 0, i, pos;
    int arr[100];
    for (i = 0; i < n; i++) arr[i] = req[i];
    sort(arr, n);
    for (i = 0; i < n; i++) if (arr[i] > head) break;
    printf("\nLOOK order: %d ", head);
    for (pos = i; pos < n; pos++) {
        total += abs(arr[pos] - head);
        head = arr[pos];
        printf("-> %d ", head);
    }
    for (pos = i - 1; pos >= 0; pos--) {
        total += abs(arr[pos] - head);
        head = arr[pos];
        printf("-> %d ", head);
    }
    printf("\nTotal head movement (LOOK): %d", total);
    printf("\nAverage seek distance: %.2f\n", (float)total / n);
}

int main() {
    int req[] = {20, 229, 39, 450, 18, 145, 120, 380, 20, 250};
    int n = 10, head = 185;
    printf("Disk Scheduling Comparison\n");
    printf("Requests: ");
    for (int i = 0; i < n; i++) printf("%d ", req[i]);
    printf("\nInitial Head Position: %d\n", head);
    scan(req, n, head);
    look(req, n, head);
    return 0;
}

