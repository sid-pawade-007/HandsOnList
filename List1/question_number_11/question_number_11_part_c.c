// This program uses fcntl which gives us lowest possible fd greater than what we specified

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, fd2;

    fd = open("fcntl.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Duplicating fd using fcntl
    fd2 = fcntl(fd, F_DUPFD, 10);

    if (fd2 == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Original FD = %d\n", fd);
    printf("Duplicated FD = %d\n", fd2);

    write(fd, "Written using fd\n", 17);

    write(fd2, "Written using fd2\n", 18);

    close(fd);
    close(fd2);

    return 0;
}
