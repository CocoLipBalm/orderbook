#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

int main() {

    int fd = socket(AF_INET, SOCK_STREAM, 0);
}
