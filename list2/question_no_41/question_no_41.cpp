
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>

using namespace std;

int main() {
    // Generate a unique key
    key_t key = ftok(".", 'A');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create a message queue
    int msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // Print key and message queue ID
    cout << "Message Queue Created Successfully!" << endl;
    cout << "Key: " << key << endl;
    cout << "Message Queue ID: " << msgid << endl;

    return 0;
}

