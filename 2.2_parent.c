#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Bubble sort function
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

int main() {
    int n, i;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Sort the array
    bubbleSort(arr, n);

    printf("\n[Parent] Sorted Array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    pid = fork();  // Create child process

    if (pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    }
    else if (pid == 0) {
        // Child process: prepare execve arguments
        char *args[n + 3];  // n array elements + program name + search item + NULL

        args[0] = "./child"; // child program name

        // Convert integers to strings
        for (i = 0; i < n; i++) {
            char *num = (char *)malloc(10 * sizeof(char));
            sprintf(num, "%d", arr[i]);
            args[i + 1] = num;
        }

        args[n + 1] = NULL; // NULL terminator required by execve

        printf("\n[Parent] Executing child process to perform binary search...\n");

        // Execute child process
        execve("./child", args, NULL);

        // If execve fails
        perror("execve failed");
        exit(1);
    }
    else {
        // Parent process waits
        wait(NULL);
        printf("\n[Parent] Child process completed.\n");
    }

    return 0;
}

