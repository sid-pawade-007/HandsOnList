
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Message {
    long msg_type;
    char msg_text[100];
};

int main() {
    // Generate a key
    key_t key = ftok(".", 'A');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create or access the message queue
    int msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // Prepare the message
    Message msg;
    msg.msg_type = 1;
    strcpy(msg.msg_text, "Ground Control to Major Tom");

    // Send the message
    if (msgsnd(msgid, &msg,
               strlen(msg.msg_text) + 1, 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    cout << "Message sent successfully!" << endl;
    cout << "Message Queue ID: " << msgid << endl;
    cout << "Message: " << msg.msg_text << endl;

    return 0;
}
