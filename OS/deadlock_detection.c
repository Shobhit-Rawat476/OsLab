
#include <stdio.h>

int main() {
    int n, m, i, j, k, y;
    int alloc[20][20], max[20][20], avail[20];

    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    printf("Enter the number of Resources: ");
    scanf("%d", &m);

    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("Enter the Max Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter the Available Matrix:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    int finish[n], work[m], need[n][m];

    // Calculating NEED matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    printf("NEED matrix is:\n");
    for (i = 0; i < n; i++) {
        printf("\n");
        for (j = 0; j < m; j++)
            printf(" %d ", need[i][j]);
    }
    printf("\n");

    // Initialize work and finish arrays
    for (i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    // Deadlock detection algorithm
    int deadlock_flag = 0;

    for (k = 0; k < n; k++) {
        int allocated = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {  // If process hasn't finished
                int can_allocate = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {  // If resources needed exceed available
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    for (y = 0; y < m; y++)
                        work[y] += alloc[i][y];  // Release allocated resources
                    finish[i] = 1;  // Mark process as finished
                    allocated = 1;
                }
            }
        }
        if (!allocated) {
            deadlock_flag = 1;
            break;
        }
    }

    // Check for any unfinished processes
    int deadlocked_processes = 0;
    printf("\nDeadlocked processes: ");
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            printf(" P%d ", i);
            deadlocked_processes = 1;
        }
    }

    if (!deadlocked_processes) {
        printf("None, system is not in deadlock.\n");
    } else {
        printf("\nSystem is in deadlock.\n");
    }

    return 0;
}
