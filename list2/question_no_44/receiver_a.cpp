
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
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

    cout << "Waiting for a message..." << endl;

    // Flag 0: blocks until a message is available
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text),
               1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    cout << "Received message: " << msg.msg_text << endl;

    return 0;
}
