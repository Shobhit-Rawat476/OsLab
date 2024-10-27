#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void findRoundRobin(struct Process proc[], int n, int quantum) {
    int currentTime = 0;
    int completed = 0;
    bool done[n];

    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime; // Initialize remaining time with burst time
        done[i] = false; // Initialize all processes as not done
    }

    while (completed < n) {
        bool found = false; // Flag to check if a process is found in this cycle

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0) {
                found = true; // Process is ready for execution
                if (proc[i].remainingTime > quantum) {
                    currentTime += quantum; // Process runs for a quantum time
                    proc[i].remainingTime -= quantum; // Decrease remaining time
                } else {
                    // If remaining time is less than or equal to quantum
                    currentTime += proc[i].remainingTime;
                    proc[i].completionTime = currentTime;
                    proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
                    proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
                    proc[i].remainingTime = 0; // Mark the process as completed
                    completed++; // Increment completed process count
                }
            }
        }

        if (!found) {
            // If no process is found, advance the current time
            currentTime++;
        }
    }
}

void displayProcessDetails(struct Process proc[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    printf("Process\tArrivalTime\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].completionTime, proc[i].turnaroundTime, proc[i].waitingTime);
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n = 5;
    struct Process proc[n];
    int quantum;

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    printf("Enter Process Details (ID, Arrival, Burst)\n");
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d\n", i + 1);
        scanf("%d %d %d", &proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime);
    }

    findRoundRobin(proc, n, quantum);
    displayProcessDetails(proc, n);

    return 0;
}

