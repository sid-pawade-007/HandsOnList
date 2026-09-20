// This program uses execl()

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Executing ls -Rl using execl()\n");
    execl("/bin/ls", "ls", "-Rl", NULL);

    // This line of code executes only if execl() fails
    perror("execl");

    return 1;
}
