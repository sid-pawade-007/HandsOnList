
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstdlib>

using namespace std;

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child 1: Execute ls -l
        close(fd[0]);

        if (fcntl(fd[1], F_DUPFD, STDOUT_FILENO) == -1) {
            perror("fcntl");
            _exit(1);
        }

        // Redirect stdout to the pipe using F_DUPFD
        // Ensure the new descriptor is STDOUT_FILENO.
        // Since stdout is open, use dup2-style setup below.
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            _exit(1);
        }

        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);

        perror("execlp ls");
        _exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        // Child 2: Execute wc
        close(fd[1]);

        if (fcntl(fd[0], F_DUPFD, 0) == -1) {
            perror("fcntl");
            _exit(1);
        }

        if (dup2(fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            _exit(1);
        }

        close(fd[0]);
        execlp("wc", "wc", (char *)NULL);

        perror("execlp wc");
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
