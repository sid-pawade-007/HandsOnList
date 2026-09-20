// Running multiple pid() and then taking average

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

static inline uint64_t rdtsc()
{
    unsigned int low, high;

    __asm__ volatile ("rdtsc": "=a"(low), "=d"(high));

    return ((uint64_t)high << 32) | low;
}

int main()
{
    uint64_t start, end;
    long long total;
    int i;
    int n = 10000;

    start = rdtsc();
    
    //Running multiple getpid() function calls
    for (i = 0; i < n; i++)
    {
        getpid();
    }
    end = rdtsc();
    total = end - start;

    printf("Number of getpid() calls = %d\n", n);
    printf("Total CPU cycles = %llu\n",(unsigned long long)total);

    // Taking average of all the calls
    printf("Average CPU cycles per getpid() = %.2f\n", (double)total / n);

    return 0;
}
