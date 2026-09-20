//This practical is about waitng max 10 sec for input using select sys call

#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
    fd_set readfds;
    struct timeval timeout;
    int result;

    // Initialize the set of file descriptors
    FD_ZERO(&readfds);

    // Add STDIN (file descriptor 0)
    FD_SET(STDIN_FILENO, &readfds);

    // Set timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input on STDIN for 10 seconds...\n");
    fflush(stdout);

    // Wait for STDIN to become ready
    result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1)
    {
        perror("select");
        return 1;
    }
    else if (result == 0)
    {
        printf("No data available on STDIN within 10 seconds.\n");
    }
    else
    {
        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            printf("Data is available on STDIN within 10 seconds!\n");

            char buffer[100];
            int n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

            if (n > 0)
            {
                buffer[n] = '\0';
                printf("You entered: %s", buffer);
            }
        }
    }

    return 0;
}
