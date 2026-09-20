//This program tells us how pointer is moved using lseek

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    off_t position;

    // Open file in read-write mode
    fd = open("BreakingBad.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Writing the first 10 bytes
    write(fd, "BREAKINBAD", 10);

    // Moving file pointer forward by 10 bytes
    position = lseek(fd, 10, SEEK_CUR);

    // Checking return value of lseek
    if (position == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Return value of lseek = %ld\n", position);

    // Writing another 10 bytes
    write(fd, "8369416128", 10);

    close(fd);

    return 0;
}
