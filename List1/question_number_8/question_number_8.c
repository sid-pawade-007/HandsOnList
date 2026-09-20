// This program is about reading file line by line
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char ch;

    // Opening the file in read-only mode--
    fd = open("pokemon", O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Reading character by character from the file--
    while (read(fd, &ch, 1) > 0) {

        // Displaying character--
        write(STDOUT_FILENO, &ch, 1);

        // When newline character is encountered then the current line is completed--
        if (ch == '\n') {
            // Line has been read and displayed--
        }
    }

    // EOF reached--
    close(fd);

    return 0;
}
