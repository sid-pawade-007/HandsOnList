//Read ticket number, acquire lock, increase ticket number

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int ticket;
    struct flock lock;

    // Open the file for reading and writing
    fd = open("ticket.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Set write lock
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    printf("Trying to acquire write lock...\n");

    // Apply write lock
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }
    printf("Write lock acquired.\n");

    // Read current ticket number
    lseek(fd, 0, SEEK_SET);
    if (read(fd, &ticket, sizeof(ticket)) != sizeof(ticket))
    {
        perror("read");
        close(fd);
        return 1;
    }
    printf("Current ticket number: %d\n", ticket);

    // Increment ticket number
    ticket++;

    // Move back to beginning of file
    lseek(fd, 0, SEEK_SET);

    // Store new ticket number
    if (write(fd, &ticket, sizeof(ticket)) != sizeof(ticket))
    {
        perror("write");
        close(fd);
        return 1;
    }
    printf("New ticket number: %d\n", ticket);

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Write lock released.\n");
    close(fd);
    return 0;
}
