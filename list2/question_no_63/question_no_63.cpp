
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        cout << "Child process started." << endl;
        cout << "Child PID: " << getpid() << endl;
        cout << "Parent PID: " << getppid() << endl;

        sleep(2);

        // Send SIGKILL to the parent process
        pid_t parent_pid = getppid();

        cout << "Child sending SIGKILL to parent PID: "
             << parent_pid << endl;

        if (kill(parent_pid, SIGKILL) == -1) {
            perror("kill");
            return 1;
        }

        sleep(1);

        cout << "New parent PID: " << getppid() << endl;
        cout << "Child is now an orphan." << endl;
    } else {
        // Parent process
        cout << "Parent process started." << endl;
        cout << "Parent PID: " << getpid() << endl;

        while (true) {
            sleep(1);
        }
    }

    return 0;
}
