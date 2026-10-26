
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

union semun {
    int val;
};

int main() {
    key_t key = ftok(".", 'C');
    int semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    union semun arg;
    arg.val = 2;
    semctl(semid, 0, SETVAL, arg);

    for (int i = 1; i <= 5; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Acquire one resource
            struct sembuf wait_op = {0, -1, 0};
            semop(semid, &wait_op, 1);

            cout << "Process " << getpid()
                 << " acquired a resource." << endl;

            sleep(2);

            cout << "Process " << getpid()
                 << " released a resource." << endl;

            // Release the resource
            struct sembuf signal_op = {0, 1, 0};
            semop(semid, &signal_op, 1);

            _exit(0);
        }

        if (pid < 0) {
            perror("fork");
            break;
        }
    }

    while (wait(NULL) > 0) {}

    semctl(semid, 0, IPC_RMID);

    cout << "All processes completed." << endl;

    return 0;
}
