// This program is about implementing read lock

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    struct flock lock;
    fd = open("Chamber_of_Secrets.txt", O_RDONLY | O_CREAT, 0666);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    lock.l_type = F_RDLCK; // Read lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Lock entire file
    lock.l_pid = getpid();
    printf("Trying to acquire read lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }
    printf("Read lock acquired.\n");
    printf("File is locked for reading.\n");
    printf("Press Enter to release the lock...\n");

    getchar();

    // Unlocking the chamber of secrets.
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Read lock released.\n");
    close(fd);

    return 0;
}
