#include <netinet/in.h>
#include <string>
#include "common_protocol_socket.h"

#define MSG_SIZE 256
void protocol_send(Socket& s, const char* msg, unsigned int len) {
    // Send length first, then the message
    uint32_t network_len = htonl(len);
    s.send((char*) &network_len, sizeof(network_len));
    s.send(msg, len);
}

std::string protocol_receive(Socket& s) {
    // Receive length first, then the message
    uint32_t len = 0;
    s.receive((char*) &len, sizeof(len));
    len = ntohl(len);
    char buf[MSG_SIZE] = "";
    s.receive(buf, len);
    std::string result(buf);
    return result;
}
