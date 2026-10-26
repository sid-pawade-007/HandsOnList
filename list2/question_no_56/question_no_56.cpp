
#include <iostream>
#include <unistd.h>
#include <cstdint>

using namespace std;

// Read the CPU Time Stamp Counter
uint64_t rdtsc() {
    unsigned int low, high;

    asm volatile("rdtsc"
                 : "=a"(low), "=d"(high));

    return ((uint64_t)high << 32) | low;
}

int main() {
    uint64_t start, end;

    // Start the timer
    start = rdtsc();

    // Execute getppid() 100 times
    for (int i = 0; i < 100; i++) {
        getppid();
    }

    // Stop the timer
    end = rdtsc();

    cout << "Number of getppid() calls: 100" << endl;
    cout << "Total TSC ticks: " << end - start << endl;
    cout << "Average TSC ticks per call: "
         << (end - start) / 100.0 << endl;

    return 0;
}
