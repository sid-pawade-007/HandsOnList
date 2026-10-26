
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>

using namespace std;

int main() {
    const char *fifo = "myfifo";
    char buffer[100];

    // Create FIFO
    if (mkfifo(fifo, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    // Open FIFO in read-only, non-blocking mode
    int fd = open(fifo, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    // Set timeout to 10 seconds
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    cout << "Waiting for data in FIFO (10 seconds)..." << endl;

    // Wait for FIFO to become readable
    int result = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select");
    }
    else if (result == 0) {
        cout << "Timeout: Aawaj nahi aayi." << endl;
    }
    else {
        ssize_t n = read(fd, buffer, sizeof(buffer) - 1);

        if (n > 0) {
            buffer[n] = '\0';
            cout << "Data received: " << buffer << endl;
        }
        else {
            cout << "FIFO became readable, but no data was received." << endl;
        }
    }

    close(fd);
    return 0;
}
