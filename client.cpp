#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

template <typename T> int send_data(int fd, const T *data, std::size_t count) {

    std::size_t total_bytes = sizeof(T) * count;

    std::size_t bytes_sent{};

    while (bytes_sent < total_bytes) {

        ssize_t result =
            send(fd, (reinterpret_cast<const char *>(data) + bytes_sent),
                 total_bytes - bytes_sent, 0);

        if (result == -1) {
            std::cerr << "sending failure" << '\n';
            return -1;
        }

        if (result == 0) {
            std::cerr << "the send did not complete" << '\n';
            return -1;
        }

        bytes_sent += result;
    }
    return 0;
}

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
    send_data(fd, string.data(), string.size());
}
