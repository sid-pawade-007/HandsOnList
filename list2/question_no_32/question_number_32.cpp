
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    int fd[2];
    char message[] = "Hello Child Process!";
    char buffer[100];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(fd[0]);  // Close read end

        write(fd[1], message, strlen(message) + 1);
        cout << "Parent: Data sent to child." << endl;

        close(fd[1]);
        wait(NULL);
    }
    else {
        // Child process
        close(fd[1]);  // Close write end

        read(fd[0], buffer, sizeof(buffer));
        cout << "Child: Received message: " << buffer << endl;

        close(fd[0]);
        exit(0);
    }

    return 0;
}
