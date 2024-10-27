#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void findSRTF(struct Process proc[], int n) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = proc[i].burstTime;
    }

    int currentTime = 0;
    int complete = 0;
    int shortest = 0;
    int minBurst = INT_MAX;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (complete < n) {
        minBurst = INT_MAX;
        shortest = -1;

        // Find the shortest job that is ready to execute
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && remainingTime[i] < minBurst && remainingTime[i] > 0) {
                minBurst = remainingTime[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        remainingTime[shortest]--;
        if (remainingTime[shortest] == 0) {
            complete++;
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
    printf("Process\tArrivalTime\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].completionTime, proc[i].turnaroundTime, proc[i].waitingTime);
    }
    printf("\n");
}

int main() {
    int n = 5;
    struct Process proc[n];
    printf("Enter Process Details (ID, Arrival, Burst)\n");
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d\n", i + 1);
        scanf("%d %d %d", &proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime);
    }

    findSRTF(proc, n);
    displayProcessDetails(proc, n);

    return 0;
}
