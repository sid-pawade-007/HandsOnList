// Changing Priority

#include <stdio.h>
#include <unistd.h>

int main()
{
    while (1)
    {
        // Call from Mom High Priority..
        printf("Mom Calling ...\n");
        sleep(2);
    }

    return 0;
}
