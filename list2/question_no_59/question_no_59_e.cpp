
#include <iostream>
#include <csignal>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    const char msg[] = "SIGALRM received from setitimer()!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGALRM, handler);

    struct itimerval timer{};

    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;

    // No repetition
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, nullptr) == -1) {
        perror("setitimer");
        return 1;
    }

    cout << "ITIMER_REAL started for 5 seconds." << endl;

    while (true) {
        pause();
    }

    return 0;
}
