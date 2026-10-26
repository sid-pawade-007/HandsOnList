
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    const char msg[] = "\nSIGINT caught using sigaction!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    struct sigaction sa{};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        perror("sigaction");
        return 1;
    }

    cout << "Press Ctrl+C to generate SIGINT." << endl;

    while (true) {
        pause();
    }

    return 0;
}
