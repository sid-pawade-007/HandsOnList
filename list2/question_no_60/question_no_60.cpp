
#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

int main() {
    // Ignore SIGINT
    signal(SIGINT, SIG_IGN);

    cout << "SIGINT is ignored for 10 seconds." << endl;
    cout << "Press Ctrl+C during this time; the program will continue."
         << endl;

    sleep(10);

    // Reset SIGINT to its default action
    signal(SIGINT, SIG_DFL);

    cout << "\nSIGINT reset to default action." << endl;
    cout << "Press Ctrl+C now to terminate the program." << endl;

    while (true) {
        pause();
    }

    return 0;
}
