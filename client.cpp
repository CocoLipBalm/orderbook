#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>

int main(int argc, char **argv) {

    std::cout << "only ip address and port number can be provided" << '\n';
    if (argc != 3) {
        std::cerr << "only ip address can be provided" << '\n';
        return 1;
    }

    struct sockaddr_in server{};

    if (inet_pton(AF_INET, argv[1], &server.sin_addr) < 1) {
        std::cerr << "error converting from presentation to numeric ip" << '\n';
        return 1;
    }

    server.sin_port = htons(atoi(argv[2]));
    server.sin_family = AF_INET;
}
