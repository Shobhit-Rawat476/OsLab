#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void findPriorityScheduling(struct Process proc[], int n) {
    int completed = 0, currentTime = 0;
    int isCompleted[n]; // Array to track completed processes
    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0; // Initialize all processes as not completed
    }

    while (completed < n) {
        int highestPriority = -1; // Index of the process with the highest priority
        int minPriority = 9999; // Set an initially high priority number

        for (int i = 0; i < n; i++) {
            // Select the process with the highest priority (lowest priority number)
            if (proc[i].arrivalTime <= currentTime && isCompleted[i] == 0) {
                if (proc[i].priority < minPriority) {
                    minPriority = proc[i].priority;
                    highestPriority = i;
                }
                // In case of tie in priority, use FCFS (earlier arrival time)
                if (proc[i].priority == minPriority) {
                    if (proc[i].arrivalTime < proc[highestPriority].arrivalTime) {
                        highestPriority = i;
                    }
                }
            }
        }

        if (highestPriority == -1) { // No process is ready at the current time
            currentTime++;
            continue;
        }

        // Execute the process with the highest priority
        currentTime += proc[highestPriority].burstTime;
        proc[highestPriority].completionTime = currentTime;
        proc[highestPriority].turnaroundTime = proc[highestPriority].completionTime - proc[highestPriority].arrivalTime;
        proc[highestPriority].waitingTime = proc[highestPriority].turnaroundTime - proc[highestPriority].burstTime;

        isCompleted[highestPriority] = 1; // Mark the process as completed
        completed++;
    }
}

void displayProcessDetails(struct Process proc[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    printf("Process\tArrivalTime\tBurstTime\tPriority\tCompletionTime\tTurnaroundTime\tWaitingTime\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].priority, proc[i].completionTime, proc[i].turnaroundTime, proc[i].waitingTime);
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n = 5;
    struct Process proc[n];
    printf("Enter Process Details (ID, Arrival, Burst, Priority)\n");
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d\n", i + 1);
        scanf("%d %d %d %d", &proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
    }

    findPriorityScheduling(proc, n);
    displayProcessDetails(proc, n);

    return 0;
}

