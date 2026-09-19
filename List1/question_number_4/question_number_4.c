#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Opening question4.txt file in read-write mode
    fd = open("question4.txt", O_RDWR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened successfully.\n");
    printf("File descriptor = %d\n", fd);

    close(fd);

    return 0;
}
