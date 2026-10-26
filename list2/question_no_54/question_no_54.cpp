
#include <iostream>
#include <sys/resource.h>
#include <cstdlib>

using namespace std;

void printLimit(const char *name, int resource) {
    struct rlimit limit;

    cout << "\n" << name << ":\n";

    if (getrlimit(resource, &limit) == -1) {
        perror("getrlimit");
        return;
    }

    cout << "Soft limit: ";

    if (limit.rlim_cur == RLIM_INFINITY)
        cout << "Unlimited" << endl;
    else
        cout << limit.rlim_cur << endl;

    cout << "Hard limit: ";

    if (limit.rlim_max == RLIM_INFINITY)
        cout << "Unlimited" << endl;
    else
        cout << limit.rlim_max << endl;
}

int main() {
    printLimit("Maximum number of open files", RLIMIT_NOFILE);
    printLimit("Maximum file size", RLIMIT_FSIZE);
    printLimit("Maximum CPU time", RLIMIT_CPU);
    printLimit("Maximum stack size", RLIMIT_STACK);
    printLimit("Maximum data segment size", RLIMIT_DATA);
    printLimit("Maximum core file size", RLIMIT_CORE);
    printLimit("Maximum number of processes", RLIMIT_NPROC);
    printLimit("Maximum address space", RLIMIT_AS);

    return 0;
}
