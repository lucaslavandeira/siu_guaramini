#include <iostream>
#include <string>
#include "Socket.h"

Socket::Socket(const char *addr, int port) {
}

Socket::~Socket() {
}

void Socket::send(const std::string &msg) {
}

void Socket::recv(std::string &msg) {
    msg = "quit";
}


