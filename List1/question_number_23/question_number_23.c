// Creating A Zombie Process

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
        printf("Child process is running.\n");
        printf("Child PID = %d\n", getpid());
        printf("Child process is exiting...\n");
        exit(0);
    }
    else
    {
        // Parent process
        printf("Parent process is running.\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        // Parent does NOT call wait()
        // Keep parent alive so child remains zombie
        printf("Parent sleeping for 30 seconds...\n");
        sleep(30);
    }
    return 0;
}
