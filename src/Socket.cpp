#include <iostream>
#include <string>
#include "Socket.h"

Socket::Socket(const char *addr, int port) {
}

Socket::~Socket() {
}

void Socket::send(const std::string &msg) {
    std::cout << "Message from client: " << msg << std::endl;
}

void Socket::recv(std::string &msg) {
    msg = "quit";
}


