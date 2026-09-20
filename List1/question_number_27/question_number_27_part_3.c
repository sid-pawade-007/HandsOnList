// This program uses execle()

#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main()
{
    printf("Executing ls -Rl using execle()\n");

    execle("/bin/ls", "ls", "-Rl", NULL, environ);
    
    // This line of code executes only if execle() fials
    perror("execle");

    return 1;
}
