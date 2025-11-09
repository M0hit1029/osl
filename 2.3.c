#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num < 2)
        return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    pid_t pid;

    // --- Step 1: Check if user provided command line argument ---
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        exit(1);
    }

    // --- Step 2: Convert argument to integer and validate ---
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Error: Please enter a positive integer.\n");
        exit(1);
    }

    // --- Step 3: Create child process ---
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // --- Child Process ---
        printf("\n[Child] Generating first %d prime numbers:\n", n);
        int count = 0, num = 2;

        // Generate first n prime numbers
        while (count < n) {
            if (isPrime(num)) {
                printf("%d ", num);
                count++;
            }
            num++;
        }
        printf("\n[Child] Prime number generation complete.\n");
        exit(0);
    }
    else {
        // --- Parent Process ---
        printf("[Parent] Waiting for child process (PID: %d) to finish...\n", pid);
        wait(NULL);
        printf("[Parent] Child process has completed.\n");
    }

    return 0;
}

