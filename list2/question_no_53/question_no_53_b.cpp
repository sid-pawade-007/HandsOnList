
#include <iostream>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void handler(int sig) {
    cout << "\nITIMER_VIRTUAL timer expired!" << endl;
}

int main() {
    signal(SIGVTALRM, handler);

    struct itimerval timer{};

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &timer, nullptr) == -1) {
        perror("setitimer");
        return 1;
    }

    cout << "ITIMER_VIRTUAL started." << endl;

    while (true) {
        // Consume CPU time in user mode
    }

    return 0;
}
