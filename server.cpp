#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

#define BACKLOG 8

int main() {

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr;
    server_addr.sin_port = htons(8080);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(server_fd, reinterpret_cast<const sockaddr *>(&server_addr),
             sizeof(server_addr)) == -1) {
        std::perror("bind"); // <cstdio>
        close(server_fd);
        return 1;
    }

    int result_listen = listen(server_fd, BACKLOG);
    if (result_listen == -1) {
        std::perror("listen");
        return 1;
    }

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            std::perror("accept");
            continue;
        }
        char buffer[1024];

        while (true) {
            ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);

            if (bytes_read == 0) {
                break; // The client has finished sending
            }

            if (bytes_read < 0) {
                perror("recv");
                break;
            }

            // Process the bytes just received.
            // std::cout.write(buffer, bytes_read);
        }

        close(client_fd);
    }
}
