
#include <iostream>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void handler(int sig) {
    cout << "\nITIMER_PROF timer expired!" << endl;
}

int main() {
    signal(SIGPROF, handler);

    struct itimerval timer{};

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, nullptr) == -1) {
        perror("setitimer");
        return 1;
    }

    cout << "ITIMER_PROF started." << endl;

    while (true) {
        // Consume CPU time for the profiling timer
    }

    return 0;
}
