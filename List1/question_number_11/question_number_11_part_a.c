// This program uses dup

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, fd2;

    // Opening file in append mode
    fd = open("Sid.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Duplicating file descriptor
    fd2 = dup(fd);

    if (fd2 == -1) {
        perror("dup");
        close(fd);
        return 1;
    }

    printf("Original FD = %d\n", fd);
    printf("Duplicated FD = %d\n", fd2);

    // Writing using original descriptor
    write(fd, "Written using fd\n", 17);

    // Writing using duplicated descriptor
    write(fd2, "Written using fd2\n", 18);

    close(fd);
    close(fd2);

    return 0;
}
