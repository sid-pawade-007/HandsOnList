// Write lock that reads and changes sales of records

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct record
{
    int id;
    char name[20];
    int sales
    ;
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
    fd = open("records.dat", O_RDWR);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    /*
       Calculate position of the required record.

       Record 1 -> 0 * sizeof(struct record)
       Record 2 -> 1 * sizeof(struct record)
       Record 3 -> 2 * sizeof(struct record)
    */
    off_t position = (record_no - 1) * sizeof(struct record);

    // Set write lock for this record
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = position;
    lock.l_len = sizeof(struct record);
    lock.l_pid = getpid();
    printf("Trying to acquire write lock on record %d...\n",
           record_no);

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Write lock acquired on record %d.\n", record_no);

    // Go to the selected record
    lseek(fd, position, SEEK_SET);

    // Read the record
    if (read(fd, &r, sizeof(struct record)) != sizeof(struct record))
    {
        perror("read");
        close(fd);
        return 1;
    }

    printf("\nCurrent Record:\n");
    printf("ID    : %d\n", r.id);
    printf("Name  : %s\n", r.name);
    printf("Sales : %d\n", r.sales);

    // Modify sales
    printf("\nEnter new sales: ");
    scanf("%d", &r.sales);

    // Go back to the beginning of the record
    lseek(fd, position, SEEK_SET);

    // Write modified record
    if (write(fd, &r, sizeof(struct record)) != sizeof(struct record))
    {
        perror("write");
        close(fd);
        return 1;
    }
    printf("Record %d modified successfully.\n", record_no);

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Write lock released.\n");
    close(fd);
    return 0;
}
