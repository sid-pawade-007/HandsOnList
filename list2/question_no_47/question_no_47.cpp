
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    // Create shared memory
    key_t key = ftok(".", 'S');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int shmid = shmget(key, 1024, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    cout << "Shared memory created successfully." << endl;
    cout << "Shared Memory ID: " << shmid << endl;

    // (a) Attach and write data
    char *data = (char *)shmat(shmid, nullptr, 0);

    if (data == (char *)-1) {
        perror("shmat");
        return 1;
    }

    strcpy(data, "Hello from shared memory!");
    cout << "Data written: " << data << endl;

    // (b) Attach in read-only mode
    char *readonly_data = (char *)shmat(shmid, nullptr, SHM_RDONLY);

    if (readonly_data == (char *)-1) {
        perror("shmat read-only");
        shmdt(data);
        return 1;
    }

    cout << "Read-only attached data: "
         << readonly_data << endl;

    cout << "Cannot overwrite data through the read-only attachment."
         << endl;

    // Detach both attachments
    // (c) Detach shared memory
    if (shmdt(readonly_data) == -1) {
        perror("shmdt read-only");
    }

    if (shmdt(data) == -1) {
        perror("shmdt");
        return 1;
    }

    cout << "Shared memory detached successfully." << endl;

    // (d) Remove shared memory
    if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
        perror("shmctl");
        return 1;
    }

    cout << "Shared memory marked for removal successfully." << endl;

    return 0;
}
