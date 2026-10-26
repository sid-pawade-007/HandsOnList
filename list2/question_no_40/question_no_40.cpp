
#include <iostream>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main() {
    struct rlimit limit;

    // Get maximum number of open files
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        cout << "Maximum number of files that can be opened:" << endl;

        if (limit.rlim_cur == RLIM_INFINITY)
            cout << "Soft limit: Unlimited" << endl;
        else
            cout << "Soft limit: " << limit.rlim_cur << endl;

        if (limit.rlim_max == RLIM_INFINITY)
            cout << "Hard limit: Unlimited" << endl;
        else
            cout << "Hard limit: " << limit.rlim_max << endl;
    } else {
        perror("getrlimit");
    }

    // Create a pipe
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Get pipe buffer size
    int pipe_size = fcntl(fd[0], F_GETPIPE_SZ);

    if (pipe_size == -1) {
        perror("fcntl");
    } else {
        cout << "\nPipe buffer size: "
             << pipe_size << " bytes" << endl;
    }

    // Close pipe descriptors
    close(fd[0]);
    close(fd[1]);

    return 0;
}
