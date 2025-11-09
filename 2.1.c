#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function for bubble sort
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function for insertion sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n, i, choice;
    pid_t pid;
    int arr[50], arr_copy[50];

    printf("Enter the number of integers: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i]; // copy for child
    }

    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1. Normal Execution (Parent waits for child)\n");
        printf("2. Orphan Process Demonstration\n");
        printf("3. Zombie Process Demonstration\n");
        printf("4. Exit\n");
        printf("==========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        pid = fork(); // create child process

        if (pid < 0) {
            printf("Fork failed!\n");
            exit(1);
        }

        switch (choice) {
            case 1:
                if (pid == 0) {
                    // Child process
                    printf("\n[Child] Performing Insertion Sort...\n");
                    insertionSort(arr_copy, n);
                    printf("[Child] Sorted array: ");
                    for (i = 0; i < n; i++) printf("%d ", arr_copy[i]);
                    printf("\n[Child] PID: %d | PPID: %d\n", getpid(), getppid());
                } else {
                    // Parent process
                    wait(NULL); // waits for child
                    printf("\n[Parent] Performing Bubble Sort...\n");
                    bubbleSort(arr, n);
                    printf("[Parent] Sorted array: ");
                    for (i = 0; i < n; i++) printf("%d ", arr[i]);
                    printf("\n[Parent] PID: %d | Child PID: %d\n", getpid(), pid);
                }
                break;

            case 2:
                if (pid == 0) {
                    // Child process (orphan)
                    sleep(5);
                    printf("\n[Child] Now I'm an ORPHAN! My new parent is init/systemd.\n");
                    printf("[Child] PID: %d | PPID: %d\n", getpid(), getppid());
                } else {
                    // Parent process exits immediately
                    printf("\n[Parent] Exiting before child...\n");
                    exit(0);
                }
                break;

            case 3:
                if (pid == 0) {
                    // Child process exits immediately
                    printf("\n[Child] Exiting immediately (will become ZOMBIE)...\n");
                    exit(0);
                } else {
                    // Parent sleeps (doesn't call wait)
                    printf("\n[Parent] Sleeping... check 'ps' command to see zombie process.\n");
                    sleep(10);
                    printf("\n[Parent] Now calling wait() to clean up child.\n");
                    wait(NULL);
                }
                break;

            case 4:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

