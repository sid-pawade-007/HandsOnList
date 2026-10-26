
#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    cout << "SIGSTOP caught!" << endl;
}

int main() {
    // Attempt to register a handler for SIGSTOP
    if (signal(SIGSTOP, handler) == SIG_ERR) {
        perror("signal");
    }

    cout << "Receiver PID: " << getpid() << endl;
    cout << "Waiting for signals..." << endl;

    while (true) {
        pause();
    }

    return 0;
}
