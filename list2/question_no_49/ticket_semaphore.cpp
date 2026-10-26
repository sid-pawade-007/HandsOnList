
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

union semun {
    int val;
};

void lock(int semid) {
    struct sembuf op = {0, -1, 0};
    semop(semid, &op, 1);
}

void unlock(int semid) {
    struct sembuf op = {0, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    key_t key = ftok(".", 'A');
    int semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    // Shared counter between processes
    int *ticket = (int *)mmap(NULL, sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (ticket == MAP_FAILED) {
        perror("mmap");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    *ticket = 0;

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            lock(semid);

            (*ticket)++;
            cout << "Process " << getpid()
                 << " generated ticket: "
                 << *ticket << endl;

            unlock(semid);
            _exit(0);
        }

        if (pid < 0) {
            perror("fork");
            break;
        }
    }

    while (wait(NULL) > 0) {}

    cout << "Total tickets generated: " << *ticket << endl;

    munmap(ticket, sizeof(int));
    //semctl(semid, 0, IPC_RMID);

    return 0;
}
