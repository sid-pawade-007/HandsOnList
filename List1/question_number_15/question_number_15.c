// This program is about displaying ENV variables

#include <stdio.h>

extern char **environ;

int main()
{
    char **env = environ;
    while (*env != NULL)
    {
        // Printing environment variables
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
