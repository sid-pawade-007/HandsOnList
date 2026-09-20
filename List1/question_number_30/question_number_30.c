// Creating daemon process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

int main()
{
    pid_t pid;
    time_t now;
    struct tm *current_time;
    int target_hour, target_minute;

    printf("Enter hour (0-23): ");
    scanf("%d", &target_hour);

    printf("Enter minute (0-59): ");
    scanf("%d", &target_minute);

    // Creating a child process
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    // Parent process exits
    if (pid > 0)
    {
        printf("Daemon started. Parent process exiting.\n");
        return 0;
    }

    // Creating a new session
    if (setsid() == -1)
    {
        perror("setsid");
        exit(1);
    }

    // Change working directory
    chdir("/");

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Run forever
    while (1)
    {
        now = time(NULL);
        current_time = localtime(&now);

        if (current_time->tm_hour == target_hour && current_time->tm_min == target_minute)
        {
            system("/home/siddhesh/HandsOnList/List1/question_number_30/script_for_question_30.sh");

            // Prevent executing repeatedly during the same minute
            sleep(60);
        }

        sleep(1);
    }

    return 0;
}
