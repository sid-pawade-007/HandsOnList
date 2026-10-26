
#include <iostream>
#include <csignal>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: ./sender <PID>" << endl;
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    // Send SIGSTOP to the receiver process
    if (kill(pid, SIGSTOP) == -1) {
        perror("kill");
        return 1;
    }

    cout << "SIGSTOP sent to process " << pid << endl;

    return 0;
}
