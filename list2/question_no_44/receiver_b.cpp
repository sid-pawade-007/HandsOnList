
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cerrno>
#include <cstdlib>

using namespace std;

struct Message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok(".", 'A');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    Message msg;

    // IPC_NOWAIT: do not wait if no message is available
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text),
               1, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            cout << "No message available in the queue." << endl;
        } else {
            perror("msgrcv");
            return 1;
        }
    } else {
        cout << "Received message: " << msg.msg_text << endl;
    }

    return 0;
}
