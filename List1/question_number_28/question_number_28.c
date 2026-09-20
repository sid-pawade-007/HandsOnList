// Finding out real time priority

#include <stdio.h>
#include <sched.h>

int main()
{
    int min_priority;
    int max_priority;

    // Getting minimum real-time priority
    min_priority = sched_get_priority_min(SCHED_FIFO);

    // Getting maximum real-time priority
    max_priority = sched_get_priority_max(SCHED_FIFO);

    if (min_priority == -1 || max_priority == -1)
    {
        perror("sched_get_priority");
        return 1;
    }
    printf("Real-time scheduling policy: SCHED_FIFO\n");
    printf("Minimum real-time priority = %d\n", min_priority);
    printf("Maximum real-time priority = %d\n", max_priority);
    return 0;
}
