
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
    // Generate a key
    key_t key = ftok(".", 'A');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create or access a message queue
    int msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // Structure to store message queue information
    struct msqid_ds info;

    // Get message queue information
    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("msgctl");
        return 1;
    }

    cout << "----- Message Queue Information -----\n";
    cout << "Key: " << key << endl;
    cout << "Message Queue ID: " << msgid << endl;

    // (a) Access permissions
    cout << "\n(a) Access Permissions: "
         << oct << (info.msg_perm.mode & 0777) << dec << endl;

    // (b) UID and GID
    cout << "(b) Owner UID: " << info.msg_perm.uid << endl;
    cout << "    Owner GID: " << info.msg_perm.gid << endl;

    // (c) Time of last message sent and received
    cout << "(c) Last message sent: "
         << ctime(&info.msg_stime);

    cout << "    Last message received: "
         << ctime(&info.msg_rtime);

    // (d) Time of last change in message queue
    cout << "(d) Last queue change: "
         << ctime(&info.msg_ctime);

    // (e) Current size of the queue in bytes
    cout << "(e) Current queue size: "
         << info.msg_cbytes << " bytes" << endl;

    // (f) Number of messages in the queue
    cout << "(f) Number of messages: "
         << info.msg_qnum << endl;

    // (g) Maximum number of bytes allowed
    cout << "(g) Maximum queue size: "
         << info.msg_qbytes << " bytes" << endl;

    // (h) PID of last sender and receiver
    cout << "(h) PID of last sender: "
         << info.msg_lspid << endl;

    cout << "    PID of last receiver: "
         << info.msg_lrpid << endl;

    return 0;
}
