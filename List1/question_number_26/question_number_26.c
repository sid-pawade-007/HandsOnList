// This program uses exec() to execute executable file

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Executing executable program...\n");
    execl("./executable", "executable", NULL);

    // This line of code executes only if execl() fails
    perror("execl");

    return 1;
}
