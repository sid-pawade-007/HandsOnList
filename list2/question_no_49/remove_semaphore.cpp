
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdlib>

using namespace std;

int main() {
    key_t key = ftok(".", 'A');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Access an existing semaphore
    int semid = semget(key, 1, 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    // Remove the semaphore
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        return 1;
    }

    cout << "Semaphore removed successfully." << endl;

    return 0;
}
