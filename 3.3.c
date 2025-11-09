#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int waiting;
    int turnaround;
};

void fcfs(struct Process p[], int n) {
    int time = 0;
    float total_wt = 0, total_tat = 0;

    printf("\nGANTT CHART:\n|");

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;

        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;

        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;

        printf(" P%d |", p[i].pid);
    }

    printf("\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        time += p[i].burst;
        printf("  %d", time);
    }

    printf("\n\nAverage Waiting Time for FCFS: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time for FCFS: %.2f\n", total_tat / n);
}

void round_robin(struct Process p[], int n, int tq) {
    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    int done[20] = {0};

    // Initialize remaining burst times
    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    printf("\nGANTT CHART:\n|");

    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                executed = 1;
                if (p[i].remaining > tq) {
                    printf(" P%d |", p[i].pid);
                    time += tq;
                    p[i].remaining -= tq;
                } else {
                    printf(" P%d |", p[i].pid);
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    completed++;

                    p[i].turnaround = time - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;

                    total_wt += p[i].waiting;
                    total_tat += p[i].turnaround;
                }
            }
        }
        if (!executed)  // No process available yet
            time++;
    }

    printf("\n\nAverage Waiting Time for Round Robin: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time for Round Robin: %.2f\n", total_tat / n);
}

int main() {
    int n, choice;
    struct Process p[20];
    int tq = 2; // Time Quantum

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival time for Process %d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Enter Burst time for Process %d: ", i + 1);
        scanf("%d", &p[i].burst);
    }

    while (1) {
        printf("\n========== CPU SCHEDULING MENU ==========\n");
        printf("1. FCFS Scheduling\n");
        printf("2. Round Robin (Preemptive)\n");
        printf("3. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                round_robin(p, n, tq);
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

