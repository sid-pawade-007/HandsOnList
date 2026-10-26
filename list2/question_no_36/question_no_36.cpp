
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

using namespace std;

int main() {
    if (mknod("myfifo3", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }

    cout << "FIFO created successfully using mknod()." << endl;
    return 0;
}
