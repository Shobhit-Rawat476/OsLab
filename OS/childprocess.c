#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    // Creating first child process
    pid_t first_child = fork();

    if (first_child < 0)
    {
        printf("Fork failed.\n");
    }
    else if (first_child == 0)
    {
        // Inside first child
        printf("First Child: My PID is %d, My Parent PID is %d.\n", getpid(), getppid());
        fflush(stdout);
        sleep(3);
        printf("First Child (After Parent Death): My Parent PID is %d.\n", getppid());
        fflush(stdout);
        exit(0);
    }
    else
    {
        printf("Parent Process: My PID is %d, terminating.\n", getpid());
        fflush(stdout);
        sleep(1);
        exit(0);
    }

    return 0;
}
