#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd[5];

    // Create and open 5 text files
    for (int i = 0; i < 5; i++) {
        char filename[20];
        //Naming files likw file1 file2 file3 .. and so on
        sprintf(filename, "file%d.txt", i + 1);

        fd[i] = open(filename, O_CREAT | O_RDWR, 0644);

        if (fd[i] == -1) {
            perror("open");
            return 1;
        }

        printf("Created %s, FD = %d\n", filename, fd[i]);
    }

    // Infnite loop so that the process keeps running in the backgrnd
    while (1) {
        sleep(1);
    }

    return 0;
}
