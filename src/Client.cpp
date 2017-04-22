#include "Client.h"
#include <string>

Client::Client(const char *addr, int port, const char *mode) :
    s(addr, port)
{
}

Client::~Client() {
}

std::string Client::send(std::string msg) {
    s.send(msg);
    std::string response;
    s.recv(response);
    return response;
}
