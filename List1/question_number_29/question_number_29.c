// This program is about finding out what scheduling policy is and changing it

#include <stdio.h>
#include <unistd.h>
#include <sched.h>

void print_policy(int policy)
{
    if (policy == SCHED_OTHER){
        printf("Scheduling Policy: SCHED_OTHER\n");
    }
    else if (policy == SCHED_FIFO){
        printf("Scheduling Policy: SCHED_FIFO\n");
    }
    else if (policy == SCHED_RR){
        printf("Scheduling Policy: SCHED_RR\n");
    }
    else{
        printf("Unknown scheduling policy\n");
    }
}

int main()
{
    int policy;
    struct sched_param param;

    // Finding out what current scheduling policy is
    policy = sched_getscheduler(0);

    if (policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy:\n");
    print_policy(policy);

    // Set priority for real-time scheduling
    param.sched_priority = 10;

    // Change policy to SCHED_FIFO
    printf("\nTrying to change policy to SCHED_FIFO...\n");

    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
    {
        perror("sched_setscheduler");
    }
    else
    {
        printf("Policy changed successfully.\n");
    }

    // Looking at policy again
    policy = sched_getscheduler(0);
    if (policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }
    print_policy(policy);
    return 0;
}
