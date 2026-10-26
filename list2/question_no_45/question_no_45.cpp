
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>

using namespace std;

int main() {
    // Generate the same key used in send_message.cpp
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

    // Get current message queue information
    struct msqid_ds info;

    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("msgctl IPC_STAT");
        return 1;
    }

    cout << "Old permissions: "
         << oct << (info.msg_perm.mode & 0777) << endl;

    // Change permissions to 0644
    info.msg_perm.mode = (info.msg_perm.mode & ~0777) | 0644;

    // Apply the changes
    if (msgctl(msgid, IPC_SET, &info) == -1) {
        perror("msgctl IPC_SET");
        return 1;
    }

    // Verify the new permissions
    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("msgctl IPC_STAT");
        return 1;
    }

    cout << "New permissions: "
         << oct << (info.msg_perm.mode & 0777) << endl;

    cout << "Message queue permissions changed successfully."
         << endl;

    return 0;
}
