// This program uses dup2 where we can specify file descripter

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, fd2;

    fd = open("Sid2.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Duplicate fd into descriptor 69
    fd2 = dup2(fd, 69);

    if (fd2 == -1) {
        perror("dup2");
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
