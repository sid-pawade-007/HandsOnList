
#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    const char msg[] = "SIGSEGV caught!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGSEGV, handler);

    cout << "Raising SIGSEGV..." << endl;
    raise(SIGSEGV);

    cout << "Program continues after signal handling."
         << endl;

    return 0;
}
