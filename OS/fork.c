#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed.\n");
    }
    else if (pid == 0)
    {
        printf("This is the child process.\n");
        printf("Child Process ID: %d\n", getpid());
    }
    else
    {
        printf("This is the parent process.\n");
        printf("Parent Process ID: %d\n", getpid());
    }

    printf("\n");
    return 0;
}
