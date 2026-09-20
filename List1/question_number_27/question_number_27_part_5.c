// This program uses execvp()

#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"ls", "-Rl", NULL};
    printf("Executing ls -Rl using execvp()\n");
    execvp("ls", args);

    // This line of code executes only if execvp() fails
    perror("execvp");

    return 1;
}
