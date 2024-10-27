#include <stdio.h>
#include <unistd.h>
int main()
{	pid_t pid = fork();
if (pid < 0)
{	printf("Fork failed.\n");
    	}
else if (pid == 0)
{	printf("Child Process: My PID is %d, My Parent PID is %d.\n", getpid(), getppid());
    	}
else
{	printf("Parent Process: My PID is %d, My Child PID is %d.\n", getpid(), pid);
    	}
printf("\n");
return 0;
}
