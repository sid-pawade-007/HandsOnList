
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main() {
    struct sigaction sa{};

    // Step 1: Ignore SIGINT
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        perror("sigaction");
        return 1;
    }

    cout << "SIGINT is ignored for 10 seconds." << endl;
    cout << "Press Ctrl+C now; the program will continue." << endl;

    sleep(10);

    // Step 2: Reset SIGINT to its default action
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        perror("sigaction");
        return 1;
    }

    cout << "\nSIGINT reset to its default action." << endl;
    cout << "Press Ctrl+C now to terminate the program." << endl;

    while (true) {
        pause();
    }

    return 0;
}
