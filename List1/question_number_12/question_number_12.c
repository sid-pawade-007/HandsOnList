// This program is about finding out mode of file using fcntl

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int flags;
    int mode;

    // Opening file
    fd = open("Walter_White.txt", O_RDWR | O_CREAT, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Getting file status flags using fcntl()
    flags = fcntl(fd, F_GETFL);

    if (flags == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    // Extracting opening access mode
    mode = flags & O_ACCMODE;

    printf("File descriptor = %d\n", fd);

    if (mode == O_RDONLY)
        printf("Opening mode: Read Only\n");

    else if (mode == O_WRONLY)
        printf("Opening mode: Write Only\n");

    else if (mode == O_RDWR)
        printf("Opening mode: Read and Write\n");

    close(fd);

    return 0;
}
