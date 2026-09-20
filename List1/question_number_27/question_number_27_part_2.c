// This program uses execlp()

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Executing ls -Rl using execlp()\n");
    execlp("ls", "ls", "-Rl", NULL);
    
    // This line of code executes only if execlp() fails
    perror("execlp");

    return 1;
}
