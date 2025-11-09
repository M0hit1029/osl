#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
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

void sjf_preemptive(struct Process p[], int n) {
    int completed = 0, time = 0, shortest = -1, min_burst;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].completed = 0;
    }

    printf("\nGANTT CHART:\n|");

    while (completed < n) {
        shortest = -1;
        min_burst = INT_MAX;

        // find process with minimum remaining time among arrived ones
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min_burst) {
                min_burst = p[i].remaining;
                shortest = i;
            }
        }

        if (shortest == -1) { // no process available
            time++;
            continue;
        }

        printf(" P%d |", p[shortest].pid);

        p[shortest].remaining--;
        time++;

        // when process completes
        if (p[shortest].remaining == 0) {
            p[shortest].completed = 1;
            completed++;
            int finish_time = time;
            p[shortest].turnaround = finish_time - p[shortest].arrival;
            p[shortest].waiting = p[shortest].turnaround - p[shortest].burst;

            if (p[shortest].waiting < 0)
                p[shortest].waiting = 0;

            total_wt += p[shortest].waiting;
            total_tat += p[shortest].turnaround;
        }
    }

    printf("\n\nAverage Waiting Time for SJF (Preemptive): %.2f", total_wt / n);
    printf("\nAverage Turnaround Time for SJF (Preemptive): %.2f\n", total_tat / n);
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
        printf("2. SJF (Preemptive)\n");
        printf("3. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf_preemptive(p, n);
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

