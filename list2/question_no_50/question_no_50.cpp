
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

void wait_sem(int semid, int semnum) {
    struct sembuf op = { (unsigned short)semnum, -1, 0 };
    if (semop(semid, &op, 1) == -1) {
        perror("semop wait");
        _exit(1);
    }
}

void signal_sem(int semid, int semnum) {
    struct sembuf op = { (unsigned short)semnum, 1, 0 };
    if (semop(semid, &op, 1) == -1) {
        perror("semop signal");
        _exit(1);
    }
}

int main() {
    key_t key = ftok(".", 'D');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create a set containing two semaphores
    int semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    union semun arg;
    arg.val = 1;

    semctl(semid, 0, SETVAL, arg);
    semctl(semid, 1, SETVAL, arg);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    if (pid == 0) {
        // Child locks semaphore 1
        wait_sem(semid, 0);
        cout << "Process 1 acquired semaphore 1." << endl;

        sleep(1);

        cout << "Process 1 waiting for semaphore 2..." << endl;
        wait_sem(semid, 1);  // Deadlock occurs here

        signal_sem(semid, 1);
        signal_sem(semid, 0);
        _exit(0);
    } else {
        // Parent locks semaphore 2
        wait_sem(semid, 1);
        cout << "Process 2 acquired semaphore 2." << endl;

        sleep(1);

        cout << "Process 2 waiting for semaphore 1..." << endl;
        wait_sem(semid, 0);  // Deadlock occurs here

        signal_sem(semid, 0);
        signal_sem(semid, 1);

        waitpid(pid, NULL, 0);
    }

    semctl(semid, 0, IPC_RMID);
    return 0;
}
