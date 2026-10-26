
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>

using namespace std;

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address{};

    // Prevent zombie child processes
    signal(SIGCHLD, SIG_IGN);

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) == -1) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    cout << "Concurrent server using fork() started."
         << endl;

    while (true) {
        client_fd = accept(server_fd, nullptr, nullptr);

        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            close(client_fd);
            continue;
        }

        if (pid == 0) {
            // Child process handles the client
            close(server_fd);

            char buffer[1024];
            ssize_t n = read(client_fd, buffer,
                             sizeof(buffer) - 1);

            if (n > 0) {
                buffer[n] = '\0';
                cout << "Client message: "
                     << buffer << endl;

                const char *reply =
                    "Ground control from fork server!";

                send(client_fd, reply,
                     strlen(reply), 0);
            }

            close(client_fd);
            _exit(0);
        }

        // Parent continues accepting clients
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
