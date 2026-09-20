// Creating Records

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct record
{
    int id;
    char name[20];
    int sales;
};

int main()
{
    int fd;
    struct record r[3] = {
        {1, "Eminem", 85},
        {2, "Arjit_Singh", 90},
        {3, "Billy_Ellish", 78}
    };
    fd = open("records.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    write(fd, &r, sizeof(r));
    printf("3 records created successfully.\n");
    close(fd);
    return 0;
}
