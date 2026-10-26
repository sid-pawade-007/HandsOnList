
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    int sock;
    struct sockaddr_in server_address{};
    char buffer[1024] = {0};

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);

    // Replace with the server machine's IP address
    if (inet_pton(AF_INET, "127.0.0.1",
                  &server_address.sin_addr) != 1) {
        cerr << "Invalid server IP address." << endl;
        close(sock);
        return 1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_address,
                sizeof(server_address)) == -1) {
        perror("connect");
        close(sock);
        return 1;
    }

    // Send message to server
    const char *message = "Hello from client!";
    if (send(sock, message, strlen(message), 0) == -1) {
        perror("send");
        close(sock);
        return 1;
    }

    // Receive reply
    ssize_t n = read(sock, buffer, sizeof(buffer) - 1);

    if (n > 0) {
        buffer[n] = '\0';
        cout << "Server says: " << buffer << endl;
    }

    close(sock);

    return 0;
}
