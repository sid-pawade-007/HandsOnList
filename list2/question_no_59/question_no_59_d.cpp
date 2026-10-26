
#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void handler(int sig) {
    const char msg[] = "SIGALRM received from alarm()!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGALRM, handler);

    cout << "Alarm set for 5 seconds..." << endl;

    alarm(5);

    while (true) {
        pause();
    }

    return 0;
}
