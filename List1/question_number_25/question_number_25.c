// Creating 3 child process and waiting for a particular child to respond

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t child1, child2, child3;
    int status;

    // Create first child
    child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1: PID = %d\n", getpid());
        sleep(2);
        printf("Child 1 exiting...\n");
        exit(1);
    }

    // Create second child
    child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2: PID = %d\n", getpid());
        sleep(5);
        printf("Child 2 exiting...\n");
        exit(2);
    }

    // Create third child
    child3 = fork();

    if (child3 == 0)
    {
        printf("Child 3: PID = %d\n", getpid());
        sleep(8);
        printf("Child 3 exiting...\n");
        exit(3);
    }

    // Parent process
    printf("\nParent PID = %d\n", getpid());
    printf("Child 1 PID = %d\n", child1);
    printf("Child 2 PID = %d\n", child2);
    printf("Child 3 PID = %d\n", child3);

    // Wait specifically for Child 2
    printf("\nParent waiting for Child 2...\n");

    if (waitpid(child2, &status, 0) == -1)
    {
        perror("waitpid");
        return 1;
    }

    printf("Parent: Child 2 has terminated.\n");

    if (WIFEXITED(status))
    {
        printf("Child 2 exit status = %d\n",
               WEXITSTATUS(status));
    }

    // Wait for remaining children
    waitpid(child1, NULL, 0);
    waitpid(child3, NULL, 0);

    printf("Parent process exiting.\n");

    return 0;
}
