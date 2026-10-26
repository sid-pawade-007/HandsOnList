
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

int main() {
    key_t key = ftok(".", 'B');
    int semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    int *shared = (int *)mmap(NULL, sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shared == MAP_FAILED) {
        perror("mmap");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    *shared = 0;

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            for (int j = 0; j < 10000; j++) {
                struct sembuf lock = {0, -1, 0};
                semop(semid, &lock, 1);

                (*shared)++;

                struct sembuf unlock = {0, 1, 0};
                semop(semid, &unlock, 1);
            }

            _exit(0);
        }

        if (pid < 0) {
            perror("fork");
            break;
        }
    }

    while (wait(NULL) > 0) {}

    cout << "Final shared counter: " << *shared << endl;

    munmap(shared, sizeof(int));
    semctl(semid, 0, IPC_RMID);

    return 0;
}
