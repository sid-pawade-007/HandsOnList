
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>

using namespace std;

void printLimit(const char *name, long value) {
    cout << name << ": ";

    if (value == -1) {
        cout << "Indeterminate or unsupported";
    } else {
        cout << value;
    }

    cout << endl;
}

int main() {
    // (a) Maximum length of arguments for exec functions
    printLimit("a. Maximum argument length for exec (ARG_MAX)",
               sysconf(_SC_ARG_MAX));

    // (b) Maximum number of simultaneous processes per user ID
    printLimit("b. Maximum processes per user ID (CHILD_MAX)",
               sysconf(_SC_CHILD_MAX));

    // (c) Number of clock ticks per second
    printLimit("c. Clock ticks per second (CLK_TCK)",
               sysconf(_SC_CLK_TCK));

    // (d) Maximum number of open files
    printLimit("d. Maximum open files (OPEN_MAX)",
               sysconf(_SC_OPEN_MAX));

    // (e) Size of a page
    printLimit("e. Page size (bytes)", getpagesize());

    // (f) Total number of pages in physical memory
    printLimit("f. Total physical memory pages",
               sysconf(_SC_PHYS_PAGES));

    // (g) Number of currently available pages in physical memory
    printLimit("g. Available physical memory pages",
               sysconf(_SC_AVPHYS_PAGES));

    return 0;
}
