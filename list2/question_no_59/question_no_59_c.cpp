
#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    const char msg[] = "SIGFPE caught!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGFPE, handler);

    cout << "Raising SIGFPE..." << endl;
    raise(SIGFPE);

    cout << "Program continues after signal handling."
         << endl;

    return 0;
}
