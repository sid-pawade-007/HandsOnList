
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    int pipe1[2], pipe2[2];
    char buffer[100];

    // Create two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(pipe1[0]);  // Close read end of pipe1
        close(pipe2[1]);  // Close write end of pipe2

        char msg1[] = "Hello from Parent";

        // Send data to child
        write(pipe1[1], msg1, strlen(msg1) + 1);

        // Receive data from child
        read(pipe2[0], buffer, sizeof(buffer));
        cout << "Parent received: " << buffer << endl;

        close(pipe1[1]);
        close(pipe2[0]);

        wait(NULL);
    }
    else {
        // Child process
        close(pipe1[1]);  // Close write end of pipe1
        close(pipe2[0]);  // Close read end of pipe2

        // Receive data from parent
        read(pipe1[0], buffer, sizeof(buffer));
        cout << "Child received: " << buffer << endl;

        char msg2[] = "Hello from Child";

        // Send data to parent
        write(pipe2[1], msg2, strlen(msg2) + 1);

        close(pipe1[0]);
        close(pipe2[1]);

        exit(0);
    }

    return 0;
}
