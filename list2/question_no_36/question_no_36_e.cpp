
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

using namespace std;

int main() {
    if (mkfifo("myfifo4", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    cout << "FIFO created successfully using mkfifo()." << endl;
    return 0;
}
