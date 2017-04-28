#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include "common_protocol_socket.h"


void protocol_send(Socket& s, const char* msg, unsigned int len) {
    uint32_t network_len = htonl(len);
    s.send((char*) &network_len, sizeof(network_len));
    s.send(msg, len);
}

std::string protocol_receive(Socket& s) {
    uint32_t len = 0;
    s.receive((char*) &len, sizeof(len));
    len = ntohl(len);
    char* buf = new char[len];
    s.receive(buf, len);
    return std::string(buf);
}
