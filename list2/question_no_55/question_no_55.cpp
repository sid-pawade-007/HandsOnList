
#include <iostream>
#include <sys/resource.h>
#include <cstdlib>

using namespace std;

int main() {
    struct rlimit limit;

    // Get the current resource limit
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        return 1;
    }

    cout << "Original soft limit: " << limit.rlim_cur << endl;
    cout << "Original hard limit: " << limit.rlim_max << endl;

    // Set the new soft limit to 50
    limit.rlim_cur = 50;

    // Apply the new resource limit
    if (setrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("setrlimit");
        return 1;
    }

    // Verify the updated limit
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        return 1;
    }

    cout << "\nResource limit changed successfully!" << endl;
    cout << "New soft limit: " << limit.rlim_cur << endl;
    cout << "Hard limit: " << limit.rlim_max << endl;

    return 0;
}
