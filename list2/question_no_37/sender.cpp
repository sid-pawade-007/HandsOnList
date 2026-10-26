
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    const char *fifo = "myfifo";

    // Create FIFO
    if (mkfifo(fifo, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    // Open FIFO for writing
    int fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char message[] = "Hello from Sender!";

    // Write message into FIFO
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    cout << "Message sent successfully." << endl;

    close(fd);
    return 0;
}
