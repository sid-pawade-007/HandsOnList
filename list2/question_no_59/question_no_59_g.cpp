
#include <iostream>
#include <csignal>
#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void handler(int sig) {
    const char msg[] = "SIGPROF received!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main() {
    signal(SIGPROF, handler);

    struct itimerval timer{};

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_PROF, &timer, nullptr) == -1) {
        perror("setitimer");
        return 1;
    }

    cout << "ITIMER_PROF started." << endl;

    // Consume CPU time
    volatile unsigned long long i = 0;
    while (true) {
        ++i;
    }

    return 0;
}
