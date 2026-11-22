#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {

    int fd =
        socket(AF_INET, SOCK_STREAM, 0); // this combination will select tcp

    if (argc != 3) {
        std::cerr << "only ip address and port number can be provided" << '\n';
        return 1;
    }

    struct sockaddr_in server{}; // tcp network api

    if (inet_pton(AF_INET, argv[1], &server.sin_addr) < 1) {
        std::cerr << "error converting from presentation to numeric ip" << '\n';
        return 1;
    }

    server.sin_port = htons(atoi(argv[2]));
    server.sin_family = AF_INET;

    if (connect(fd, reinterpret_cast<sockaddr *>(&server), sizeof(server)) ==
        -1) {
        std::cerr << "connection failed" << '\n';
        close(fd);
        return 1;
    }
    std::string string{"Hello\n"};

    int bytes_sent = send(fd, string.data(), string.size(), 0);
    while (bytes_sent < sizeof(*string.data()) * string.size()) {
        bytes_sent += send(fd, string.data(), string.size(), 0);
    }
}
