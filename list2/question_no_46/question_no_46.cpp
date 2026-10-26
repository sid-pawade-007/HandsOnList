
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>

using namespace std;

int main() {
    // Generate the same key used to create the queue
    key_t key = ftok(".", 'A');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Access the existing message queue
    int msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, nullptr) == -1) {
        perror("msgctl");
        return 1;
    }

    cout << "Message queue removed successfully!" << endl;

    return 0;
}
