#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void findPreemptivePriority(struct Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;
    int shortest = -1;
    int minPriority = INT_MAX;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed < n) {
        // Find the process with the highest priority (lowest priority number) that has arrived and is not completed
        minPriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && proc[i].priority < minPriority) {
                minPriority = proc[i].priority;
                shortest = i;
            }
        }

        if (shortest == -1) {
            // No process is ready, advance the current time
            currentTime++;
            continue;
        }

        // Execute the process with the highest priority
        proc[shortest].remainingTime--;

        if (proc[shortest].remainingTime == 0) {
            completed++;
            proc[shortest].completionTime = currentTime + 1;
            proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
            totalWaitingTime += proc[shortest].waitingTime;
            totalTurnaroundTime += proc[shortest].turnaroundTime;
        }

        currentTime++;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

void displayProcessDetails(struct Process proc[], int n) {
    printf("Process\tArrivalTime\tBurstTime\tPriority\tCompletionTime\tTurnaroundTime\tWaitingTime\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].priority, proc[i].completionTime, proc[i].turnaroundTime, proc[i].waitingTime);
    }
    printf("\n");
}

int main() {
    int n = 5;
    struct Process proc[n];
    printf("Enter Process Details (ID, Arrival, Burst, Priority)\n");
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d\n", i + 1);
        scanf("%d %d %d %d", &proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
        proc[i].remainingTime = proc[i].burstTime;  // Initialize remaining time with burst time
    }

    findPreemptivePriority(proc, n);
    displayProcessDetails(proc, n);

    return 0;
}
