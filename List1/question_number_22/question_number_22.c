// Writing in file through parent process and child process

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd;
    pid_t pid;

    // Opening the file before fork()
    fd = open("One_Piece.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Creating child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        write(fd, "I am going to be the Pirate King -- Monkey D Luffy(Child of Dragon)\n", 25);
        printf("Child process wrote on this file.\n");
    }
    else
    {
        // Parent process
        write(fd, "I will free the world from Celestial Dragons -- Monkey D Dragon(Parent of Luffy)\n", 26);
        printf("Parent process wrote on this file.\n");

        // Wait for child
        wait(NULL);
    }
    close(fd);
    return 0;
}
