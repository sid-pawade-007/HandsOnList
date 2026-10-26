
#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    const char msg[] = "\nSIGINT caught! Press Ctrl+C again if needed.\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGINT, handler);

    cout << "Press Ctrl+C to generate SIGINT." << endl;

    while (true) {
        pause();
    }

    return 0;
}
