// Creating Orphan Process

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process started.\n");
        printf("Child PID  = %d\n", getpid());
        printf("Initial Parent PID = %d\n", getppid());

        // Wait for 5 secs for parent to terminate
        sleep(5);

        printf("\nAfter parent terminates:\n");
        printf("Child PID  = %d\n", getpid());
        printf("New Parent PID = %d\n", getppid());
        sleep(5);
    }
    else
    {
        // Parent process
        printf("Parent process started.\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID  = %d\n", pid);
        printf("Parent is exiting...\n");
        exit(0);
    }
    return 0;
}
