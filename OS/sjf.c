#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void findSJF(struct Process proc[], int n) {
    int completed = 0, currentTime = 0;
    int isCompleted[n]; // Array to track completed processes
    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0; // Initialize all processes as not completed
    }

    while (completed < n) {
        int shortest = -1; // Index of the shortest process
        int minBurst = 9999; // Set an initially high burst time

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && isCompleted[i] == 0) {
                if (proc[i].burstTime < minBurst) {
                    minBurst = proc[i].burstTime;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) { // No process is ready at current time
            currentTime++;
            continue;
        }

        // Process the selected shortest job
        currentTime += proc[shortest].burstTime;
        proc[shortest].completionTime = currentTime;
        proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
        proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;

        isCompleted[shortest] = 1; // Mark the process as completed
        completed++;
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
    printf("Enter Process Details (ID, Arrival, Burst)\n");
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d\n", i + 1);
        scanf("%d %d %d", &proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime);
    }

    findSJF(proc, n);
    displayProcessDetails(proc, n);

    return 0;
}
