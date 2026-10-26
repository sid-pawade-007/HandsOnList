
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    int fd[2];
    char write_msg[] = "Hello from the pipe!";
    char read_msg[100];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Write data into the pipe
    if (write(fd[1], write_msg, strlen(write_msg) + 1) == -1) {
        perror("Write failed");
        return 1;
    }

    // Read data from the pipe
    if (read(fd[0], read_msg, sizeof(read_msg)) == -1) {
        perror("Read failed");
        return 1;
    }

    // Display the received data
    cout << "Message read from pipe: " << read_msg << endl;

    // Close the pipe file descriptors
    close(fd[0]);
    close(fd[1]);

    return 0;
}
