
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdlib>

using namespace std;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key = ftok(".", 'C');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create a semaphore
    int semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    // Initialize counting semaphore to 5
    union semun arg;
    arg.val = 5;

    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        return 1;
    }

    cout << "Counting semaphore created successfully." << endl;
    cout << "Semaphore ID: " << semid << endl;
    cout << "Initial value: 5" << endl;

    return 0;
}
