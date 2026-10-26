
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    const char msg[] = "SIGFPE caught using sigaction!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main() {
    struct sigaction sa{};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGFPE, &sa, nullptr) == -1) {
        perror("sigaction");
        return 1;
    }

    cout << "Raising SIGFPE..." << endl;
    raise(SIGFPE);

    cout << "Signal handled successfully." << endl;
    return 0;
}
