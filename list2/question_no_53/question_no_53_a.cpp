
#include <iostream>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void handler(int sig) {
    cout << "\nITIMER_REAL timer expired!" << endl;
}

int main() {
    signal(SIGALRM, handler);

    struct itimerval timer{};

    // Initial expiration: 10 seconds and 10 microseconds
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    // Repeating interval: 10 seconds and 10 microseconds
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &timer, nullptr) == -1) {
        perror("setitimer");
        return 1;
    }

    cout << "ITIMER_REAL started." << endl;

    while (true) {
        pause();
    }

    return 0;
}
