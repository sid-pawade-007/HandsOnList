
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

using namespace std;

int main() {
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";
    char buffer[100];

    // Create FIFOs if they do not already exist
    if (mkfifo(fifo1, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo1");
        return 1;
    }

    if (mkfifo(fifo2, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo2");
        return 1;
    }

    // Open FIFO1 for reading and FIFO2 for writing
    int fd1 = open(fifo1, O_RDONLY);
    if (fd1 == -1) {
        perror("open fifo1");
        return 1;
    }

    int fd2 = open(fifo2, O_WRONLY);
    if (fd2 == -1) {
        perror("open fifo2");
        close(fd1);
        return 1;
    }

    // Receive message
    ssize_t n = read(fd1, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        cout << "Program 2 received: " << buffer << endl;
    }

    // Send reply
    char reply[] = "Comencing countdown, Engines on!";
    write(fd2, reply, strlen(reply) + 1);
    cout << "Program 2 sent: " << reply << endl;

    close(fd1);
    close(fd2);

    return 0;
}
