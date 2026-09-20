// Reading the sales of record

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct record
{
    int id;
    char name[20];
    int sales;
};

int main()
{
    int fd;
    int record_no;
    struct record r;
    struct flock lock;

    printf("Enter record number (1-3): ");
    scanf("%d", &record_no);

    if (record_no < 1 || record_no > 3)
    {
        printf("Invalid record number.\n");
        return 1;
    }

    fd = open("records.dat", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Calculate position of record
    off_t position = (record_no - 1) * sizeof(struct record);

    // Set read lock
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = position;
    lock.l_len = sizeof(struct record);
    lock.l_pid = getpid();

    printf("Trying to acquire read lock on record %d...\n",
           record_no);

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Read lock acquired on record %d.\n", record_no);

    // Move to required record
    lseek(fd, position, SEEK_SET);

    // Read record
    if (read(fd, &r, sizeof(struct record)) != sizeof(struct record))
    {
        perror("read");
        close(fd);
        return 1;
    }

    printf("\nRecord Details:\n");
    printf("ID    : %d\n", r.id);
    printf("Name  : %s\n", r.name);
    printf("Sales : %d\n", r.sales);

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("\nRead lock released.\n");
    close(fd);
    return 0;
}
