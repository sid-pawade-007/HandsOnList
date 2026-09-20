//Printing Process id of parent and child

#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)  // Printing pid of Child Process
    {
        printf("Child Process:\n");
        printf("Child PID  = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
    }
    else  // Printing pid of Parent Process
    {
        printf("Parent Process:\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID  = %d\n", pid);
    }

    return 0;
}
