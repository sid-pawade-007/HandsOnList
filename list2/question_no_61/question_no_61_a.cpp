
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    const char msg[] = "SIGSEGV caught using sigaction!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main() {
    struct sigaction sa{};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGSEGV, &sa, nullptr) == -1) {
        perror("sigaction");
        return 1;
    }

    cout << "Raising SIGSEGV..." << endl;
    raise(SIGSEGV);

    cout << "Signal handled successfully." << endl;
    return 0;
}
