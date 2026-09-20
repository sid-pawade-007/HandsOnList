// This program uses execv()

#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"ls", "-Rl", NULL};
    printf("Executing ls -Rl using execv()\n");
    execv("/bin/ls", args);

    // This line of code executes only if execv() fails
    perror("execv");

    return 1;
}
