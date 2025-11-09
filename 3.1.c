#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int completed;
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

void sjf(struct Process p[], int n) {
    int completed = 0, time = 0, min_index;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
        p[i].completed = 0;

    printf("\nGANTT CHART:\n|");

    while (completed < n) {
        min_index = -1;

        // Find the process with the smallest burst time among available processes
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time) {
                if (min_index == -1 || p[i].burst < p[min_index].burst)
                    min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        p[min_index].waiting = time - p[min_index].arrival;
        time += p[min_index].burst;
        p[min_index].turnaround = p[min_index].waiting + p[min_index].burst;
        p[min_index].completed = 1;
        completed++;

        total_wt += p[min_index].waiting;
        total_tat += p[min_index].turnaround;

        printf(" P%d |", p[min_index].pid);
    }

    printf("\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        printf("  %d", time);
    }

    printf("\n\nAverage Waiting Time for SJF: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time for SJF: %.2f\n", total_tat / n);
}

int main() {
    int n, choice;
    struct Process p[20];

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
        printf("2. SJF (Non-Preemptive)\n");
        printf("3. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf(p, n);
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

