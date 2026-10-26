
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

    // Create two FIFOs
    if (mkfifo(fifo1, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo1");
        return 1;
    }

    if (mkfifo(fifo2, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo2");
        return 1;
    }

    // Open FIFO1 for writing and FIFO2 for reading
    int fd1 = open(fifo1, O_WRONLY);
    if (fd1 == -1) {
        perror("open fifo1");
        return 1;
    }

    int fd2 = open(fifo2, O_RDONLY);
    if (fd2 == -1) {
        perror("open fifo2");
        close(fd1);
        return 1;
    }

    // Send message
    char message[] = "Ground Control to Major Tom";
    write(fd1, message, strlen(message) + 1);
    cout << "Program 1 sent: " << message << endl;

    // Receive reply
    ssize_t n = read(fd2, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        cout << "Program 1 received: " << buffer << endl;
    }

    close(fd1);
    close(fd2);

    return 0;
}
