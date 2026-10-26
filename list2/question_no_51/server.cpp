
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address{};
    char buffer[1024] = {0};

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind socket to port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) == -1) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // Listen for client connections
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    cout << "Server waiting for client..." << endl;

    socklen_t addrlen = sizeof(address);
    client_fd = accept(server_fd, (struct sockaddr *)&address,
                       &addrlen);

    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        return 1;
    }

    cout << "Client connected." << endl;

    // Receive message from client
    ssize_t n = read(client_fd, buffer, sizeof(buffer) - 1);

    if (n > 0) {
        buffer[n] = '\0';
        cout << "Client says: " << buffer << endl;
    }

    // Send reply to client
    const char *reply = "Ground control to Major Tom";
    if (send(client_fd, reply, strlen(reply), 0) == -1) {
        perror("send");
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
