
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <cstring>

using namespace std;

void *handle_client(void *arg) {
    int client_fd = *(int *)arg;
    delete (int *)arg;

    char buffer[1024];

    ssize_t n = read(client_fd, buffer,
                     sizeof(buffer) - 1);

    if (n > 0) {
        buffer[n] = '\0';

        cout << "Client message: "
             << buffer << endl;

        const char *reply = "Ground control from thread server!";

        send(client_fd, reply, strlen(reply), 0);
    }

    close(client_fd);
    return nullptr;
}

int main() {
    int server_fd;
    struct sockaddr_in address{};

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

    cout << "Concurrent server using pthread_create() started."
         << endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);

        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        int *arg = new int(client_fd);
        pthread_t thread;

        if (pthread_create(&thread, nullptr,
                           handle_client, arg) != 0) {
            cerr << "Thread creation failed." << endl;
            close(client_fd);
            delete arg;
            continue;
        }

        // Automatically release thread resources on completion
        pthread_detach(thread);
    }

    close(server_fd);
    return 0;
}
