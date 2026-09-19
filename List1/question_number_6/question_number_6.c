#include <unistd.h>

int main() {
    char buffer[100];
    int n;

    // This will allow us to read fron STDIN--
    n = read(0, buffer, sizeof(buffer));

    // this is writing to STDOUT--
    write(1, buffer, n);

    return 0;
}
