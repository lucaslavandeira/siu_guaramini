#include "Client.h"
#include <string>

Client::Client(const char *addr, int port, const char *mode) :
    s(addr, port)
{
}

Client::~Client() {
}

std::string Client::send(std::string msg) {
    s.send(msg, 0);
    std::string response;
    s.receive(0);
    return response;
}
