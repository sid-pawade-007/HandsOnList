//This program will give us stats of a file 
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct stat st;
    char filename[100];

    printf("Enter file name: ");
    scanf("%99s", filename);

    // Geting the file information
    if (stat(filename, &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("\nFile Information\n");
    printf("-------------------------\n");

    // a. Inode
    printf("a. Inode              : %ld\n", st.st_ino);

    // b. Number of hard links
    printf("b. Hard links         : %ld\n", st.st_nlink);

    // c. UID
    printf("c. UID                : %d\n", st.st_uid);

    // d. GID
    printf("d. GID                : %d\n", st.st_gid);

    // e. Size
    printf("e. Size               : %ld bytes\n", st.st_size);

    // f. Block size
    printf("f. Block size         : %ld bytes\n", st.st_blksize);

    // g. Number of blocks
    printf("g. Number of blocks   : %ld\n", st.st_blocks);

    // h. Last access time
    printf("h. Last access        : %s", ctime(&st.st_atime));

    // i. Last modification time
    printf("i. Last modification  : %s", ctime(&st.st_mtime));

    // j. Last change time
    printf("j. Last change        : %s", ctime(&st.st_ctime));

    return 0;
}
