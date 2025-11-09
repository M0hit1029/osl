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

void cscan(int req[], int n, int head) {
    int total = 0, pos, i;
    int arr[100];
    for (i = 0; i < n; i++) arr[i] = req[i];
    sort(arr, n);
    for (i = 0; i < n; i++) if (arr[i] > head) break;
    printf("\nC-SCAN order: %d ", head);
    for (pos = i; pos < n; pos++) {
        total += abs(arr[pos] - head);
        head = arr[pos];
        printf("-> %d ", head);
    }
    total += (499 - head);
    total += 499;
    head = 0;
    for (pos = 0; pos < i; pos++) {
        total += abs(arr[pos] - head);
        head = arr[pos];
        printf("-> %d ", head);
    }
    printf("\nTotal head movement (C-SCAN): %d", total);
    printf("\nAverage seek distance: %.2f\n", (float)total / n);
}

void clook(int req[], int n, int head) {
    int total = 0, pos, i;
    int arr[100];
    for (i = 0; i < n; i++) arr[i] = req[i];
    sort(arr, n);
    for (i = 0; i < n; i++) if (arr[i] > head) break;
    printf("\nC-LOOK order: %d ", head);
    for (pos = i; pos < n; pos++) {
        total += abs(arr[pos] - head);
        head = arr[pos];
        printf("-> %d ", head);
    }
    if (i != 0) {
        total += abs(head - arr[0]);
        head = arr[0];
        for (pos = 0; pos < i; pos++) {
            total += abs(arr[pos] - head);
            head = arr[pos];
            printf("-> %d ", head);
        }
    }
    printf("\nTotal head movement (C-LOOK): %d", total);
    printf("\nAverage seek distance: %.2f\n", (float)total / n);
}

int main() {
    int req[] = {10, 229, 39, 400, 18, 145, 120, 480, 20, 250};
    int n = 10, head = 85;
    printf("Disk Scheduling Comparison\n");
    printf("Requests: ");
    for (int i = 0; i < n; i++) printf("%d ", req[i]);
    printf("\nInitial Head Position: %d\n", head);
    cscan(req, n, head);
    clook(req, n, head);
    return 0;
}

