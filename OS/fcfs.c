#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void findFCFS(struct Process proc[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime; // If the CPU is idle, skip to the arrival time of the next process
        }
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;

        currentTime = proc[i].completionTime; // Move current time to the completion time of the current process
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

    findFCFS(proc, n);
    displayProcessDetails(proc, n);

    return 0;
}
