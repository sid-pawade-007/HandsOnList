
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main() {
    const char *fifo = "myfifo";
    char buffer[100];

    // Open FIFO for reading
    int fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Read message from FIFO
    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[n] = '\0';

    cout << "Message received: " << buffer << endl;

    close(fd);
    return 0;
}
